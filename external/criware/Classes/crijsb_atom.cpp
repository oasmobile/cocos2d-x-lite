#include <stdint.h>
#include <cri_atom_ex.h>
#include "crijsb_utility.h"
//#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#undef OK
#include <platform/CCFileUtils.h>

//==========================================================================
// CriAtomEx JavaScript bindings
//==========================================================================
class CriJsbAtomEx
{
	static se::Class*  js_class;
	static se::Object* js_prototype;

public:
	static void registerAcfFile(const CriChar8 *path, se::Value oncomplete, se::Value onerror) {
		/* regist acf file */
		#if defined(XPT_TGT_ANDROID)
		CriBool ret = criAtomEx_RegisterAcfFile(NULL, path, NULL, 0);
		#else
		std::string fullpath = (path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
		CriBool ret = criAtomEx_RegisterAcfFile(NULL, fullpath.c_str(), NULL, 0);
		#endif
		///* Call oncomplete/onerror if acf regist is successful */
		se::ScriptEngine* se = se::ScriptEngine::getInstance();
		
		if (ret == CRI_TRUE) {
			/* when success */
			if (oncomplete.isObject()) {
				se::Object* obj = oncomplete.toObject();
				if (obj->isFunction()) {
					obj->call(se::EmptyValueArray, NULL, NULL);
				}
			}
		}
		else {
			/* when fail */
			if (onerror.isObject()) {
				se::Object* obj = onerror.toObject();
				if (obj->isFunction()) {
					obj->call(se::EmptyValueArray, NULL, NULL);
				}
			}
		}
	}
	static void registerAcfFileById(CriFsBinderHn binder, CriUint16 id) {
		criAtomEx_RegisterAcfFileById(binder, id, NULL, 0);
	}
	static void attachDspBusSetting(const CriChar8 *name) {
		criAtomEx_AttachDspBusSetting(name, NULL, 0);
	}
	
	static bool Register(se::Object* obj);
};
CRIJSB_DEFINE_FUNC(AtomExregisterAcfFile,			&CriJsbAtomEx::registerAcfFile)
CRIJSB_DEFINE_FUNC(AtomExregisterAcfFileById,		&CriJsbAtomEx::registerAcfFileById)
CRIJSB_DEFINE_FUNC(AtomExunregisterAcf,				&criAtomEx_UnregisterAcf)
CRIJSB_DEFINE_FUNC(AtomExattachDspBusSetting,		&CriJsbAtomEx::attachDspBusSetting)
CRIJSB_DEFINE_FUNC(AtomExdetachDspBusSetting,		&criAtomEx_DetachDspBusSetting)
CRIJSB_DEFINE_FUNC(AtomExapplyDspBusSnapshot,		&criAtomEx_ApplyDspBusSnapshot)
CRIJSB_DEFINE_FUNC(AtomExsetRandomSeed,				&criAtomEx_SetRandomSeed)

se::Object* CriJsbAtomEx::js_prototype = nullptr;
se::Class* CriJsbAtomEx::js_class = nullptr;

bool CriJsbAtomEx::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomEx", obj, nullptr, nullptr);

	cls->defineStaticFunction("registerAcfFile",		REGSITRY_FUNC_NAME(AtomExregisterAcfFile));
	cls->defineStaticFunction("registerAcfFileById",	REGSITRY_FUNC_NAME(AtomExregisterAcfFileById));
	cls->defineStaticFunction("unregisterAcf",			REGSITRY_FUNC_NAME(AtomExunregisterAcf));
	cls->defineStaticFunction("attachDspBusSetting",	REGSITRY_FUNC_NAME(AtomExattachDspBusSetting));
	cls->defineStaticFunction("detachDspBusSetting",	REGSITRY_FUNC_NAME(AtomExdetachDspBusSetting));
	cls->defineStaticFunction("applyDspBusSnapshot",	REGSITRY_FUNC_NAME(AtomExapplyDspBusSnapshot));
	cls->defineStaticFunction("setRandomSeed",			REGSITRY_FUNC_NAME(AtomExsetRandomSeed));
	cls->install();
	//JSBClassType::registerClass<CriJsbAtomEx>(cls);

	CriJsbAtomEx::js_prototype = cls->getProto();
	CriJsbAtomEx::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

//==========================================================================
// CriAtomExAcb JavaScript bindings
//==========================================================================
class CriJsbAtomExAcb
{
	CriAtomExAcbHn handle;					/* ACB handle */

