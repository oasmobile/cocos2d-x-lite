#include "base/ccConfig.h"
#ifndef __cocos2dx_sqlite_h__
#define __cocos2dx_sqlite_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_SQLiteStatement_class;
extern JS::PersistentRootedObject *jsb_SQLiteStatement_prototype;

bool js_cocos2dx_sqlite_SQLiteStatement_constructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void js_cocos2dx_sqlite_SQLiteStatement_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_sqlite_SQLiteStatement(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_sqlite(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_sqlite_SQLiteStatement_reset(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_execute(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_dataCount(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_dataType(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_bind(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_nextRow(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_valueCount(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_restartSelect(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_bindNull(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_valueName(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_valueString(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_valueInt(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_valueDouble(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteStatement_SQLiteStatement(JSContext *cx, uint32_t argc, JS::Value *vp);

extern JSClass  *jsb_SQLiteWrapper_class;
extern JS::PersistentRootedObject *jsb_SQLiteWrapper_prototype;

bool js_cocos2dx_sqlite_SQLiteWrapper_constructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void js_cocos2dx_sqlite_SQLiteWrapper_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_sqlite_SQLiteWrapper(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_sqlite(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_sqlite_SQLiteWrapper_begin(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_rollback(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_exec(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_directStatement(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_commit(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_getPath(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_init(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_close(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_lastError(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_open(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_create(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cocos2dx_sqlite_SQLiteWrapper_SQLiteWrapper(JSContext *cx, uint32_t argc, JS::Value *vp);

#endif // __cocos2dx_sqlite_h__
