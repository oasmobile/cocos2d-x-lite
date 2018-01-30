LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := cri_file_system

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include

ifdef CRI_LINK_DEBUG_LIB
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_file_system_androidD.a
else
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_file_system_android.a
endif

include $(PREBUILT_STATIC_LIBRARY)