	static se::Class* js_class;			/* Declare JS class */
	static se::Object* js_prototype;			/* Declare JS prototype */

private:
	CriJsbAtomExAcb(CriAtomExAcbHn handle) :
		handle(handle) {
	}
	~CriJsbAtomExAcb() {
		this->release();
	}

public:
	static se::Object* loadAcbFile(const CriChar8 *acb_path, const CriChar8 *awb_path, se::Value oncomplete, se::Value onerror) {
 		/* Load acb/awb file */
        #if defined(XPT_TGT_ANDROID)
        CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(NULL, acb_path, NULL, awb_path, NULL, 0);
        #else
		std::string acb_fullpath = (acb_path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(acb_path);
		std::string awb_fullpath = (awb_path == nullptr) ? "" : cocos2d::FileUtils::getInstance()->fullPathForFilename(awb_path);
		CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(NULL, acb_fullpath.c_str(), NULL, awb_fullpath.c_str(), NULL, 0);
        #endif

		/* Call oncomplete/onerror if acb/awb loading is successful */
		se::ScriptEngine* se = se::ScriptEngine::getInstance();
		if (handle != CRI_NULL) {
			/* when success */
			if (oncomplete.isObject()) {
				se::Object* obj = oncomplete.toObject();
				if (obj->isFunction()) {
					obj->call(se::EmptyValueArray, NULL, NULL);
				}
			}
		}
		else {
			/* when fail */
			if (onerror.isObject()) {
				se::Object* obj = onerror.toObject();
				if (obj->isFunction()) {
					obj->call(se::EmptyValueArray, NULL, NULL);
				}
			}
			return nullptr;
		}

		/* Create ACB handle instance */
		CriJsbAtomExAcb* acb = new CriJsbAtomExAcb(handle);

		/* Create JS object */		
		se::Object *seobj = se::Object::createObjectWithClass(js_class);
		/* Set Instance */
		criJsbUtil_SetObjectInstance(seobj, acb->handle);

		return seobj;
	}

	void release() {
		/* Destroy ACB */
		if (this->handle) {
			criAtomExAcb_Release(this->handle);
			this->handle = nullptr;
		}
	}

	static void js_finalize(se::Object *seobj) {
		criJsbUtil_RemoveObjectInstance(seobj);
	}

	/* Create JS object of cue infomation */
	static se::Object* createCueInfo(const CriAtomExCueInfo& info) {
		se::Object* resobj = se::Object::createPlainObject();

		/* Set property */
		resobj->setProperty("id",						se::Value(info.id));
		resobj->setProperty("type",						se::Value(info.type));
		resobj->setProperty("name",						se::Value(info.name));
		resobj->setProperty("user_data",				se::Value(info.user_data));
		resobj->setProperty("length",					se::Value((double)info.length));
		resobj->setProperty("num_limits",				se::Value(info.num_limits));
		resobj->setProperty("num_blocks",				se::Value(info.num_blocks));
		resobj->setProperty("priority",					se::Value(info.priority));
		resobj->setProperty("header_visibility",		se::Value(info.header_visibility));
		resobj->setProperty("ignore_player_parameter",	se::Value(info.ignore_player_parameter));

		/* Create JS object of category array */
		se::Object* categoriesArray = se::Object::createArrayObject(CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK);
		for (int index = 0; index < CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK; index++) {
			categoriesArray->setArrayElement(index, se::Value(info.categories[index]));
		}
		resobj->setProperty("categories", se::Value(categoriesArray));

		return resobj;
	}
	/* Get cue infomation */
	se::Object* getCueInfoByIndex(CriSint32 index) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoByIndex(this->handle, index, &info);
		return createCueInfo(info);
	}
	/* Get cue infomation */
	se::Object* getCueInfoById(CriSint32 id) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoById(this->handle, id, &info);
		return createCueInfo(info);
	}
	/* Get cue infomation */
	se::Object* getCueInfoByName(const CriChar8 *name) {
		CriAtomExCueInfo info;
		criAtomExAcb_GetCueInfoByName(this->handle, name, &info);
		return createCueInfo(info);
	}
	/* Create JS object for AISAC controll */
	static se::Object* createAisacControlInfo(const CriAtomExAisacControlInfo& info) {
		se::Object* resobj = se::Object::createPlainObject();

		resobj->setProperty("id", se::Value(info.id));
		resobj->setProperty("name", se::Value(info.name));

		return resobj;
	}
	/* Get AISAC controll */
	se::Object* getUsableAisacControlById(CriAtomExCueId id, CriUint16 index) {
		CriAtomExAisacControlInfo info;
		criAtomExAcb_GetUsableAisacControlById(this->handle, id, index, &info);
		return createAisacControlInfo(info);
	}
	/* Get AISAC controll */
	se::Object* getUsableAisacControlByName(const CriChar8 *name, CriUint16 index) {
		CriAtomExAisacControlInfo info;
		criAtomExAcb_GetUsableAisacControlByName(this->handle, name, index, &info);
		return createAisacControlInfo(info);
	}
	/* Create JS object of wave infomation */
	static se::Object* createWaveformInfo(const CriAtomExWaveformInfo& info) {
		se::Object* resobj = se::Object::createPlainObject();
		
		resobj->setProperty("wave_id",			se::Value(info.wave_id));
		resobj->setProperty("format",			se::Value((int32_t)info.format));
		resobj->setProperty("sampling_rate",	se::Value(info.sampling_rate));
		resobj->setProperty("num_channels",		se::Value(info.num_channels));
		resobj->setProperty("num_samples",		se::Value((int32_t)info.num_samples));
		resobj->setProperty("streaming_flag",	se::Value(info.streaming_flag));

		return resobj;
	}
	/* Get wave infomation */
	se::Object* getWaveformInfoById(CriAtomExCueId id) {
		CriAtomExWaveformInfo info;
		criAtomExAcb_GetWaveformInfoById(this->handle, id, &info);
		return createWaveformInfo(info);
	}
	/* Get wave infomation */
	se::Object* getWaveformInfoByName(const CriChar8 *name) {
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

	static bool Register(se::Object* obj);
};

CRIJSB_DEFINE_METHOD(AtomExAcb_release,							&CriJsbAtomExAcb::release)
CRIJSB_DEFINE_METHOD(AtomExAcb_getNumCues,						&CriJsbAtomExAcb::getNumCues)
CRIJSB_DEFINE_METHOD(AtomExAcb_getCueInfoByIndex,				&CriJsbAtomExAcb::getCueInfoByIndex)
CRIJSB_DEFINE_METHOD(AtomExAcb_getCueInfoById,					&CriJsbAtomExAcb::getCueInfoById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getCueInfoByName,				&CriJsbAtomExAcb::getCueInfoByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_existsId,						&CriJsbAtomExAcb::existsId)
CRIJSB_DEFINE_METHOD(AtomExAcb_existsName,						&CriJsbAtomExAcb::existsName)
CRIJSB_DEFINE_METHOD(AtomExAcb_getNumUsableAisacControlsById,	&CriJsbAtomExAcb::getNumUsableAisacControlsById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getNumUsableAisacControlsByName, &CriJsbAtomExAcb::getNumUsableAisacControlsByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_getUsableAisacControlById,		&CriJsbAtomExAcb::getUsableAisacControlById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getUsableAisacControlByName,		&CriJsbAtomExAcb::getUsableAisacControlByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_getWaveformInfoById,				&CriJsbAtomExAcb::getWaveformInfoById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getWaveformInfoByName,			&CriJsbAtomExAcb::getWaveformInfoByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_getNumCuePlayingCountByName,		&CriJsbAtomExAcb::getNumCuePlayingCountByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_getNumCuePlayingCountById,		&CriJsbAtomExAcb::getNumCuePlayingCountById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getBlockIndexById,				&CriJsbAtomExAcb::getBlockIndexById)
CRIJSB_DEFINE_METHOD(AtomExAcb_getBlockIndexByName,				&CriJsbAtomExAcb::getBlockIndexByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_resetCueTypeStateByName,			&CriJsbAtomExAcb::resetCueTypeStateByName)
CRIJSB_DEFINE_METHOD(AtomExAcb_resetCueTypeStateById,			&CriJsbAtomExAcb::resetCueTypeStateById)

CRIJSB_DEFINE_FUNC(AtomExAcb_loadAcbFile,						&CriJsbAtomExAcb::loadAcbFile)
CRIJSB_DEFINE_FUNC(AtomExAcb_releaseAll,						&criAtomExAcb_ReleaseAll)

se::Object* CriJsbAtomExAcb::js_prototype = nullptr;
se::Class* CriJsbAtomExAcb::js_class = nullptr;

bool CriJsbAtomExAcb::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomExAcb", obj, nullptr, nullptr);

	cls->defineFunction("release",							REGSITRY_FUNC_NAME(AtomExAcb_release));
	cls->defineFunction("getNumCues",						REGSITRY_FUNC_NAME(AtomExAcb_getNumCues));
	cls->defineFunction("getCueInfoByIndex",				REGSITRY_FUNC_NAME(AtomExAcb_getCueInfoByIndex));
	cls->defineFunction("getCueInfoById",					REGSITRY_FUNC_NAME(AtomExAcb_getCueInfoById));
	cls->defineFunction("getCueInfoByName",					REGSITRY_FUNC_NAME(AtomExAcb_getCueInfoByName));
	cls->defineFunction("existsId",							REGSITRY_FUNC_NAME(AtomExAcb_existsId));
	cls->defineFunction("existsName",						REGSITRY_FUNC_NAME(AtomExAcb_existsName));
	cls->defineFunction("getNumUsableAisacControlsById",	REGSITRY_FUNC_NAME(AtomExAcb_getNumUsableAisacControlsById));
	cls->defineFunction("getNumUsableAisacControlsByName",	REGSITRY_FUNC_NAME(AtomExAcb_getNumUsableAisacControlsByName));
	cls->defineFunction("getUsableAisacControlById",		REGSITRY_FUNC_NAME(AtomExAcb_getUsableAisacControlById));
	cls->defineFunction("getUsableAisacControlByName",		REGSITRY_FUNC_NAME(AtomExAcb_getUsableAisacControlByName));
	cls->defineFunction("getWaveformInfoById",				REGSITRY_FUNC_NAME(AtomExAcb_getWaveformInfoById));
	cls->defineFunction("getWaveformInfoByName",			REGSITRY_FUNC_NAME(AtomExAcb_getWaveformInfoByName));
	cls->defineFunction("getNumCuePlayingCountByName",		REGSITRY_FUNC_NAME(AtomExAcb_getNumCuePlayingCountByName));
	cls->defineFunction("getNumCuePlayingCountById",		REGSITRY_FUNC_NAME(AtomExAcb_getNumCuePlayingCountById));
	cls->defineFunction("getBlockIndexById",				REGSITRY_FUNC_NAME(AtomExAcb_getBlockIndexById));
	cls->defineFunction("getBlockIndexByName",				REGSITRY_FUNC_NAME(AtomExAcb_getBlockIndexByName));
	cls->defineFunction("resetCueTypeStateByName",			REGSITRY_FUNC_NAME(AtomExAcb_resetCueTypeStateByName));
	cls->defineFunction("resetCueTypeStateById",			REGSITRY_FUNC_NAME(AtomExAcb_resetCueTypeStateById));

	cls->defineStaticFunction("loadAcbFile",				REGSITRY_FUNC_NAME(AtomExAcb_loadAcbFile));
	cls->defineStaticFunction("releaseAll",					REGSITRY_FUNC_NAME(AtomExAcb_releaseAll));
	cls->install();
	//JSBClassType::registerClass<CriJsbAtomExAcb>(cls);

	CriJsbAtomExAcb::js_prototype = cls->getProto();
	CriJsbAtomExAcb::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

//==========================================================================
// CriJsbAtomExPlayback JavaScript bindings
//==========================================================================
class CriJsbAtomExPlayback
{
	CriAtomExPlaybackId id;
private:
	CriJsbAtomExPlayback(CriAtomExPlaybackId id) :id(id) {}
public:
	static se::Object* js_prototype;			/* Declare JS prototype */
	static se::Class* js_class;			/* Declare JS class */
	static se::Object* status_object;

