#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_Crypto_proto;
extern se::Class* __jsb_Crypto_class;

bool js_register_Crypto(se::Object* obj);
bool register_all_cocos2dx_crypto(se::Object* obj);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_encodeBase64Len);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_decodeBase64Len);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_MD5File);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_decodeBase64);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_bin2hex);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_encodeBase64);
SE_DECLARE_FUNC(js_cocos2dx_crypto_Crypto_MD5);

