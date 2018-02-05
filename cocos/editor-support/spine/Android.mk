LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spine_static

LOCAL_MODULE_FILENAME := libspine

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
Animation.c \
AnimationState.c \
AnimationStateData.c \
Atlas.c \
AtlasAttachmentLoader.c \
Attachment.c \
AttachmentLoader.c \
AttachmentVertices.cpp \
Bone.c \
BoneData.c \
BoundingBoxAttachment.c \
Cocos2dAttachmentLoader.cpp \
Event.c \
EventData.c \
IkConstraint.c \
IkConstraintData.c \
Json.c \
MeshAttachment.c \
PathAttachment.c \
PathConstraint.c \
PathConstraintData.c \
RegionAttachment.c \
Skeleton.c \
SkeletonAnimation.cpp \
SkeletonBatch.cpp \
SkeletonBinary.c \
SkeletonBounds.c \
SkeletonData.c \
SkeletonJson.c \
SkeletonRenderer.cpp \
Skin.c \
Slot.c \
SlotData.c \
TransformConstraint.c \
TransformConstraintData.c \
VertexAttachment.c \
extension.c \
spine-cocos2dx.cpp \
Array.c \
ClippingAttachment.c \
Color.c \
PointAttachment.c \
SkeletonClipping.c \
SkeletonTwoColorBatch.cpp \
Triangulator.c \
VertexEffect.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
						   $(LOCAL_PATH)/../..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
					$(LOCAL_PATH)/../..

include $(BUILD_STATIC_LIBRARY)
