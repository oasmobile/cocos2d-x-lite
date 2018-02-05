#include <stdint.h>
#include <cri_atom_ex.h>
#include "crijsb_utility.h"
#undef OK
#include <platform/CCFileUtils.h>

//==========================================================================
// CriAtomEx JavaScript bindings
//==========================================================================
class CriJsbAtomEx
{
	static const JSClass js_class;			/* Declare JS class */
	static JSObject *js_prototype;			/* Declare JS prototype */

public:
	static void registerAcfFile(const CriChar8 *path, JS::HandleValue oncomplete, JS::HandleValue onerror) {
		/* regist acf file */
		#if defined(XPT_TGT_ANDROID)
		CriBool ret = criAtomEx_RegisterAcfFile(NULL, path, NULL, 0);
		#else
		std::string fullpath = (path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
		CriBool ret = criAtomEx_RegisterAcfFile(NULL, fullpath.c_str(), NULL, 0);
		#endif
		/* Call oncomplete/onerror if acf regist is successful */
		ScriptingCore* scritping_core = ScriptingCore::getInstance();
		JSContext* context = scritping_core->getGlobalContext();
		JS::RootedObject global(context, ScriptingCore::getInstance()->getGlobalObject());
		JS::RootedValue rval(context);
		if (ret == CRI_TRUE) {
			/* when success */
			JS_CallFunctionValue(
				context,
				global,
				oncomplete,
				JS::HandleValueArray::empty(),
				&rval
			);
		}
		else {
			/* when fail */
			JS_CallFunctionValue(
				context,
				global,
				onerror,
				JS::HandleValueArray::empty(),
				&rval
			);
		}
	}
	static void registerAcfFileById(CriFsBinderHn binder, CriUint16 id) {
		criAtomEx_RegisterAcfFileById(binder, id, NULL, 0);
	}
	static void attachDspBusSetting(const CriChar8 *name) {
		criAtomEx_AttachDspBusSetting(name, NULL, 0);
	}

	static void Register(JSContext *cx, JS::HandleObject global) {
		/* property Definition*/
		const static JSPropertySpec properties[] = {
			JS_PS_END
		};
		/* method Definition*/
		const static JSFunctionSpec funcs[] = {
			JS_FS_END
		};
		/* static method Definition*/
		const static JSFunctionSpec st_funcs[] = {
			CRIJSB_STMETHOD("registerAcfFile",					&CriJsbAtomEx::registerAcfFile),
			CRIJSB_STMETHOD("registerAcfFileById",				&CriJsbAtomEx::registerAcfFileById),
			CRIJSB_STMETHOD("unregisterAcf",					&criAtomEx_UnregisterAcf),
			CRIJSB_STMETHOD("attachDspBusSetting",				&CriJsbAtomEx::attachDspBusSetting),
			CRIJSB_STMETHOD("detachDspBusSetting",				&criAtomEx_DetachDspBusSetting),
			CRIJSB_STMETHOD("applyDspBusSnapshot",				&criAtomEx_ApplyDspBusSnapshot),
			CRIJSB_STMETHOD("setRandomSeed",					&criAtomEx_SetRandomSeed),
			JS_FS_END
		};
		/* regist for JS class */
		js_prototype = JS_InitClass(cx, global, NULL,
			&js_class, criJsbUtil_StubConstructor, 0,
			properties, funcs, NULL, st_funcs);
	}
};
/* JS class Definition */
static const JSClassOps CriJsbAtomEx_classOps = {
	nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, criJsbUtil_StubFinalize,
	nullptr, nullptr, nullptr, nullptr
};
const JSClass CriJsbAtomEx::js_class = {
	"AtomEx",
	JSCLASS_HAS_PRIVATE,
	&CriJsbAtomEx_classOps
};
/* JS prototype Definition */
JSObject *CriJsbAtomEx::js_prototype = NULL;


//==========================================================================
// CriAtomExAcb JavaScript bindings
//==========================================================================
class CriJsbAtomExAcb
{
	CriAtomExAcbHn handle;					/* ACB handle */