	/* Create JS object for playback */
	static se::Object* create(CriAtomExPlaybackId id) {

		/* Create handle instance */
		CriJsbAtomExPlayback* playback = new CriJsbAtomExPlayback(id);

		/* Create JSObject */
		se::Object* seobj = se::Object::createObjectWithClass(js_class);
		criJsbUtil_SetObjectInstance(seobj, playback);

		return seobj;
	}
	static void js_finalize(se::Object *seobj) {/*Do Nothing*/ }

	void Stop() { criAtomExPlayback_Stop(this->id); }
	void StopWithoutReleaseTime() { criAtomExPlayback_StopWithoutReleaseTime(this->id); }
	void Pause(CriBool sw) { criAtomExPlayback_Pause(this->id, sw); }
	void Resume(CriAtomExResumeMode mode) { criAtomExPlayback_Resume(this->id, mode); }
	CriBool isPaused() { return criAtomExPlayback_IsPaused(this->id); }
	CriAtomExBlockIndex GetCurrentBlockIndex() { return criAtomExPlayback_GetCurrentBlockIndex(this->id); }
	void SetNextBlockIndex(CriAtomExBlockIndex index) { criAtomExPlayback_SetNextBlockIndex(this->id, index); }
	CriAtomExPlaybackStatus GetStatus() { return criAtomExPlayback_GetStatus(this->id); }
	CriSint64 GetTime() { return criAtomExPlayback_GetTime(this->id); }
	CriSint64 GetTimeSyncedWithAudio() { return criAtomExPlayback_GetTimeSyncedWithAudio(this->id); }

	static se::Object* getStatusObject() {
		if (CriJsbAtomExPlayback::status_object == NULL) {
			se::Object* resobj = se::Object::createPlainObject();
			resobj->setProperty("PREP",		se::Value((int)CRIATOMEXPLAYBACK_STATUS_PREP));
			resobj->setProperty("PLAYING",	se::Value((int)CRIATOMEXPLAYBACK_STATUS_PLAYING));
			resobj->setProperty("REMOVED",	se::Value((int)CRIATOMEXPLAYBACK_STATUS_REMOVED));

			CriJsbAtomExPlayback::status_object = resobj;
		}
		return CriJsbAtomExPlayback::status_object;
	}

	static bool Register(se::Object* obj);
};
CRIJSB_DEFINE_STPROP_GET(AtomExPlayback_getStatusObject,	&CriJsbAtomExPlayback::getStatusObject)

CRIJSB_DEFINE_METHOD(AtomExPlayback_stop,					&CriJsbAtomExPlayback::Stop)
CRIJSB_DEFINE_METHOD(AtomExPlayback_stopWithoutReleaseTime, &CriJsbAtomExPlayback::StopWithoutReleaseTime)
CRIJSB_DEFINE_METHOD(AtomExPlayback_pause,					&CriJsbAtomExPlayback::Pause)
CRIJSB_DEFINE_METHOD(AtomExPlayback_resume,					&CriJsbAtomExPlayback::Resume)
CRIJSB_DEFINE_METHOD(AtomExPlayback_isPaused,				&CriJsbAtomExPlayback::isPaused)
CRIJSB_DEFINE_METHOD(AtomExPlayback_getCurrentBlockIndex,	&CriJsbAtomExPlayback::GetCurrentBlockIndex)
CRIJSB_DEFINE_METHOD(AtomExPlayback_setNextBlockIndex,		&CriJsbAtomExPlayback::SetNextBlockIndex)
CRIJSB_DEFINE_METHOD(AtomExPlayback_GetStatus,				&CriJsbAtomExPlayback::GetStatus)
CRIJSB_DEFINE_METHOD(AtomExPlayback_GetTime,				&CriJsbAtomExPlayback::GetTime)
CRIJSB_DEFINE_METHOD(AtomExPlayback_GetTimeSyncedWithAudio, &CriJsbAtomExPlayback::GetTimeSyncedWithAudio)

se::Object* CriJsbAtomExPlayback::js_prototype = nullptr;
se::Class* CriJsbAtomExPlayback::js_class = nullptr;
se::Object* CriJsbAtomExPlayback::status_object = nullptr;

bool CriJsbAtomExPlayback::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomExPlayback", obj, nullptr, nullptr);
	cls->defineStaticProperty("Status",							REGSITRY_FUNC_NAME(AtomExPlayback_getStatusObject), nullptr);

	cls->defineFunction("stop",									REGSITRY_FUNC_NAME(AtomExPlayback_stop));
	cls->defineFunction("stopWithoutReleaseTime",				REGSITRY_FUNC_NAME(AtomExPlayback_stopWithoutReleaseTime));
	cls->defineFunction("pause",								REGSITRY_FUNC_NAME(AtomExPlayback_pause));
	cls->defineFunction("resume",								REGSITRY_FUNC_NAME(AtomExPlayback_resume));
	cls->defineFunction("isPaused",								REGSITRY_FUNC_NAME(AtomExPlayback_isPaused));
	cls->defineFunction("getCurrentBlockIndex",					REGSITRY_FUNC_NAME(AtomExPlayback_getCurrentBlockIndex));
	cls->defineFunction("setNextBlockIndex",					REGSITRY_FUNC_NAME(AtomExPlayback_setNextBlockIndex));
	cls->defineFunction("getStatus",							REGSITRY_FUNC_NAME(AtomExPlayback_GetStatus));
	cls->defineFunction("getTime",								REGSITRY_FUNC_NAME(AtomExPlayback_GetTime));
	cls->defineFunction("getTimeSyncedWithAudio",				REGSITRY_FUNC_NAME(AtomExPlayback_GetTimeSyncedWithAudio));

	cls->install();
	//JSBClassType::registerClass<CriJsbAtomExPlayback>(cls);

	CriJsbAtomExPlayback::js_prototype = cls->getProto();
	CriJsbAtomExPlayback::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

//==========================================================================
// CriAtomExPlayer JavaScript bindings
//==========================================================================
class CriJsbAtomExPlayer
{
	CriAtomExPlayerHn handle;				/* player handle */
private:
	CriJsbAtomExPlayer(CriAtomExPlayerHn handle) :
		handle(handle) {
	}
	~CriJsbAtomExPlayer() {
		this->destroy();
	}

public:
	static se::Class* js_class;			/* Declare JS class */
	static se::Object* js_prototype;			/* Declare JS prototype */
	static se::Object* status_object;

	/* Create JS object for player */
	static se::Object* create() {
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
		se::Object* seobj = se::Object::createObjectWithClass(js_class);
		criJsbUtil_SetObjectInstance(seobj, player);

		return seobj;
	}
	/* Destroy player */
	void destroy() {
		if (this->handle) {
			criAtomExPlayer_Destroy(this->handle);
			this->handle = nullptr;
		}
	}
	/* finalize player */
	static void js_finalize(se::Object* seobj) {
		criJsbUtil_RemoveObjectInstance(seobj);
	}

