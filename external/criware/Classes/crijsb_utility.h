#ifndef CRI_INCL_CRIWARE_BINDING_H
#define CRI_INCL_CRIWARE_BINDING_H

#include <stdint.h>
#include <vector>
#include <cri_xpt.h>
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "ScriptingCore.h"
#include "crijsb_binding_templates.h"

#define REGSITRY_FUNC_NAME(funcname) funcname##Registry

#define CRIJSB_DEFINE_FUNC(funcname,funcptr) \
    static bool funcname(se::State& s){ \
	return cribt::call_with_context(CriJsbContext(s), funcptr); \
} \
	SE_BIND_FUNC(funcname);

#define CRIJSB_DEFINE_METHOD(funcname,funcptr) \
    static bool funcname(se::State& s){ \
	void* thisptr = s.nativeThisObject(); \
	return cribt::call_with_context(CriJsbContext(s), funcptr, thisptr); \
} \
	SE_BIND_FUNC(funcname);

#define CRIJSB_DEFINE_FINALIZER(funcname) \
    SE_BIND_FINALIZE_FUNC(funcname); 

#define CRIJSB_DEFINE_CTOR(funcname,cls,finalizeCb) \
    SE_BIND_CTOR(funcname,cls,finalizeCb); 

#define CRIJSB_DEFINE_PROP_GET(funcname,getter) \
    bool funcname(se::State& s){ \
	void* thisptr = s.nativeThisObject(); \
	return cribt::call_with_context(CriJsbContext(s), getter, thisptr); \
} \
    SE_BIND_PROP_GET(funcname); 

#define CRIJSB_DEFINE_PROP_SET(funcname,setter) \
    bool funcname(se::State& s){ \
	void* thisptr = s.nativeThisObject(); \
	return cribt::call_with_context(CriJsbContext(s), setter, thisptr); \
} \
    SE_BIND_PROP_SET(funcname); 

#define CRIJSB_DEFINE_STPROP_GET(funcname,getter) \
    static bool funcname(se::State& s){ \
	return cribt::call_with_context(CriJsbContext(s), getter); \
} \
    SE_BIND_PROP_GET(funcname); 

#define CRIJSB_DEFINE_STPROP_SET(funcname,setter) \
    static bool funcname(se::State& s){ \
	return cribt::call_with_context(CriJsbContext(s), setter); \
} \
    SE_BIND_PROP_SET(funcname); 


/* Set C++ instance of SE object */
void criJsbUtil_SetObjectInstance(se::Object *hnobj, void *instance);
/* Remove C++ instance of SE object */
void criJsbUtil_RemoveObjectInstance(se::Object *hnobj);
/* Get C++ instance from SE object */
void *criJsbUtil_GetObjectInstance(se::Object *hnobj);
/* Get SE object from C++ instance */
se::Object *criJsbUtil_GetInstanceObject(void *instance);

//bool criJsbUtil_CommonConstructor(se::State& s) {
//	return true;
//}
//bool criJsbUtil_CommonFinalize(se::State& s){
//	return true;
//}

struct CriJsbContext
{
	/* Get argument */
	se::Value get_arg_seval(int index) const {
		if (index >= (int)state.args().size()) {
			return se::Value::Null;
		}
		return state.args()[index];
	}

	///* Set result */
	//void set_result_(const se::Value& res) const {
	//	args.rval().set(res);
	//}

	/* Get argument by JS::Value */
	se::Value get_arg(cribt::identity<se::Value>, int index) const {
		return get_arg_seval(index);
	}