	static const JSClass js_class;			/* Declare JS class */
	static JSObject *js_prototype;			/* Declare JS prototype */

private:
	CriJsbAtomExAcb(CriAtomExAcbHn handle) :
		handle(handle) {
	}
	~CriJsbAtomExAcb() {
		this->release();
	}

public:
	static JSObject* loadAcbFile(const CriChar8 *acb_path, const CriChar8 *awb_path, JS::HandleValue oncomplete, JS::HandleValue onerror) {
 		/* Load acb/awb file */
        #if defined(XPT_TGT_ANDROID)
        CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(NULL, acb_path, NULL, awb_path, NULL, 0);
        #else
		std::string acb_fullpath = (acb_path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(acb_path);
		std::string awb_fullpath = (awb_path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(awb_path);
		CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(NULL, acb_fullpath.c_str(), NULL, awb_fullpath.c_str(), NULL, 0);
        #endif

		/* Call oncomplete/onerror if acb/awb loading is successful */
		ScriptingCore* scritping_core = ScriptingCore::getInstance();
		JSContext* context = scritping_core->getGlobalContext();
		JS::RootedObject global(context, ScriptingCore::getInstance()->getGlobalObject());
		JS::RootedValue rval(context);
		if (handle != CRI_NULL) {
			/* when success */
			JS_CallFunctionValue(
				scritping_core->getGlobalContext(),
				global,
				oncomplete,
				JS::HandleValueArray::empty(),
				&rval
			);
		}
		else {
			/* when fail */
			JS_CallFunctionValue(
				scritping_core->getGlobalContext(),
				global,
				onerror,
				JS::HandleValueArray::empty(),
				&rval
			);
			return nullptr;
		}

		/* Create ACB handle instance */
		CriJsbAtomExAcb* acb = new CriJsbAtomExAcb(handle);

		/* Create JS object */
		JSObject *jsobj = JS_NewObjectWithGivenProto(context, &js_class, JS::RootedObject(context, js_prototype));
		/* Set Instance */
		JS_SetPrivate(jsobj, acb);

		criJsbUtil_SetObjectInstance(context, JS::RootedObject(context, jsobj), acb->handle);

		return jsobj;
	}

	void release() {
		/* Destroy ACB */
		if (this->handle) {
			criJsbUtil_RemoveObjectInstance(this->handle);
			criAtomExAcb_Release(this->handle);
			this->handle = nullptr;
		}
	}

	static void js_finalize(JSFreeOp *fop, JSObject *jsobj) {
		CriJsbAtomExAcb* acb = (CriJsbAtomExAcb*)JS_GetPrivate(jsobj);
		if (acb) {
			delete acb;
		}
	}

	/* Create JS object of cue infomation */
	static JSObject* createCueInfo(const CriAtomExCueInfo& info) {
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();

		JS::RootedObject resobj(cx, JS_NewObjectWithGivenProto(cx, nullptr, nullptr));
		/* Set property */
		JS_SetProperty(cx, resobj, "id", JS::RootedValue(cx, JS::Int32Value(info.id)));
		JS_SetProperty(cx, resobj, "type", JS::RootedValue(cx, JS::Int32Value(info.type)));
		JS_SetProperty(cx, resobj, "name", JS::RootedValue(cx, JS::StringValue(JS_NewStringCopyZ(cx, info.name))));
		JS_SetProperty(cx, resobj, "user_data", JS::RootedValue(cx, JS::StringValue(JS_NewStringCopyZ(cx, info.user_data))));
		JS_SetProperty(cx, resobj, "length", JS::RootedValue(cx, JS::DoubleValue((double)info.length)));
		JS_SetProperty(cx, resobj, "num_limits", JS::RootedValue(cx, JS::Int32Value(info.num_limits)));
		JS_SetProperty(cx, resobj, "num_blocks", JS::RootedValue(cx, JS::Int32Value(info.num_blocks)));
		JS_SetProperty(cx, resobj, "priority", JS::RootedValue(cx, JS::Int32Value(info.priority)));
		JS_SetProperty(cx, resobj, "header_visibility", JS::RootedValue(cx, JS::BooleanValue(0 != info.header_visibility)));
		JS_SetProperty(cx, resobj, "ignore_player_parameter", JS::RootedValue(cx, JS::BooleanValue(0 != info.ignore_player_parameter)));
		/* Create JS object of category array */
		JSObject *categoriesArray = JS_NewUint16Array(cx, CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK);
		bool flag;
		memcpy(JS_GetArrayBufferViewData(categoriesArray, &flag, JS::AutoCheckCannotGC()), info.categories, sizeof(info.categories));
		JS_SetProperty(cx, resobj, "categories", JS::RootedValue(cx, JS::ObjectOrNullValue(categoriesArray)));

		return resobj;
	}
	/* Get cue infomation */
	JSObject* getCueInfoByIndex(CriSint32 index) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoByIndex(this->handle, index, &info);
		return createCueInfo(info);
	}
	/* Get cue infomation */
	JSObject* getCueInfoById(CriSint32 id) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoById(this->handle, id, &info);
		return createCueInfo(info);
	}
	/* Get cue infomation */
	JSObject* getCueInfoByName(const CriChar8 *name) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoByName(this->handle, name, &info);
		return createCueInfo(info);
	}
	/* Create JS object for AISAC controll */
	static JSObject* createAisacControlInfo(const CriAtomExAisacControlInfo& info) {
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();

		JS::RootedObject resobj(cx, JS_NewObjectWithGivenProto(cx, nullptr, nullptr));
		JS_SetProperty(cx, resobj, "id", JS::RootedValue(cx, JS::Int32Value(info.id)));
		JS_SetProperty(cx, resobj, "name", JS::RootedValue(cx, JS::StringValue(JS_NewStringCopyZ(cx, info.name))));
		return resobj;
	}
	/* Get AISAC controll */
	JSObject* getUsableAisacControlById(CriAtomExCueId id, CriUint16 index) {
		CriAtomExAisacControlInfo info;
		criAtomExAcb_GetUsableAisacControlById(this->handle, id, index, &info);
		return createAisacControlInfo(info);
	}
	/* Get AISAC controll */
	JSObject* getUsableAisacControlByName(const CriChar8 *name, CriUint16 index) {
		CriAtomExAisacControlInfo info;
		criAtomExAcb_GetUsableAisacControlByName(this->handle, name, index, &info);
		return createAisacControlInfo(info);
	}
	/* Create JS object of wave infomation */
	static JSObject* createWaveformInfo(const CriAtomExWaveformInfo& info) {
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();

		JS::RootedObject resobj(cx, JS_NewObjectWithGivenProto(cx, nullptr, nullptr));
		JS_SetProperty(cx, resobj, "wave_id", JS::RootedValue(cx, JS::Int32Value(info.wave_id)));
		JS_SetProperty(cx, resobj, "format", JS::RootedValue(cx, JS::Int32Value((int32_t)info.format)));
		JS_SetProperty(cx, resobj, "sampling_rate", JS::RootedValue(cx, JS::Int32Value(info.sampling_rate)));
		JS_SetProperty(cx, resobj, "num_channels", JS::RootedValue(cx, JS::Int32Value(info.num_channels)));
		JS_SetProperty(cx, resobj, "num_samples", JS::RootedValue(cx, JS::Int32Value((int32_t)info.num_samples)));
		JS_SetProperty(cx, resobj, "streaming_flag", JS::RootedValue(cx, JS::BooleanValue(0 != info.streaming_flag)));

		return resobj;
	}
	/* Get wave infomation */
	JSObject* getWaveformInfoById(CriAtomExCueId id) {
		CriAtomExWaveformInfo info;
		criAtomExAcb_GetWaveformInfoById(this->handle, id, &info);
		return createWaveformInfo(info);
	}
	/* Get wave infomation */
	JSObject* getWaveformInfoByName(const CriChar8 *name) {
		CriAtomExWaveformInfo info;
		criAtomExAcb_GetWaveformInfoByName(this->handle, name, &info);
		return createWaveformInfo(info);
	}