	se::Object* prepare() {
		CriAtomExPlaybackId id = criAtomExPlayer_Prepare(this->handle);
		return CriJsbAtomExPlayback::create(id);
	}
	se::Object* start() {
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
	void setSilentMode(CriAtomExSilentMode mode) { criAtomExPlayer_SetSilentMode(this->handle, mode); }
	void setRandomSeed(CriSint32 seed) { criAtomExPlayer_SetRandomSeed(this->handle, seed); }
	void limitLoopCount(CriSint32 count) { criAtomExPlayer_LimitLoopCount(this->handle, count); }

    static se::Object* getStatusObject() {
        if (CriJsbAtomExPlayer::status_object == NULL) {
			se::Object* resobj = se::Object::createPlainObject();
			resobj->setProperty("STOP",			se::Value((int)CRIATOMEXPLAYER_STATUS_STOP));
			resobj->setProperty("PREP",			se::Value((int)CRIATOMEXPLAYER_STATUS_PREP));
			resobj->setProperty("PLAYING",		se::Value((int)CRIATOMEXPLAYER_STATUS_PLAYING));
			resobj->setProperty("PLAYEND",		se::Value((int)CRIATOMEXPLAYER_STATUS_PLAYEND));
			resobj->setProperty("ERROR",		se::Value((int)CRIATOMEXPLAYER_STATUS_ERROR));

            CriJsbAtomExPlayer::status_object = resobj;
        }
        return CriJsbAtomExPlayer::status_object;
    }

	static bool Register(se::Object* obj);
};

CRIJSB_DEFINE_STPROP_GET(AtomExPlayer_getStatusObject,			&CriJsbAtomExPlayer::getStatusObject)

CRIJSB_DEFINE_METHOD(AtomExPlayer_destroy,						&CriJsbAtomExPlayer::destroy)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCueId,						&CriJsbAtomExPlayer::setCueId)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCueIndex,					&CriJsbAtomExPlayer::setCueIndex)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCueName,					&CriJsbAtomExPlayer::setCueName)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFile,						&CriJsbAtomExPlayer::setFile)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setContentId,					&CriJsbAtomExPlayer::setContentId)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setWaveId,					&CriJsbAtomExPlayer::setWaveId)
CRIJSB_DEFINE_METHOD(AtomExPlayer_prepare,						&CriJsbAtomExPlayer::prepare)
CRIJSB_DEFINE_METHOD(AtomExPlayer_start,						&CriJsbAtomExPlayer::start)
CRIJSB_DEFINE_METHOD(AtomExPlayer_stop,							&CriJsbAtomExPlayer::stop)
CRIJSB_DEFINE_METHOD(AtomExPlayer_stopWithoutReleaseTime,		&CriJsbAtomExPlayer::stopWithoutReleaseTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_pause,						&CriJsbAtomExPlayer::pause)
CRIJSB_DEFINE_METHOD(AtomExPlayer_resume,						&CriJsbAtomExPlayer::resume)
CRIJSB_DEFINE_METHOD(AtomExPlayer_isPaused,						&CriJsbAtomExPlayer::isPaused)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getTime,						&CriJsbAtomExPlayer::getTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getStatus,					&CriJsbAtomExPlayer::getStatus)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFormat,					&CriJsbAtomExPlayer::setFormat)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setNumChannels,				&CriJsbAtomExPlayer::setNumChannels)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setSamplingRate,				&CriJsbAtomExPlayer::setSamplingRate)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setSoundRendererType,			&CriJsbAtomExPlayer::setSoundRendererType)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setAsrRackId,					&CriJsbAtomExPlayer::setAsrRackId)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setStartTime,					&CriJsbAtomExPlayer::setStartTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setSequencePrepareTime,		&CriJsbAtomExPlayer::setSequencePrepareTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_update,						&CriJsbAtomExPlayer::update)
CRIJSB_DEFINE_METHOD(AtomExPlayer_updateAll,					&CriJsbAtomExPlayer::updateAll)
CRIJSB_DEFINE_METHOD(AtomExPlayer_resetParameters,				&CriJsbAtomExPlayer::resetParameters)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setVolume,					&CriJsbAtomExPlayer::setVolume)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setPitch,						&CriJsbAtomExPlayer::setPitch)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setPan3dAngle,				&CriJsbAtomExPlayer::setPan3dAngle)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setPan3dInteriorDistance,		&CriJsbAtomExPlayer::setPan3dInteriorDistance)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setPan3dVolume,				&CriJsbAtomExPlayer::setPan3dVolume)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setPanType,					&CriJsbAtomExPlayer::setPanType)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setBandpassFileterParameters, &CriJsbAtomExPlayer::setBandpassFileterParameters)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setBiquadFilterParameters,	&CriJsbAtomExPlayer::setBiquadFilterParameters)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setVoicePriority,				&CriJsbAtomExPlayer::setVoicePriority)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setVoiceControlMethod,		&CriJsbAtomExPlayer::setVoiceControlMethod)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setBusSendLevel,				&CriJsbAtomExPlayer::setBusSendLevel)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setBusSendLevelOffset,		&CriJsbAtomExPlayer::setBusSendLevelOffset)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setAisacControlById,			&CriJsbAtomExPlayer::setAisacControlById)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setAisacControlByName,		&CriJsbAtomExPlayer::setAisacControlByName)
//CRIJSB_DEFINE_METHOD(AtomExPlayer_set3dSourceHn,				&CriJsbAtomExPlayer::set3dSourceHn)
//CRIJSB_DEFINE_METHOD(AtomExPlayer_set3dListenerHn,				&CriJsbAtomExPlayer::set3dListenerHn)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCategoryById,				&CriJsbAtomExPlayer::setCategoryById)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCategoryByName,			&CriJsbAtomExPlayer::setCategoryByName)
CRIJSB_DEFINE_METHOD(AtomExPlayer_unsetCategory,				&CriJsbAtomExPlayer::unsetCategory)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setCuePriority,				&CriJsbAtomExPlayer::setCuePriority)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setEnvelopeAttackTime,		&CriJsbAtomExPlayer::setEnvelopeAttackTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setEnvelopeHoldTime,			&CriJsbAtomExPlayer::setEnvelopeHoldTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setEnvelopeDecayTime,			&CriJsbAtomExPlayer::setEnvelopeDecayTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setEnvelopeReleaseTime,		&CriJsbAtomExPlayer::setEnvelopeReleaseTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setEnvelopeSustainLevel,		&CriJsbAtomExPlayer::setEnvelopeSustainLevel)
CRIJSB_DEFINE_METHOD(AtomExPlayer_attachFader,					&CriJsbAtomExPlayer::attachFader)
CRIJSB_DEFINE_METHOD(AtomExPlayer_detachFader,					&CriJsbAtomExPlayer::detachFader)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFadeOutTime,				&CriJsbAtomExPlayer::setFadeOutTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getFadeOutTime,				&CriJsbAtomExPlayer::getFadeOutTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFadeInTime,				&CriJsbAtomExPlayer::setFadeInTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getFadeInTime,				&CriJsbAtomExPlayer::getFadeInTime)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFadeInStartOffset,			&CriJsbAtomExPlayer::setFadeInStartOffset)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getFadeInStartOffset,			&CriJsbAtomExPlayer::getFadeInStartOffset)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFadeOutEndDelay,			&CriJsbAtomExPlayer::setFadeOutEndDelay)
CRIJSB_DEFINE_METHOD(AtomExPlayer_getFadeOutEndDelay,			&CriJsbAtomExPlayer::getFadeOutEndDelay)
CRIJSB_DEFINE_METHOD(AtomExPlayer_isFading,						&CriJsbAtomExPlayer::isFading)
CRIJSB_DEFINE_METHOD(AtomExPlayer_resetFaderParameters,			&CriJsbAtomExPlayer::resetFaderParameters)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setFirstBlockIndex,			&CriJsbAtomExPlayer::setFirstBlockIndex)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setSelectorLabel,				&CriJsbAtomExPlayer::setSelectorLabel)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setSilentMode,				&CriJsbAtomExPlayer::setSilentMode)
CRIJSB_DEFINE_METHOD(AtomExPlayer_setRandomSeed,				&CriJsbAtomExPlayer::setRandomSeed)
CRIJSB_DEFINE_METHOD(AtomExPlayer_limitLoopCount,				&CriJsbAtomExPlayer::limitLoopCount)

CRIJSB_DEFINE_FUNC(AtomExPlayer_create,							&CriJsbAtomExPlayer::create)

static bool AtomExPlayer_finalize(se::State& s) {
	CriAtomExPlayerHn handle = (CriAtomExPlayerHn)s.nativeThisObject();
	if (handle) {
		criAtomExPlayer_Destroy(handle);
		handle = nullptr;
	}
	return true;
}
CRIJSB_DEFINE_FINALIZER(AtomExPlayer_finalize)

static bool AtomExPlayer_constructor(se::State& s) {
	CriAtomExPlayerConfig config;
	criAtomExPlayer_SetDefaultConfig(&config);
	CriAtomExPlayerHn handle = criAtomExPlayer_Create(&config, NULL, 0);
	if (handle == nullptr) {
		return nullptr;
	}
	s.thisObject()->setPrivateData(handle);
	return true;
}
CRIJSB_DEFINE_CTOR(AtomExPlayer_constructor, CriJsbAtomExPlayer::js_class, AtomExPlayer_finalize);

se::Object* CriJsbAtomExPlayer::js_prototype = nullptr;
se::Class* CriJsbAtomExPlayer::js_class = nullptr;
se::Object* CriJsbAtomExPlayer::status_object = nullptr;

