#include "scripting/js-bindings/auto/jsb_cocos2dx_crypto_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "Crypto/Crypto.h"

se::Object* __jsb_Crypto_proto = nullptr;
se::Class* __jsb_Crypto_class = nullptr;

static bool js_cocos2dx_crypto_Crypto_encodeBase64Len(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_encodeBase64Len : Error processing arguments");
        int result = Crypto::encodeBase64Len(arg0, arg1);
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_encodeBase64Len : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_encodeBase64Len)

static bool js_cocos2dx_crypto_Crypto_decodeBase64Len(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_decodeBase64Len : Error processing arguments");
        int result = Crypto::decodeBase64Len(arg0);
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_decodeBase64Len : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_decodeBase64Len)

static bool js_cocos2dx_crypto_Crypto_MD5File(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_MD5File : Error processing arguments");
        const char* result = Crypto::MD5File(arg0);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_MD5File : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_MD5File)

static bool js_cocos2dx_crypto_Crypto_decodeBase64(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_decodeBase64 : Error processing arguments");
        const std::string result = Crypto::decodeBase64(arg0, arg1);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_decodeBase64 : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_decodeBase64)

static bool js_cocos2dx_crypto_Crypto_bin2hex(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        unsigned char* arg0 = nullptr;
        int arg1 = 0;
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
        ok = false;
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_bin2hex : Error processing arguments");
        char* result = Crypto::bin2hex(arg0, arg1);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_bin2hex : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_bin2hex)

static bool js_cocos2dx_crypto_Crypto_encodeBase64(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        ok &= seval_to_int32(args[2], (int32_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_encodeBase64 : Error processing arguments");
        const std::string result = Crypto::encodeBase64(arg0, arg1, arg2);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_encodeBase64 : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_encodeBase64)

static bool js_cocos2dx_crypto_Crypto_MD5(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        void* arg0 = nullptr;
        int arg1 = 0;
        unsigned char* arg2 = nullptr;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
        ok = false;
        ok &= seval_to_int32(args[1], (int32_t*)&arg1);
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
        ok = false;
        SE_PRECONDITION2(ok, false, "js_cocos2dx_crypto_Crypto_MD5 : Error processing arguments");
        Crypto::MD5(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_crypto_Crypto_MD5)



static bool js_Crypto_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (Crypto)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        Crypto* cobj = (Crypto*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_Crypto_finalize)

bool js_register_cocos2dx_crypto_Crypto(se::Object* obj)
{
    auto cls = se::Class::create("Crypto", obj, nullptr, nullptr);

    cls->defineStaticFunction("encodeBase64Len", _SE(js_cocos2dx_crypto_Crypto_encodeBase64Len));
    cls->defineStaticFunction("decodeBase64Len", _SE(js_cocos2dx_crypto_Crypto_decodeBase64Len));
    cls->defineStaticFunction("MD5File", _SE(js_cocos2dx_crypto_Crypto_MD5File));
    cls->defineStaticFunction("decodeBase64", _SE(js_cocos2dx_crypto_Crypto_decodeBase64));
    cls->defineStaticFunction("bin2hex", _SE(js_cocos2dx_crypto_Crypto_bin2hex));
    cls->defineStaticFunction("encodeBase64", _SE(js_cocos2dx_crypto_Crypto_encodeBase64));
    cls->defineStaticFunction("MD5", _SE(js_cocos2dx_crypto_Crypto_MD5));
    cls->defineFinalizeFunction(_SE(js_Crypto_finalize));
    cls->install();
    JSBClassType::registerClass<Crypto>(cls);

    __jsb_Crypto_proto = cls->getProto();
    __jsb_Crypto_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_cocos2dx_crypto(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("jsb", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("jsb", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_cocos2dx_crypto_Crypto(ns);
    return true;
}

