import jax.numpy as jnp
import flax,optax,jax
import os
import numpy as np
import flax.linen as nn
from flax.training import train_state
import tensorflow as tf
from jax.experimental import jax2tf

def get_all_files(directory):
    all_files = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            all_files.append(file_path)
    return all_files

def read_txt(path):
    data = []
    with open(path,'r') as f:
        while(1):
            l = f.readline()
            # try:
            l = l.strip()
            if not l:
                break
            l = float(l)
                
            # except Exception as e:
            #     break
            data.append(l)
    if len(data)!=2000:
        print(path)
    return data    



def to_one_hot(index, num):
    one_hot = np.eye(num)[index]
    return one_hot

    
class DataLoad():

    def __init__(self,base_path=''):

        self.mean = 0
        self.std = 1
        self.datas = []
        self.load_data(base_path)
        pass

    def load_data(self,base_path):
        all_f = get_all_files(base_path+'0_t/')
        for f in all_f:
            d_tmp = read_txt(f)
            self.datas.append({'input':d_tmp,'label':0})
        
        all_f = get_all_files(base_path+'cd_t/')
        for f in all_f:
            d_tmp = read_txt(f)
            self.datas.append({'input':d_tmp,'label':1})

        all_f = get_all_files(base_path+'rl_t/')
        for f in all_f:
            d_tmp = read_txt(f)
            self.datas.append({'input':d_tmp,'label':2})
        
        inputs = [i['input'] for i in self.datas]

        inputs = np.concatenate(inputs)
        self.mean = np.mean(inputs)
        self.std = np.std(inputs)
        print('mean:{},std:{}'.format(self.mean,self.std))

    def sample(self,batch_size):
        indexs = np.random.choice(len(self.datas),batch_size)
        batch_input = [self.datas[i]['input'] for i in indexs]
        batch_label = [self.datas[i]['label'] for i in indexs]
        return (np.array(batch_input)-self.mean)/self.std,to_one_hot(batch_label,3)
    
    def get_test_data(self):
        for d in self.datas:
            yield (jnp.array([d['input']],dtype=jnp.float32)-2074.241764305899)/330.3760492693207,to_one_hot([d['label']],3)
    

def cross_entropy_with_logits(softmax_logits, labels):
    # softmax_logits = softmax(logits)
    loss = -jnp.sum(labels * jnp.log(softmax_logits+ + 1e-8), axis=-1)
    return loss
class   ZxcModule(nn.Module):

    @nn.compact
    def __call__(self, x):
        x = x.reshape((x.shape[0], 40, 50, 1))
        #池化，窗口大小3*3，步长3*3，不足边缘不池化
        x = nn.avg_pool(x, window_shape=(3, 3), strides=(3, 3), padding='VALID')
        # cnn
        x = nn.Conv(features=2, kernel_size=(3, 3))(x)
        
        x = nn.max_pool(x, window_shape=(2, 2), strides=(2, 2), padding='VALID')
        x = nn.Conv(features=2, kernel_size=(3, 3))(x)
        x = nn.relu(x)
        x = nn.max_pool(x, window_shape=(2, 2), strides=(2, 2), padding='VALID')
        x = nn.Conv(features=2, kernel_size=(3, 3))(x)
        x = nn.relu(x)
        x = x.reshape(x.shape[0], -1)
        x = nn.Dense(24)(x)
        x = nn.relu(x)
        x = nn.Dense(3)(x)
        # x = jax.nn.softmax(x)
        return x 

def cross_entropy_loss(logits, labels):
    # loss = cross_entropy_with_logits(logits, labels)
    loss = optax.softmax_cross_entropy(logits, labels)
    return jnp.mean(loss)

def model2lite(state,shape=[1,1],save_name='model.tflite'):

    def predict_(input):
        logits = state.apply_fn(state.params, input)
        return logits
    tf_predict = tf.function(
      jax2tf.convert(predict_, enable_xla=False),
      input_signature=[
          tf.TensorSpec(
              #输入张量的形状
              shape=shape,
            #   数据类型
              dtype=tf.float32,
              #输入张量的名称
              name='input')
      ],
      #禁用梯度
      autograph=False)
    #转换
    converter = tf.lite.TFLiteConverter.from_concrete_functions(
        [tf_predict.get_concrete_function()], tf_predict)


    converter.target_spec.supported_ops = [
        tf.lite.OpsSet.TFLITE_BUILTINS,  # enable TensorFlow Lite ops.
        tf.lite.OpsSet.SELECT_TF_OPS  # enable TensorFlow ops.
    ]

    tflite_float_model = converter.convert()
    with open(save_name,'wb') as f:
        f.write(tflite_float_model)
    return tflite_float_model

@jax.jit
def step(state,inputs, labels):

    def loss_fn(params):
        logits = state.apply_fn(params, inputs)
        loss = cross_entropy_loss(logits, labels)
        return loss

    loss,grads = jax.value_and_grad(loss_fn)(state.params)
    state = state.apply_gradients(grads=grads)

    return loss,state

def create_state(learning_rate,data_sample):
    model = ZxcModule()
    params = model.init(jax.random.PRNGKey(0), data_sample)

    schedule = optax.exponential_decay(
    init_value=learning_rate,  # 初始学习率
    transition_steps=1000,  # 多少步后开始衰减
    decay_rate=0.99,  # 每次衰减率
    )
    tx = optax.adam(schedule)
    return train_state.TrainState.create(
        apply_fn=model.apply,
        params=params,
        tx=tx
    )


def eval_lite(lite_model_path):
    d = DataLoad(r'test/')

    ds = d.get_test_data()
    interpreter = tf.lite.Interpreter(lite_model_path)
    interpreter.allocate_tensors()
    input_tensor_index = interpreter.get_input_details()[0]['index']
    output = interpreter.get_output_details()[0]['index']

    for input,label in ds:
        interpreter.set_tensor(input_tensor_index, input)
        interpreter.invoke()
        out_data = interpreter.get_tensor(output)
        print(jax.nn.softmax(out_data),label)


def model_test():
    d = DataLoad(r'test/')
    data_sample,_ = d.sample(1)
    model = ZxcModule()
    params = model.init(jax.random.PRNGKey(0), data_sample)
    rs = model.apply(params,data_sample)
    print(rs.shape)

if __name__ == '__main__':
    # model_test()
    #############################
    d = DataLoad()
    m = ZxcModule()
    inputs,b = d.sample(10)
    print(inputs.shape)
    state = create_state(0.002,inputs)
    
    echo = 100000
    count = 0
    loss = 0
    for i in range(echo):
        
        inputs,b = d.sample(32)
        l,state = step(state,inputs,b)
        loss += l
        count+=1
        if count==1000:
            print(loss/1000)
            loss = 0
            count=0
    
    
    model_lite = model2lite(state,[1,2000])

    print(len(model_lite))
    eval_lite('model.tflite')
#######################################



