#include "scripting/js-bindings/auto/jsb_cocos2dx_sqlite_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "sqlite/SQLiteWrapper.h"

JSClass  *jsb_SQLiteStatement_class;
JS::PersistentRootedObject *jsb_SQLiteStatement_prototype;

bool js_cocos2dx_sqlite_SQLiteStatement_reset(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_reset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->reset();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_reset : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_reset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_execute(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_execute : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->execute();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_execute : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_execute : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_dataCount(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_dataCount : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->dataCount();
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_dataCount : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_dataCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_dataType(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : Error processing arguments");
        int ret = (int)cobj->dataType(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_dataType : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_dataType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_bind(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    bool ok = true;
    SQLiteStatement* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    cobj = (SQLiteStatement *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : Invalid Native Object");
    do {
        ok = true;
        if (argc == 2) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= jsval_to_double(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->bind(arg0, arg1);
            JS::RootedValue jsret(cx, JS::NullHandleValue);
            jsret = JS::BooleanValue(ret);
            JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : error parsing return value");
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        ok = true;
        if (argc == 2) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->bind(arg0, arg1);
            JS::RootedValue jsret(cx, JS::NullHandleValue);
            jsret = JS::BooleanValue(ret);
            JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : error parsing return value");
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        ok = true;
        if (argc == 2) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->bind(arg0, arg1);
            JS::RootedValue jsret(cx, JS::NullHandleValue);
            jsret = JS::BooleanValue(ret);
            JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bind : error parsing return value");
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_bind : arguments error");
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_nextRow(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_nextRow : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->nextRow();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_nextRow : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_nextRow : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_valueCount(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueCount : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->valueCount();
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueCount : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_valueCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_restartSelect(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_restartSelect : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->restartSelect();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_restartSelect : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_restartSelect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_bindNull(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : Error processing arguments");
        bool ret = cobj->bindNull(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_bindNull : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_valueName(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : Error processing arguments");
        std::string ret = cobj->valueName(arg0);
        JS::RootedValue jsret(cx);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueName : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_valueName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_valueString(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : Error processing arguments");
        std::string ret = cobj->valueString(arg0);
        JS::RootedValue jsret(cx);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueString : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_valueString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_valueInt(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : Error processing arguments");
        int ret = cobj->valueInt(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_valueInt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_valueDouble(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteStatement* cobj = (SQLiteStatement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : Error processing arguments");
        double ret = cobj->valueDouble(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::DoubleValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteStatement_valueDouble : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteStatement_constructor(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    SQLiteStatement* cobj = new (std::nothrow) SQLiteStatement();

    // create the js object and link the native object with the javascript object
    JS::RootedObject jsobj(cx);
    JS::RootedObject proto(cx, jsb_SQLiteStatement_prototype->get());
    jsb_ref_create_jsobject(cx, cobj, jsb_SQLiteStatement_class, proto, &jsobj, "SQLiteStatement");
    JS::RootedValue retVal(cx, JS::ObjectOrNullValue(jsobj));
    args.rval().set(retVal);
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok) 
    {
        JS::HandleValueArray argsv(args);
        ScriptingCore::getInstance()->executeFunctionWithOwner(retVal, "_ctor", argsv);
    }
    return true;
}


void js_register_cocos2dx_sqlite_SQLiteStatement(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps SQLiteStatement_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        nullptr,
        nullptr, nullptr, nullptr, nullptr
    };
    static JSClass SQLiteStatement_class = {
        "SQLiteStatement",
        JSCLASS_HAS_PRIVATE,
        &SQLiteStatement_classOps
    };
    jsb_SQLiteStatement_class = &SQLiteStatement_class;

    static JSFunctionSpec funcs[] = {
        JS_FN("reset", js_cocos2dx_sqlite_SQLiteStatement_reset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("execute", js_cocos2dx_sqlite_SQLiteStatement_execute, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dataCount", js_cocos2dx_sqlite_SQLiteStatement_dataCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dataType", js_cocos2dx_sqlite_SQLiteStatement_dataType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("bind", js_cocos2dx_sqlite_SQLiteStatement_bind, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("nextRow", js_cocos2dx_sqlite_SQLiteStatement_nextRow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("valueCount", js_cocos2dx_sqlite_SQLiteStatement_valueCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("restartSelect", js_cocos2dx_sqlite_SQLiteStatement_restartSelect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("bindNull", js_cocos2dx_sqlite_SQLiteStatement_bindNull, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("valueName", js_cocos2dx_sqlite_SQLiteStatement_valueName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("valueString", js_cocos2dx_sqlite_SQLiteStatement_valueString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("valueInt", js_cocos2dx_sqlite_SQLiteStatement_valueInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("valueDouble", js_cocos2dx_sqlite_SQLiteStatement_valueDouble, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JS::RootedObject proto(cx, JS_InitClass(
        cx, global,
        parent_proto,
        jsb_SQLiteStatement_class,
        js_cocos2dx_sqlite_SQLiteStatement_constructor, 0,
        nullptr,
        funcs,
        nullptr,
        nullptr));

    // add the proto and JSClass to the type->js info hash table
    js_type_class_t *typeClass = jsb_register_class<SQLiteStatement>(cx, jsb_SQLiteStatement_class, proto);
    jsb_SQLiteStatement_prototype = typeClass->proto;
    JS::RootedValue className(cx);
    std_string_to_jsval(cx, "SQLiteStatement", &className);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
}

JSClass  *jsb_SQLiteWrapper_class;
JS::PersistentRootedObject *jsb_SQLiteWrapper_prototype;

bool js_cocos2dx_sqlite_SQLiteWrapper_begin(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_begin : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->begin();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_begin : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_begin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_rollback(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_rollback : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->rollback();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_rollback : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_rollback : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_exec(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : Error processing arguments");
        SQLiteStatement* ret = cobj->exec(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            JS::RootedObject jsretObj(cx);
            js_get_or_create_jsobject<SQLiteStatement>(cx, (SQLiteStatement*)ret, &jsretObj);
            jsret = JS::ObjectOrNullValue(jsretObj);
        } else {
            jsret = JS::NullHandleValue;
        };
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_exec : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_exec : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_directStatement(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : Error processing arguments");
        bool ret = cobj->directStatement(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_directStatement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_commit(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_commit : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->commit();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_commit : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_commit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_getPath(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : Error processing arguments");
        std::string ret = cobj->getPath(arg0, arg1);
        JS::RootedValue jsret(cx);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_getPath : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_init(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_init : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_close(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_close : Invalid Native Object");
    if (argc == 0) {
        cobj->close();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_close : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_lastError(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_lastError : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->lastError();
        JS::RootedValue jsret(cx);
        ok &= std_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_lastError : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_lastError : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_open(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    SQLiteWrapper* cobj = (SQLiteWrapper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : Error processing arguments");
        bool ret = cobj->open(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_sqlite_SQLiteWrapper_open : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_open : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_sqlite_SQLiteWrapper_create(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 0) {

        auto ret = SQLiteWrapper::create();
        JS::RootedObject jsret(cx);
        JS::RootedObject proto(cx, jsb_SQLiteWrapper_prototype->get());
        jsb_ref_autoreleased_create_jsobject(cx, ret, jsb_SQLiteWrapper_class, proto, &jsret, "SQLiteWrapper");
        args.rval().set(JS::ObjectOrNullValue(jsret));
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cocos2dx_sqlite_SQLiteWrapper_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_sqlite_SQLiteWrapper_constructor(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    SQLiteWrapper* cobj = new (std::nothrow) SQLiteWrapper();

    // create the js object and link the native object with the javascript object
    JS::RootedObject jsobj(cx);
    JS::RootedObject proto(cx, jsb_SQLiteWrapper_prototype->get());
    jsb_ref_create_jsobject(cx, cobj, jsb_SQLiteWrapper_class, proto, &jsobj, "SQLiteWrapper");
    JS::RootedValue retVal(cx, JS::ObjectOrNullValue(jsobj));
    args.rval().set(retVal);
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok) 
    {
        JS::HandleValueArray argsv(args);
        ScriptingCore::getInstance()->executeFunctionWithOwner(retVal, "_ctor", argsv);
    }
    return true;
}


void js_register_cocos2dx_sqlite_SQLiteWrapper(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps SQLiteWrapper_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        nullptr,
        nullptr, nullptr, nullptr, nullptr
    };
    static JSClass SQLiteWrapper_class = {
        "SQLiteWrapper",
        JSCLASS_HAS_PRIVATE,
        &SQLiteWrapper_classOps
    };
    jsb_SQLiteWrapper_class = &SQLiteWrapper_class;

    static JSFunctionSpec funcs[] = {
        JS_FN("begin", js_cocos2dx_sqlite_SQLiteWrapper_begin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("rollback", js_cocos2dx_sqlite_SQLiteWrapper_rollback, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("exec", js_cocos2dx_sqlite_SQLiteWrapper_exec, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("directStatement", js_cocos2dx_sqlite_SQLiteWrapper_directStatement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("commit", js_cocos2dx_sqlite_SQLiteWrapper_commit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPath", js_cocos2dx_sqlite_SQLiteWrapper_getPath, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_sqlite_SQLiteWrapper_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("close", js_cocos2dx_sqlite_SQLiteWrapper_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lastError", js_cocos2dx_sqlite_SQLiteWrapper_lastError, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("open", js_cocos2dx_sqlite_SQLiteWrapper_open, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_sqlite_SQLiteWrapper_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JS::RootedObject proto(cx, JS_InitClass(
        cx, global,
        parent_proto,
        jsb_SQLiteWrapper_class,
        js_cocos2dx_sqlite_SQLiteWrapper_constructor, 0,
        nullptr,
        funcs,
        nullptr,
        st_funcs));

    // add the proto and JSClass to the type->js info hash table
    js_type_class_t *typeClass = jsb_register_class<SQLiteWrapper>(cx, jsb_SQLiteWrapper_class, proto);
    jsb_SQLiteWrapper_prototype = typeClass->proto;
    JS::RootedValue className(cx);
    std_string_to_jsval(cx, "SQLiteWrapper", &className);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
}

void register_all_cocos2dx_sqlite(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_sqlite_SQLiteWrapper(cx, ns);
    js_register_cocos2dx_sqlite_SQLiteStatement(cx, ns);
}