	CriSint32 getNumCues() { return criAtomExAcb_GetNumCues(this->handle); }
	bool existsId(CriAtomExCueId id) { return 0 != criAtomExAcb_ExistsId(this->handle, id); }
	bool existsName(const CriChar8 *name) { return 0 != criAtomExAcb_ExistsName(this->handle, name); }
	CriSint32 getNumUsableAisacControlsById(CriAtomExCueId id) { return criAtomExAcb_GetNumUsableAisacControlsById(this->handle, id); }
	CriSint32 getNumUsableAisacControlsByName(const CriChar8 *name) { return criAtomExAcb_GetNumUsableAisacControlsByName(this->handle, name); }
	CriSint32 getNumCuePlayingCountById(CriAtomExCueId id) { return criAtomExAcb_GetNumCuePlayingCountById(this->handle, id); }
	CriSint32 getNumCuePlayingCountByName(const CriChar8 *name) { return criAtomExAcb_GetNumCuePlayingCountByName(this->handle, name); }
	CriSint32 getBlockIndexById(CriAtomExCueId id, const CriChar8 *block_name) { return criAtomExAcb_GetBlockIndexById(this->handle, id, block_name); }
	CriSint32 getBlockIndexByName(const CriChar8 *name, const CriChar8 *block_name) { return criAtomExAcb_GetBlockIndexByName(this->handle, name, block_name); }
	void resetCueTypeStateById(CriAtomExCueId id) { criAtomExAcb_ResetCueTypeStateById(this->handle, id); }
	void resetCueTypeStateByName(const CriChar8 *name) { criAtomExAcb_ResetCueTypeStateByName(this->handle, name); }

	static void Register(JSContext *cx, JS::HandleObject global) {
		/* property definition */
		const static JSPropertySpec properties[] = {
			JS_PS_END
		};
		/* method definition */
		const static JSFunctionSpec funcs[] = {
			CRIJSB_METHOD("release",							&CriJsbAtomExAcb::release),
			CRIJSB_METHOD("getNumCues",							&CriJsbAtomExAcb::getNumCues),
			CRIJSB_METHOD("getCueInfoByIndex",					&CriJsbAtomExAcb::getCueInfoByIndex),
			CRIJSB_METHOD("getCueInfoById",						&CriJsbAtomExAcb::getCueInfoById),
			CRIJSB_METHOD("getCueInfoByName",					&CriJsbAtomExAcb::getCueInfoByName),
			CRIJSB_METHOD("existsId",							&CriJsbAtomExAcb::existsId),
			CRIJSB_METHOD("existsName",							&CriJsbAtomExAcb::existsName),
			CRIJSB_METHOD("getNumUsableAisacControlsById",		&CriJsbAtomExAcb::getNumUsableAisacControlsById),
			CRIJSB_METHOD("getNumUsableAisacControlsByName",	&CriJsbAtomExAcb::getNumUsableAisacControlsByName),
			CRIJSB_METHOD("getUsableAisacControlById",			&CriJsbAtomExAcb::getUsableAisacControlById),
			CRIJSB_METHOD("getUsableAisacControlByName",		&CriJsbAtomExAcb::getUsableAisacControlByName),
			CRIJSB_METHOD("getWaveformInfoById",				&CriJsbAtomExAcb::getWaveformInfoById),
			CRIJSB_METHOD("getWaveformInfoByName",				&CriJsbAtomExAcb::getWaveformInfoByName),
			CRIJSB_METHOD("getNumCuePlayingCountByName",		&CriJsbAtomExAcb::getNumCuePlayingCountByName),
			CRIJSB_METHOD("getNumCuePlayingCountById",			&CriJsbAtomExAcb::getNumCuePlayingCountById),
			CRIJSB_METHOD("getBlockIndexById",					&CriJsbAtomExAcb::getBlockIndexById),
			CRIJSB_METHOD("getBlockIndexByName",				&CriJsbAtomExAcb::getBlockIndexByName),
			CRIJSB_METHOD("resetCueTypeStateByName",			&CriJsbAtomExAcb::resetCueTypeStateByName),
			CRIJSB_METHOD("resetCueTypeStateById",				&CriJsbAtomExAcb::resetCueTypeStateById),
			JS_FS_END
		};
		/* static method definition */
		const static JSFunctionSpec st_funcs[] = {
			CRIJSB_STMETHOD("loadAcbFile",						&CriJsbAtomExAcb::loadAcbFile),
			CRIJSB_STMETHOD("releaseAll",						&criAtomExAcb_ReleaseAll),
			JS_FS_END
		};
		/* regist for JS class */
		js_prototype = JS_InitClass(cx, global, nullptr,
			&js_class, criJsbUtil_StubConstructor, 0,
			properties, funcs, NULL, st_funcs);
	}
};

static const JSClassOps CriJsbAtomExAcb_ClassOps{
	nullptr,nullptr,nullptr,nullptr,
	nullptr,nullptr,nullptr,CriJsbAtomExAcb::js_finalize,
	nullptr,nullptr,nullptr,nullptr
};

