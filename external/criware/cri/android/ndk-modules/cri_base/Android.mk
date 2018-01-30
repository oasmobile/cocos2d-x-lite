LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := cri_base

ifdef CRI_LINK_DEBUG_LIB
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_base_androidD.a
else
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_base_android.a
endif

include $(PREBUILT_STATIC_LIBRARY)