	/* Get argument by character */
	const CriChar8* get_arg(cribt::identity<const CriChar8*>, int index) const {
		///* if null,undefined */
		se::Value sestr = get_arg_seval(index);

		if (sestr.isNullOrUndefined()) {
			return nullptr;
		}
		const std::string& str = sestr.toString();

		size_t remain = STRING_BUFFER_SIZE - stringOffset;
		size_t len = str.length();

		char *ptr = nullptr;
		if (len + 1 <= remain) {
			/* buffer sufficient */
			ptr = &stringBuffer[stringOffset];
			stringOffset += len + 1;
			memcpy(ptr, str.c_str(), len);
			ptr[len] = '\0';
			return ptr;
		}
		else {
			/* buffer not sufficient */
			extendedStrings.emplace_back(str);
			return extendedStrings.rbegin()->c_str();
		}
	}

	/* Get argument by bool */
	bool get_arg(cribt::identity<bool>, int index) const {
		return get_arg_seval(index).toBoolean();
	}

	/* Get argument by arithmetic */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_arithmetic<T>::value>::type* = 0) const {
		return static_cast<T>(get_arg_seval(index).toNumber());
	}

	/* Get argument by enum */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_enum<T>::value>::type* = 0) const {
		return static_cast<T>(get_arg_seval(index).toInt32());
	}

	/* Get argument by pointer */
	template <typename T>
	T get_arg(cribt::identity<T>, int index, typename std::enable_if<std::is_pointer<T>::value>::type* = 0) const {
		auto val = get_arg_seval(index);
		if (val.isObject()) {
			se::Object *seobj = val.toObject();
			return reinterpret_cast<T>(criJsbUtil_GetObjectInstance(seobj));
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
		/*set_result_(JS::NullValue());*/
		state.rval().setNull();
	}

	/* Set result by character */
	void set_result(const CriChar8* res) const {
		if (res == nullptr) {
			//set_result_(JS::NullValue());
			state.rval().setNull();
		}
		else {
			//set_result_(JS::StringValue(JS_NewStringCopyZ(cx, res)));
			state.rval().setString(res);
		}
	}

	/* Set result by bool */
	void set_result(bool res) const {
		//set_result_(JS::BooleanValue(res));
		state.rval().setBoolean(res);
	}

	/* Set result by SEObject */
	void set_result(se::Object *res) const {
		//set_result_(JS::ObjectValue(*res));
		state.rval().setObject(res);
	}
	
	/* Set result by pointer */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr) const {
		if (res) {
			/* Get SEObject from instance */
			se::Object *seobj = criJsbUtil_GetInstanceObject(res);			
			if (seobj) {
				/* Set JSObject */
				se::HandleObject hnobj(seobj);
				state.rval().setObject(hnobj);
				return;
			}
		}
		/* set null */
		state.rval().setNull();
	}

	/* Set result by integral */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr) const {
		//set_result_(JS::Int32Value((int32_t)res));
		state.rval().setInt32((int32_t)res);
	}

	/* Set result by floating point */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr) const {
		//set_result_(JS::DoubleValue((double)res));
		state.rval().setFloat((float)res);
	}

	/* Set result by enum */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr) const {
		//set_result_(JS::Int32Value((int32_t)res));
		state.rval().setInt32((int32_t)res);
	}

	/* Set result by instance(not implement) */
	template <typename T>
	void set_result(T res, typename std::enable_if<std::is_class<T>::value>::type* = nullptr) const {
		//set_result_(JS::Int32Value((int32_t)res));
		state.rval().setInt32((int32_t)res);
	}

	//CriJsbContext(JSContext *cx, uint32_t argc, JS::Value *vp)
	//	: cx(cx), args(JS::CallArgsFromVp(argc, vp)) {}
	//CriJsbContext(JSContext *cx, JS::MutableHandleValue& vp, bool setter)
	//	: cx(cx), args(JS::CallArgsFromVp(1, vp.address())) {}
	//JSContext *cx;
	//JS::CallArgs args;
	
	CriJsbContext(se::State& s)
	: state(s) {}
	se::State& state;

	static const size_t STRING_BUFFER_SIZE = 1024;
	mutable char stringBuffer[STRING_BUFFER_SIZE];
	mutable size_t stringOffset = 0;
	mutable std::vector<std::string> extendedStrings;
};

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#define CRIJSB_LAMBDA_TO_FP(type) (type)
//#else
//#define CRIJSB_LAMBDA_TO_FP(type) +
//#endif
//#define CRIJSB_LAMBDA_TO_FP(type) +
//
//#define CRIJSB_FUNC_WRAPPER(funcptr) +[](se::State& s) { \
//	return cribt::call_with_context(CriJsbContext(s), funcptr); \
//}


