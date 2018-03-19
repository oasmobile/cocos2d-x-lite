#include <cocos2d.h>
#include <cri_xpt.h>

/*=========================================================================*/
#if defined(XPT_TGT_PC)
#include <Windows.h>
#include "cri_atom_wasapi.h"
#define CriAtomExConfig_XXX				CriAtomExConfig_WASAPI
#define criAtomEx_SetDefaultConfig_XXX	criAtomEx_SetDefaultConfig_WASAPI
#define criAtomEx_Initialize_XXX		criAtomEx_Initialize_WASAPI
#define criAtomEx_Finalize_XXX			criAtomEx_Finalize_WASAPI
/*=========================================================================*/
#elif defined(XPT_TGT_MACOSX)
#include <cri_atom_macosx.h>
#define CriAtomExConfig_XXX				CriAtomExConfig_MACOSX
#define criAtomEx_SetDefaultConfig_XXX	criAtomEx_SetDefaultConfig_MACOSX
#define criAtomEx_Initialize_XXX		criAtomEx_Initialize_MACOSX
#define criAtomEx_Finalize_XXX			criAtomEx_Finalize_MACOSX
/*=========================================================================*/
#elif defined(XPT_TGT_IOS)
#include <cri_atom_ios.h>
#define CriAtomExConfig_XXX				CriAtomExConfig_IOS
#define criAtomEx_SetDefaultConfig_XXX	criAtomEx_SetDefaultConfig_IOS
#define criAtomEx_Initialize_XXX		criAtomEx_Initialize_IOS
#define criAtomEx_Finalize_XXX			criAtomEx_Finalize_IOS
/*=========================================================================*/
#elif defined(XPT_TGT_ANDROID)
#include <platform/android/jni/JniHelper.h>
#include <cri_atom_android.h>
#include <cri_file_system_android.h>
#define CriAtomExConfig_XXX				CriAtomExConfig_ANDROID
#define criAtomEx_SetDefaultConfig_XXX	criAtomEx_SetDefaultConfig_ANDROID
#define criAtomEx_Initialize_XXX		criAtomEx_Initialize_ANDROID
#define criAtomEx_Finalize_XXX			criAtomEx_Finalize_ANDROID
#endif
//#if defined(CRI_ATOM_MONITOR)
#include "cri_atom_ex_monitor.h"
//#endif
#include "cricocos2d_initializer.h"

typedef struct CriJSBConfig
{
	CriSint32	max_virtual_voices;
	CriSint32	max_voice_limit_groups;
	CriSint32	max_categories;
	CriSint32	num_standard_memory_voices;
	CriSint32	num_standard_streaming_voices;
	CriSint32	num_hca_mx_memory_voices;
	CriSint32	num_hca_mx_streaming_voices;
	CriSint32	output_sampling_rate;
	CriSint32	num_asr_output_channels;
	CriBool		uses_in_game_preview;
	CriFloat32	server_frequency;
	CriSint32	max_parameter_blocks;
	CriSint32	categories_per_playback;
	CriSint32	num_buses;
} CriJSBConfig;

typedef struct CriJSBContext
{
	CriBool								is_initialized;
	CriJSBConfig						config;

	CriAtomExDbasId						dbas_id;

	CriAtomExVoicePoolHn				standard_onmemory_voice_pool;
	CriAtomExVoicePoolHn				standard_streaming_voice_pool;
	CriAtomExVoicePoolHn				hca_mx_onmemory_voice_pool;
	CriAtomExVoicePoolHn				hca_mx_streaming_voice_pool;
}CriJSBContext;

static CriJSBContext crijsb_cx = { CRI_FALSE };

static CriSint32	max_standard_memory_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE * 4;
static CriSint32	max_standard_streaming_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE * 4;

static void crijsb_SetDefaultConfig(CriJSBConfig* config)
{
	config->max_virtual_voices = 32;
	config->max_voice_limit_groups = 32;
	config->max_categories = 32;
	config->num_standard_memory_voices = 16;
	config->num_standard_streaming_voices = 8;
	config->num_hca_mx_memory_voices = 0;
	config->num_hca_mx_streaming_voices = 0;
	config->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;
	config->uses_in_game_preview = CRI_TRUE;
	config->server_frequency = 60.0f;
	config->max_parameter_blocks = 1024;
	config->categories_per_playback = 4;
	config->num_buses = CRIATOMEXASR_DEFAULT_NUM_BASES;
}

