# Copyright (c) 2017 CRI Middleware Co., Ltd.

LOCAL_PATH:=$(call my-dir)

# Application
include $(CLEAR_VARS)
LOCAL_MODULE    := criware_cc

# CocosCreator Intergretion Source
LOCAL_C_INCLUDES:= ../../Classes
LOCAL_C_INCLUDES+= ../../cri/android/include/
LOCAL_SRC_FILES += \
	../../Classes/cricocos2d_initializer.cpp \
	../../Classes/crijsb_atom.cpp \
	../../Classes/crijsb_register.cpp \
	../../Classes/crijsb_utility.cpp 
LOCAL_CXXFLAGS += -std=c++11

# COCOS2D_JAVASCRIPT Must be defined
LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT
LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_STATIC_LIBRARIES :
LOCAL_STATIC_LIBRARIES += spidermonkey_static
ifeq ($(USE_CRI_ATOM_MONITOR), true)
LOCAL_STATIC_LIBRARIES += cri_atom_monitor
else
# You can use CRI Filesystem funcitons without CRI Atom library.
LOCAL_STATIC_LIBRARIES += cri_atom
endif
LOCAL_STATIC_LIBRARIES += cri_file_system
LOCAL_STATIC_LIBRARIES += cri_base
LOCAL_C_INCLUDES	   += $(LOCAL_PATH)/../../../../cocos/
LOCAL_C_INCLUDES	   += $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/auto/
LOCAL_C_INCLUDES	   += $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual/

include $(BUILD_STATIC_LIBRARY)

# Import CRI Modules

$(call import-module,criware/cri/android/ndk-modules/cri_base)
$(call import-module,criware/cri/android/ndk-modules/cri_file_system)
ifeq ($(USE_CRI_ATOM_MONITOR), true)
$(call import-module,criware/cri/android/ndk-modules/cri_atom_monitor)
else
$(call import-module,criware/cri/android/ndk-modules/cri_atom)
endif