//#define CRIJSB_METHOD_WRAPPER(funcptr) CRIJSB_LAMBDA_TO_FP(JSNative)[](JSContext *cx, uint32_t argc, JS::Value *vp) { \
//    void *thisptr = JS_GetPrivate(JS_THIS_OBJECT(cx, vp)); \
//	if (thisptr) return cribt::call_with_context(CriJsbContext(s), funcptr, thisptr); \
//	else criJsbUtil_ErrorInvalidNativeObject(cx, JS_THIS_OBJECT(cx, vp)); \
//	return false; \
//}


///* Set C function */
//#define CRIJSB_FUNC(func) \
//	JS_FN(#func, CRIJSB_FUNC_WRAPPER(func), \
//	(uint16_t)cribt::get_arguments_count(func), \
//	JSPROP_PERMANENT | JSPROP_ENUMERATE)

///* Set Standard JS function (bool func(JSContext *cx, uint32_t argc, jsval *vp)) */
//#define CRIJSB_FUNC_RAW(funcname, func, numargs) \
//	JS_FN(funcname, func, numargs, JSPROP_PERMANENT | JSPROP_ENUMERATE)
//
///* Define C++ member function */
//#define CRIJSB_METHOD(funcname, funcptr) \
//	JS_FN(funcname, CRIJSB_METHOD_WRAPPER(funcptr), \
//	(uint16_t)cribt::get_arguments_count(funcptr), \
//	JSPROP_PERMANENT | JSPROP_ENUMERATE)
//
///* Define C++ static member function */
//#define CRIJSB_STMETHOD(funcname, funcptr) \
//	JS_FN(funcname, CRIJSB_FUNC_WRAPPER(funcptr), \
//	(uint16_t)cribt::get_arguments_count(funcptr), \
//	JSPROP_PERMANENT | JSPROP_ENUMERATE)
//
//
//
//
///* Define C++ property getter */
//#define CRIJSB_GETTER_WRAPPER(getter) [](JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) { \
//	void *thisptr = JS_GetPrivate(obj); \
//	if (thisptr) return cribt::call_with_context(CriJsbContext(cx, vp, false), getter, thisptr); \
//	else criJsbUtil_ErrorInvalidNativeObject(cx, obj); \
//	return false; \
//}
//
///* Define C++ property setter */
//#define CRIJSB_SETTER_WRAPPER(setter) [](JSContext* cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) { \
//	void *thisptr = JS_GetPrivate(obj); \
//	if (thisptr) return cribt::call_with_context(CriJsbContext(cx, vp, true), setter, thisptr); \
//	else criJsbUtil_ErrorInvalidNativeObject(cx, obj); \
//	return false; \
//}
//
///* Define C++ member function for property getter */
//#define CRIJSB_PROP_GET(propname, getter)  \
//	JS_PSG(propname, CRIJSB_METHOD_WRAPPER(getter), JSPROP_PERMANENT | JSPROP_ENUMERATE)
//
///* Define C++ member function for property getter/setter */
//#define CRIJSB_PROP_BOTH(propname, getter, setter)  \
//	JS_PSGS(propname, CRIJSB_METHOD_WRAPPER(getter), CRIJSB_METHOD_WRAPPER(setter), JSPROP_PERMANENT | JSPROP_ENUMERATE)
//
//#define CRIJSB_STPROP_GET(propname, getter)  \
//    JS_PSG(propname, CRIJSB_FUNC_WRAPPER(getter), JSPROP_PERMANENT | JSPROP_ENUMERATE)

#endif
