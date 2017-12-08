#include "scripting/js-bindings/auto/jsb_cocos2dx_crypto_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "crypto/Crypto.h"

JSClass  *jsb_Crypto_class;
JS::PersistentRootedObject *jsb_Crypto_prototype;

bool js_cocos2dx_crypto_Crypto_encodeBase64Len(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_encodeBase64Len : Error processing arguments");

        int ret = Crypto::encodeBase64Len(arg0, arg1);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_encodeBase64Len : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_encodeBase64Len : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_MD5String(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        void* arg0 = nullptr;
        int arg1 = 0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_MD5String : Error processing arguments");

        const std::string ret = Crypto::MD5String(arg0, arg1);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_MD5String : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_MD5String : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_decodeBase64Len(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_decodeBase64Len : Error processing arguments");

        int ret = Crypto::decodeBase64Len(arg0);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_decodeBase64Len : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_decodeBase64Len : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_MD5File(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_MD5File : Error processing arguments");

        const char* ret = Crypto::MD5File(arg0);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= c_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_MD5File : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_MD5File : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_decodeBase64(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_decodeBase64 : Error processing arguments");

        const std::string ret = Crypto::decodeBase64(arg0, arg1);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_decodeBase64 : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_decodeBase64 : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_bin2hex(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        unsigned char* arg0 = nullptr;
        int arg1 = 0;
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_bin2hex : Error processing arguments");

        char* ret = Crypto::bin2hex(arg0, arg1);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= c_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_bin2hex : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_bin2hex : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_encodeBase64(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 3) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_encodeBase64 : Error processing arguments");

        const std::string ret = Crypto::encodeBase64(arg0, arg1, arg2);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_encodeBase64 : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_encodeBase64 : wrong number of arguments");
    return false;
}

bool js_cocos2dx_crypto_Crypto_MD5(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 3) {
        void* arg0 = nullptr;
        int arg1 = 0;
        unsigned char* arg2 = nullptr;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_crypto_Crypto_MD5 : Error processing arguments");
        Crypto::MD5(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_crypto_Crypto_MD5 : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_crypto_Crypto(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps Crypto_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        nullptr,
        nullptr, nullptr, nullptr, nullptr
    };
    static JSClass Crypto_class = {
        "Crypto",
        JSCLASS_HAS_PRIVATE,
        &Crypto_classOps
    };
    jsb_Crypto_class = &Crypto_class;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("encodeBase64Len", js_cocos2dx_crypto_Crypto_encodeBase64Len, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("MD5String", js_cocos2dx_crypto_Crypto_MD5String, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("decodeBase64Len", js_cocos2dx_crypto_Crypto_decodeBase64Len, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("MD5File", js_cocos2dx_crypto_Crypto_MD5File, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("decodeBase64", js_cocos2dx_crypto_Crypto_decodeBase64, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("bin2hex", js_cocos2dx_crypto_Crypto_bin2hex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("encodeBase64", js_cocos2dx_crypto_Crypto_encodeBase64, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("MD5", js_cocos2dx_crypto_Crypto_MD5, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JS::RootedObject proto(cx, JS_InitClass(
        cx, global,
        parent_proto,
        jsb_Crypto_class,
        dummy_constructor<Crypto>, 0,
        nullptr,
        nullptr,
        nullptr,
        st_funcs));

    // add the proto and JSClass to the type->js info hash table
    js_type_class_t *typeClass = jsb_register_class<Crypto>(cx, jsb_Crypto_class, proto);
    jsb_Crypto_prototype = typeClass->proto;
    JS::RootedValue className(cx);
    std_string_to_jsval(cx, "Crypto", &className);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}

void register_all_cocos2dx_crypto(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_crypto_Crypto(cx, ns);
}

