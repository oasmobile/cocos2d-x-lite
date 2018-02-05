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
 * ��{�f�[�^�^�錾
 *****************************************************************************/

#ifndef _TYPEDEF_CriUint8
#define _TYPEDEF_CriUint8
typedef uint8_t					CriUint8;		/* �����Ȃ��P�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriSint8
#define _TYPEDEF_CriSint8
typedef int8_t					CriSint8;		/* �������P�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriUint16
#define _TYPEDEF_CriUint16
typedef uint16_t				CriUint16;		/* �����Ȃ��Q�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriSint16
#define _TYPEDEF_CriSint16
typedef int16_t					CriSint16;		/* �������Q�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriUint32
#define _TYPEDEF_CriUint32
typedef uint32_t				CriUint32;		/* �����Ȃ��S�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriSint32
#define _TYPEDEF_CriSint32
typedef int32_t					CriSint32;		/* �������S�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriUint64
#define _TYPEDEF_CriUint64
typedef uint64_t				CriUint64;		/* �����Ȃ��W�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriSint64
#define _TYPEDEF_CriSint64
typedef int64_t					CriSint64;		/* �������W�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriUint128
#define _TYPEDEF_CriUint128
typedef struct {								/* �����Ȃ�16�o�C�g���� */
	CriUint64			h;						/* ���64�r�b�g */
	CriUint64			l;						/* ����64�r�b�g */
} CriUint128;
#endif

#ifndef _TYPEDEF_CriSint128
#define _TYPEDEF_CriSint128
typedef struct {								/* ������16�o�C�g���� */
	CriSint64	h;								/* ���64�r�b�g */
	CriUint64	l;								/* ����64�r�b�g */
} CriSint128;
#endif

#ifndef _TYPEDEF_CriFloat16
#define _TYPEDEF_CriFloat16
typedef CriSint16				CriFloat16;		/* �Q�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriFloat32
#define _TYPEDEF_CriFloat32
typedef float					CriFloat32;		/* �S�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriFloat64
#define _TYPEDEF_CriFloat64
typedef double					CriFloat64;		/* �W�o�C�g���� */
#endif

#ifndef _TYPEDEF_CriFixed32
#define _TYPEDEF_CriFixed32
typedef CriSint32				CriFixed32;		/* �Œ菬���_32�r�b�g */
#endif

#ifndef _TYPEDEF_CriBool
#define _TYPEDEF_CriBool
typedef CriSint32				CriBool;		/* �_���^�i�_���萔��l�ɂƂ�j */
#endif

#ifndef _TYPEDEF_CriChar8
#define _TYPEDEF_CriChar8
typedef char					CriChar8;		/* �����^ */
#endif

/*****************************************************************************
 * �|�C���^���i�[�\�Ȑ����^
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
 * �Ăяo���K��
 *****************************************************************************/

#ifndef CRIAPI
#define CRIAPI
#endif	/* endif CRIAPI */

#endif	/* CRI_INCL_CRI_XPTS_IOS_H */

/* end of file */