bool CriJsbAtomExPlayer::Register(se::Object* obj) {
	{
		auto cls = se::Class::create("AtomExPlayer", obj, nullptr, REGSITRY_FUNC_NAME(AtomExPlayer_constructor));
		/* property definition */
		cls->defineStaticProperty("Status",						REGSITRY_FUNC_NAME(AtomExPlayer_getStatusObject), nullptr);

		cls->defineFunction("destroy",							REGSITRY_FUNC_NAME(AtomExPlayer_destroy));
		cls->defineFunction("setCueId",							REGSITRY_FUNC_NAME(AtomExPlayer_setCueId));
		cls->defineFunction("setCueIndex",						REGSITRY_FUNC_NAME(AtomExPlayer_setCueIndex));
		cls->defineFunction("setCueName",						REGSITRY_FUNC_NAME(AtomExPlayer_setCueName));
		cls->defineFunction("setFile",							REGSITRY_FUNC_NAME(AtomExPlayer_setFile));
		cls->defineFunction("setContentId",						REGSITRY_FUNC_NAME(AtomExPlayer_setContentId));
		cls->defineFunction("setWaveId",						REGSITRY_FUNC_NAME(AtomExPlayer_setWaveId));
		cls->defineFunction("prepare",							REGSITRY_FUNC_NAME(AtomExPlayer_prepare));
		cls->defineFunction("start",							REGSITRY_FUNC_NAME(AtomExPlayer_start));
		cls->defineFunction("stop",								REGSITRY_FUNC_NAME(AtomExPlayer_stop));
		cls->defineFunction("stopWithoutReleaseTime",			REGSITRY_FUNC_NAME(AtomExPlayer_stopWithoutReleaseTime));
		cls->defineFunction("pause",							REGSITRY_FUNC_NAME(AtomExPlayer_pause));
		cls->defineFunction("resume",							REGSITRY_FUNC_NAME(AtomExPlayer_resume));
		cls->defineFunction("isPaused",							REGSITRY_FUNC_NAME(AtomExPlayer_isPaused));
		cls->defineFunction("getTime",							REGSITRY_FUNC_NAME(AtomExPlayer_getTime));
		cls->defineFunction("getStatus",						REGSITRY_FUNC_NAME(AtomExPlayer_getStatus));
		cls->defineFunction("setFormat",						REGSITRY_FUNC_NAME(AtomExPlayer_setFormat));
		cls->defineFunction("setNumChannels",					REGSITRY_FUNC_NAME(AtomExPlayer_setNumChannels));
		cls->defineFunction("setSamplingRate",					REGSITRY_FUNC_NAME(AtomExPlayer_setSamplingRate));
		cls->defineFunction("setSoundRendererType",				REGSITRY_FUNC_NAME(AtomExPlayer_setSoundRendererType));
		cls->defineFunction("setAsrRackId",						REGSITRY_FUNC_NAME(AtomExPlayer_setAsrRackId));
		cls->defineFunction("setStartTime",						REGSITRY_FUNC_NAME(AtomExPlayer_setStartTime));
		cls->defineFunction("setSequencePrepareTime",			REGSITRY_FUNC_NAME(AtomExPlayer_setSequencePrepareTime));
		cls->defineFunction("update",							REGSITRY_FUNC_NAME(AtomExPlayer_update));
		cls->defineFunction("updateAll",						REGSITRY_FUNC_NAME(AtomExPlayer_updateAll));
		cls->defineFunction("resetParameters",					REGSITRY_FUNC_NAME(AtomExPlayer_resetParameters));
		cls->defineFunction("setVolume",						REGSITRY_FUNC_NAME(AtomExPlayer_setVolume));
		cls->defineFunction("setPitch",							REGSITRY_FUNC_NAME(AtomExPlayer_setPitch));
		cls->defineFunction("setPan3dAngle",					REGSITRY_FUNC_NAME(AtomExPlayer_setPan3dAngle));
		cls->defineFunction("setPan3dInteriorDistance",			REGSITRY_FUNC_NAME(AtomExPlayer_setPan3dInteriorDistance));
		cls->defineFunction("setPan3dVolume",					REGSITRY_FUNC_NAME(AtomExPlayer_setPan3dVolume));
		cls->defineFunction("setPanType",						REGSITRY_FUNC_NAME(AtomExPlayer_setPanType));
		cls->defineFunction("setBandpassFileterParameters",		REGSITRY_FUNC_NAME(AtomExPlayer_setBandpassFileterParameters));
		cls->defineFunction("setBiquadFilterParameters",		REGSITRY_FUNC_NAME(AtomExPlayer_setBiquadFilterParameters));
		cls->defineFunction("setVoicePriority",					REGSITRY_FUNC_NAME(AtomExPlayer_setVoicePriority));
		cls->defineFunction("setVoiceControlMethod",			REGSITRY_FUNC_NAME(AtomExPlayer_setVoiceControlMethod));
		cls->defineFunction("setBusSendLevel",					REGSITRY_FUNC_NAME(AtomExPlayer_setBusSendLevel));
		cls->defineFunction("setBusSendLevelOffset",			REGSITRY_FUNC_NAME(AtomExPlayer_setBusSendLevelOffset));
		cls->defineFunction("setAisacControlById",				REGSITRY_FUNC_NAME(AtomExPlayer_setAisacControlById));
		cls->defineFunction("setAisacControlByName",			REGSITRY_FUNC_NAME(AtomExPlayer_setAisacControlByName));
		//cls->defineFunction("set3dSourceHn",					REGSITRY_FUNC_NAME(AtomExPlayer_set3dSourceHn));
		//cls->defineFunction("set3dListenerHn",					REGSITRY_FUNC_NAME(AtomExPlayer_set3dListenerHn));
		cls->defineFunction("setCategoryById",					REGSITRY_FUNC_NAME(AtomExPlayer_setCategoryById));
		cls->defineFunction("setCategoryByName",				REGSITRY_FUNC_NAME(AtomExPlayer_setCategoryByName));
		cls->defineFunction("unsetCategory",					REGSITRY_FUNC_NAME(AtomExPlayer_unsetCategory));
		cls->defineFunction("setCuePriority",					REGSITRY_FUNC_NAME(AtomExPlayer_setCuePriority));
		cls->defineFunction("setEnvelopeAttackTime",			REGSITRY_FUNC_NAME(AtomExPlayer_setEnvelopeAttackTime));
		cls->defineFunction("setEnvelopeHoldTime",				REGSITRY_FUNC_NAME(AtomExPlayer_setEnvelopeHoldTime));
		cls->defineFunction("setEnvelopeDecayTime",				REGSITRY_FUNC_NAME(AtomExPlayer_setEnvelopeDecayTime));
		cls->defineFunction("setEnvelopeReleaseTime",			REGSITRY_FUNC_NAME(AtomExPlayer_setEnvelopeReleaseTime));
		cls->defineFunction("setEnvelopeSustainLevel",			REGSITRY_FUNC_NAME(AtomExPlayer_setEnvelopeSustainLevel));
		cls->defineFunction("attachFader",						REGSITRY_FUNC_NAME(AtomExPlayer_attachFader));
		cls->defineFunction("detachFader",						REGSITRY_FUNC_NAME(AtomExPlayer_detachFader));
		cls->defineFunction("setFadeOutTime",					REGSITRY_FUNC_NAME(AtomExPlayer_setFadeOutTime));
		cls->defineFunction("getFadeOutTime",					REGSITRY_FUNC_NAME(AtomExPlayer_getFadeOutTime));
		cls->defineFunction("setFadeInTime",					REGSITRY_FUNC_NAME(AtomExPlayer_setFadeInTime));
		cls->defineFunction("getFadeInTime",					REGSITRY_FUNC_NAME(AtomExPlayer_getFadeInTime));
		cls->defineFunction("setFadeInStartOffset",				REGSITRY_FUNC_NAME(AtomExPlayer_setFadeInStartOffset));
		cls->defineFunction("getFadeInStartOffset",				REGSITRY_FUNC_NAME(AtomExPlayer_getFadeInStartOffset));
		cls->defineFunction("setFadeOutEndDelay",				REGSITRY_FUNC_NAME(AtomExPlayer_setFadeOutEndDelay));
		cls->defineFunction("getFadeOutEndDelay",				REGSITRY_FUNC_NAME(AtomExPlayer_getFadeOutEndDelay));
		cls->defineFunction("isFading",							REGSITRY_FUNC_NAME(AtomExPlayer_isFading));
		cls->defineFunction("resetFaderParameters",				REGSITRY_FUNC_NAME(AtomExPlayer_resetFaderParameters));
		cls->defineFunction("setFirstBlockIndex",				REGSITRY_FUNC_NAME(AtomExPlayer_setFirstBlockIndex));
		cls->defineFunction("setSelectorLabel",					REGSITRY_FUNC_NAME(AtomExPlayer_setSelectorLabel));
		cls->defineFunction("setSilentMode",					REGSITRY_FUNC_NAME(AtomExPlayer_setSilentMode));
		cls->defineFunction("setRandomSeed",					REGSITRY_FUNC_NAME(AtomExPlayer_setRandomSeed));
		cls->defineFunction("limitLoopCount",					REGSITRY_FUNC_NAME(AtomExPlayer_limitLoopCount));

		cls->defineStaticFunction("create",						REGSITRY_FUNC_NAME(AtomExPlayer_create));

		cls->install();
		//JSBClassType::registerClass<CriJsbAtomExPlayer>(cls);

		CriJsbAtomExPlayer::js_prototype = cls->getProto();
		CriJsbAtomExPlayer::js_class = cls;

		se::ScriptEngine::getInstance()->clearException();
		return true;
	}
}

