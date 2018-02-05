#include "crijsb_utility.h"

void criJsbUtil_SetObjectInstance(JSContext *cx, JS::HandleObject hnobj, void *instance)
{
	js_proxy_t *proxy = jsb_new_proxy(cx, instance, hnobj);
}

void criJsbUtil_RemoveObjectInstance(JSContext *cx, JS::HandleObject hnobj, void *instance)
{
	js_proxy_t *jpxy = jsb_get_js_proxy(cx, hnobj);
	js_proxy_t *npxy = jsb_get_native_proxy(instance);
	if (npxy) {
		jsb_remove_proxy(npxy);
	}
	if (jpxy) {
		jsb_remove_proxy(jpxy);
	}
	
}

void criJsbUtil_RemoveObjectInstance(void *instance)
{
	js_proxy_t *npxy = jsb_get_native_proxy(instance);
	if (npxy) {
		jsb_remove_proxy(npxy);
	}
}

void *criJsbUtil_GetObjectInstance(JSContext *cx, JS::HandleObject hnobj)
{
	js_proxy_t *proxy = jsb_get_js_proxy(cx, hnobj);
	return (proxy ? proxy->ptr : nullptr);
}

JSObject *criJsbUtil_GetInstanceObject(void* instance)
{
	js_proxy_t *proxy = jsb_get_native_proxy(instance);
	if (proxy) {
		return proxy->obj;
	}
	else {
		return nullptr;
	}
}

void criJsbUtil_ErrorInvalidNativeObject(JSContext *cx, JSObject *jsobj)
{
	if (!JS_IsExceptionPending(cx)) {
		const JSClass *jsclass = JS_GetClass(jsobj);
		JS_ReportErrorUTF8(cx, "Invalid Native Object. class=%s", jsclass->name);
	}
}

bool criJsbUtil_StubConstructor(JSContext *cx, uint32_t argc, JS::Value *vp)
{
	return false;
}

void criJsbUtil_StubFinalize(JSFreeOp *fop, JSObject *jsobj)
{
}