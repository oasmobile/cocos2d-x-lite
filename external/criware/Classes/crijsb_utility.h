#ifndef CRI_INCL_CRIWARE_BINDING_H
#define CRI_INCL_CRIWARE_BINDING_H

#include <stdint.h>
#include <vector>
#include <cri_xpt.h>
#include "ScriptingCore.h"
#include "crijsb_binding_templates.h"

/* Set C++ instance of JS object */
void criJsbUtil_SetObjectInstance(JSContext *cx, JS::HandleObject obj, void *instance);
/* Remove C++ instance of JS object */
void criJsbUtil_RemoveObjectInstance(JSContext *cx, JS::HandleObject hnobj, void *instance);
void criJsbUtil_RemoveObjectInstance(void *instance);
/* Get C++ instance from JS object */
void *criJsbUtil_GetObjectInstance(JSContext *cx, JS::HandleObject hnobj);
/* Get JS object from C++ instance */
JSObject *criJsbUtil_GetInstanceObject(void* instance);
/* Error if can not get JS object */
void criJsbUtil_ErrorInvalidNativeObject(JSContext *cx, JSObject *jsobj);

bool criJsbUtil_StubConstructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void criJsbUtil_StubFinalize(JSFreeOp *fop, JSObject *jsobj);

struct CriJsbContext
{
	/* Get argument */
	JS::HandleValue get_arg_jsval(int index) const {
		return args.get(index);
	}

	/* Set result */
	void set_result_(const JS::Value& res) const {
		args.rval().set(res);
	}

	/* Get argument by JS::Value */
	JS::HandleValue get_arg(cribt::identity<JS::HandleValue>, int index) const {
		return get_arg_jsval(index);
	}

	/* Get argument by character */
	const CriChar8* get_arg(cribt::identity<const CriChar8*>, int index) const {
		auto val = get_arg_jsval(index);
		/* if null,undefined */
		if (val.isNullOrUndefined()) {
			return nullptr;
		}

		JSString *str = val.toString();
		size_t remain = STRING_BUFFER_SIZE - stringOffset;
		size_t len = JS_GetStringEncodingLength(cx, str);

		char *ptr = nullptr;
		if (len + 1 <= remain) {
			/* buffer sufficient */
			ptr = &stringBuffer[stringOffset];
			stringOffset += len + 1;
		}
		else {
			/* buffer not sufficient */
			extendedStrings.emplace_back(len + 1, 0);
			ptr = (char*)extendedStrings.rbegin()->data();
			remain = len + 1;
		}
		/* convert to character */
		JS_EncodeStringToBuffer(cx, str, ptr, remain);
		ptr[len] = '\0';
		return ptr;
	}

	/* Get argument by bool */
	bool get_arg(cribt::identity<bool>, int index) const {
		return get_arg_jsval(index).toBoolean();
	}

	/* Get argument by arithmetic */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_arithmetic<T>::value>::type* = 0) const {
		return static_cast<T>(get_arg_jsval(index).toNumber());
	}

	/* Get argument by enum */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_enum<T>::value>::type* = 0) const {
		return static_cast<T>(get_arg_jsval(index).toInt32());
	}

	/* Get argument by pointer */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_pointer<T>::value>::type* = 0) const {
		auto val = get_arg_jsval(index);
		if (val.isObject()) {
			JSObject *jsobj = val.toObjectOrNull();
			return reinterpret_cast<T>(criJsbUtil_GetObjectInstance(cx, JS::RootedObject(cx, jsobj)));
		}
		return nullptr;
	}

	/* Get argument by instance(not implement) */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_class<T>::value>::type* = 0) const {
		T res = {};
		return res;
	}

	/* Set result by void */
	void set_result() const {
		set_result_(JS::NullValue());
	}

	/* Set result by character */
	void set_result(const CriChar8* res) const {
		if (res == nullptr) {
			set_result_(JS::NullValue());
		}
		else {
			set_result_(JS::StringValue(JS_NewStringCopyZ(cx, res)));
		}
	}

	/* Set result by bool */
	void set_result(bool res) const {
		set_result_(JS::BooleanValue(res));
	}

	/* Set result by JSObject */
	void set_result(JSObject *res) const {
		set_result_(JS::ObjectValue(*res));
	}
	
	/* Set result by pointer */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr) const {
		if (res) {
			/* Get JSObject from instance */
			JSObject *jsobj = criJsbUtil_GetInstanceObject(res);
			if (jsobj) {
				/* Set JSObject */
				set_result_(JS::ObjectValue(*jsobj));
				return;
			}
		}
		/* set null */
		set_result_(JS::NullValue());
	}

	/* Set result by integral */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr) const {
		set_result_(JS::Int32Value((int32_t)res));
	}

	/* Set result by floating point */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr) const {
		set_result_(JS::DoubleValue((double)res));
	}

	/* Set result by enum */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr) const {
		set_result_(JS::Int32Value((int32_t)res));
	}

	/* Set result by instance(not implement) */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_class<T>::value>::type* = nullptr) const {
		set_result_(JS::Int32Value((int32_t)res));
	}

	CriJsbContext(JSContext *cx, uint32_t argc, JS::Value *vp)
		: cx(cx), args(JS::CallArgsFromVp(argc, vp)) {}
	CriJsbContext(JSContext *cx, JS::MutableHandleValue& vp, bool setter)
		: cx(cx), args(JS::CallArgsFromVp(1, vp.address())) {}
	JSContext *cx;
	JS::CallArgs args;

	static const size_t STRING_BUFFER_SIZE = 1024;
	mutable char stringBuffer[STRING_BUFFER_SIZE];
	mutable size_t stringOffset = 0;
	mutable std::vector<std::string> extendedStrings;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define CRIJSB_LAMBDA_TO_FP(type) (type)
