/**
  ******************************************************************************
  * @file    test_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Sep  5 19:09:57 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "test_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_test_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_test_weights_array_u64[386] = {
  0x3d4541cebef88be6U, 0xbf5ffd663f06413bU, 0x3f8a5b163e3487c0U, 0x3f935bbd3ef557b5U,
  0xc0074c15bf8d96a4U, 0x3e45f024bf89f669U, 0xbf1143ddbf815aadU, 0x3ea3b1bf3d1764c5U,
  0x3f199085bf018bbfU, 0xbdbd2625befbda96U, 0x3e465a12bf724060U, 0xbf80cb343ee6cd50U,
  0xbe0159023f97b26fU, 0xbea2cc0d3dd0f34fU, 0xbf06e16f3ed0adccU, 0x3f894a613fada8c6U,
  0xbdf8320cbf479984U, 0x3f5ec708bd1aed04U, 0x3e2c34b23f973818U, 0xbe4f6d763d843591U,
  0xbd61ae15bec06b02U, 0x3db776223e0dfde9U, 0xbfa2c0d63fa80e3bU, 0x3e19a794bf97741dU,
  0x3f8025363f98349bU, 0xbe87e4c33f5e419cU, 0xbe9fef463ece604fU, 0xbe4602eb3f10a976U,
  0xbfa03e70bf1ca9a2U, 0x3d152d903fb362c2U, 0xbe32a49f3fad43e5U, 0xbf9647a73dc41cf2U,
  0x3fb2f6423f3e077fU, 0xbe95235b3f91d9dbU, 0x3f9aadf1bf0e0320U, 0x3ffee8e5bf9797c6U,
  0x3d5906fabdbe54afU, 0xc0358dcf3eca7faeU, 0xbe125ab3bcd936aeU, 0x3e8a0f57bf3bcbf7U,
  0x3f3000f7be622ed2U, 0x3fc373993fbbeb73U, 0x3fd9625fbed45043U, 0xbe00e0863f8168a6U,
  0xbf7cdbf4beef645dU, 0xbfc0d4a33fbf0943U, 0x3f7e27a13e90bfc9U, 0xbfb3d5a3bf6fb4dfU,
  0x3e63bf24bf8168a6U, 0x3e350af53f1b4c79U, 0xbe374515be4613a9U, 0x3f24995b3f230eadU,
  0xbee38ebd3f621147U, 0xbf1274aa3ea37ad2U, 0x3e7a6d4b3e919e86U, 0xbf179ed0befff75eU,
  0xbd5bd2363ee813f5U, 0x3ea73cd7bec6e694U, 0xbee508163e7dc863U, 0x3f7153523ce47012U,
  0x3f5a19973e51d80cU, 0x3f173cdc3fde4185U, 0xc0015a36be7d758eU, 0xbf9816943ef748ceU,
  0xbf0429b83fa9f30cU, 0xbf29d8363c310f8eU, 0xbfaa89a7bfc0dae9U, 0xbdb7ef86be65ade3U,
  0xbf6c27043e841821U, 0xbe1da9513efa893fU, 0xbe8e63cfbe3dce44U, 0x3e8257db3f88a1fbU,
  0x3f5c5e8a3e8ecd55U, 0x3f7c722dbfc04171U, 0x3f3dea923f95749aU, 0x3e866018bf25f110U,
  0xbe921fa63ee8a978U, 0x3e95e45cbe1d2a81U, 0x3f85109c3e09bdb4U, 0x3eb92f82bf862f76U,
  0x3f47683abe37699eU, 0xc01b73903fa3384eU, 0x3f80e7a5bd9e2f1bU, 0xbe89d761bf453ab5U,
  0x3e5865a7bf7d95c6U, 0x3f9820c93eb0b728U, 0x3e71cce83f49c6d4U, 0x3efb2a9d3effb2fdU,
  0xbed4fc133f273215U, 0xbf02612a3e847fc4U, 0x3ed8d17d3d6ede58U, 0x3de62826be33f48cU,
  0x3f6db47ebfe420caU, 0x3e1f28db3db1c98bU, 0xbf32ff8f3ee05b10U, 0x3f7db01cbe878f34U,
  0xbc98a3fabfdaa7a3U, 0x3f7225a0bd668a8cU, 0xbd5c53bebf710376U, 0x402c6d153f92ce84U,
  0x3e8670893cf1616aU, 0x3f6dc5d5be8c75adU, 0x3f9b32683f77947dU, 0xbea29a30bede01a2U,
  0x3fee536cc003cff1U, 0xbf91932cbdf6256dU, 0xbf0cb0813f6e6decU, 0x3f022e2ebeb9eab4U,
  0x3f1ec940bf86123fU, 0x3f93c5f1bfd6694aU, 0xbe2e1972bf570954U, 0x3f9a3d213f26530cU,
  0x3fbb96dd3fc1ac27U, 0xbf618da1bf26a86bU, 0x3e83788f3f75401cU, 0x3e40ba89bea65669U,
  0xbbae3025bded7725U, 0xbedd18c1bd6092e6U, 0xbed8da9b3e81409bU, 0xbeffb6d5beea17eeU,
  0xbedfcbbc3e7dea7eU, 0x3e4a96a03e8a1b5fU, 0x3edaed593f820af7U, 0xbf97d1aabed465daU,
  0x3f3b6dcebfde7c5cU, 0x3ed4d981bea8ede7U, 0xbea8b2b13f341bf6U, 0x3de171523e920d8cU,
  0x3fdea425bf10d1b9U, 0xbe8c8a22be832bbfU, 0x3e4b7095bdbe5600U, 0xbeb78ea53eede678U,
  0x3d071d06beecf0cfU, 0x3c147f65bf06f7e2U, 0x3f5f72623dc3f4d3U, 0x3f9ba5f03f1987edU,
  0x3f7ecef4bd3851b9U, 0xbcef154cbf72c55fU, 0x3d1900773f8621f6U, 0x3e07e726bd1468b6U,
  0xbea45f69be0aa0dfU, 0xbe01bd553ed4ca07U, 0x3e823bf13f58b81eU, 0x3ef25866bf0cca5cU,
  0x3e5eee313f3cabe2U, 0x3ea14655becb129eU, 0xbf5d745cbf347df6U, 0x3ef18a6d3f62a13fU,
  0x3f0a7906bf9c008bU, 0xbf79f7183df5c00aU, 0xbda132ffbee4a4dfU, 0x3ee8c9b7beb29c19U,
  0xbe88206a3f92b448U, 0xbe55ad683f3727b6U, 0x3e903b753f28662cU, 0x3f1e41bcbebf65a6U,
  0xbce4a0ad3e6c482bU, 0xbf34f56f3f07b06eU, 0xbf0ffbb5be3af2f5U, 0x3f9d6800bdc11735U,
  0x3e9c57903ecc557dU, 0x3f0b37b4bf0f17c3U, 0xbee7cabb3da87aebU, 0xc056ed403f1f7ccbU,
  0xbf3878edc028c3f3U, 0xbf811944bec302ecU, 0x3e3616443f8faca3U, 0xbe1cad163e34b4bdU,
  0x3f073741bfd4bc09U, 0x3fa67c04be475e3aU, 0xbd2e6e023e302d52U, 0x3f69641bbec7cf33U,
  0x3e490e453f311d76U, 0xbef155cd3f1bc05eU, 0x3f2f2bb83f7c15ceU, 0xbe0cc181bedbc178U,
  0x3f06b0983e83442bU, 0xbeff7b683e1c86e1U, 0x3e86aead3fdd1be7U, 0x3f5fb668bf0c1fdfU,
  0x3eed42423f05f28dU, 0x3ee8a4453b789fbbU, 0xbe410a423deea29fU, 0xbf3b45dfbb819ea2U,
  0x3ed56b08be97f2f2U, 0x3f2dfad4be05baa2U, 0x3ec6a29d3e926537U, 0x3f509b14bde4031cU,
  0x3f37f6babe8901abU, 0x3d29b790be31a890U, 0x3e11bdd8beec00a2U, 0x3eba7b0bbdac56b0U,
  0x3e4813af3f690eb7U, 0xbeb5f6d43f06e87eU, 0x3f224ed43f6a1212U, 0xbea7ffc03fa710b3U,
  0xbeffb55cc03daf2fU, 0xbf65d739be6fbf02U, 0xbe47927b3f29a9d8U, 0xbd8882febee0e39fU,
  0x3e1b0f593fbee95eU, 0x3e9f4fadbeb10b66U, 0xbde9bc1a3f9cba69U, 0xbfbb4aedbe730ea4U,
  0xbef2b022bf4b0924U, 0x3f484a453e9e1d10U, 0x3dd135c53e795ff4U, 0x3fa7e3be3f0ffebbU,
  0x3e62b2ab3f803589U, 0xbe4a45c63e1fee65U, 0x3e5932bc3f5db930U, 0xbe9bd8acbed5724eU,
  0x3f664e44bf56f6acU, 0xbe01cbfa3e534427U, 0xbf36f66a3fc4c37bU, 0x3f8b73efbf15cc4bU,
  0x3f0539323d8d1e3bU, 0x3f82c1eebe9501aaU, 0xbf66ca30bccaa1f9U, 0x3fb11b0c3f08b7e6U,
  0x3f3988b73fe929a7U, 0x3f6c8e6ebb57b9deU, 0x3f629d08bf318531U, 0xbf0f7f3ebf4512b3U,
  0x3e9e7e333ef7e224U, 0xbf0e8ed73e85deedU, 0xbeaa66cb3ff2af8cU, 0x3ffccb47bf297626U,
  0xbf8b92b8be4e2d2bU, 0xbf6ef98cbe693cebU, 0x3f4965613e6776e6U, 0x3f954f093f0adaadU,
  0xbee02b713ec64346U, 0x3f6c173cbe3b48e0U, 0xbb6311193f1bf2e1U, 0xbe99b43fbe4def87U,
  0xbe817471c017c48aU, 0xbdc5cb603e3d5038U, 0xbf93f0b23e83dee0U, 0x3ede1ec43dfa2174U,
  0xbeb2c04b3d25ba09U, 0xbebfae23bcdb4ba7U, 0xbd862b08bedfcdbfU, 0xbda194553d831c7bU,
  0xbf0d4179bd61f5cbU, 0xbe8ab9e7bea6247eU, 0xbad8547f3e2f0997U, 0xbe2ee397bdc0dbc4U,
  0x3e80bca5be0aa226U, 0xbe192b16bdd4a580U, 0xbe7ec163beb2d8ffU, 0x3db5a2c53d823c4aU,
  0xbea3f0c33fc76c5eU, 0x3d5185223f80a078U, 0x3f3038bdbe579ea1U, 0x3eef8d3cbf8e3b1dU,
  0xbf28bff63f4d722cU, 0xbf3862b3be5b4509U, 0xbf038da93f586cf7U, 0xbef03375bee2eb05U,
  0x3f00daebbf773b8dU, 0xc02719cc3e2d50f2U, 0x3f393c49bf3eb9caU, 0xbf3a3f31bf674d3fU,
  0x3dae7cf5bf80b38aU, 0x3f0547bbbf3b5773U, 0x3f517bcd3eb03588U, 0x3f4c6def3f5b0c46U,
  0x3e8b3ac23e89cb74U, 0xbedf014cbf112a31U, 0x3f278f233eca3b26U, 0x3f52a075bcda6d6bU,
  0x3efb818ebf216de3U, 0x3d5fef9e3f1f57e2U, 0xbd23b617bdf85c8bU, 0x3f2e65a6be3c7ea1U,
  0x3e4e07683f3d316bU, 0x3e97581bbe4a3ba8U, 0x3ea3cf10be5c89fdU, 0x3e1ea274becdf7c5U,
  0x3f5f4397bef755e2U, 0x3ebbddb83f2aadfcU, 0x3e60f68e3e471de3U, 0x3e921dee3f22ee15U,
  0xbd90eda33e1bf8d5U, 0x3e49755e3f0bb84eU, 0x3f2818a83f3a652bU, 0xbf34ad573ed1a7fdU,
  0xbd726d3abdde89faU, 0xbdf22997bebb49efU, 0xbe171096bd5f1764U, 0xbdd40d4e3c03c7b0U,
  0xbe383dce3e0d0ab0U, 0xbef8ae423cebfbcaU, 0xbcb19085bd360d70U, 0xbca44ac4be87816fU,
  0xbea269b1be1d9a45U, 0x3c37e7f2bda78426U, 0x3db6d33ebe3c426cU, 0x3de15f63be03ffd5U,
  0xbf6830943fba67aaU, 0x3da1fdc2bf1c4dddU, 0x3e3ed839bed33ea9U, 0xbed02eb23e3c2bb2U,
  0x3f7bdfd8bf9f56f7U, 0x3e82895b3efc0d9cU, 0x3d2d08f5be55b737U, 0x3ecbf62d3c88472eU,
  0x3de3fef23e4d8040U, 0x3ebdcbdd3f1ffff3U, 0x3f25f5533ce66842U, 0xbf469c953e8971c4U,
  0xbf6236b4bf918dcdU, 0x3f5bdc61be24f628U, 0xbe2c596b3fd06978U, 0xbf95055dc008c175U,
  0x3f116c583dd81921U, 0xbc9c37f2be583c08U, 0x3ea33038bf45646bU, 0xbde58a253e0fff6fU,
  0xbf0a83dc3f0c1251U, 0x3eb71b33be812064U, 0x3e4f4b443ed2d622U, 0x3ed9b5e73e965cf7U,
  0x3e96cb47be7eb379U, 0x3e243ed03db69035U, 0x3eb563f8bf3b5810U, 0xbf13d9fc3e5037a6U,
  0x3eceb9a0bf51f56bU, 0xbf825e223f1c8b09U, 0x3d1d8e503e7eefa6U, 0x3f0df46d3f781e5dU,
  0x3f56b805bedf27c8U, 0xbdc506f33e8c3955U, 0x3f47fd78bf9aa4b2U, 0xbf851c71bd3ef633U,
  0x3e844cad3f18f4b4U, 0xc01ea14b3fb52e40U, 0x3faf97bf3f6cc0a7U, 0xc01b5b3ac00ae27fU,
  0x3f6fb07ac048a188U, 0xc045fd7cc01ee0fdU, 0xbffad4683f00f039U, 0x3e72d2bcc0069eaaU,
  0xbfa0d409be4351abU, 0x3f4158d0c00f1626U, 0x3fa5fcaebdffec95U, 0x3fc1cb1140105b2fU,
  0x40cdf0f73e943f28U, 0xc05799fd406ef3b1U, 0x406726d7405f648bU, 0xc078d6c8bf8c695bU,
  0x401d49e640313f4bU, 0xbfa66df4c03896b9U, 0xc03d78f4408379bbU, 0x3f474192c0b51916U,
  0xc0a5823abd581f09U, 0x3f87f464c042d203U, 0x3f444c70be01e925U, 0xbf4c3c05c00e4e51U,
  0x3f98bdfa3eb6a7e8U, 0x3f350376bff76babU, 0xc00a6164bf4169fdU, 0x3ee8c223404a555dU,
  0xc086d27a4049c3eaU, 0x3fe2c0023e846090U, 0x3ea576b4bde19438U, 0x3f8649083f469182U,
  0xbff325efbe32e42bU, 0xbf3182563f3bad2fU, 0xbf99f975bec0b0edU, 0xbfd51b4abfabaf5eU,
  0xc07b6ad1bf80ce56U, 0x3d89d81cbfbe8b05U, 0xbf851a21bfb292d0U, 0x3ede65c2c038e28eU,
  0x3dfd6ed9c0677748U, 0xbfb9d44c3f284210U, 0x3e8598e2c002fc2fU, 0xbfe938f33f038fa2U,
  0x403d0ae03db421ccU, 0x3eab49ef3ca448a3U, 0x3f28113cbdfb2cbbU, 0x3fe61f9540193e72U,
  0xbfbeb6be3d7d600cU, 0x3f4bad32U,
};


ai_handle g_test_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_test_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

