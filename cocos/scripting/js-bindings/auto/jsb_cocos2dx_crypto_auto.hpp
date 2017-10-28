#include "base/ccConfig.h"
#ifndef __cocos2dx_crypto_h__
#define __cocos2dx_crypto_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_Crypto_class;
extern JS::PersistentRootedObject *jsb_Crypto_prototype;

bool js_cocos2dx_crypto_Crypto_constructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void js_cocos2dx_crypto_Crypto_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_crypto_Crypto(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_crypto(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_crypto_Crypto_encodeBase64Len(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_MD5String(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_decodeBase64Len(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_MD5File(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_decodeBase64(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_bin2hex(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_encodeBase64(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_crypto_Crypto_MD5(JSContext *cx, uint32_t argc, JS::Value *vp);

#endif // __cocos2dx_crypto_h__