//==========================================================================
// CriJsbAtomExCategory JavaScript bindings
//==========================================================================
class CriJsbAtomExCategory
{
public:
	static se::Object* js_prototype;			/* Declare JS prototype */
	static se::Class* js_class;			/* Declare JS class */

	static bool Register(se::Object* obj);
};
CRIJSB_DEFINE_FUNC(AtomExCategory_getNumCuePlayingCountById,	&criAtomExCategory_GetNumCuePlayingCountById)
CRIJSB_DEFINE_FUNC(AtomExCategory_getNumCuePlayingCountByName,	&criAtomExCategory_GetNumCuePlayingCountByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_setVolumeById,				&criAtomExCategory_SetVolumeById)
CRIJSB_DEFINE_FUNC(AtomExCategory_setVolumeByName,				&criAtomExCategory_SetVolumeByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_getVolumeById,				&criAtomExCategory_GetVolumeById)
CRIJSB_DEFINE_FUNC(AtomExCategory_getVolumeByName,				&criAtomExCategory_GetVolumeByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_pauseById,					&criAtomExCategory_PauseById)
CRIJSB_DEFINE_FUNC(AtomExCategory_pauseByName,					&criAtomExCategory_PauseByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_isPausedById,					&criAtomExCategory_IsPausedById)
CRIJSB_DEFINE_FUNC(AtomExCategory_isPausedByName,				&criAtomExCategory_IsPausedByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_soloById,						&criAtomExCategory_SoloById)
CRIJSB_DEFINE_FUNC(AtomExCategory_soloByName,					&criAtomExCategory_SoloByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_isSoloedById,					&criAtomExCategory_IsSoloedById)
CRIJSB_DEFINE_FUNC(AtomExCategory_isSoloedByName,				&criAtomExCategory_IsSoloedByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_muteById,						&criAtomExCategory_MuteById)
CRIJSB_DEFINE_FUNC(AtomExCategory_muteByName,					&criAtomExCategory_MuteByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_isMutedById,					&criAtomExCategory_IsMutedById)
CRIJSB_DEFINE_FUNC(AtomExCategory_isMutedByName,				&criAtomExCategory_IsMutedByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_setAisacControlById,			&criAtomExCategory_SetAisacControlById)
CRIJSB_DEFINE_FUNC(AtomExCategory_setAisacControlByName,		&criAtomExCategory_SetAisacControlByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_setFadeInTimeById,			&criAtomExCategory_SetFadeInTimeById)
CRIJSB_DEFINE_FUNC(AtomExCategory_setFadeInTimeByName,			&criAtomExCategory_SetFadeInTimeByName)
CRIJSB_DEFINE_FUNC(AtomExCategory_setFadeOutTimeById,			&criAtomExCategory_SetFadeOutTimeById)
CRIJSB_DEFINE_FUNC(AtomExCategory_setFadeOutTimeByName,			&criAtomExCategory_SetFadeOutTimeByName)

se::Object* CriJsbAtomExCategory::js_prototype = nullptr;
se::Class* CriJsbAtomExCategory::js_class = nullptr;

bool CriJsbAtomExCategory::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomExCategory", obj, nullptr, nullptr);

	cls->defineStaticFunction("getNumCuePlayingCountById",			REGSITRY_FUNC_NAME(AtomExCategory_getNumCuePlayingCountById));
	cls->defineStaticFunction("getNumCuePlayingCountByName",		REGSITRY_FUNC_NAME(AtomExCategory_getNumCuePlayingCountByName));
	cls->defineStaticFunction("setVolumeById",						REGSITRY_FUNC_NAME(AtomExCategory_setVolumeById));
	cls->defineStaticFunction("setVolumeByName",					REGSITRY_FUNC_NAME(AtomExCategory_setVolumeByName));
	cls->defineStaticFunction("getVolumeById",						REGSITRY_FUNC_NAME(AtomExCategory_getVolumeById));
	cls->defineStaticFunction("getVolumeByName",					REGSITRY_FUNC_NAME(AtomExCategory_getVolumeByName));
	cls->defineStaticFunction("pauseById",							REGSITRY_FUNC_NAME(AtomExCategory_pauseById));
	cls->defineStaticFunction("pauseByName",						REGSITRY_FUNC_NAME(AtomExCategory_pauseByName));
	cls->defineStaticFunction("isPausedById",						REGSITRY_FUNC_NAME(AtomExCategory_isPausedById));
	cls->defineStaticFunction("isPausedByName",						REGSITRY_FUNC_NAME(AtomExCategory_isPausedByName));
	cls->defineStaticFunction("soloById",							REGSITRY_FUNC_NAME(AtomExCategory_soloById));
	cls->defineStaticFunction("soloByName",							REGSITRY_FUNC_NAME(AtomExCategory_soloByName));
	cls->defineStaticFunction("isSoloedById",						REGSITRY_FUNC_NAME(AtomExCategory_isSoloedById));
	cls->defineStaticFunction("isSoloedByName",						REGSITRY_FUNC_NAME(AtomExCategory_isSoloedByName));
	cls->defineStaticFunction("muteById",							REGSITRY_FUNC_NAME(AtomExCategory_muteById));
	cls->defineStaticFunction("muteByName",							REGSITRY_FUNC_NAME(AtomExCategory_muteByName));
	cls->defineStaticFunction("isMutedById",						REGSITRY_FUNC_NAME(AtomExCategory_isMutedById));
	cls->defineStaticFunction("isMutedByName",						REGSITRY_FUNC_NAME(AtomExCategory_isMutedByName));
	cls->defineStaticFunction("setAisacControlById",				REGSITRY_FUNC_NAME(AtomExCategory_setAisacControlById));
	cls->defineStaticFunction("setAisacControlByName",				REGSITRY_FUNC_NAME(AtomExCategory_setAisacControlByName));
	cls->defineStaticFunction("setFadeInTimeById",					REGSITRY_FUNC_NAME(AtomExCategory_setFadeInTimeById));
	cls->defineStaticFunction("setFadeInTimeByName",				REGSITRY_FUNC_NAME(AtomExCategory_setFadeInTimeByName));
	cls->defineStaticFunction("setFadeOutTimeById",					REGSITRY_FUNC_NAME(AtomExCategory_setFadeOutTimeById));
	cls->defineStaticFunction("setFadeOutTimeByName",				REGSITRY_FUNC_NAME(AtomExCategory_setFadeOutTimeByName));

	cls->install();
	//JSBClassType::registerClass<CriJsbAtomExCategory>(cls);

	CriJsbAtomExCategory::js_prototype = cls->getProto();
	CriJsbAtomExCategory::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

//==========================================================================
// CriJsbAtomEx3dSource JavaScript bindings
//==========================================================================
class CriJsbAtomEx3dSource
{
	CriAtomEx3dSourceHn handle;
private:
	CriJsbAtomEx3dSource(CriAtomEx3dSourceHn handle) :
		handle(handle) {
	}
	~CriJsbAtomEx3dSource() {
		this->destroy();
	}
public:
	static se::Object* js_prototype;			/* Declare JS prototype */
	static se::Class* js_class;					/* Declare JS class */

	/* Create JS object for 3dSource */
	static se::Object* create() {
		/* Create handle */
		CriAtomEx3dSourceConfig config;
		criAtomEx3dSource_SetDefaultConfig(&config);
		CriAtomEx3dSourceHn handle = criAtomEx3dSource_Create(&config, NULL, 0);
		if (handle == nullptr) {
			return nullptr;
		}

		/* Create handle instance */
		CriJsbAtomEx3dSource* player = new CriJsbAtomEx3dSource(handle);

		/* Create JSObject */
		se::Object* seobj = se::Object::createObjectWithClass(js_class);
		criJsbUtil_SetObjectInstance(seobj, player);

		return seobj;
	}
	/* Destroy 3dSource */
	void destroy() {
		if (this->handle) {
			criAtomEx3dSource_Destroy(this->handle);
			this->handle = nullptr;
		}
	}
	/* finalize 3dSource */
	static void js_finalize(se::Object* seobj) {
		criJsbUtil_RemoveObjectInstance(seobj);
	}

