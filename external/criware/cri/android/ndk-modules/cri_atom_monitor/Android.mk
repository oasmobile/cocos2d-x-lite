LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := cri_atom_monitor

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
LOCAL_EXPORT_LDLIBS     := -lOpenSLES

ifdef CRI_LINK_DEBUG_LIB
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_atom_monitor_androidD.a
else
LOCAL_SRC_FILES         := ../../libs/$(TARGET_ARCH_ABI)/libcri_atom_monitor_android.a
endif

include $(PREBUILT_STATIC_LIBRARY)