const JSClass CriJsbAtomExAcb::js_class = {
	"AtomExAcb",
	JSCLASS_HAS_PRIVATE,
	&CriJsbAtomExAcb_ClassOps
};
JSObject *CriJsbAtomExAcb::js_prototype = NULL;

//==========================================================================
// CriJsbAtomExPlayback JavaScript bindings
//==========================================================================
class CriJsbAtomExPlayback
{
	CriAtomExPlaybackId id;

	static const JSClass js_class;			/* Declare JS class */
	static JSObject *js_prototype;			/* Declare JS prototype */

private:
	CriJsbAtomExPlayback(CriAtomExPlaybackId id) :id(id) {}
public:
	/* Create JS object for playback */
	static JSObject* create(CriAtomExPlaybackId id) {

		/* Create handle instance */
		CriJsbAtomExPlayback* playback = new CriJsbAtomExPlayback(id);

		/* Create JSObject */
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
		JSObject *jsobj = JS_NewObjectWithGivenProto(cx, &js_class, JS::RootedObject(cx, js_prototype));
		JS_SetPrivate(jsobj, playback);

		return jsobj;
	}
		
	void Stop() { criAtomExPlayback_Stop(this->id); }
	void StopWithoutReleaseTime() { criAtomExPlayback_StopWithoutReleaseTime(this->id); }	
	void Pause(CriBool sw) { criAtomExPlayback_Pause(this->id, sw); }
	void Resume(CriAtomExResumeMode mode) { criAtomExPlayback_Resume(this->id, mode); }
	CriBool isPaused() { return criAtomExPlayback_IsPaused(this->id); }
	CriAtomExBlockIndex GetCurrentBlockIndex() { return criAtomExPlayback_GetCurrentBlockIndex(this->id); }
	void SetNextBlockIndex(CriAtomExBlockIndex index) { criAtomExPlayback_SetNextBlockIndex(this->id, index); }

	static void Register(JSContext *cx, JS::HandleObject global) {
		/* property definition */
		const static JSPropertySpec properties[] = {
			JS_PS_END
		};
		/* method definition */
		const static JSFunctionSpec funcs[] = {
			CRIJSB_METHOD("stop",							&CriJsbAtomExPlayback::Stop),
			CRIJSB_METHOD("stopWithoutReleaseTime",			&CriJsbAtomExPlayback::StopWithoutReleaseTime),
			CRIJSB_METHOD("pause",							&CriJsbAtomExPlayback::Pause),
			CRIJSB_METHOD("resume",							&CriJsbAtomExPlayback::Resume),
			CRIJSB_METHOD("isPaused",						&CriJsbAtomExPlayback::isPaused),
			CRIJSB_METHOD("getCurrentBlockIndex",			&CriJsbAtomExPlayback::GetCurrentBlockIndex),
			CRIJSB_METHOD("setNextBlockIndex",				&CriJsbAtomExPlayback::SetNextBlockIndex),
			JS_FS_END
		};

		/* static method definition */
		const static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

		/* regist for JS class */
		js_prototype = JS_InitClass(cx, global, NULL,
			&js_class, criJsbUtil_StubConstructor, 0,
			properties, funcs, NULL, st_funcs);
	}
};

static const JSClassOps CriJsbAtomExPlayback_ClassOps{
	nullptr,nullptr,nullptr,nullptr,
	nullptr,nullptr,nullptr,criJsbUtil_StubFinalize,
	nullptr,nullptr,nullptr,nullptr
};

/* JS class definition */
const JSClass CriJsbAtomExPlayback::js_class = {
	"AtomExPlayback",
	JSCLASS_HAS_PRIVATE,
	&CriJsbAtomExPlayback_ClassOps
};
/* JS prototype definition */
JSObject *CriJsbAtomExPlayback::js_prototype = NULL;

//==========================================================================
// CriAtomExPlayer JavaScript bindings
//==========================================================================
class CriJsbAtomExPlayer
{
	CriAtomExPlayerHn handle;				/* player handle */

	static const JSClass js_class;			/* JS class */
	static JSObject *js_prototype;			/* JS prototype */
        static JSObject *status_object;
private:
	CriJsbAtomExPlayer(CriAtomExPlayerHn handle) :
		handle(handle) {
	}
	~CriJsbAtomExPlayer() {
		this->destroy();
	}

public:
	/* Create JS object for player */
	static JSObject* create() {
		/* Create handle */
		CriAtomExPlayerConfig config;
		criAtomExPlayer_SetDefaultConfig(&config);
		CriAtomExPlayerHn handle = criAtomExPlayer_Create(&config, NULL, 0);
		if (handle == nullptr) {
			return nullptr;
		}

		/* Create handle instance */
		CriJsbAtomExPlayer* player = new CriJsbAtomExPlayer(handle);

		/* Create JSObject */
		JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
		JSObject *jsobj = JS_NewObjectWithGivenProto(cx, &js_class, JS::RootedObject(cx, js_prototype));
		JS_SetPrivate(jsobj, player);

		criJsbUtil_SetObjectInstance(cx, JS::RootedObject(cx, jsobj), player->handle);
		return jsobj;
	}
	/* Destroy player */
	void destroy() {
		if (this->handle) {
			criJsbUtil_RemoveObjectInstance(this->handle);
			criAtomExPlayer_Destroy(this->handle);
			this->handle = nullptr;
		}
	}
	/* finalize player */
	static void js_finalize(JSFreeOp *fop, JSObject *jsobj) {
		CriJsbAtomExPlayer* player = (CriJsbAtomExPlayer*)JS_GetPrivate(jsobj);
		if (player) {
			delete player;
		}
	}

	JSObject* prepare() {
		CriAtomExPlaybackId id = criAtomExPlayer_Prepare(this->handle);
		return CriJsbAtomExPlayback::create(id);
	}
	JSObject* start() {
		CriAtomExPlaybackId id = criAtomExPlayer_Start(this->handle);
		return CriJsbAtomExPlayback::create(id);
	}