class CriWareAutoExecuter
{
public:
	void update(float dt) {

	}
};
static CriWareAutoExecuter criware_executer;

/* Default callback function */
void criWare_ErrorCallback(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8* errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	CCLOG("[CRIWARE] ERROR: %s\n", errmsg);
}

/* Default memory allocation function */
void* criWare_MemAlloc(void*, CriUint32 size)
{
	return malloc((size_t)size);
}

/* Default memory free function */
void criWare_MemFree(void*, void* ptr)
{
	free(ptr);
}

void CRICOCOS2D::criWare_Initialize()
{
	CriFsConfig			fs_config;
	CriAtomExConfig_XXX	config;
	CriSint32			total_streaming_voices;

	if (crijsb_cx.is_initialized) {
		CCLOG("[CRIWARE] ERROR: CRIWARE is already initialized.\n");
		return;
	}
		
	/* Set error callback */
	criErr_SetCallback(criWare_ErrorCallback);

	criFs_SetUserAllocator(criWare_MemAlloc, criWare_MemFree, NULL);
	criFs_SetDefaultConfig(&fs_config);
	criFs_Initialize(fs_config, NULL, 0);

	/* Set initialize config */
	crijsb_SetDefaultConfig(&crijsb_cx.config);
	criAtomEx_SetUserAllocator(criWare_MemAlloc, criWare_MemFree, NULL);
	criAtomEx_SetDefaultConfig_XXX(&config);
	config.atom_ex.server_frequency = crijsb_cx.config.server_frequency;
	config.atom_ex.max_virtual_voices = crijsb_cx.config.max_virtual_voices;
	config.atom_ex.max_voice_limit_groups = crijsb_cx.config.max_voice_limit_groups;
	config.atom_ex.max_categories = crijsb_cx.config.max_categories;
	config.atom_ex.max_sequences = crijsb_cx.config.max_virtual_voices;
	config.atom_ex.max_tracks = crijsb_cx.config.max_virtual_voices * 2;
	config.atom_ex.max_track_items = crijsb_cx.config.max_virtual_voices * 2;
	config.atom_ex.max_parameter_blocks = crijsb_cx.config.max_parameter_blocks;
	config.atom_ex.categories_per_playback = crijsb_cx.config.categories_per_playback;
	criAtomEx_Initialize_XXX(&config, NULL, 0);
	
//#if defined(CRI_ATOM_MONITOR)
	if (crijsb_cx.config.uses_in_game_preview != CRI_FALSE) {
		/* In-game preview initialize */
		criAtomExMonitor_Initialize(NULL, NULL, 0);
		criAtomMeter_AttachLoudnessMeter(NULL, NULL, 0);
}
//#endif

	/* PerformanceMonitor initialize */
	criAtom_AttachPerformanceMonitor();
	criAtom_ResetPerformanceMonitor();

	total_streaming_voices =
		crijsb_cx.config.num_standard_streaming_voices + crijsb_cx.config.num_hca_mx_streaming_voices;

	/* Create D-BAS */
	if (total_streaming_voices > 0) {
		CriAtomExDbasConfig	dbas_config;
		criAtomExDbas_SetDefaultConfig(&dbas_config);
		dbas_config.max_streams = total_streaming_voices;
		dbas_config.max_bps = 384 * 1000 * total_streaming_voices;
		crijsb_cx.dbas_id = criAtomExDbas_Create(&dbas_config, NULL, 0);
	}

#pragma region Voicepool
	/* Create standard voice pool */
	if (crijsb_cx.config.num_standard_memory_voices > 0) {
		CriAtomExStandardVoicePoolConfig	standard_pool_config;
		criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&standard_pool_config);
		standard_pool_config.num_voices = crijsb_cx.config.num_standard_memory_voices;
		standard_pool_config.player_config.max_sampling_rate = max_standard_memory_sampling_rate;
		standard_pool_config.player_config.streaming_flag = CRI_FALSE;
		crijsb_cx.standard_onmemory_voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&standard_pool_config, NULL, 0);
	}
	else {
		crijsb_cx.standard_onmemory_voice_pool = NULL;
	}

	/* Create steaming voice pool */
	if (crijsb_cx.config.num_standard_streaming_voices > 0) {
		CriAtomExStandardVoicePoolConfig	standard_pool_config;
		criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&standard_pool_config);
		standard_pool_config.num_voices = crijsb_cx.config.num_standard_streaming_voices;
		standard_pool_config.player_config.max_sampling_rate = max_standard_streaming_sampling_rate;
		standard_pool_config.player_config.streaming_flag = CRI_TRUE;
		crijsb_cx.standard_streaming_voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&standard_pool_config, NULL, 0);
	}
	else {
		crijsb_cx.standard_streaming_voice_pool = NULL;
	}

	/* Create HCA-MX memory voice pool */
	if (crijsb_cx.config.num_hca_mx_memory_voices > 0) {
		CriAtomExHcaMxVoicePoolConfig		hca_mx_pool_config;
		criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hca_mx_pool_config);
		hca_mx_pool_config.num_voices = crijsb_cx.config.num_hca_mx_memory_voices;
		hca_mx_pool_config.player_config.max_sampling_rate = crijsb_cx.config.output_sampling_rate;
		hca_mx_pool_config.player_config.streaming_flag = CRI_FALSE;
		crijsb_cx.hca_mx_onmemory_voice_pool = criAtomExVoicePool_AllocateHcaMxVoicePool(&hca_mx_pool_config, NULL, 0);
	}
	else {
		crijsb_cx.hca_mx_onmemory_voice_pool = NULL;
	}

	/* Create HCA-MX streaming voice pool */
	if (crijsb_cx.config.num_hca_mx_streaming_voices > 0) {
		CriAtomExHcaMxVoicePoolConfig		hca_mx_pool_config;
		criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hca_mx_pool_config);
		hca_mx_pool_config.num_voices = crijsb_cx.config.num_hca_mx_streaming_voices;
		hca_mx_pool_config.player_config.max_sampling_rate = crijsb_cx.config.output_sampling_rate;
		hca_mx_pool_config.player_config.streaming_flag = CRI_TRUE;
		crijsb_cx.hca_mx_streaming_voice_pool = criAtomExVoicePool_AllocateHcaMxVoicePool(&hca_mx_pool_config, NULL, 0);
	}
	else {
		crijsb_cx.hca_mx_streaming_voice_pool = NULL;
	}