	void resetParameters()													
		{ criAtomEx3dSource_ResetParameters(this->handle); }
	//void setConeOrientation()												
	//	{ criAtomEx3dSource_SetConeOrientation(this->handle); }
	void setConeParameter(CriFloat32 inside_angle, CriFloat32 outside_angle, CriFloat32 outside_volume)	
		{ criAtomEx3dSource_SetConeParameter(this->handle, inside_angle, outside_angle, outside_volume); }
	void setDistanceAisacControlId(CriUint16 aisac_control_id)
		{ criAtomEx3dSource_SetDistanceAisacControlId(this->handle, aisac_control_id); }
	void setDopplerFactor(CriFloat32 doppler_factor)						
		{ criAtomEx3dSource_SetDopplerFactor(this->handle, doppler_factor); }
	void setListenerBasedAngleAisacControlId(CriUint16 aisac_control_id)
		{ criAtomEx3dSource_SetListenerBasedAngleAisacControlId(this->handle, aisac_control_id); }
	void setSourceBasedAngleAisacControlId(CriUint16 aisac_control_id)
		{ criAtomEx3dSource_SetSourceBasedAngleAisacControlId(this->handle, aisac_control_id); }
	void setMaxAngleAisacDelta(CriFloat32 max_delta)
		{ criAtomEx3dSource_SetMaxAngleAisacDelta(this->handle, max_delta); }
	void setMinMaxAttenuationDistance(CriFloat32 min_attenuation_distance,	CriFloat32 max_attenuation_distance)
		{ criAtomEx3dSource_SetMinMaxAttenuationDistance(this->handle, min_attenuation_distance, max_attenuation_distance); }
	//void setPosition()
	//	{ criAtomEx3dSource_SetPosition(this->handle); }
	//void setVelocity()
	//	{ criAtomEx3dSource_SetVelocity(this->handle); }
	void setVolume(CriFloat32 volume)
		{ criAtomEx3dSource_SetVolume(this->handle, volume); }
	void update()
		{ criAtomEx3dSource_Update(this->handle); }

	static bool Register(se::Object* obj);
};

CRIJSB_DEFINE_METHOD(AtomEx3dSource_destroy,								&CriJsbAtomEx3dSource::destroy)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_resetParameters,						&CriJsbAtomEx3dSource::resetParameters)
//CRIJSB_DEFINE_METHOD(AtomEx3dSource_setConeOrientation,						&CriJsbAtomEx3dSource::setConeOrientation)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setConeParameter,						&CriJsbAtomEx3dSource::setConeParameter)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setDistanceAisacControlId,				&CriJsbAtomEx3dSource::setDistanceAisacControlId)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setDopplerFactor,						&CriJsbAtomEx3dSource::setDopplerFactor)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setListenerBasedAngleAisacControlId,	&CriJsbAtomEx3dSource::setListenerBasedAngleAisacControlId)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setSourceBasedAngleAisacControlId,		&CriJsbAtomEx3dSource::setSourceBasedAngleAisacControlId)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setMaxAngleAisacDelta,					&CriJsbAtomEx3dSource::setMaxAngleAisacDelta)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setMinMaxAttenuationDistance,			&CriJsbAtomEx3dSource::setMinMaxAttenuationDistance)
//CRIJSB_DEFINE_METHOD(AtomEx3dSource_setPosition,							&CriJsbAtomEx3dSource::setPosition)
//CRIJSB_DEFINE_METHOD(AtomEx3dSource_setVelocity,							&CriJsbAtomEx3dSource::setVelocity)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_setVolume,								&CriJsbAtomEx3dSource::setVolume)
CRIJSB_DEFINE_METHOD(AtomEx3dSource_update,									&CriJsbAtomEx3dSource::update)

CRIJSB_DEFINE_FUNC(AtomEx3dSource_changeDefaultConeParameter,				&criAtomEx3dSource_ChangeDefaultConeParameter)
CRIJSB_DEFINE_FUNC(AtomEx3dSource_changeDefaultDopplerFactor,				&criAtomEx3dSource_ChangeDefaultDopplerFactor)
CRIJSB_DEFINE_FUNC(AtomEx3dSource_changeDefaultMinMaxDistance,				&criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance)
CRIJSB_DEFINE_FUNC(AtomEx3dSource_changeDefaultDefaultVolume,				&criAtomEx3dSource_ChangeDefaultVolume)
CRIJSB_DEFINE_FUNC(AtomEx3dSource_create,									&CriJsbAtomEx3dSource::create)

se::Object* CriJsbAtomEx3dSource::js_prototype = nullptr;
se::Class* CriJsbAtomEx3dSource::js_class = nullptr;

bool CriJsbAtomEx3dSource::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomEx3dSource", obj, nullptr, nullptr);

	cls->defineFunction("destroy",									REGSITRY_FUNC_NAME(AtomEx3dSource_destroy));
	cls->defineFunction("resetParameters",							REGSITRY_FUNC_NAME(AtomEx3dSource_resetParameters));
	cls->defineFunction("update",									REGSITRY_FUNC_NAME(AtomEx3dSource_update));

	cls->defineStaticFunction("changeDefaultConeParameter",			REGSITRY_FUNC_NAME(AtomEx3dSource_changeDefaultConeParameter));
	cls->defineStaticFunction("changeDefaultDopplerFactor",			REGSITRY_FUNC_NAME(AtomEx3dSource_changeDefaultDopplerFactor));
	cls->defineStaticFunction("changeDefaultMinMaxDistance",		REGSITRY_FUNC_NAME(AtomEx3dSource_changeDefaultMinMaxDistance));
	cls->defineStaticFunction("changeDefaultDefaultVolume",			REGSITRY_FUNC_NAME(AtomEx3dSource_changeDefaultDefaultVolume));
	cls->defineStaticFunction("create",								REGSITRY_FUNC_NAME(AtomEx3dSource_create));

	cls->install();
	//JSBClassType::registerClass<CriJsbAtomEx3dSource>(cls);

	CriJsbAtomEx3dSource::js_prototype = cls->getProto();
	CriJsbAtomEx3dSource::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

//==========================================================================
// CriJsbAtomEx3dListener JavaScript bindings
//==========================================================================
class CriJsbAtomEx3dListener
{
	CriAtomEx3dListenerHn handle;
private:
	CriJsbAtomEx3dListener(CriAtomEx3dListenerHn handle) :
		handle(handle) {
	}
	~CriJsbAtomEx3dListener() {
		this->destroy();
	}
public:
	static se::Object* js_prototype;			/* Declare JS prototype */
	static se::Class* js_class;					/* Declare JS class */

	/* Create JS object for 3dListener */
	static se::Object* create() {
		/* Create handle */
		CriAtomEx3dListenerConfig config;
		criAtomEx3dListener_SetDefaultConfig(&config);
		CriAtomEx3dListenerHn handle = criAtomEx3dListener_Create(&config, NULL, 0);
		if (handle == nullptr) {
			return nullptr;
		}

		/* Create handle instance */
		CriJsbAtomEx3dListener* player = new CriJsbAtomEx3dListener(handle);

		/* Create JSObject */
		se::Object* seobj = se::Object::createObjectWithClass(js_class);
		criJsbUtil_SetObjectInstance(seobj, player);

		return seobj;
	}
	/* Destroy 3dListener */
	void destroy() {
		if (this->handle) {
			criAtomEx3dListener_Destroy(this->handle);
			this->handle = nullptr;
		}
	}
	/* finalize 3dListener */
	static void js_finalize(se::Object* seobj) {
		criJsbUtil_RemoveObjectInstance(seobj);
	}

	void resetParameters()												{ criAtomEx3dListener_ResetParameters(this->handle); }
	void setDirectionFocusLevel(CriFloat32 direction_focus_level)		{ criAtomEx3dListener_SetDirectionFocusLevel(this->handle, direction_focus_level); }
	void setDistanceFactor(CriFloat32 distance_factor)					{ criAtomEx3dListener_SetDistanceFactor(this->handle, distance_factor); }
	void setDistanceFocusLevel(CriFloat32 distance_focus_level)			{ criAtomEx3dListener_SetDistanceFocusLevel(this->handle, distance_focus_level); }
	//void setFocusPoint()												{ criAtomEx3dListener_SetFocusPoint(this->handle); }
	//void setOrientation()												{ criAtomEx3dListener_SetOrientation(this->handle); }
	//void setPosition()													{ criAtomEx3dListener_SetPosition(this->handle); }
	//void setVelocity()													{ criAtomEx3dListener_SetVelocity(this->handle); }
	void update()														{ criAtomEx3dListener_Update(this->handle); }