	void setCueId(CriAtomExAcbHn acb, CriSint32 id) { criAtomExPlayer_SetCueId(this->handle, acb, id); }
	void setCueIndex(CriAtomExAcbHn acb, CriSint32 index) { criAtomExPlayer_SetCueIndex(this->handle, acb, index); }
	void setCueName(CriAtomExAcbHn acb, const CriChar8 *name) { criAtomExPlayer_SetCueName(this->handle, acb, name); }
	void setFile(CriFsBinderHn binder, const CriChar8 *file) { criAtomExPlayer_SetFile(this->handle, binder, file); }
	void setContentId(CriFsBinderHn binder, CriSint32 id) { criAtomExPlayer_SetContentId(this->handle, binder, id); }
	void setWaveId(CriAtomAwbHn awb, CriSint32 id) { criAtomExPlayer_SetWaveId(this->handle, awb, id); }
	void stop() { criAtomExPlayer_Stop(this->handle); }
	void stopWithoutReleaseTime() { criAtomExPlayer_StopWithoutReleaseTime(this->handle); }
	void pause(bool paused) { criAtomExPlayer_Pause(this->handle, paused); }
	void resume(CriAtomExResumeMode mode) { criAtomExPlayer_Resume(this->handle, mode); }
	bool isPaused() const { return 0 != criAtomExPlayer_IsPaused(this->handle); }
	CriSint64 getTime() const { return criAtomExPlayer_GetTime(this->handle); }
	CriAtomExPlayerStatus getStatus() const { return criAtomExPlayer_GetStatus(this->handle); }
	void setFormat(CriAtomExFormat format) { criAtomExPlayer_SetFormat(this->handle, format); }
	void setNumChannels(CriSint32 num_channels) { criAtomExPlayer_SetNumChannels(this->handle, num_channels); }
	void setSamplingRate(CriSint32 sampling_rate) { criAtomExPlayer_SetSamplingRate(this->handle, sampling_rate); }
	void setSoundRendererType(CriAtomSoundRendererType type) { criAtomExPlayer_SetSoundRendererType(this->handle, type); }
	void setAsrRackId(CriSint32 id) { criAtomExPlayer_SetAsrRackId(this->handle, id); }
	void setStartTime(CriSint32 time) { criAtomExPlayer_SetStartTime(this->handle, time); }
	void setSequencePrepareTime(CriSint32 time) { criAtomExPlayer_SetSequencePrepareTime(this->handle, time); }
	void update(CriAtomExPlaybackId playback_id) { criAtomExPlayer_Update(this->handle, playback_id); }
	void updateAll() { criAtomExPlayer_UpdateAll(this->handle); }
	void resetParameters() { criAtomExPlayer_ResetParameters(this->handle); }
	void setVolume(CriFloat32 volume) { criAtomExPlayer_SetVolume(this->handle, volume); }
	void setPitch(CriFloat32 pitch) { criAtomExPlayer_SetPitch(this->handle, pitch); }
	void setPan3dAngle(CriFloat32 angle) { criAtomExPlayer_SetPan3dAngle(this->handle, angle); }
	void setPan3dInteriorDistance(CriFloat32 distance) { criAtomExPlayer_SetPan3dInteriorDistance(this->handle, distance); }
	void setPan3dVolume(CriFloat32 volume) { criAtomExPlayer_SetPan3dVolume(this->handle, volume); }
	void setPanType(CriAtomExPanType type) { criAtomExPlayer_SetPanType(this->handle, type); }
	void setBandpassFileterParameters(
		CriFloat32 cof_low, CriFloat32 cof_high) {
		criAtomExPlayer_SetBandpassFilterParameters(this->handle, cof_low, cof_high);
	}
	void setBiquadFilterParameters(CriAtomExBiquadFilterType type,
		CriFloat32 frequency, CriFloat32 gain, CriFloat32 q_value) {
		criAtomExPlayer_SetBiquadFilterParameters(this->handle, type, frequency, gain, q_value);
	}
	void setVoicePriority(CriSint32 priority) { criAtomExPlayer_SetVoicePriority(this->handle, priority); }
	void setVoiceControlMethod(CriAtomExVoiceControlMethod method) { criAtomExPlayer_SetVoiceControlMethod(this->handle, method); }
	void setBusSendLevel(CriSint32 bus_index, CriFloat32 level) { criAtomExPlayer_SetBusSendLevel(this->handle, bus_index, level); }
	void setBusSendLevelOffset(CriSint32 bus_index, CriFloat32 level) { criAtomExPlayer_SetBusSendLevelOffset(this->handle, bus_index, level); }
	void setAisacControlById(CriSint32 id, CriFloat32 value) { criAtomExPlayer_SetAisacControlById(this->handle, id, value); }
	void setAisacControlByName(const CriChar8 *name, CriFloat32 value) { criAtomExPlayer_SetAisacControlByName(this->handle, name, value); }
	void set3dSourceHn(CriAtomEx3dSourceHn source) { criAtomExPlayer_Set3dSourceHn(this->handle, source); }
	void set3dListenerHn(CriAtomEx3dListenerHn listener) { criAtomExPlayer_Set3dListenerHn(this->handle, listener); }
	void setCategoryById(CriAtomExCategoryId category_id) { criAtomExPlayer_SetCategoryById(this->handle, category_id); }
	void setCategoryByName(const CriChar8 *category_name) { criAtomExPlayer_SetCategoryByName(this->handle, category_name); }
	void unsetCategory() { criAtomExPlayer_UnsetCategory(this->handle); }
	void setCuePriority(CriSint32 priority) { criAtomExPlayer_SetCuePriority(this->handle, priority); }
	void setEnvelopeAttackTime(CriFloat32 time) { criAtomExPlayer_SetEnvelopeAttackTime(this->handle, time); }
	void setEnvelopeHoldTime(CriFloat32 time) { criAtomExPlayer_SetEnvelopeHoldTime(this->handle, time); }
	void setEnvelopeDecayTime(CriFloat32 time) { criAtomExPlayer_SetEnvelopeDecayTime(this->handle, time); }
	void setEnvelopeReleaseTime(CriFloat32 time) { criAtomExPlayer_SetEnvelopeReleaseTime(this->handle, time); }
	void setEnvelopeSustainLevel(CriFloat32 level) { criAtomExPlayer_SetEnvelopeSustainLevel(this->handle, level); }
	void attachFader() { criAtomExPlayer_AttachFader(this->handle, NULL, NULL, 0); }
	void detachFader() { criAtomExPlayer_DetachFader(this->handle); }
	void setFadeOutTime(CriSint32 ms) { criAtomExPlayer_SetFadeOutTime(this->handle, ms); }
	CriSint32 getFadeOutTime() const { return criAtomExPlayer_GetFadeOutTime(this->handle); }
	void setFadeInTime(CriSint32 ms) { criAtomExPlayer_SetFadeInTime(this->handle, ms); }
	CriSint32 getFadeInTime() const { return criAtomExPlayer_GetFadeInTime(this->handle); }
	void setFadeInStartOffset(CriSint32 ms) { criAtomExPlayer_SetFadeInStartOffset(this->handle, ms); }
	CriSint32 getFadeInStartOffset() const { return criAtomExPlayer_GetFadeInStartOffset(this->handle); }
	void setFadeOutEndDelay(CriSint32 ms) { criAtomExPlayer_SetFadeOutEndDelay(this->handle, ms); }
	CriSint32 getFadeOutEndDelay() const { return criAtomExPlayer_GetFadeOutEndDelay(this->handle); }
	bool isFading() const { return 0 != criAtomExPlayer_IsFading(this->handle); }
	void resetFaderParameters() { criAtomExPlayer_ResetFaderParameters(this->handle); }
	void setFirstBlockIndex(CriSint32 index) { criAtomExPlayer_SetFirstBlockIndex(this->handle, index); }
	void setSelectorLabel(
		const CriChar8 *selector, const CriChar8 *label) {
		criAtomExPlayer_SetSelectorLabel(this->handle, selector, label);
	}
	void setRandomSeed(CriSint32 seed) { criAtomExPlayer_SetRandomSeed(this->handle, seed); }
	void limitLoopCount(CriSint32 count) { criAtomExPlayer_LimitLoopCount(this->handle, count); }

