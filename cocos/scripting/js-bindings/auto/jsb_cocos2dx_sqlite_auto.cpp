#include "scripting/js-bindings/auto/jsb_cocos2dx_sqlite_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "sqlite/SQLiteWrapper.h"

se::Object* __jsb_SQLiteStatement_proto = nullptr;
se::Class* __jsb_SQLiteStatement_class = nullptr;

static bool js_cocos2dx_sqlite_SQLiteStatement_reset(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->reset();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_reset : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_reset)

static bool js_cocos2dx_sqlite_SQLiteStatement_execute(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_execute : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->execute();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_execute : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_execute)

static bool js_cocos2dx_sqlite_SQLiteStatement_dataCount(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_dataCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->dataCount();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_dataCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_dataCount)

static bool js_cocos2dx_sqlite_SQLiteStatement_dataType(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : Error processing arguments");
        unsigned int result = (unsigned int)cobj->dataType(arg0);
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_dataType)

static bool js_cocos2dx_sqlite_SQLiteStatement_bind(se::State& s)
{
    CC_UNUSED bool ok = true;
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2( cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 2) {
            int arg0 = 0;
            ok &= seval_to_int32(args[0], (int32_t*)&arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= seval_to_double(args[1], &arg1);
            if (!ok) { ok = true; break; }
            bool result = cobj->bind(arg0, arg1);
            ok &= boolean_to_seval(result, &s.rval());
            SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : Error processing arguments");
            return true;
        }
    } while(false);

    do {
        if (argc == 2) {
            int arg0 = 0;
            ok &= seval_to_int32(args[0], (int32_t*)&arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= seval_to_std_string(args[1], &arg1);
            if (!ok) { ok = true; break; }
            bool result = cobj->bind(arg0, arg1);
            ok &= boolean_to_seval(result, &s.rval());
            SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : Error processing arguments");
            return true;
        }
    } while(false);

    do {
        if (argc == 2) {
            int arg0 = 0;
            ok &= seval_to_int32(args[0], (int32_t*)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= seval_to_int32(args[1], (int32_t*)&arg1);
            if (!ok) { ok = true; break; }
            bool result = cobj->bind(arg0, arg1);
            ok &= boolean_to_seval(result, &s.rval());
            SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : Error processing arguments");
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_bind)

static bool js_cocos2dx_sqlite_SQLiteStatement_nextRow(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_nextRow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->nextRow();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_nextRow : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_nextRow)

static bool js_cocos2dx_sqlite_SQLiteStatement_valueCount(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_valueCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->valueCount();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_valueCount)

static bool js_cocos2dx_sqlite_SQLiteStatement_restartSelect(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_restartSelect : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->restartSelect();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_restartSelect : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_restartSelect)

static bool js_cocos2dx_sqlite_SQLiteStatement_bindNull(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : Error processing arguments");
        bool result = cobj->bindNull(arg0);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_bindNull)

static bool js_cocos2dx_sqlite_SQLiteStatement_valueName(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : Error processing arguments");
        std::string result = cobj->valueName(arg0);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_valueName)

static bool js_cocos2dx_sqlite_SQLiteStatement_valueString(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : Error processing arguments");
        std::string result = cobj->valueString(arg0);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_valueString)

static bool js_cocos2dx_sqlite_SQLiteStatement_valueInt(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : Error processing arguments");
        int result = cobj->valueInt(arg0);
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_valueInt)

static bool js_cocos2dx_sqlite_SQLiteStatement_valueDouble(se::State& s)
{
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : Error processing arguments");
        double result = cobj->valueDouble(arg0);
        ok &= double_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteStatement_valueDouble)

SE_DECLARE_FINALIZE_FUNC(js_SQLiteStatement_finalize)

static bool js_cocos2dx_sqlite_SQLiteStatement_constructor(se::State& s)
{
    SQLiteStatement* cobj = new (std::nothrow) SQLiteStatement();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_cocos2dx_sqlite_SQLiteStatement_constructor, __jsb_SQLiteStatement_class, js_SQLiteStatement_finalize)




static bool js_SQLiteStatement_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (SQLiteStatement)", s.nativeThisObject());
    SQLiteStatement* cobj = (SQLiteStatement*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_SQLiteStatement_finalize)

bool js_register_cocos2dx_sqlite_SQLiteStatement(se::Object* obj)
{
    auto cls = se::Class::create("SQLiteStatement", obj, nullptr, _SE(js_cocos2dx_sqlite_SQLiteStatement_constructor));

    cls->defineFunction("reset", _SE(js_cocos2dx_sqlite_SQLiteStatement_reset));
    cls->defineFunction("execute", _SE(js_cocos2dx_sqlite_SQLiteStatement_execute));
    cls->defineFunction("dataCount", _SE(js_cocos2dx_sqlite_SQLiteStatement_dataCount));
    cls->defineFunction("dataType", _SE(js_cocos2dx_sqlite_SQLiteStatement_dataType));
    cls->defineFunction("bind", _SE(js_cocos2dx_sqlite_SQLiteStatement_bind));
    cls->defineFunction("nextRow", _SE(js_cocos2dx_sqlite_SQLiteStatement_nextRow));
    cls->defineFunction("valueCount", _SE(js_cocos2dx_sqlite_SQLiteStatement_valueCount));
    cls->defineFunction("restartSelect", _SE(js_cocos2dx_sqlite_SQLiteStatement_restartSelect));
    cls->defineFunction("bindNull", _SE(js_cocos2dx_sqlite_SQLiteStatement_bindNull));
    cls->defineFunction("valueName", _SE(js_cocos2dx_sqlite_SQLiteStatement_valueName));
    cls->defineFunction("valueString", _SE(js_cocos2dx_sqlite_SQLiteStatement_valueString));
    cls->defineFunction("valueInt", _SE(js_cocos2dx_sqlite_SQLiteStatement_valueInt));
    cls->defineFunction("valueDouble", _SE(js_cocos2dx_sqlite_SQLiteStatement_valueDouble));
    cls->defineFinalizeFunction(_SE(js_SQLiteStatement_finalize));
    cls->install();
    JSBClassType::registerClass<SQLiteStatement>(cls);

    __jsb_SQLiteStatement_proto = cls->getProto();
    __jsb_SQLiteStatement_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_SQLiteWrapper_proto = nullptr;
se::Class* __jsb_SQLiteWrapper_class = nullptr;

static bool js_cocos2dx_sqlite_SQLiteWrapper_begin(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_begin : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->begin();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_begin : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_begin)

static bool js_cocos2dx_sqlite_SQLiteWrapper_rollback(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_rollback : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->rollback();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_rollback : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_rollback)

static bool js_cocos2dx_sqlite_SQLiteWrapper_exec(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : Error processing arguments");
        SQLiteStatement* result = cobj->exec(arg0);
        ok &= native_ptr_to_seval<SQLiteStatement>((SQLiteStatement*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_exec)

static bool js_cocos2dx_sqlite_SQLiteWrapper_directStatement(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : Error processing arguments");
        bool result = cobj->directStatement(arg0);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_directStatement)

static bool js_cocos2dx_sqlite_SQLiteWrapper_commit(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_commit : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->commit();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_commit : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_commit)

static bool js_cocos2dx_sqlite_SQLiteWrapper_getPath(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : Error processing arguments");
        std::string result = cobj->getPath(arg0, arg1);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_getPath)

static bool js_cocos2dx_sqlite_SQLiteWrapper_init(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->init();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_init)

static bool js_cocos2dx_sqlite_SQLiteWrapper_close(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_close : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->close();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_close)

static bool js_cocos2dx_sqlite_SQLiteWrapper_lastError(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_lastError : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->lastError();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_lastError : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_lastError)

static bool js_cocos2dx_sqlite_SQLiteWrapper_open(se::State& s)
{
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : Error processing arguments");
        bool result = cobj->open(arg0);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_open)

static bool js_cocos2dx_sqlite_SQLiteWrapper_create(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        auto result = SQLiteWrapper::create();
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_SQLiteWrapper_class);
        obj->setPrivateData(result);
        s.rval().setObject(obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_sqlite_SQLiteWrapper_create)

SE_DECLARE_FINALIZE_FUNC(js_SQLiteWrapper_finalize)

static bool js_cocos2dx_sqlite_SQLiteWrapper_constructor(se::State& s)
{
    SQLiteWrapper* cobj = new (std::nothrow) SQLiteWrapper();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_cocos2dx_sqlite_SQLiteWrapper_constructor, __jsb_SQLiteWrapper_class, js_SQLiteWrapper_finalize)




static bool js_SQLiteWrapper_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (SQLiteWrapper)", s.nativeThisObject());
    SQLiteWrapper* cobj = (SQLiteWrapper*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_SQLiteWrapper_finalize)

bool js_register_cocos2dx_sqlite_SQLiteWrapper(se::Object* obj)
{
    auto cls = se::Class::create("SQLiteWrapper", obj, nullptr, _SE(js_cocos2dx_sqlite_SQLiteWrapper_constructor));

    cls->defineFunction("begin", _SE(js_cocos2dx_sqlite_SQLiteWrapper_begin));
    cls->defineFunction("rollback", _SE(js_cocos2dx_sqlite_SQLiteWrapper_rollback));
    cls->defineFunction("exec", _SE(js_cocos2dx_sqlite_SQLiteWrapper_exec));
    cls->defineFunction("directStatement", _SE(js_cocos2dx_sqlite_SQLiteWrapper_directStatement));
    cls->defineFunction("commit", _SE(js_cocos2dx_sqlite_SQLiteWrapper_commit));
    cls->defineFunction("getPath", _SE(js_cocos2dx_sqlite_SQLiteWrapper_getPath));
    cls->defineFunction("init", _SE(js_cocos2dx_sqlite_SQLiteWrapper_init));
    cls->defineFunction("close", _SE(js_cocos2dx_sqlite_SQLiteWrapper_close));
    cls->defineFunction("lastError", _SE(js_cocos2dx_sqlite_SQLiteWrapper_lastError));
    cls->defineFunction("open", _SE(js_cocos2dx_sqlite_SQLiteWrapper_open));
    cls->defineStaticFunction("create", _SE(js_cocos2dx_sqlite_SQLiteWrapper_create));
    cls->defineFinalizeFunction(_SE(js_SQLiteWrapper_finalize));
    cls->install();
    JSBClassType::registerClass<SQLiteWrapper>(cls);

    __jsb_SQLiteWrapper_proto = cls->getProto();
    __jsb_SQLiteWrapper_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_cocos2dx_sqlite(se::Object* obj)
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

    js_register_cocos2dx_sqlite_SQLiteWrapper(ns);
    js_register_cocos2dx_sqlite_SQLiteStatement(ns);
    return true;
}

