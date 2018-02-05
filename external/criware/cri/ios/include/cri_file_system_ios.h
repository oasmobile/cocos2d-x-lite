/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2009 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header for iOS
 * File     : cri_file_system_ios.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system_ios.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_IOS_H_INCLUDED
#define	CRI_FILE_SYSTEM_IOS_H_INCLUDED

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      �ϐ��錾
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      �֐��錾
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_IOS
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� 8 �ł��B<BR>
 */
CriError CRIAPI criFs_SetFileAccessThreadPriority_IOS(int prio);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_IOS
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h�����Ⴂ�v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� -13 �ł��B<BR>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_IOS(int prio);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define criFs_SetFileAccessThreadPriority_iOS criFs_SetFileAccessThreadPriority_IOS
#define criFs_SetDataDecompressionThreadPriority_iOS criFs_SetDataDecompressionThreadPriority_IOS

#endif	/* CRI_FILE_SYSTEM_IOS_H_INCLUDED */

/* --- end of file --- */