    static JSObject* getStatusObject() {
        if (CriJsbAtomExPlayer::status_object == NULL) {
            JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RootedObject object(cx, JS_NewObjectWithGivenProto(cx, nullptr, nullptr));
            JS_DefineProperty(cx, object, "STOP", (int) CRIATOMEXPLAYER_STATUS_STOP,
                          JSPROP_ENUMERATE | JSPROP_PERMANENT, NULL, NULL);
            JS_DefineProperty(cx, object, "PREP", (int) CRIATOMEXPLAYER_STATUS_PREP,
                          JSPROP_ENUMERATE | JSPROP_PERMANENT, NULL, NULL);
            JS_DefineProperty(cx, object, "PLAYING", (int) CRIATOMEXPLAYER_STATUS_PLAYING,
                          JSPROP_ENUMERATE | JSPROP_PERMANENT, NULL, NULL);
            JS_DefineProperty(cx, object, "PLAYEND", (int) CRIATOMEXPLAYER_STATUS_PLAYEND,
                          JSPROP_ENUMERATE | JSPROP_PERMANENT, NULL, NULL);
            JS_DefineProperty(cx, object, "ERROR", (int) CRIATOMEXPLAYER_STATUS_ERROR,
                          JSPROP_ENUMERATE | JSPROP_PERMANENT, NULL, NULL);
            CriJsbAtomExPlayer::status_object = object;
        }
        return CriJsbAtomExPlayer::status_object;
    }