#else
#define CRIJSB_LAMBDA_TO_FP(type) +
#endif

#define CRIJSB_FUNC_WRAPPER(funcptr) CRIJSB_LAMBDA_TO_FP(JSNative)[](JSContext *cx, uint32_t argc, JS::Value *vp) { \
	return cribt::call_with_context(CriJsbContext(cx, argc, vp), funcptr); \
}

#define CRIJSB_METHOD_WRAPPER(funcptr) CRIJSB_LAMBDA_TO_FP(JSNative)[](JSContext *cx, uint32_t argc, JS::Value *vp) { \
    void *thisptr = JS_GetPrivate(JS_THIS_OBJECT(cx, vp)); \
	if (thisptr) return cribt::call_with_context(CriJsbContext(cx, argc, vp), funcptr, thisptr); \
	else criJsbUtil_ErrorInvalidNativeObject(cx, JS_THIS_OBJECT(cx, vp)); \
	return false; \
}

/* Set C function */
#define CRIJSB_FUNC(func) \
	JS_FN(#func, CRIJSB_FUNC_WRAPPER(func), \
	(uint16_t)cribt::get_arguments_count(func), \
	JSPROP_PERMANENT | JSPROP_ENUMERATE)

/* Set Standard JS function (bool func(JSContext *cx, uint32_t argc, jsval *vp)) */
#define CRIJSB_FUNC_RAW(funcname, func, numargs) \
	JS_FN(funcname, func, numargs, JSPROP_PERMANENT | JSPROP_ENUMERATE)

/* Define C++ member function */
#define CRIJSB_METHOD(funcname, funcptr) \
	JS_FN(funcname, CRIJSB_METHOD_WRAPPER(funcptr), \
	(uint16_t)cribt::get_arguments_count(funcptr), \
	JSPROP_PERMANENT | JSPROP_ENUMERATE)

/* Define C++ static member function */
#define CRIJSB_STMETHOD(funcname, funcptr) \
	JS_FN(funcname, CRIJSB_FUNC_WRAPPER(funcptr), \
	(uint16_t)cribt::get_arguments_count(funcptr), \
	JSPROP_PERMANENT | JSPROP_ENUMERATE)

/* Define C++ property getter */
#define CRIJSB_GETTER_WRAPPER(getter) [](JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) { \
	void *thisptr = JS_GetPrivate(obj); \
	if (thisptr) return cribt::call_with_context(CriJsbContext(cx, vp, false), getter, thisptr); \
	else criJsbUtil_ErrorInvalidNativeObject(cx, obj); \
	return false; \
}

/* Define C++ property setter */
#define CRIJSB_SETTER_WRAPPER(setter) [](JSContext* cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) { \
	void *thisptr = JS_GetPrivate(obj); \
	if (thisptr) return cribt::call_with_context(CriJsbContext(cx, vp, true), setter, thisptr); \
	else criJsbUtil_ErrorInvalidNativeObject(cx, obj); \
	return false; \
}

/* Define C++ member function for property getter */
#define CRIJSB_PROP_GET(propname, getter)  \
	JS_PSG(propname, CRIJSB_METHOD_WRAPPER(getter), JSPROP_PERMANENT | JSPROP_ENUMERATE)

/* Define C++ member function for property getter/setter */
#define CRIJSB_PROP_BOTH(propname, getter, setter)  \
	JS_PSGS(propname, CRIJSB_METHOD_WRAPPER(getter), CRIJSB_METHOD_WRAPPER(setter), JSPROP_PERMANENT | JSPROP_ENUMERATE)

#define CRIJSB_STPROP_GET(propname, getter)  \
    JS_PSG(propname, CRIJSB_FUNC_WRAPPER(getter), JSPROP_PERMANENT | JSPROP_ENUMERATE)

#endif
