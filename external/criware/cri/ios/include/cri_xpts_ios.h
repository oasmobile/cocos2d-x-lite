/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Middleware Library
 * Module   : CRI Common Header for iOS
 * File     : cri_xpts_ios.h
 * Date     : 2013-11-07
 * Version  : 1.00
 ****************************************************************************/
#ifndef CRI_INCL_CRI_XPTS_IOS_H
#define CRI_INCL_CRI_XPTS_IOS_H

#include <stddef.h>
#include <stdint.h>


/*****************************************************************************
 * 基本データ型宣言
 *****************************************************************************/

#ifndef _TYPEDEF_CriUint8
#define _TYPEDEF_CriUint8
typedef uint8_t					CriUint8;		/* 符号なし１バイト整数 */
#endif

#ifndef _TYPEDEF_CriSint8
#define _TYPEDEF_CriSint8
typedef int8_t					CriSint8;		/* 符号つき１バイト整数 */
#endif

#ifndef _TYPEDEF_CriUint16
#define _TYPEDEF_CriUint16
typedef uint16_t				CriUint16;		/* 符号なし２バイト整数 */
#endif

#ifndef _TYPEDEF_CriSint16
#define _TYPEDEF_CriSint16
typedef int16_t					CriSint16;		/* 符号つき２バイト整数 */
#endif

#ifndef _TYPEDEF_CriUint32
#define _TYPEDEF_CriUint32
typedef uint32_t				CriUint32;		/* 符号なし４バイト整数 */
#endif

#ifndef _TYPEDEF_CriSint32
#define _TYPEDEF_CriSint32
typedef int32_t					CriSint32;		/* 符号つき４バイト整数 */
#endif

#ifndef _TYPEDEF_CriUint64
#define _TYPEDEF_CriUint64
typedef uint64_t				CriUint64;		/* 符号なし８バイト整数 */
#endif

#ifndef _TYPEDEF_CriSint64
#define _TYPEDEF_CriSint64
typedef int64_t					CriSint64;		/* 符号つき８バイト整数 */
#endif

#ifndef _TYPEDEF_CriUint128
#define _TYPEDEF_CriUint128
typedef struct {								/* 符号なし16バイト整数 */
	CriUint64			h;						/* 上位64ビット */
	CriUint64			l;						/* 下位64ビット */
} CriUint128;
#endif

#ifndef _TYPEDEF_CriSint128
#define _TYPEDEF_CriSint128
typedef struct {								/* 符号つき16バイト整数 */
	CriSint64	h;								/* 上位64ビット */
	CriUint64	l;								/* 下位64ビット */
} CriSint128;
#endif

#ifndef _TYPEDEF_CriFloat16
#define _TYPEDEF_CriFloat16
typedef CriSint16				CriFloat16;		/* ２バイト実数 */
#endif

#ifndef _TYPEDEF_CriFloat32
#define _TYPEDEF_CriFloat32
typedef float					CriFloat32;		/* ４バイト実数 */
#endif

#ifndef _TYPEDEF_CriFloat64
#define _TYPEDEF_CriFloat64
typedef double					CriFloat64;		/* ８バイト実数 */
#endif

#ifndef _TYPEDEF_CriFixed32
#define _TYPEDEF_CriFixed32
typedef CriSint32				CriFixed32;		/* 固定小数点32ビット */
#endif

#ifndef _TYPEDEF_CriBool
#define _TYPEDEF_CriBool
typedef CriSint32				CriBool;		/* 論理型（論理定数を値にとる） */
#endif

#ifndef _TYPEDEF_CriChar8
#define _TYPEDEF_CriChar8
typedef char					CriChar8;		/* 文字型 */
#endif

/*****************************************************************************
 * ポインタを格納可能な整数型
 *****************************************************************************/
#ifndef _TYPEDEF_CriSintPtr
#define _TYPEDEF_CriSintPtr
typedef intptr_t				CriSintPtr;
#endif

#ifndef _TYPEDEF_CriUintPtr
#define _TYPEDEF_CriUintPtr
typedef uintptr_t				CriUintPtr;
#endif

/*****************************************************************************
 * 呼び出し規約
 *****************************************************************************/

#ifndef CRIAPI
#define CRIAPI
#endif	/* endif CRIAPI */

#endif	/* CRI_INCL_CRI_XPTS_IOS_H */

/* end of file */