	static void Register(JSContext *cx, JS::HandleObject global) {
		/* property definition */
		const static JSPropertySpec properties[] = {
			CRIJSB_PROP_GET("status",						&CriJsbAtomExPlayer::getStatus),
			CRIJSB_PROP_GET("time",							&CriJsbAtomExPlayer::getTime),
			CRIJSB_PROP_GET("paused",						&CriJsbAtomExPlayer::isPaused),
			JS_PS_END
		};

      		 const static JSPropertySpec st_properties[] = {
            		CRIJSB_STPROP_GET("Status",                     &CriJsbAtomExPlayer::getStatusObject),
            		JS_PS_END
        	};
         
		/* method difinition */
		const static JSFunctionSpec funcs[] = {
			CRIJSB_METHOD("destroy",						&CriJsbAtomExPlayer::destroy),
			CRIJSB_METHOD("setCueId",						&CriJsbAtomExPlayer::setCueId),
			CRIJSB_METHOD("setCueIndex",					&CriJsbAtomExPlayer::setCueIndex),
			CRIJSB_METHOD("setCueName",						&CriJsbAtomExPlayer::setCueName),
			CRIJSB_METHOD("setFile",						&CriJsbAtomExPlayer::setFile),
			CRIJSB_METHOD("setContentId",					&CriJsbAtomExPlayer::setContentId),
			CRIJSB_METHOD("setWaveId",						&CriJsbAtomExPlayer::setWaveId),
			CRIJSB_METHOD("prepare",						&CriJsbAtomExPlayer::prepare),
			CRIJSB_METHOD("start",							&CriJsbAtomExPlayer::start),
			CRIJSB_METHOD("stop",							&CriJsbAtomExPlayer::stop),
			CRIJSB_METHOD("stopWithoutReleaseTime",			&CriJsbAtomExPlayer::stopWithoutReleaseTime),
			CRIJSB_METHOD("pause",							&CriJsbAtomExPlayer::pause),
			CRIJSB_METHOD("resume",							&CriJsbAtomExPlayer::resume),
			CRIJSB_METHOD("isPaused",						&CriJsbAtomExPlayer::isPaused),
			CRIJSB_METHOD("getTime",						&CriJsbAtomExPlayer::getTime),
			CRIJSB_METHOD("getStatus",						&CriJsbAtomExPlayer::getStatus),
			CRIJSB_METHOD("setFormat",						&CriJsbAtomExPlayer::setFormat),
			CRIJSB_METHOD("setNumChannels",					&CriJsbAtomExPlayer::setNumChannels),
			CRIJSB_METHOD("setSamplingRate",				&CriJsbAtomExPlayer::setSamplingRate),
			CRIJSB_METHOD("setSoundRendererType",			&CriJsbAtomExPlayer::setSoundRendererType),
			CRIJSB_METHOD("setAsrRackId",					&CriJsbAtomExPlayer::setAsrRackId),
			CRIJSB_METHOD("setStartTime",					&CriJsbAtomExPlayer::setStartTime),
			CRIJSB_METHOD("setSequencePrepareTime",			&CriJsbAtomExPlayer::setSequencePrepareTime),
			CRIJSB_METHOD("update",							&CriJsbAtomExPlayer::update),
			CRIJSB_METHOD("updateAll",						&CriJsbAtomExPlayer::updateAll),
			CRIJSB_METHOD("resetParameters",				&CriJsbAtomExPlayer::resetParameters),
			CRIJSB_METHOD("setVolume",						&CriJsbAtomExPlayer::setVolume),
			CRIJSB_METHOD("setPitch",						&CriJsbAtomExPlayer::setPitch),
			CRIJSB_METHOD("setPan3dAngle",					&CriJsbAtomExPlayer::setPan3dAngle),
			CRIJSB_METHOD("setPan3dInteriorDistance",		&CriJsbAtomExPlayer::setPan3dInteriorDistance),
			CRIJSB_METHOD("setPan3dVolume",					&CriJsbAtomExPlayer::setPan3dVolume),
			CRIJSB_METHOD("setPanType",						&CriJsbAtomExPlayer::setPanType),
			CRIJSB_METHOD("setBandpassFileterParameters",	&CriJsbAtomExPlayer::setBandpassFileterParameters),
			CRIJSB_METHOD("setBiquadFilterParameters",		&CriJsbAtomExPlayer::setBiquadFilterParameters),
			CRIJSB_METHOD("setVoicePriority",				&CriJsbAtomExPlayer::setVoicePriority),
			CRIJSB_METHOD("setVoiceControlMethod",			&CriJsbAtomExPlayer::setVoiceControlMethod),
			CRIJSB_METHOD("setBusSendLevel",				&CriJsbAtomExPlayer::setBusSendLevel),
			CRIJSB_METHOD("setBusSendLevelOffset",			&CriJsbAtomExPlayer::setBusSendLevelOffset),
			CRIJSB_METHOD("setAisacControlById",			&CriJsbAtomExPlayer::setAisacControlById),
			CRIJSB_METHOD("setAisacControlByName",			&CriJsbAtomExPlayer::setAisacControlByName),
			CRIJSB_METHOD("set3dSourceHn",					&CriJsbAtomExPlayer::set3dSourceHn),
			CRIJSB_METHOD("set3dListenerHn",				&CriJsbAtomExPlayer::set3dListenerHn),
			CRIJSB_METHOD("setCategoryById",				&CriJsbAtomExPlayer::setCategoryById),
			CRIJSB_METHOD("setCategoryByName",				&CriJsbAtomExPlayer::setCategoryByName),
			CRIJSB_METHOD("unsetCategory",					&CriJsbAtomExPlayer::unsetCategory),
			CRIJSB_METHOD("setCuePriority",					&CriJsbAtomExPlayer::setCuePriority),
			CRIJSB_METHOD("setEnvelopeAttackTime",			&CriJsbAtomExPlayer::setEnvelopeAttackTime),
			CRIJSB_METHOD("setEnvelopeHoldTime",			&CriJsbAtomExPlayer::setEnvelopeHoldTime),
			CRIJSB_METHOD("setEnvelopeDecayTime",			&CriJsbAtomExPlayer::setEnvelopeDecayTime),
			CRIJSB_METHOD("setEnvelopeReleaseTime",			&CriJsbAtomExPlayer::setEnvelopeReleaseTime),
			CRIJSB_METHOD("setEnvelopeSustainLevel",		&CriJsbAtomExPlayer::setEnvelopeSustainLevel),
			CRIJSB_METHOD("attachFader",					&CriJsbAtomExPlayer::attachFader),
			CRIJSB_METHOD("detachFader",					&CriJsbAtomExPlayer::detachFader),
			CRIJSB_METHOD("setFadeOutTime",					&CriJsbAtomExPlayer::setFadeOutTime),
			CRIJSB_METHOD("getFadeOutTime",					&CriJsbAtomExPlayer::getFadeOutTime),
			CRIJSB_METHOD("setFadeInTime",					&CriJsbAtomExPlayer::setFadeInTime),
			CRIJSB_METHOD("getFadeInTime",					&CriJsbAtomExPlayer::getFadeInTime),
			CRIJSB_METHOD("setFadeInStartOffset",			&CriJsbAtomExPlayer::setFadeInStartOffset),
			CRIJSB_METHOD("getFadeInStartOffset",			&CriJsbAtomExPlayer::getFadeInStartOffset),
			CRIJSB_METHOD("setFadeOutEndDelay",				&CriJsbAtomExPlayer::setFadeOutEndDelay),
			CRIJSB_METHOD("getFadeOutEndDelay",				&CriJsbAtomExPlayer::getFadeOutEndDelay),
			CRIJSB_METHOD("isFading",						&CriJsbAtomExPlayer::isFading),
			CRIJSB_METHOD("resetFaderParameters",			&CriJsbAtomExPlayer::resetFaderParameters),
			CRIJSB_METHOD("setFirstBlockIndex",				&CriJsbAtomExPlayer::setFirstBlockIndex),
			CRIJSB_METHOD("setSelectorLabel",				&CriJsbAtomExPlayer::setSelectorLabel),
			CRIJSB_METHOD("setRandomSeed",					&CriJsbAtomExPlayer::setRandomSeed),
			CRIJSB_METHOD("limitLoopCount",					&CriJsbAtomExPlayer::limitLoopCount),
			JS_FS_END
		};
		/* static method difinition */
		const static JSFunctionSpec st_funcs[] = {
			CRIJSB_STMETHOD("create",						&CriJsbAtomExPlayer::create),
			JS_FS_END
		};
		/* regist for JS class */
		js_prototype = JS_InitClass(cx, global, nullptr,
			&js_class, CRIJSB_FUNC_WRAPPER(&CriJsbAtomExPlayer::create), 0,
			properties, funcs, st_properties, st_funcs);
	}
};