#pragma endregion

	CCLOG("[CRIWARE] Initialized");
	crijsb_cx.is_initialized = CRI_TRUE;
}

void CRICOCOS2D::criWare_Finalize()
{
	if (crijsb_cx.is_initialized == CRI_FALSE) {
		CCLOG("[CRIWARE] ERROR: CRIWARE is already finalized.\n");
		return;
	}

	criAtomExVoicePool_FreeAll();
	/* Destroy D-BAS */
	if (crijsb_cx.dbas_id != CRIATOMEXDBAS_ILLEGAL_ID) {
		criAtomExDbas_Destroy(crijsb_cx.dbas_id);
		crijsb_cx.dbas_id = CRIATOMEXDBAS_ILLEGAL_ID;
	}
	/* Detach PerformanceMonitor */
	criAtom_DetachPerformanceMonitor();

//#if defined(CRI_ATOM_MONITOR)
	if (crijsb_cx.config.uses_in_game_preview != CRI_FALSE) {
		/* Detach LoudnessMeter */
		criAtomMeter_DetachLoudnessMeter();
		/* In-game preview finalize */
		criAtomExMonitor_Finalize();
	}
//#endif
	
	criAtomEx_Finalize_XXX();
	criFs_Finalize();	

	crijsb_cx.is_initialized = CRI_FALSE;
}

void CRICOCOS2D::criWare_Suspend()
{
#if defined(XPT_TGT_IOS)
	criAtomEx_StopSound_IOS();
#elif defined(XPT_TGT_ANDROID)
	criAtomEx_StopSound_ANDROID();
#endif
}

void CRICOCOS2D::criWare_Resume()
{
#if defined(XPT_TGT_IOS)
	criAtomEx_StartSound_IOS();
#elif defined(XPT_TGT_ANDROID)
	criAtomEx_StartSound_ANDROID();
#endif
}

bool CRICOCOS2D::criWare_IsInitialized() {
	return crijsb_cx.is_initialized;
}

void CRICOCOS2D::criWare_EnableAssetsAccess(){
	#if defined(XPT_TGT_ANDROID)
	// Enable accessing to 'assets' directory.
	// Get a context of activity through a JNI helper.
	cocos2d::JniMethodInfo methodInfo;
	cocos2d::JniHelper::getStaticMethodInfo(
		methodInfo,
		"org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;"
										   );
	auto android_context_object = (jobject)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	criFs_EnableAssetsAccess_ANDROID(cocos2d::JniHelper::getJavaVM(), android_context_object);
	#endif
}