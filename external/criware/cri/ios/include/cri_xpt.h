/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 1998-2014 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Middleware Library
 * Module   : CRI Common Header for iPhone
 * File     : cri_xpt.h
 * Date     : 2014-07-03
 * Version  : 1.06
 *
 ****************************************************************************/

#ifndef CRI_INCL_CRI_XPT_H
#define CRI_INCL_CRI_XPT_H

#include <TargetConditionals.h>
#include <Availability.h>

#define XPT_TGT_IOS
#define XPT_TGT_IPHONE
#define XPT_CCS_LEND

#if TARGET_IPHONE_SIMULATOR
	#if TARGET_CPU_X86
    	#define CRI_TARGET_STR "iOS_SIM_X86"
	#elif TARGET_CPU_X86_64
    	#define CRI_TARGET_STR "iOS_SIM_X86_64"
	#else
		#error unsupported architecture
	#endif
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__)
    #define CRI_TARGET_STR "iOS_ARMv6"
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__)
    #define CRI_TARGET_STR "iOS_ARMv7"
#elif defined(__ARM_ARCH_7S__)
    #define CRI_TARGET_STR "iOS_ARMv7s"
#elif defined(__ARM64_ARCH_8__)
    #define CRI_TARGET_STR "iOS_ARMv8_A64"
#else
	#error unsupported architecture
#endif

#include "cri_xpts_ios.h"

#define XPT_SUPPORT_MULTICHANNEL

#include "cri_xpt_post.h"

#endif  /* CRI_INCL_CRI_XPT_H */
/* End Of File */