	static bool Register(se::Object* obj);
};

CRIJSB_DEFINE_METHOD(AtomEx3dListener_destroy,					&CriJsbAtomEx3dListener::destroy)
CRIJSB_DEFINE_METHOD(AtomEx3dListener_resetParameters,			&CriJsbAtomEx3dListener::resetParameters)
CRIJSB_DEFINE_METHOD(AtomEx3dListener_setDirectionFocusLevel,	&CriJsbAtomEx3dListener::setDirectionFocusLevel)
CRIJSB_DEFINE_METHOD(AtomEx3dListener_setDistanceFactor,		&CriJsbAtomEx3dListener::setDistanceFactor)
CRIJSB_DEFINE_METHOD(AtomEx3dListener_setDistanceFocusLevel,	&CriJsbAtomEx3dListener::setDistanceFocusLevel)
//CRIJSB_DEFINE_METHOD(AtomEx3dListener_setFocusPoint,			&CriJsbAtomEx3dListener::setFocusPoint)
//CRIJSB_DEFINE_METHOD(AtomEx3dListener_setOrientation,			&CriJsbAtomEx3dListener::setOrientation)
//CRIJSB_DEFINE_METHOD(AtomEx3dListener_setPosition,				&CriJsbAtomEx3dListener::setPosition)
//CRIJSB_DEFINE_METHOD(AtomEx3dListener_setVelocity,				&CriJsbAtomEx3dListener::setVelocity)
CRIJSB_DEFINE_METHOD(AtomEx3dListener_update,					&CriJsbAtomEx3dListener::update)

CRIJSB_DEFINE_FUNC(AtomEx3dListener_create,						&CriJsbAtomEx3dListener::create)

se::Object* CriJsbAtomEx3dListener::js_prototype = nullptr;
se::Class* CriJsbAtomEx3dListener::js_class = nullptr;

bool CriJsbAtomEx3dListener::Register(se::Object* obj) {
	auto cls = se::Class::create("AtomEx3dListener", obj, nullptr, nullptr);

	cls->defineFunction("destroy",					REGSITRY_FUNC_NAME(AtomEx3dListener_destroy));
	cls->defineFunction("resetParameters",			REGSITRY_FUNC_NAME(AtomEx3dListener_resetParameters));
	cls->defineFunction("setDirectionFocusLevel",	REGSITRY_FUNC_NAME(AtomEx3dListener_setDirectionFocusLevel));
	cls->defineFunction("setDistanceFactor",		REGSITRY_FUNC_NAME(AtomEx3dListener_setDistanceFactor));
	cls->defineFunction("setDistanceFocusLevel",	REGSITRY_FUNC_NAME(AtomEx3dListener_setDistanceFocusLevel));
	//cls->defineFunction("setFocusPoint",			REGSITRY_FUNC_NAME(AtomEx3dListener_setFocusPoint));
	//cls->defineFunction("setOrientation",			REGSITRY_FUNC_NAME(AtomEx3dListener_setOrientation));
	//cls->defineFunction("setPosition",				REGSITRY_FUNC_NAME(AtomEx3dListener_setPosition));
	//cls->defineFunction("setVelocity",				REGSITRY_FUNC_NAME(AtomEx3dListener_setVelocity));
	cls->defineFunction("update",					REGSITRY_FUNC_NAME(AtomEx3dListener_update));

	cls->defineStaticFunction("create",				REGSITRY_FUNC_NAME(AtomEx3dListener_create));

	cls->install();
	//JSBClassType::registerClass<CriJsbAtomEx3dListener>(cls);

	CriJsbAtomEx3dListener::js_prototype = cls->getProto();
	CriJsbAtomEx3dListener::js_class = cls;

	se::ScriptEngine::getInstance()->clearException();
	return true;
}

/* Regist CRI ATOM */
bool criJsbAtom_Register(se::Object* global)
{
	se::Value nsVal;
	if (!global->getProperty("cri", &nsVal))
	{
		se::HandleObject jsobj(se::Object::createPlainObject());
		nsVal.setObject(jsobj);
		global->setProperty("cri", nsVal);
	}
	se::Object* ns = nsVal.toObject();

	CriJsbAtomEx::Register(ns);
	CriJsbAtomExAcb::Register(ns);
	CriJsbAtomExPlayback::Register(ns);
	CriJsbAtomExPlayer::Register(ns);
	CriJsbAtomExCategory::Register(ns);
	CriJsbAtomEx3dSource::Register(ns);
	CriJsbAtomEx3dListener::Register(ns);

	{
		se::Value AtomExBiquadFilterType;
		se::HandleObject resobj(se::Object::createPlainObject());
		resobj->setProperty("OFF", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_OFF));
		resobj->setProperty("LOWPASS", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_LOWPASS));
		resobj->setProperty("HIGHPASS", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_HIGHPASS));
		resobj->setProperty("NOTCH", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_NOTCH));
		resobj->setProperty("LOWSHELF", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_LOWSHELF));
		resobj->setProperty("HIGHSHELF", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_HIGHSHELF));		
		resobj->setProperty("PEAKING", se::Value((int)CRIATOMEX_BIQUAD_FILTER_TYPE_PEAKING));
		AtomExBiquadFilterType.setObject(resobj);
		ns->setProperty("AtomExBiquadFilterType", AtomExBiquadFilterType);
	}

	{
		se::Value AtomExPanType;
		se::HandleObject resobj(se::Object::createPlainObject());
		resobj->setProperty("PAN3D", se::Value((int)CRIATOMEX_PAN_TYPE_PAN3D));
		resobj->setProperty("POS3D", se::Value((int)CRIATOMEX_PAN_TYPE_3D_POS));
		resobj->setProperty("AUTO", se::Value((int)CRIATOMEX_PAN_TYPE_AUTO));
		AtomExPanType.setObject(resobj);
		ns->setProperty("AtomExPanType", AtomExPanType);
	}

	{
		se::Value AtomExResumeMode;
		se::HandleObject resobj(se::Object::createPlainObject());
		resobj->setProperty("ALL_PLAYBACK", se::Value((int)CRIATOMEX_RESUME_ALL_PLAYBACK));
		resobj->setProperty("PAUSED_PLAYBACK", se::Value((int)CRIATOMEX_RESUME_PAUSED_PLAYBACK));
		resobj->setProperty("PREPARED_PLAYBACK", se::Value((int)CRIATOMEX_RESUME_PREPARED_PLAYBACK));
		AtomExResumeMode.setObject(resobj);
		ns->setProperty("AtomExResumeMode", AtomExResumeMode);
	}

	{
		se::Value AtomExSilentMode;
		se::HandleObject resobj(se::Object::createPlainObject());
		resobj->setProperty("NORMAL", se::Value((int)CRIATOMEX_SILENT_MODE_NORMAL));
		resobj->setProperty("STOP", se::Value((int)CRIATOMEX_SILENT_MODE_STOP));
		resobj->setProperty("VIRTUAL", se::Value((int)CRIATOMEX_SILENT_MODE_VIRTUAL));
		resobj->setProperty("VIRTUAL_RETRIGGER", se::Value((int)CRIATOMEX_SILENT_MODE_VIRTUAL_RETRIGGER));
		AtomExSilentMode.setObject(resobj);
		ns->setProperty("AtomExSilentMode", AtomExSilentMode);
	}

	{
		se::Value AtomExVoiceControlMethod;
		se::HandleObject resobj(se::Object::createPlainObject());
		resobj->setProperty("PREFER_LAST", se::Value((int)CRIATOMEX_PREFER_LAST));
		resobj->setProperty("PREFER_FIRST", se::Value((int)CRIATOMEX_PREFER_FIRST));
		resobj->setProperty("PREFER_DATA", se::Value((int)CRIATOMEX_PREFER_DATA));
		AtomExVoiceControlMethod.setObject(resobj);
		ns->setProperty("AtomExVoiceControlMethod", AtomExVoiceControlMethod);
	}
	return true;
}