static const JSClassOps CriJsbAtomExPlayer_ClassOps{
	nullptr,nullptr,nullptr,nullptr,
	nullptr,nullptr,nullptr,CriJsbAtomExPlayer::js_finalize,
	nullptr,nullptr,nullptr,nullptr
};

const JSClass CriJsbAtomExPlayer::js_class = {
	"AtomExPlayer",
	JSCLASS_HAS_PRIVATE,
	&CriJsbAtomExPlayer_ClassOps
};
JSObject *CriJsbAtomExPlayer::js_prototype = NULL;

JSObject *CriJsbAtomExPlayer::status_object = NULL;


//==========================================================================
// CriJsbAtomExCategory JavaScript bindings
//==========================================================================
class CriJsbAtomExCategory
{
	static const JSClass js_class;			/* Declare JS class */
	static JSObject *js_prototype;			/* Declare JS prototype */

public:
	static void Register(JSContext *cx, JS::HandleObject global) {
		/* property definition */
		const static JSPropertySpec properties[] = {
			JS_PS_END
		};
		/* method definition */
		const static JSFunctionSpec funcs[] = {
			JS_FS_END
		};
		/* static method definition */
		const static JSFunctionSpec st_funcs[] = {
			CRIJSB_STMETHOD("setVolumeById",					&criAtomExCategory_SetVolumeById),
			CRIJSB_STMETHOD("setVolumeByName",					&criAtomExCategory_SetVolumeByName),
			CRIJSB_STMETHOD("getVolumeById",					&criAtomExCategory_GetVolumeById),
			CRIJSB_STMETHOD("getVolumeByName",					&criAtomExCategory_GetVolumeByName),
			CRIJSB_STMETHOD("pauseById",						&criAtomExCategory_PauseById),
			CRIJSB_STMETHOD("pauseByName",						&criAtomExCategory_PauseByName),
			CRIJSB_STMETHOD("isPausedById",						&criAtomExCategory_IsPausedById),
			CRIJSB_STMETHOD("isPausedByName",					&criAtomExCategory_IsPausedByName),
			CRIJSB_STMETHOD("soloById",							&criAtomExCategory_SoloById),
			CRIJSB_STMETHOD("soloByName",						&criAtomExCategory_SoloByName),
			CRIJSB_STMETHOD("isSoloedById",						&criAtomExCategory_IsSoloedById),
			CRIJSB_STMETHOD("isSoloedByName",					&criAtomExCategory_IsSoloedByName),
			JS_FS_END
		};
		/* regist for JS class */
		js_prototype = JS_InitClass(cx, global, NULL,
			&js_class, criJsbUtil_StubConstructor, 0,
			properties, funcs, NULL, st_funcs);
	}
};

static const JSClassOps CriJsbAtomExCategory_ClassOps{
	nullptr,nullptr,nullptr,nullptr,
	nullptr,nullptr,nullptr,criJsbUtil_StubFinalize,
	nullptr,nullptr,nullptr,nullptr
};

/* JS class definition */
const JSClass CriJsbAtomExCategory::js_class = {
	"AtomExCategory",
	JSCLASS_HAS_PRIVATE,
	&CriJsbAtomExCategory_ClassOps
};
/* JS prototype definition */
JSObject *CriJsbAtomExCategory::js_prototype = NULL;


/* Regist CRI ATOM to JS Context */
void criJsbAtom_Register(JSContext *cx, JS::HandleObject global)
{
	// Get the ns
	JS::RootedObject name_space(cx);
	//get_or_create_js_obj(cx, global, "cri", &ns);
	{
		const std::string name = "cri";
		JS::RootedValue nsval(cx);
		JS_GetProperty(cx, global, name.c_str(), &nsval);
		name_space.set(JS_NewPlainObject(cx));
		nsval = JS::ObjectOrNullValue(name_space);
		JS_SetProperty(cx, global, name.c_str(), nsval);
	}
	CriJsbAtomEx::Register(cx, name_space);
	CriJsbAtomExAcb::Register(cx, name_space);
	CriJsbAtomExPlayback::Register(cx, name_space);
	CriJsbAtomExPlayer::Register(cx, name_space);
	CriJsbAtomExCategory::Register(cx, name_space);
}
