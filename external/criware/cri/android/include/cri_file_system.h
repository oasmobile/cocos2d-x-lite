/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2016 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header
 * File     : cri_file_system.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_H_INCLUDED
#define	CRI_FILE_SYSTEM_H_INCLUDED

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"

#ifdef __cplusplus
#if defined(XPT_TGT_TBCG)
#if !defined(XPT_DISABLE_FSV1API)
	/* ���o�[�W����API */
	/* Old version API */
	#include "cri_file_system_ver1api.h"
#endif
#endif
#endif

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/* �o�[�W������� */
/* Version Number */
#define CRI_FS_VERSION		(0x02750500)
#define CRI_FS_VER_NUM		"2.75.05"
#define CRI_FS_VER_NAME		"CRI File System"

/*JP
 * \brief �R���t�B�M�����[�V�����̃f�t�H���g�l
 */
#if defined(XPT_TGT_NITRO)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(4)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(8)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(128)
#elif defined(XPT_TGT_3DS)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(4)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(8)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(XPT_TGT_TBCG)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(1)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(XPT_TGT_EMSCRIPTEN)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_SINGLE
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(1)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(CRI_USE_FILESYSTEM_PLATFORM_HEADER)
#include "cri_file_system_platform.h"
#else
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#endif

/*JP
 * \brief �f�t�H���g�f�o�C�XID
 */
#define CRIFS_DEVICE_DEFAULT	(CRIFS_DEVICE_00)
/*JP
 * \brief �������t�@�C���V�X�e���f�o�C�XID
 */
#define CRIFS_DEVICE_MEMORY		(CRIFS_DEVICE_07)

/*JP
 * \brief �f�t�H���g�f�o�C�XID����`
 * \par ���l:
 * ���̒�`�͔p�~�\��ł��B������::CRIFS_DEVICE_DEFAULT���g�p���Ă��������B
 * \sa CRIFS_DEVICE_DEFAULT
 */
#define CRIFS_DEFAULT_DEVICE	(CRIFS_DEVICE_DEFAULT)

/*JP
 * \brief �������t�@�C���p�X�̍ő咷
 * \ingroup FSLIB_CRIFS
 * \par ����:
 * �������t�@�C���p�X�̍ő咷�ł��BNULL���������܂݂܂��B<br>
 * �������t�@�C���p�X�������̐��l�𒴉߂��邱�Ƃ͂���܂���B<br>
 * \attention
 * ���̒l�́A�����傫���Ȃ�\��������܂��B<br>
 * \sa criFs_AddressToPath
 */
#define CRIFS_MAX_MEMORY_FILE_PATH	(44)

/*JP
 * \brief �����ȃo�C���hID
 * \ingroup FSLIB_BINDER
 * \par ����:
 * ���g�p�o�C���_�ɗ^������ID�ł��B�o�C���h�Ɏ��s�������ɂ��Ԃ��Ă��邱�Ƃ�����܂��B<br>
 * \sa CriFsBindId, criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory
 */
#define CRIFSBINDER_BID_NULL		(0)

/*JP
 * \brief �L���o�C���hID�̊J�n�ԍ�
 * \ingroup FSLIB_BINDER
 * \par ����:
 * �L���ȃo�C���hID�̊J�n�ԍ��ł��B<br>
 * �e��o�C���h�֐��ŕԂ�ID������ID�����傫����ΗL���ł��B<br>
 * \sa CriFsBindId, criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory
 */
#define CRIFSBINDER_BID_START		(1)

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*JP
 * \brief ���[�U�A���P�[�^�̓o�^
 * \ingroup FSLIB_CRIFS
 * \param[in]	p_malloc_func	�������m�ۊ֐�
 * \param[in]	p_free_func		����������֐�
 * \param[in]	p_obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * CRI File System���C�u�����Ƀ������A���P�[�^�i�������̊m�ہ^����֐��j��o�^���܂��B<br>
 * CRI File System���C�u�����������C�u�������ōs�Ȃ�����������������A
 * ���[�U�Ǝ��̃�������������ɒu�����������ꍇ�Ɏg�p���܂��B
 */
#define criFs_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
{\
	criFs_SetUserMallocFunction(p_malloc_func, p_obj);\
	criFs_SetUserFreeFunction(p_free_func, p_obj);\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI File System API
 *=========================================================================*/
/*JP
 * \brief �X���b�h���f��
 * \par ����:
 * CRI File System���C�u�������ǂ̂悤�ȃX���b�h���f���œ��삷�邩��\���܂��B<br>
 * ���C�u�������������i::criFs_InitializeLibrary�֐��j�ɁA::CriFsConfig�\���̂ɂĎw�肵�܂��B
 * \sa CriFsConfig
 * \sa criFs_InitializeLibrary
 */
typedef enum CriFsThreadModelTag {
	/*JP
	 * \brief �}���`�X���b�h
	 * \par ����:
	 * ���C�u�����͓����ŃX���b�h���쐬���A�}���`�X���b�h�ɂē��삵�܂��B<br>
	 * �X���b�h��::criFs_InitializeLibrary�֐��Ăяo�����ɍ쐬����܂��B
	 */
	/*EN Multi thread				*/
	CRIFS_THREAD_MODEL_MULTI = 0,

	/*JP
	 * \brief �}���`�X���b�h�i���[�U�쓮���j
	 * \par ����:
	 * ���C�u�����͓����ŃX���b�h���쐬���A�}���`�X���b�h�ɂē��삵�܂��B<br>
	 * �X���b�h�� ::criFs_InitializeLibrary �֐��Ăяo�����ɍ쐬����܂��B<br>
	 * �T�[�o�������͍̂쐬���ꂽ�X���b�h��Ŏ��s����܂����A
	 * CRIFS_THREAD_MODEL_MULTI �Ƃ͈قȂ�A�����I�ɂ͎��s����܂���B<br>
	 * ���[�U�� ::criFs_ExecuteMain �֐��Ŗ����I�ɃT�[�o�������쓮����K�v������܂��B<br>
	 * �i  ::criFs_ExecuteMain �֐������s����ƁA�X���b�h���N�����A�T�[�o���������s����܂��B�j<br>
	 */
	CRIFS_THREAD_MODEL_MULTI_USER_DRIVEN = 3,

	/*JP
	 * \brief ���[�U�}���`�X���b�h
	 * \par ����:
	 * ���C�u���������ł̓X���b�h���쐬���܂��񂪁A���[�U���Ǝ��ɍ쐬�����X���b�h����T�[�o�����֐��i::criFs_ExecuteFileAccess�֐��A::criFs_ExecuteDataDecompression�֐��j���Ăяo����悤�A�����̔r������͍s���܂��B
	 */
	/*EN User multi thread				*/
	CRIFS_THREAD_MODEL_USER_MULTI = 1,

	/*JP
	 * \brief �V���O���X���b�h
	 * \par ����:
	 * ���C�u���������ŃX���b�h���쐬���܂���B�܂��A�����̔r��������s���܂���B<br>
	 * ���̃��f����I�������ꍇ�A�eAPI�ƃT�[�o�����֐��i::criFs_ExecuteFileAccess�֐��A::criFs_ExecuteDataDecompression�֐��j�Ƃ𓯈�X���b�h����Ăяo���悤�ɂ��Ă��������B
	 */
	/*EN Single thread				*/
	CRIFS_THREAD_MODEL_SINGLE = 2,

	/* enum be 4bytes */
	CRIFS_THREAD_MODEL_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsThreadModel;

/*JP
 * \brief �R���t�B�M�����[�V����
 * \par ����:
 * CRI File System���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ���C�u�������������i::criFs_InitializeLibrary�֐��j�Ɉ����Ƃ��Ė{�\���̂��w�肵�܂��B<br>
 * \par
 * CRI File System���C�u�����́A���������Ɏw�肳�ꂽ�R���t�B�M�����[�V�����ɉ����āA�������\�[�X��K�v�Ȑ��������m�ۂ��܂��B<br>
 * ���̂��߁A�R���t�B�M�����[�V�����Ɏw�肷��l�����������邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y���������}���邱�Ƃ��\�ł��B<br>
 * �������A�R���t�B�M�����[�V�����Ɏw�肵�����ȏ�̃n���h�����m�ۂ��邱�Ƃ͂ł��Ȃ��Ȃ邽�߁A�l����������������ƁA�n���h���̊m�ۂɎ��s����\��������܂��B<br>
 * \par ���l:
 * �f�t�H���g�ݒ���g�p����ꍇ�A ::criFs_SetDefaultConfig �֐��Ńf�t�H���g�p�����[�^���Z�b�g���A ::criFs_InitializeLibrary �֐��Ɏw�肵�Ă��������B<br>
 * \attention
 * �����I�Ƀ����o��������\���ɔ����A�ݒ�O��::criFs_SetDefaultConfig �֐��ŏ��������Ă���g�p���Ă��������B<br>
 * \sa criFs_InitializeLibrary, criFs_SetDefaultConfig
 */
typedef struct CriFsConfigTag {
	/*JP
		\brief �X���b�h���f��
		\par ����:
		CRI File System�̃X���b�h���f�����w�肵�܂��B<br>
		\sa CriFsThreadModel
	*/
	CriFsThreadModel thread_model;

	/*JP
		\brief �g�p����CriFsBinder�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����o�C���_�iCriFsBinder�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsBinder_Create �֐����g�p���ăo�C���_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����o�C���_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_binders�ɂ́u�����Ɏg�p����o�C���_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsBinder_Create �֐��� ::criFsBinder_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃o�C���_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_binders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃo�C���_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃo�C���_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_binders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����o�C���_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_binders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsBinder_Create, criFsBinder_Destroy
	*/
	CriSint32 num_binders;

	/*JP
		\brief �g�p����CriFsLoader�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p���郍�[�_�iCriFsLoader�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsLoader_Create �֐����g�p���ă��[�_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p���郍�[�_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_loaders�ɂ́u�����Ɏg�p���郍�[�_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsLoader_Create �֐��� ::criFsLoader_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃��[�_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_loaders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃ��[�_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃ��[�_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_loaders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p���郍�[�_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_loaders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsLoader_Create, criFsLoader_Destroy
	*/
	CriSint32 num_loaders;

	/*JP
		\brief �g�p����CriFsGroupLoader�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����O���[�v���[�_�iCriFsGroupLoader�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsGroupLoader_Create �֐����g�p���ăO���[�v���[�_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����O���[�v���[�_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_group_loaders�ɂ́u�����Ɏg�p����O���[�v���[�_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsGoupLoader_Create �֐��� ::criFsGroupLoader_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃O���[�v���[�_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_group_loaders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃO���[�v���[�_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃO���[�v���[�_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_group_loaders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����O���[�v���[�_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_group_loaders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsGroupLoader_Create, criFsGroupLoader_Destroy
	*/
	CriSint32 num_group_loaders;

	/*JP
		\brief �g�p����CriFsStdio�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����CriFsStdio�n���h���̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsStdio_OpenFile �֐����g�p����CriFsStdio�n���h�����쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����CriFsStdio�n���h���̐����w�肷��K�v������܂��B<br>
		<br>
		num_stdio_handles�ɂ́u�����Ɏg�p����CriFsStdio�n���h���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsStdio_OpenFile �֐��� ::criFsStdio_CloseFile �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1��CriFsStdio�n���h�������g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_stdio_handles��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂ�CriFsStdio�n���h����10�g�p����ꍇ�ɂ́A���̑��̏�ʂ�CriFsStdio�n���h����S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_stdio_handles��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����CriFsStdio�n���h���̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_stdio_handles�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\attention
		�u���b�W���C�u�������g�p����ADX���C�u������~���僉�C�u�����𕹗p����ꍇ�A
		ADXT�n���h����criSsPly�n���h���͓����I��CriFsStdio�n���h�����쐬���܂��B<br>
		���̂��߁A�u���b�W���C�u�������g�p����ꍇ�ɂ́ACRI File System���C�u��������������
		num_stdio_handles��ADXT�n���h����criSsPly�n���h���̐����������l���w�肵�Ă��������B<br>
		\sa criFsStdio_OpenFile, criFsStdio_CloseFile
	*/
	CriSint32 num_stdio_handles;

	/*JP
		\brief �g�p����CriFsInstaller�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����C���X�g�[���iCriFsInstaller�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsInstaller_Create �֐����g�p���ăC���X�g�[�����쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����C���X�g�[���̐����w�肷��K�v������܂��B<br>
		<br>
		num_installers�ɂ́u�����Ɏg�p����C���X�g�[���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsInstaller_Create �֐��� ::criFsInstaller_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃C���X�g�[�������g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_installers��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃC���X�g�[����10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃC���X�g�[����S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_installers��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����C���X�g�[���̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_installers�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\attention
		::criFs_SetDefaultConfig �}�N�����g�p���ăR���t�B�M�����[�V����������������ꍇ�Anum_installers�̐���0�ɐݒ肳��܂��B<br>
		���̂��߁A�C���X�g�[�����g�p����ꍇ�ɂ́A�A�v���P�[�V��������num_installers�𖾎��I�Ɏw�肷��K�v������܂��B<br>
		\sa criFsInstaller_Create, criFsInstaller_Destroy
	*/
	CriSint32 num_installers;

	/*JP
		\brief �ő哯���o�C���h��
		\par ����:
		�A�v���P�[�V�������Ńo�C���h�������s���A�ێ�����o�C���hID�iCriFsBindId�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criBinder_BindCpk �֐������g�p���ăo�C���h�������s���ꍇ�A
		�{�p�����[�^�Ɏg�p����o�C���hID�̐����w�肷��K�v������܂��B<br>
		<br>
		max_binds�ɂ́u�����Ɏg�p����o�C���hID�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsBinder_BindCpk �֐��� ::criFsBinder_Unbind �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃o�C���hID�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�max_binds��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃo�C���hID��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃo�C���h����؍s��Ȃ��ꍇ�ł����Ă��A
		max_binds��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����o�C���hID�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Amax_binds�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory, criFsBinder_Unbind
	*/
	CriSint32 max_binds;

	/*JP
		\brief �ő哯���I�[�v���t�@�C����
		\par ����:
		�A�v���P�[�V�������ŃI�[�v������t�@�C���̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsStdio_OpenFile �֐������g�p���ăt�@�C�����I�[�v������ꍇ�A
		�{�p�����[�^�ɃI�[�v������t�@�C���̐����w�肷��K�v������܂��B<br>
		<br>
		max_files�ɂ́u�����ɃI�[�v������t�@�C���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsStdio_OpenFile �֐��� ::criFsStdio_CloseFile �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃t�@�C�������I�[�v�����Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�max_files��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃt�@�C����10�I�[�v������ꍇ�ɂ́A���̑��̏�ʂŃt�@�C����1�����I�[�v�����Ȃ��ꍇ�ł����Ă��A
		max_files��10���w�肷��K�v������܂��B<br>
		\par �⑫:
		CRI File System���C�u�����́A�ȉ��̊֐������s�����ꍇ�Ƀt�@�C�����I�[�v�����܂��B<br>
		\table "�t�@�C�����I�[�v���������" align=center border=1 cellspacing=0 cellpadding=4
		{�֐�					|���l	}
		[criFsBinder_BindCpk	|�I�[�v�������t�@�C���̐���1�B<br> criFsBinder_Unbind �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsBinder_BindFile	|�I�[�v�������t�@�C���̐���1�B<br> criFsBinder_Unbind �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsBinder_BindFiles	|���X�g�Ɋ܂܂�鐔���t�@�C�����I�[�v�������B<br> criFsBinder_Unbind �֐������s�����܂Ńt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsLoader_Load		|�I�[�v�������t�@�C���̐���1�B<br> ���[�h����������܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�t�@�C���̓I�[�v������Ȃ��i�o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		[criFsStdio_OpenFile	|�I�[�v�������t�@�C���̐���1�B<br> criFsStdio_CloseFile �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�t�@�C���̓I�[�v������Ȃ��i�o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		[criFsInstaller_Copy	|�I�[�v�������t�@�C���̐���2�B<br> �t�@�C���R�s�[����������܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�I�[�v�������t�@�C����1�ɂȂ�i1���o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		\endtable
		\attention
		�u���b�W���C�u�������g�p����ADX���C�u������~���僉�C�u�����𕹗p����ꍇ�A
		ADXT�n���h����criSsPly�n���h���͓����I��CriFsStdio�n���h�����쐬���܂��B<br>
		���̂��߁A�u���b�W���C�u�������g�p����ꍇ�ɂ́ACRI File System���C�u��������������
		max_files��ADXT�n���h����criSsPly�n���h���̐����������l���w�肵�Ă��������B<br>
	*/
	CriSint32 max_files;

	/*JP
		\brief �p�X�̍ő咷�i�o�C�g�P�ʁj
		\par ����:
		�A�v���P�[�V�������Ŏw�肷��t�@�C���p�X�̍ő咷���w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsLoader_Load �֐������g�p���ăt�@�C���ɃA�N�Z�X����ꍇ�A
		�{�p�����[�^�ɃA�v���P�[�V�����Ŏg�p����p�X������̍ő咷���w�肷��K�v������܂��B<br>
		<br>
		max_path�ɂ́u�g�p����p�X������̍ő吔�v���w�肵�܂��B<br>
		�����ʂ�256�o�C�g�̃t�@�C���p�X���g�p����ꍇ�A���̑��̏�ʂ�32�o�C�g�̃t�@�C���p�X�����g��Ȃ��ꍇ�ł��A
		max_path�ɂ�256���w�肷��K�v������܂��B<br>
		\par ���l:
		�p�X�̍ő咷�ɂ́A�I�[��NULL�������܂񂾐����w�肷��K�v������܂��B<br>
		�i�u�������{�P�o�C�g�v�̒l���w�肷��K�v������܂��B�j<br>
		\attention
		PC���A���[�U���A�v���P�[�V���������R�ȏꏊ�ɃC���X�g�[���\�ȏꍇ�ɂ́A�z�肳���ő�T�C�Y�� max_path �Ɏw�肷��K�v������܂��̂ŁA�����ӂ��������B<br>
	*/
	CriSint32 max_path;

	/*JP
		\brief ���C�u�����o�[�W�����ԍ�
		\par ����:
		CRI File System���C�u�����̃o�[�W�����ԍ��ł��B<br>
		::criFs_SetDefaultConfig �֐��ɂ��A�{�w�b�_�ɒ�`����Ă���o�[�W�����ԍ����ݒ肳��܂��B<br>
		\attention
		�A�v���P�[�V�����ł́A���̒l��ύX���Ȃ��ł��������B<br>
	*/
	CriUint32 version;
} CriFsConfig;

/*JP
 * \brief �t�@�C���I�[�v���G���[�������̃��g���C���@
 */
typedef enum CriFsOpenRetryModeTag {
	CRIFS_OPEN_RETRY_NONE = 0,			/*JP< ���g���C���Ȃ� */
	CRIFS_OPEN_RETRY_INFINITE = -1,		/*JP< �����Ƀ��g���C���� */
	/* enum be 4bytes */
	CRIFS_OPEN_RETRY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsOpenRetryMode;

/*JP
 * \brief �t�@�C�����[�h�G���[�������̃��g���C���@
 */
typedef enum CriFsReadRetryModeTag {
	CRIFS_READ_RETRY_NONE = 0,			/*JP< ���g���C���Ȃ� */
	CRIFS_READ_RETRY_INFINITE = -1,		/*JP< �����Ƀ��g���C���� */
	/* enum be 4bytes */
	CRIFS_READ_RETRY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsReadRetryMode;

/*JP
 * \brief �f�t�H���g�̃p�X��؂蕶���̐ݒ�
 */
typedef enum CriFsDefaultPathSeparatorTag {
	CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE = 0,		/*JP< �v���b�g�t�H�[���W���̃p�X��؂蕶���ɕϊ����� */
	CRIFS_DEFAULT_PATH_SEPARATOR_NONE = 1,						/*JP< �p�X��؂蕶����ϊ��������̂܂܎g�p���� */
	CRIFS_DEFAULT_PATH_SEPARATOR_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsDefaultPathSeparator;

/*JP
 * \brief �t�@�C��I/O���[�h�̐ݒ� 
 */
typedef enum CriFsFileIoModeTag {
	CRIFS_FILE_IO_MODE_DEFAULT = 0,				/*JP< �@��f�t�H���g�̃t�@�C��I/O���[�h */
	CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE = 1,	/*JP< �t�@�C���n���h�������L���� */
	CRIFS_FILE_IO_MODE_OPEN_EVERY_TIME = 2,		/*JP< �t�@�C���A�N�Z�X���ƂɃt�@�C���̃I�[�v�����s�� */
	/* enum be 4bytes */
	CRIFS_FILE_IO_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileIoMode;

/*JP
 * \brief �������m�ۊ֐�
 * \ingroup FSLIB_CRIFS
 * \param[in]	obj		���[�U�w��I�u�W�F�N�g
 * \param[in]	size	�v���������T�C�Y�i�o�C�g�P�ʁj
 * \return		void*	�m�ۂ����������̃A�h���X�i���s����NULL�j
 * \par ����:
 * �������m�ۊ֐��o�^�p�̃C���^�[�t�F�[�X�ł��B<br>
 * CRI File System���C�u���������C�u�������ōs�Ȃ��������m�ۏ������A
 * ���[�U�Ǝ��̃������m�ۏ����ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * \par ���l:
 * �R�[���o�b�N�֐������s�����ۂɂ́Asize�ɕK�v�Ƃ���郁�����̃T�C�Y���Z�b�g
 * ����Ă��܂��B<br>
 * �R�[���o�b�N�֐�����size���̃��������m�ۂ��A�m�ۂ����������̃A�h���X��
 * �߂�l�Ƃ��ĕԂ��Ă��������B<br>
 * ���A������ obj �ɂ́A::criFs_SetUserMallocFunction �֐��œo�^�������[�U�w��
 * �I�u�W�F�N�g���n����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g�� ::criFs_SetUserMallocFunction �֐��̈����ɃZ�b�g���Ă����A
 * �{�R�[���o�b�N�֐��̈������o�R���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * �������̊m�ۂɎ��s�����ꍇ�A�G���[�R�[���o�b�N���Ԃ��ꂽ��A�Ăяo�����̊֐���
 * ���s����\��������܂��̂ł����ӂ��������B
 * \sa CriFsFreeFunc, criFs_SetUserMallocFunction
 */
typedef void *(CRIAPI *CriFsMallocFunc)(void *obj, CriUint32 size);

/*JP
 * \brief ����������֐�
 * \ingroup FSLIB_CRIFS
 * \param[in]	obj		���[�U�w��I�u�W�F�N�g
 * \param[in]	mem		������郁�����A�h���X
 * \return				�Ȃ�
 * \par ����:
 * ����������֐��o�^�p�̃C���^�[�t�F�[�X�ł��B<br>
 * CRI File System���C�u�����������C�u�������ōs�Ȃ�����������������A
 * ���[�U�Ǝ��̃�������������ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * \par ���l:
 * �R�[���o�b�N�֐������s�����ۂɂ́Amem�ɉ�����ׂ��������̃A�h���X���Z�b�g
 * ����Ă��܂��B<br>
 * �R�[���o�b�N�֐�����mem�̗̈�̃�������������Ă��������B
 * ���A������ obj �ɂ́A::criFs_SetUserFreeFunction �֐��œo�^�������[�U�w��
 * �I�u�W�F�N�g���n����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g�� ::criFs_SetUserFreeFunction �֐��̈����ɃZ�b�g���Ă����A
 * �{�R�[���o�b�N�֐��̈������o�R���ĎQ�Ƃ��Ă��������B<br>
 * \sa criFsMallocFunc, criFs_SetUserFreeFunction
 */
typedef void (CRIAPI *CriFsFreeFunc)(void *obj, void *mem);

/*JP
 * \brief CPK�R���e���c�t�@�C��ID
 * \ingroup FSLIB_CRIFS
 * \par �����F
 * CPK�R���e���c�t�@�C��ID�́ACPK�t�@�C���Ɋi�[���ꂽ�X�̃R���e���c�t�@�C�������ʂ��邽�߂̂��̂ł��B<br>
 * �t�@�C������ID�̗���������CPK�t�@�C���́A32�r�b�g��ID���g�p���邱�Ƃ��ł��܂��B
 * �t�@�C�����������Ȃ�CPK�t�@�C���́A16�r�b�g��ID���g�p���邱�Ƃ��ł��܂��B
 * �ǂ���̏ꍇ���A���̒l��L����ID�Ƃ��Ďg�p�ł��܂��B
 */
typedef CriSint32 CriFsFileId;

/*==========================================================================
 *      CriFsIo API
 *=========================================================================*/
/*JP
 * \brief �f�o�C�XID
 */
/*EN
 * \brief Device ID
 */
typedef enum CriFsDeviceIdTag {
	CRIFS_DEVICE_00 = 0,	/*JP< �f�t�H���g�f�o�C�X */
	CRIFS_DEVICE_01,
	CRIFS_DEVICE_02,
	CRIFS_DEVICE_03,
	CRIFS_DEVICE_04,
	CRIFS_DEVICE_05,
	CRIFS_DEVICE_06,
	CRIFS_DEVICE_07,		/*JP< ������ */
	CRIFS_DEVICE_MAX,

	CRIFS_DEVICE_INVALID	= -1,	/*JP< ���� */

	/* enum be 4bytes */
	CRIFS_DEVICE_ENUM_BE_SINT32 = 0x7fffffff
} CriFsDeviceId;

/*JP
 * \brief �f�o�C�X���
 */
/*EN
 * \brief Device Information
 */
typedef struct CriFsDeviceInfoTag {
	CriBool can_read;					/*JP< �ǂݍ��݉\�ȃf�o�C�X���ǂ���				*/
	CriBool can_write;					/*JP< �������݉\�ȃf�o�C�X���ǂ���				*/
	CriBool can_seek;					/*JP< �V�[�N�\�ȃf�o�C�X���ǂ���					*/
	CriSint32 minimum_read_size;		/*JP< �ǂݍ��݉\�ȍŏ��P�ʂ̃T�C�Y				*/
	CriSint32 minimum_write_size;		/*JP< �������݉\�ȍŏ��P�ʂ̃T�C�Y				*/
	CriSint32 minimum_seek_size;		/*JP< �V�[�N�\�ȍŏ��P�ʂ̃T�C�Y					*/
	CriSint32 read_buffer_alignment;	/*JP< �ǂݍ��ݐ�o�b�t�@�ɗv�������A���C�����g	*/
	CriSint32 write_buffer_alignment;	/*JP< �������ݐ�o�b�t�@�ɗv�������A���C�����g	*/
} CriFsDeviceInfo;

/*JP
 * \brief �t�@�C���I�[�v�����[�h
 */
/*EN
 * \brief File Opening Mode
 */
typedef enum {
	CRIFS_FILE_MODE_APPEND			= 0,	/*JP< �����t�@�C���ɒǋL								*/	/*EN< Appends to an existing file						*/
	CRIFS_FILE_MODE_CREATE			= 1,	/*JP< �t�@�C���̐V�K�쐬�i�����̃t�@�C���͏㏑���j		*/	/*EN< Creates a new file always							*/
	CRIFS_FILE_MODE_CREATE_NEW		= 2,	/*JP< �t�@�C���̐V�K�쐬�i�㏑���s�j					*/	/*EN< Creates a new file (Can not overwrite)			*/
	CRIFS_FILE_MODE_OPEN			= 3,	/*JP< �����t�@�C���̃I�[�v��							*/	/*EN< Opens an existing file							*/
	CRIFS_FILE_MODE_OPEN_OR_CREATE	= 4,	/*JP< �t�@�C���̃I�[�v���i���݂��Ȃ��ꍇ�͐V�K�쐬�j	*/	/*EN< Opens a file if available (Or creates new file)	*/
	CRIFS_FILE_MODE_TRUNCATE		= 5,	/*JP< �����t�@�C����0Byte�ɐ؂�l�߂ăI�[�v��			*/	/*EN< Opens a file and truncates it						*/

													/* ���� */
	CRIFS_FILE_MODE_OPEN_WITHOUT_DECRYPTING	= 10,	/*JP< �t�@�C���̃I�[�v���i�Í����������Ȃ��j	*/	/*EN< Opens a file without decrypting	*/

	/* enum be 4bytes */
	CRIFS_FILE_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileMode;

/*JP
 * \brief �t�@�C���A�N�Z�X���
 */
/*EN
 * \brief Kind of File Access
 */
typedef enum {
	CRIFS_FILE_ACCESS_READ			= 0,	/*JP< �ǂݍ��݂̂�		*/	/*EN< Read Only			*/
	CRIFS_FILE_ACCESS_WRITE			= 1,	/*JP< �������݂̂�		*/	/*EN< Write Only		*/
	CRIFS_FILE_ACCESS_READ_WRITE	= 2,	/*JP< �ǂݏ���			*/	/*EN< Read and Write	*/

	/* enum be 4bytes */
	CRIFS_FILE_ACCESS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileAccess;

/*JP
 * \brief I/O�C���^�[�t�F�[�X�̃G���[�R�[�h
 */
/*JP
 * \brief Error of I/O Interface
 */
typedef enum {
	CRIFS_IO_ERROR_OK				=   0,	/*JP< �G���[�Ȃ� */
	CRIFS_IO_ERROR_NG				=  -1,	/*JP< ��ʃG���[ */
	CRIFS_IO_ERROR_TRY_AGAIN		=  -2,	/*JP< ���g���C���ׂ� */

											/* ���� */
	CRIFS_IO_ERROR_NG_NO_ENTRY		= -11,	/*JP< �ʃG���[�i�t�@�C�������j */
	CRIFS_IO_ERROR_NG_INVALID_DATA	= -12,	/*JP< �ʃG���[�i�f�[�^���s���j */

	/* enum be 4bytes */
	CRIFS_IO_ERROR_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsIoError;

/*JP
 * \brief �t�@�C���n���h��
 */
/*EN
 * \brief File Handle
 */
typedef void *CriFsFileHn;

/*JP
 * \brief I/O�C���^�[�t�F�[�X
 */
/*EN
 * \brief I/O Interface
 */
typedef struct CriFsIoInterfaceTag {
	/*JP
	 * \brief �t�@�C���̗L���̊m�F
	 * \param[in]	path	�t�@�C���̃p�X
	 * \param[out]	result	�t�@�C�������݂��邩�ǂ���
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���̗L�����m�F����֐��ł��B<br>
	 * �t�@�C�������݂���ꍇ�� CRI_TRUE ���A
	 * ���݂��Ȃ��ꍇ�� CRI_FALSE �� result �ɃZ�b�g����K�v������܂��B<br>
	 */
	CriFsIoError (CRIAPI *Exists)(const CriChar8 *path, CriBool *result);

	/*JP
	 * \brief �t�@�C���̍폜
	 * \param[in]	path	�t�@�C���̃p�X
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C�����폜����֐��ł��B<br>
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *Remove)(const CriChar8 *path);

	/*JP
	 * \brief �t�@�C�����̕ύX
	 * \param[in]	path	���l�[���O�̃t�@�C���̃p�X
	 * \param[in]	path	���l�[����̃t�@�C���̃p�X
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �t�@�C�����̕ύX���s�Ȃ��֐��ł��B<br>
	 * old_path �Ŏw�肳�ꂽ�t�@�C�����A new_path �Ƀ��l�[�����܂��B<br>
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *Rename)(const CriChar8 *old_path, const CriChar8 *new_path);

	/*JP
	 * \brief �t�@�C���̃I�[�v��
	 * \param[in]	path	�t�@�C���̃p�X
	 * \param[in]	mode	�t�@�C���I�[�v�����[�h
	 * \param[in]	access	�t�@�C���A�N�Z�X���
	 * \param[out]	filehn	�t�@�C���n���h��
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C�����I�[�v������֐��ł��B<br>
	 * �I�[�v���ɐ��������ꍇ�ACriFsFileHn �^�̃t�@�C���n���h����Ԃ��K�v������܂��B<br>
	 * \par �⑫:
	 * CriFsFileHn �� void �|�C���^�Ƃ��Ē�`����Ă��܂��B<br>
	 * �Ǝ��̃t�@�C�����\���̂��`���A���̃A�h���X�� CriFsFileHn �^�ɃL���X�g���ĕԂ��Ă��������B<br>
	 * ���A�t�@�C���I�[�v�����Ƀ������̊m�ۂ��K�v�ȏꍇ�ɂ́A�{�֐����œ��I�Ƀ������̊m�ۂ��s�Ȃ��Ă��������B<br>
	 * \attention
	 * �߂�l�̃G���[�R�[�h�i CriFsIoError �j�ɂ́A�֐����Ōp���s�\�ȃG���[����������
	 * �ꍇ�Ɍ��� CRIFS_IO_ERROR_NG ���Z�b�g���Ă��������B<br>
	 * �i�t�@�C���̃I�[�v���Ɏ��s�����ꍇ�ł��A�A�v���P�[�V�����ŏ������p���\�ȏꍇ�ɂ�
	 * filehn �� NULL ���Z�b�g���ACRIFS_IO_ERROR_OK ��Ԃ��K�v������܂��B�j<br>
	 * �܂��A�f�B�X�N�}���҂����̗��R�ɂ��A�֐������s���ꂽ�^�C�~���O�ŃI�[�v������
	 * �����s�ł��Ȃ��ꍇ�A�G���[�R�[�h�Ƃ��� CRIFS_IO_ERROR_TRY_AGAIN ��Ԃ����ƂŁA
	 * ��莞�Ԍ�i��10ms��j�ɍēx�I�[�v����������蒼�����Ƃ��\�ł��B<br>
	 * �i�֐��̎��s�^�C�~���O��摗�肷�邱�Ƃ��\�ł��B�j
	 */
	CriFsIoError (CRIAPI *Open)(
		const CriChar8 *path, CriFsFileMode mode, CriFsFileAccess access, CriFsFileHn *filehn);

	/*JP
	 * \brief �t�@�C���̃N���[�Y
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���n���h�����N���[�Y����֐��ł��B<br>
	 * �t�@�C���I�[�v�����ɓ��I�Ƀ������̊m�ۂ��s�Ȃ����ꍇ�́A�N���[�Y���Ƀ�������������Ă��������B<br>
	 */
	CriFsIoError (CRIAPI *Close)(CriFsFileHn filehn);

	/*JP
	 * \brief �t�@�C���T�C�Y�̎擾
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	file_size	�t�@�C���T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���n���h������A���Y�t�@�C���̃T�C�Y���擾����֐��ł��B<br>
	 * \attention
	 * ���̊֐��̓��C���X���b�h�ォ�璼�ڎ��s�����\��������܂��B<br>
	 * ���̂��߁A���̊֐��̒��Œ����ԏ������u���b�N���邱�Ƃ͔�����K�v������܂��B<br>
	 * �t�@�C���n���h������t�@�C���T�C�Y���擾����̂Ɏ��Ԃ�������ꍇ�ɂ́A
	 * �t�@�C���I�[�v�����ɂ��炩���߃t�@�C���T�C�Y���擾�i�t�@�C���n���h�����ɕێ��j
	 * ���Ă����A�{�֐����s���ɂ��̒l��Ԃ��悤�֐����������Ă��������B<br>
	 */
	CriFsIoError (CRIAPI *GetFileSize)(CriFsFileHn filehn, CriSint64 *file_size);

	/*JP
	 * \brief �ǂݍ��݂̊J�n
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[in]	offset	�ǂݍ��݊J�n�ʒu
	 * \param[in]	read_size	�ǂݍ��݃T�C�Y
	 * \param[in]	buffer	�ǂݍ��ݐ�o�b�t�@
	 * \param[in]	buffer	�o�b�t�@�T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �f�[�^�̓ǂݍ��݂��J�n����֐��ł��B<br>
	 * offset �Ŏw�肳�ꂽ�ʒu����A read_size �Ŏw�肳�ꂽ�T�C�Y�������f�[�^��
	 * buffer �ɓǂݍ��݂܂��B<br>
	 * �֐��̃C���^�[�t�F�[�X�Ƃ��Ă͔񓯊�I/O�����ɂ�������z�肵�Ă��܂����A
	 * �X���b�h���g�p����ꍇ�i�X���b�h���f���� CRIFS_THREAD_MODEL_MULTI ���w�肷��ꍇ�j
	 * �ɂ́A���̊֐��𓯊�I/O�������g���Ď������Ă���肠��܂���B<br>
	 * �i�֐����Ńt�@�C���̓ǂݍ��݂���������܂ő҂��Ă���肠��܂���B�j<br>
	 * \attention
	 * ���ۂɓǂݍ��߂��T�C�Y�́A GetReadSize �֐��ŕԂ��K�v������܂��B<br>
	 * ����I/O�����ɂ��{�֐�����������ꍇ�ł��A�ǂݍ��߂��T�C�Y�� GetReadSize �֐�
	 * �����s�����܂ŁA�t�@�C���n���h�����ɕێ�����K�v������܂��B<br>
	 */
	CriFsIoError (CRIAPI *Read)(CriFsFileHn filehn, CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size);

	/*JP
	 * \brief �ǂݍ��݊����`�F�b�N
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	result	�t�@�C���̓ǂݍ��݂������������ǂ���
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �t�@�C���̓ǂݍ��݂������������ǂ������m�F����֐��ł��B<br>
	 * �t�@�C���̓ǂݍ��݂����������ꍇ�� CRI_TRUE ���A
	 * �ǂݍ��ݓr���̏ꍇ�� CRI_FALSE �� result �ɃZ�b�g����K�v������܂��B<br>
	 * \attention
	 * result �ɂ́A���[�h�����̐��ۂɊ֌W�Ȃ��A���[�h�����������������_
	 * �i�f�o�C�X�ւ̃A�N�Z�X���I���������_�j�� CRI_TRUE ���Z�b�g����K�v������܂��B<br>
	 * ���[�h�G���[�����������ꍇ�ł��A result �� CRI_TRUE ���Z�b�g���A
	 * �֐��̖߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B<br>
	 * �i���[�h�����������������ǂ����ɂ��ẮA GetReadSize �֐��Ŕ��ʂ��Ă��܂��B�j<br>
	 * result �� CRI_FALSE ��Ԃ�����́ACRI File System
	 * ���C�u�����͑��̓ǂݍ��ݗv������؏������܂���B<br>
	 * �i���[�h�G���[�������� result �� CRI_FALSE ���Z�b�g���������ꍇ�A
	 * �t�@�C���̃��[�h���ł��Ȃ��Ȃ�����A�n���h����
	 * Destroy �֐����珈�������A���Ȃ��Ȃ�\��������܂��B<br>
	 */
	CriFsIoError (CRIAPI *IsReadComplete)(CriFsFileHn filehn, CriBool *result);

	/*JP
	 * \brief �t�@�C���ǂݍ��݂̃L�����Z�����s
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �f�o�C�X���̃t�@�C���ǂݍ��݂ɑ΂��ăL�����Z���𔭍s���A�����ɕ��A����֐��ł��B
	 * �߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B<br>
	 * CRIFS_IO_ERROR_OK�ȊO�̒l��Ԃ��Ă��A
	 * CRI File System�̓����CRIFS_IO_ERROR_OK��Ԃ����ꍇ�Ɠ����ł��B<br>
	 */
	CriFsIoError (CRIAPI *CancelRead)(CriFsFileHn filehn);

	/*JP
	 * \brief �ǂݍ��݃T�C�Y�̎擾
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	read_size	�ǂݍ��߂��T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * ���[�h�������s�Ȃ������ʁA���ۂɃo�b�t�@�ɓǂݍ��߂��f�[�^�̃T�C�Y��Ԃ��֐��ł��B<br>
	 * �t�@�C���̏I�[���ł́A Read �֐��Ŏw�肵���T�C�Y���̃f�[�^���K�������ǂݍ��߂�Ƃ͌���܂���B<br>
	 * \attention
	 * ���[�h�G���[�����������ꍇ�A read_size �� -1 ���Z�b�g���A
	 * �֐��̖߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B
	 */
	CriFsIoError (CRIAPI *GetReadSize)(CriFsFileHn filehn, CriSint64 *read_size);

	/*JP
	 * \brief �������݂̊J�n
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[in]	offset	�������݊J�n�ʒu
	 * \param[in]	write_size	�������݃T�C�Y
	 * \param[in]	buffer	�������ݐ�o�b�t�@
	 * \param[in]	buffer	�o�b�t�@�T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �f�[�^�̏������݂��J�n����֐��ł��B<br>
	 * offset �Ŏw�肳�ꂽ�ʒu����A write_size �Ŏw�肳�ꂽ�T�C�Y�������f�[�^��
	 * buffer ���珑�����݂܂��B<br>
	 * �֐��̃C���^�[�t�F�[�X�Ƃ��Ă͔񓯊�I/O�����ɂ�������z�肵�Ă��܂����A
	 * �X���b�h���g�p����ꍇ�i�X���b�h���f���� CRIFS_THREAD_MODEL_MULTI ���w�肷��ꍇ�j
	 * �ɂ́A���̊֐��𓯊�I/O�������g���Ď������Ă���肠��܂���B<br>
	 * �i�֐����Ńt�@�C���̏������݂���������܂ő҂��Ă���肠��܂���B�j<br>
	 * \attention
	 * ���ۂɏ������߂��T�C�Y�́A GetWriteSize �֐��ŕԂ��K�v������܂��B<br>
	 * ����I/O�����ɂ��{�֐�����������ꍇ�ł��A�������߂��T�C�Y�� GetWriteSize �֐�
	 * �����s�����܂ŁA�t�@�C���n���h�����ɕێ�����K�v������܂��B<br>
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *Write)(CriFsFileHn filehn, CriSint64 offset, CriSint64 write_size, void *buffer, CriSint64 buffer_size);

	/*JP
	 * \brief �������݊����`�F�b�N
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	result	�t�@�C���̏������݂������������ǂ���
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �t�@�C���̏������݂������������ǂ������m�F����֐��ł��B<br>
	 * �t�@�C���̏������݂����������ꍇ�� CRI_TRUE ���A
	 * �������ݓr���̏ꍇ�� CRI_FALSE �� result �ɃZ�b�g����K�v������܂��B<br>
	 * \attention
	 * ���C�g�G���[�����������ꍇ�A result �� CRI_TRUE ���Z�b�g���A
	 * �֐��̖߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 * \attention
	 * result �ɂ́A���C�g�����̐��ۂɊ֌W�Ȃ��A���C�g�����������������_
	 * �i�f�o�C�X�ւ̃A�N�Z�X���I���������_�j�� CRI_TRUE ���Z�b�g����K�v������܂��B<br>
	 * ���C�g�G���[�����������ꍇ�ł��A result �� CRI_TRUE ���Z�b�g���A
	 * �֐��̖߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B<br>
	 * �i���C�g�����������������ǂ����ɂ��ẮA GetReadSize �֐��Ŕ��ʂ��Ă��܂��B�j<br>
	 * result �� CRI_FALSE ��Ԃ�����́ACRI File System
	 * ���C�u�����͑��̓ǂݍ��ݗv������؏������܂���B<br>
	 * �i���C�g�G���[�������� result �� CRI_FALSE ���Z�b�g���������ꍇ�A
	 * �t�@�C���̃��[�h���ł��Ȃ��Ȃ�����A�n���h����
	 * Destroy �֐����珈�������A���Ȃ��Ȃ�\��������܂��B<br>
	 */
	CriFsIoError (CRIAPI *IsWriteComplete)(CriFsFileHn filehn, CriBool *result);

	/*JP
	 * \brief �t�@�C���������݂̃L�����Z�����s
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	result	�L�����Z�������s�ł�����
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �f�o�C�X���̃t�@�C���������݂ɑ΂��ăL�����Z���𔭍s���A�����ɕ��A����֐��ł��B
	 * �߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B<br>
	 * CRIFS_IO_ERROR_OK�ȊO�̒l��Ԃ��Ă��A
	 * CRI File System�̓����CRIFS_IO_ERROR_OK��Ԃ����ꍇ�Ɠ����ł��B<br>
	 */
	CriFsIoError (CRIAPI *CancelWrite)(CriFsFileHn filehn);

	/*JP
	 * \brief �������݃T�C�Y�̎擾
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	write_size	�������߂��T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * ���C�g�������s�Ȃ������ʁA���ۂɃo�b�t�@�ɓǂݍ��߂��f�[�^�̃T�C�Y��Ԃ��֐��ł��B<br>
	 * \attention
	 * ���C�g�G���[�����������ꍇ�A write_size �� -1 ���Z�b�g���A
	 * �֐��̖߂�l�� CRIFS_IO_ERROR_OK ��Ԃ��Ă��������B
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *GetWriteSize)(CriFsFileHn filehn, CriSint64 *write_size);

	/*JP
	 * \brief �t���b�V���̎��s
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �������ݗp�Ƀo�b�t�@�����O����Ă���f�[�^���A
	 * �����I�Ƀf�o�C�X�ɏ����o���������s���֐��ł��B<br>
	 * �i ANSI C �W���� API �ł� fflush �֐��ɑ������鏈���ł��B�j<br>
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *Flush)(CriFsFileHn filehn);

	/*JP
	 * \brief �t�@�C���T�C�Y�̕ύX
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	size	�t�@�C���T�C�Y
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �t�@�C���̃T�C�Y���w�肵���T�C�Y�ɕύX����֐��ł��B<br>
	 * \par �⑫:
	 * �{�֐��́ADMA�]���T�C�Y�̐������ɂ��f�o�C�X�ւ̏������݂��o�C�g�P�ʂ�
	 * �s�Ȃ��Ȃ��ꍇ�ɁA�t�@�C���T�C�Y��␳���邽�߂Ɏg�p���܂��B<br>
	 * ���̂��߁A�������݂��o�C�g�P�ʂŉ\�ȃf�o�C�X�ɂ��ẮA���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 * \par ���l:
	 * �f�o�C�X�ŏ������݂��s�Ȃ�Ȃ��ꍇ�ɂ́A���̊֐������������A
	 * �\���̂̃����o�� CRI_NULL ���w�肷�邱�Ƃ��\�ł��B<br>
	 */
	CriFsIoError (CRIAPI *Resize)(CriFsFileHn filehn, CriSint64 size);

	/*JP
	 * \brief �l�C�e�B�u�t�@�C���n���h���̎擾
	 * \param[in]	filehn	�t�@�C���n���h��
	 * \param[out]	native_filehn	�l�C�e�B�u�̃t�@�C���n���h��
	 * \return	CriFsIoError	�G���[�R�[�h
	 * \par ����:
	 * �v���b�g�t�H�[��SDK�ŗ��p�����t�@�C���̃n���h�����擾����֐��ł��B<br>
	 * �Ⴆ�΁A ANSI C �W���� fopen �֐����g�p���ăt�@�C�����I�[�v�������ꍇ�A
	 * native_filehn �Ƃ��ăt�@�C���|�C���^�i FILE * �j��Ԃ��K�v������܂��B<br>
	 * \par ���l:
	 * ����APLAYSTATION3�ȊO�̋@��ł͂��̊֐�����������K�v�͂���܂���B<br>
	 */
	CriFsIoError (CRIAPI *GetNativeFileHandle)(CriFsFileHn filehn, void **native_filehn);

	/*JP
	 * \brief �ǂݍ��݃v���O���X���Z�R�[���o�b�N�̐ݒ�
	 * \param[in]	filehn		�t�@�C���n���h��
	 * \param[in]	callback    �ǂݍ��݃v���O���X���Z�R�[���o�b�N
	 * \param[in]	obj			�����I�u�W�F�N�g
	 * \par ����:
	 * �{�֐��́A::criFsLoader_GetProgress �œ�����i�����A�P�ʓǂݍ��݃T�C�Y���
	 * �ׂ������x�ōX�V�����邽�߂́A�ǂݍ��݃v���O���X���Z�R�[���o�b�N��ݒ肷��֐��ł��B<br>
	 * �{�֐����������Ȃ��ꍇ��A�{�֐��œn���ꂽ�R�[���o�b�N�֐����g�p���Ȃ��ꍇ�A
	 * ::criFsLoader_GetProgress �œ�����i���́A��{�I�ɒP�ʓǂݍ��݃T�C�Y���ɍX�V����܂��B<br>
	 * �{�֐�����������ꍇ�́A�n���ꂽ�R�[���o�b�N�֐��� Read �֐����ŌĂяo���Ă��������B
	 * �܂��A�Ăяo���ۂɂ͑������� obj�A�������Ƀ������ւ̓ǂݍ��݂����������T�C�Y��
	 * �o�C�g�P�ʂœn���Ă��������B<br>
	 * �Ⴆ�΁A���[�h�v�����f�o�C�X���� 8192byte ���ɕ������ēǂݍ��ޏꍇ�́A
	 * 8192byte �̓ǂݍ��݊������ɁA�������� 8192 ��n���ČĂяo���Ă��������B<br>
	 * ���́A�ǂݍ��݃v���O���X���Z�R�[���o�b�N�Ăяo���ɂ���� ::criFsLoader_GetProgress
	 * �œ�����i�����X�V����܂��B�P�ʓǂݍ��݃T�C�Y���ׂ������x�ōX�V��
	 * �s�����Ƃ� ::criFsLoader_GetProgress �œ�����i���̗��x���ׂ����Ȃ�܂��B<br>
	 * \par ���l:
	 * �ǂݍ��݃��N�G�X�g���ׂ������x�œǂݍ��ݐi�����擾�ł��Ȃ��ꍇ�́A
	 * �������郁���b�g�͂���܂���B
	 * \sa ::criFsLoader_GetProgress
	 */
	CriFsIoError (CRIAPI *SetAddReadProgressCallback)(CriFsFileHn filehn, void(*callback)(void*, CriSint32), void* obj);
} CriFsIoInterface, *CriFsIoInterfacePtr;

/*JP
 * \brief I/O�I���R�[���o�b�N�֐�
 * \param[in]	path	�t�@�C���̃p�X
 * \param[out]	device_id	�f�o�C�XID
 * \param[out]	ioif	I/O�C���^�[�t�F�[�X
 * \par ����:
 * I/O�I���R�[���o�b�N�֐��́ACRI File System���C�u������I/O�������A
 * ���[�U�̓Ǝ�I/O�C�[�^�[�t�F�[�X�Œu��������ۂɎg�p���܂��B<br>
 * ��̓I�ɂ́A���[�U�� ::CriFsSelectIoCbFunc �^�̊֐����������A
 * ���̊֐��� ::criFs_SetSelectIoCallback �֐��ɃZ�b�g����K�v������܂��B<br>
 * ::CriFsSelectIoCbFunc �֐��́A���͂��ꂽ�t�@�C���̃p�X�i������path�j����͂��A
 * ���̃t�@�C�������݂���f�o�C�X��ID�i������device_id�j�ƁA
 * �f�o�C�X�ɃA�N�Z�X���邽�߂�I/O�C���^�[�t�F�[�X�i������ioif�j��Ԃ��K�v������܂��B<br>
 * \par �⑫:
 * ���C�u�������f�t�H���g��Ԃŗ��p����I/O�C���^�[�t�F�[�X�́A ::criFs_GetDefaultIoInterface �֐��Ŏ擾�\�ł��B<br>
 * ����̃t�@�C���݂̂�Ǝ���I/O�C���^�[�t�F�[�X�������������ꍇ�ɂ́A
 * ���̃t�@�C����S�� ::criFs_GetDefaultIoInterface �֐��Ŏ擾����I/O�C���^�[�t�F�[�X�ŏ������Ă��������B<br>
 * \code
 * CriError
 * \endcode
 * \sa criFs_SetSelectIoCallback, criFs_GetDefaultIoInterface
 */
typedef CriError (CRIAPI *CriFsSelectIoCbFunc)(
	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif);

/*==========================================================================
 *      CriFsBinder API
 *=========================================================================*/
struct CriFsBinderHnObjTag;
/*JP
 * \brief CriFsBinder�n���h��
 * \ingroup FSLIB_BINDER
 * \par �����F
 * �o�C���_�Ƃ́A�t�@�C���������ǂ��������߂̃f�[�^�x�[�X�ł��B<br>
 * - CriFsBinderHn (�o�C���_�n���h��)�ƃo�C���h<br>
 * �o�C���_�𗘗p����ɂ́A�o�C���_�n���h��( CriFsBinderHn )���쐬���A
 * CPK�t�@�C���^�t�@�C���^�f�B���N�g�����o�C���_�Ɍ��т��܂��B
 * ���̃o�C���_�ւ̌��ѕt�����o�C���h�ƌĂт܂��B<br>
 * �o�C���_���쐬����ƁA�o�C���_�n���h��( CriFsBinderHn )���擾����܂��B<br>
 * - CriFsBindId �i�o�C���hID�j<br>
 * �o�C���_�Ƀo�C���h���s���ƁA�o�C���hID���쐬����܂��B�X�̃o�C���h�����ʂ��邽�߂Ɏg�p���܂��B<br>
 * - �t�@�C���̃o�C���h�ƃA���o�C���h<br>
 * �o�C���_�ɂ́ACPK�t�@�C����t�@�C���A�f�B���N�g�����ǂ̂悤�ȑg�ݍ��킹�łł��o�C���h�ł��܂��B<br>
 * �o�C���h�������ڂ̃o�C���h��Ԃ��������邱�Ƃ��A���o�C���h�ƌĂт܂��B<br>
 * - ���p�ł���o�C���h��<br>
 * �쐬�ł���o�C���_���⓯���Ƀo�C���h�ł���ő吔�́A CriFsConfig ��
 * num_binders (�o�C���_��)�� max_binds (�����o�C���h�\�ȍő吔)�Ŏw�肵�܂��B<br>
 * - CPK�t�@�C���̃o�C���h<br>
 * CPK�t�@�C���Ɏ��[����Ă���X�̃t�@�C���i�R���e���c�t�@�C���j�ɃA�N�Z�X����ɂ́A
 * CPK�t�@�C�����o�C���h����K�v������܂��B<br>
 * CPK�t�@�C���̃R���e���c�t�@�C�����o�C���h�ł��܂��B����CPK�t�@�C�����A���o�C���h�����ꍇ�A
 * �o�C���h����Ă���R���e���c�t�@�C�����A���o�C���h����܂��i�ÖٓI�A���o�C���h�j�B<br>
 * - �o�C���_�̃v���C�I���e�B<br>
 * �o�C���_�́A�ړI�̃t�@�C�����ǂ̃o�C���hID�ɂ���̂����������܂��B<br>
 * ���̃o�C���hID�̌������́A��{�I�ɂ̓o�C���h���ꂽ���ԂɂȂ�܂����A�o�C���hID�̃v���C�I���e�B��
 * ���삷�邱�ƂŁA��������ύX���邱�Ƃ��ł��܂��B<br>
 * - �o�C���_��CriFs��API<br>
 * CriFsLoader, CriFsGroupLoader, CriFsBinder�ɂ́A�o�C���_�������Ɏ���API������܂��B
 * ���̍ۂɂ́A CriFsBinderHn �� CriFsBindId �A�ǂ�����w�肷��̂��ɒ��ӂ��Ă��������B
 */
typedef struct CriFsBinderHnObjTag *CriFsBinderHn;

/*JP
 * \brief CriFsBinder ID
 * \ingroup FSLIB_BINDER
 * \par �����F
 * �o�C���_�ɑ΂��ăo�C���h���s���ƁA CriFsBindId (�o�C���hID)���쐬����܂��B<br>
 * �o�C���hID�́A�X�̃o�C���h�����ʂ��邽�߂̂��̂ŁA�l�͕����Ȃ�32�r�b�g�l�͈̔͂�
 * �Ƃ�܂��B<br>
 * ���̌^�̕ϐ��́A�����ȃo�C���hID�ł��邱�Ƃ��Ӗ�������ʒl CRIFSBINDER_BID_NULL (�[��)
 * ���Ƃ�ꍇ������܂��B<br>
 */
typedef CriUint32 CriFsBindId;

/*JP
 * \brief �t�@�C�����\����
 * \ingroup FSLIB_BINDER
 * \par �����F
 * criFsBinder_Find(ById) �֐��̏o�͏��ł��B
 * ���������t�@�C���ɃA�N�Z�X���邽�߂̏����i�[���܂��B<br>
 * CPK�t�@�C���̃R���e���c�t�@�C���ł���ꍇ�Apath��CPK�t�@�C�����Aoffset��CPK�t�@�C��
 * �擪����̃I�t�Z�b�g�ʒu�ƂȂ�܂��B<br>
 * \sa criFsBinder_Find(), criFsBinder_FindById()
 */
typedef struct CriFsBinderFileInfoTag {
	CriFsFileHn filehn;		/*JP< �t�@�C���n���h�� */
	CriChar8 *path;			/*JP< �p�X�� */
	CriSint64 offset;		/*JP< �t�@�C���̐擪����̃I�t�Z�b�g�ʒu */
	CriSint64 read_size;   	/*JP< �Ǎ��T�C�Y�i���k�t�@�C���T�C�Y�j */
	CriSint64 extract_size;	/*JP< �W�J�T�C�Y�i���̃t�@�C���T�C�Y�A�񈳏k�Ȃ�read_size�Ɠ��l�j */
	CriFsBindId binderid;	/*JP< �o�C���hID�i�ǂ̃o�C���h�悩�猩�������������j */
	CriUint32 reserved[1];	/*JP< �\��̈� */
} CriFsBinderFileInfo;

/*JP
 * \brief �R���e���c�t�@�C�����\����
 * \ingroup FSLIB_BINDER
 * \par �����F
 * criFsBinder_GetContentsFileInfoById �֐��̏o�͏��ł��B<br>
 * ��������CPK�t�@�C���̃R���e���c�t�@�C���ɃA�N�Z�X���邽�߂̏����i�[���܂��B<br>
 * \sa criFsBinder_GetContentsFileInfoById()
 */
typedef struct CriFsBinderContentsFileInfoTag {
	CriChar8 *directory;	/*JP< �f�B���N�g���� */
	CriChar8 *filename;		/*JP< �t�@�C���� */
	CriUint32 read_size; 	/*JP< �Ǎ��T�C�Y�i�t�@�C���T�C�Y�j */
	CriUint32 extract_size;	/*JP< �W�J�T�C�Y�i�񈳏k�̏ꍇ�Aread_size�Ɠ��l�j */
	CriUint64 offset;		/*JP< CPK�t�@�C���̐擪����̃I�t�Z�b�g�ʒu */
	CriFsFileId id;			/*JP< �t�@�C��ID */
	CriChar8 *ustr;			/*JP< ���[�U������i���Ή��j */
} CriFsBinderContentsFileInfo;

/*JP
 * \brief �o�C���_�X�e�[�^�X
 * \ingroup FSLIB_BINDER
 * \par �����F
 * criFsBinder_GetStatus �֐��Ŏ擾�����A�o�C���hID�̏�Ԃł��B<br>
 * �o�C���h����������܂ŁA�o�C���h�������ڂɃA�N�Z�X���邱�Ƃ͂ł��܂���B<br>
 * �o�C���h�Ώۂ����݂��Ȃ�������A�o�C���h�ɕK�v�ȃ��\�[�X���s������ꍇ�́A
 * �o�C���h���s�ƂȂ�܂��B<br>
 * �o�C���h���s���̏ڂ������̓G���[�R�[���o�b�N�֐��Ŏ擾���Ă��������B
 * \sa criFsBinder_GetStatus()
 */
typedef enum {
	CRIFSBINDER_STATUS_NONE = 0,
	CRIFSBINDER_STATUS_ANALYZE,		/*JP< �o�C���h������ */
	CRIFSBINDER_STATUS_COMPLETE,	/*JP< �o�C���h���� */
	CRIFSBINDER_STATUS_UNBIND,		/*JP< �A���o�C���h������ */
	CRIFSBINDER_STATUS_REMOVED,		/*JP< �A���o�C���h���� */
	CRIFSBINDER_STATUS_INVALID,		/*JP< �o�C���h���� */
	CRIFSBINDER_STATUS_ERROR,		/*JP< �o�C���h���s */

	/* enum be 4bytes */
	CRIFSBINDER_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBinderStatus;

/*JP
 * \brief �o�C���h���
 * \ingroup FSLIB_BINDER
 * \par �����F
 * �����o�C���h����Ă���̂��������܂��B<br>
*/
typedef enum {
	CRIFSBINDER_KIND_NONE = 0,		/*JP< �Ȃ�							*/
	CRIFSBINDER_KIND_DIRECTORY,		/*JP< �f�B���N�g���o�C���h			*/
	CRIFSBINDER_KIND_CPK,			/*JP< CPK�o�C���h					*/
	CRIFSBINDER_KIND_CPKDOUBLE,		/*JP< CPK�o�C���h					*/
	CRIFSBINDER_KIND_FILE,			/*JP< �t�@�C���o�C���h				*/
	CRIFSBINDER_KIND_FILES,			/*JP< �����t�@�C���o�C���h			*/
	CRIFSBINDER_KIND_FILE_SECTION,	/*JP< �t�@�C���Z�N�V�����o�C���h	*/
	CRIFSBINDER_KIND_SYSTEM,		/*JP< �o�C���_�[�V�X�e���֘A		*/

	/* enum be 4bytes */
	CRIFSBINDER_KIND_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBinderKind;

/*JP
 * \brief Cpk�o�C���h�G���[�������̃G���[���
 * \ingroup FSLIB_BINDER
 * \par �����F
 * Cpk�o�C���h�������ɂȂ����ۂ̌����������܂��B<br>
*/
typedef enum {
	CRIFS_BINDCPK_ERROR_NONE = 0,		/*JP< �G���[���� */
	CRIFS_BINDCPK_ERROR_DATA,			/*JP< �f�[�^�s���� */
	CRIFS_BINDCPK_ERROR_CANNOT_READ,	/*JP< �ǂ߂Ȃ��i���f�B�A�������Ȃǁj */
	CRIFS_BINDCPK_ERROR_NONEXISTENT,	/*JP< (CPK)�t�@�C���������i���f�B�A�͑��݂���j*/
	/* enum be 4bytes */
	CRIFS_BINDCPK_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBindCpkError;

/*JP
 * \brief �o�C���_���
 * \ingroup FSLIB_BINDER
 * \par �����F
 * �o�C���_���擾API�̏o�͏��ł��B<br>
 * \sa criFsBinder_GetBinderIdInfo()
*/
typedef struct CriFsBinderInfoTag {
	CriFsBinderKind kind;				/*JP< �o�C���_��� */
	CriFsBinderStatus status;			/*JP< �o�C���_�X�e�[�^�X */
	CriSint32 priority;					/*JP< �v���C�I���e�B�ݒ� */
	CriSint32 nfiles;					/*JP< �t�@�C����<br>
										  �o�C���_���<br>
										  ::CRIFSBINDER_KIND_FILES:�o�C���h�t�@�C����<br>
										  ::CRIFSBINDER_KIND_CPK:�R���e���c�t�@�C����<br>
										  ���F�O
										*/
	const CriChar8 *path;				/*JP< Bind�֐��Ăяo�����ɓn���ꂽ�p�X�� */
	const CriChar8 *real_path;			/*JP< ���ۂɃo�C���h����ΏۂƂȂ����p�X�� */
	const CriChar8 *current_directory;	/*JP< �J�����g�f�B���N�g���ݒ� */
	CriFsBindId bndrid;				/*JP< ���o�C���_���Q�Ƃ��Ă���ꍇ�̎Q�Ɛ�o�C���hID<br>
											CPK�̃R���e���c�t�@�C�����t�@�C���o�C���h�����ꍇ�A
											CPK�̃o�C���hID������܂��B */
} CriFsBinderInfo;

/* ROM�A�h���X�̖����l */
#define CRIFS_ROM_ADDRESS_INVALID  0xFFFFFFFFFFFFFFFF

/*==========================================================================
 *      CriFsLoader API
 *=========================================================================*/
struct CriFsLoaderObjTag;
/*JP
 * \brief CriFsLoader�n���h��
 */
typedef struct CriFsLoaderObjTag *CriFsLoaderHn;

/*JP
 * \brief ���[�h�I���R�[���o�b�N�֐�
 */
typedef void (CRIAPI *CriFsLoaderLoadEndCbFunc)(void *obj, CriFsLoaderHn loader);

/*JP
 * \brief �Í��������R�[���o�b�N�֐�
 * \sa criFsLoader_SetInplaceDecryptionCbFunc
 */
typedef CriError (*CriFsInplaceDecryptionCbFunc)(
	void* user_data, CriUint8* data, CriUint64 data_size);

/*JP
 * \brief ���[�h�X�e�[�^�X
 */
/*EN
 * \brief Loading Status
 */
typedef enum {
	CRIFSLOADER_STATUS_STOP,		/*JP< ��~��		*/	/*EN< Stopping			*/
	CRIFSLOADER_STATUS_LOADING,		/*JP< ���[�h��		*/	/*EN< Loading			*/
	CRIFSLOADER_STATUS_COMPLETE,	/*JP< ����			*/	/*EN< Complete			*/
	CRIFSLOADER_STATUS_ERROR,		/*JP< �G���[		*/	/*EN< Error				*/
	/* enum be 4bytes */
	CRIFSLOADER_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoaderStatus;

/*JP
 * \brief ���[�_�v���C�I���e�B
 */
/*EN
 * \brief Priority
 */
typedef enum {
	CRIFSLOADER_PRIORITY_HIGHEST 		= 2,	/*JP< �ō�		*/	/*EN< Highest		*/
	CRIFSLOADER_PRIORITY_ABOVE_NORMAL 	= 1,	/*JP< ��		*/	/*EN< Above normal	*/
	CRIFSLOADER_PRIORITY_NORMAL 		= 0,	/*JP< ����		*/	/*EN< Normal		*/
	CRIFSLOADER_PRIORITY_BELOW_NORMAL 	= -1,	/*JP< ��		*/	/*EN< Below normal	*/
	CRIFSLOADER_PRIORITY_LOWEST 		= -2,	/*JP< �Œ�		*/	/*EN< Lowest		*/
	/* enum be 4bytes */
	CRIFSLOADER_PRIORITY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoaderPriority;

/*==========================================================================
 *      Group Loader API
 *=========================================================================*/

/*JP
 * \brief �����t�@�C�����̐�����ݒ肷��API�Łu�������v���������ʒl
 * \ingroup FSLIB_GROUPLOADER
 * \par �����F
 * criFsGroupLoader_LimitNumPreparingFiles �֐��ł��̒l���w�肵���ꍇ��A
 * criFsGroupLoader_LimitNumPreparingFiles �֐����g�p���Ȃ��ꍇ�A����������
 * criFsGroupLoader_LoadBulk �֐����Ŋ��������܂��B<br>
 * \sa criFsGroupLoader_LimitNumPreparingFiles()
 */
#define CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT			0

/*JP
 * \brief CriFsGroupLoader �n���h��
 * \ingroup FSLIB_GROUPLOADER
 * \par �����F
 * CPK�t�@�C���̃O���[�v���𗘗p����ɂ́A�O���[�v���[�_���쐬����K�v������܂��B<br>
 * �O���[�v���[�_���쐬����ƁA�O���[�v���[�_�n���h�����Ԃ���܂��B<br>
 * �O���[�v���[�_�ւ̃A�N�Z�X�́A�O���[�v���[�_�n���h�����g�p���čs���܂��B
 */
struct _CriFsGroupLoaderHnObj;
typedef struct _CriFsGroupLoaderHnObj *CriFsGroupLoaderHn;

/*JP
 * \brief �O���[�v�t�@�C�����\����
 * \ingroup FSLIB_GROUPLOADER
 * \par �����F
 * �O���[�v���[�_�ň�����X�̃t�@�C���Ɋւ�����ł��B
*/
typedef	struct CriFsGroupFileInfoTag {
	CriChar8	*directory;     /*JP< �R���e���c�t�@�C���̃f�B���N�g����    */
	CriChar8	*filename;		/*JP< �R���e���c�t�@�C���̃t�@�C����        */
	CriUint32	filesize;		/*JP< �R���e���c�t�@�C���̃t�@�C���T�C�Y	*/
	void		*datapointer;	/*JP< �R���e���c�t�@�C���̃f�[�^�|�C���^	*/
	CriUint32	gfinfotag;		/*JP< �R���e���c�t�@�C���̔ėp�^�O          */
	CriFsFileId	id;				/*JP< �R���e���c�t�@�C����ID                */
	CriUint32	continue_num;	/*JP< �R���e���c�t�@�C���̘A����            */
} CriFsGroupFileInfo;

/*JP
 * \brief �O���[�v���[�h�R�[���o�b�N�֐�
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	obj		���[�U�[�o�^�I�u�W�F�N�g
 * \param[in]	gfinfo	�ǂݍ��ރt�@�C���̏��
 * \return		gfinfo�Ŏ������t�@�C����ǂݍ��ރo�b�t�@�̈�ւ̃|�C���^�iNULL:���[�h�̃X�L�b�v�j
 * \par �����F
 * �O���[�v���[�h�R�[���o�b�N�֐��́A�O���[�v���[�_���ɐݒ肵�܂��B<br>
 * �O���[�v���[�h���A���[�h����t�@�C�����Ƀ��[�h�̒��O�Ɍďo����܂��B<br>
 * �ǂݍ��ރt�@�C���̃t�@�C������T�C�Y�Ȃǂ̃t�@�C����� gfinfo�œn����܂��B<br>
 * �R�[���o�b�N�֐��̕Ԓl��gfinfo�Ŏ����ꂽ�t�@�C����ǂݍ��ރo�b�t�@�ւ̃|�C���^�ƂȂ�܂��B
 * ���̕Ԓl��NULL�̏ꍇ�A���̃t�@�C���͓ǂݍ��܂�܂���B<br>
 * �O���[�v���[�h�R�[���o�b�N�֐����ݒ肳��Ă���ꍇ�ACPK�t�@�C���ɐݒ肳��Ă���O���[�v����
 * �Ǎ��A�h���X�͎g�p����܂���B
 * \sa criFsGroupLoader_SetLoadStartCallback()
 */
typedef void *(CRIAPI *CriFsGroupLoaderLoadStartCbFunc)(void *obj, const CriFsGroupFileInfo *gfinfo);

/*==========================================================================
 *      Log Output API
 *=========================================================================*/
/*JP
 * \brief �A�N�Z�X���O�o�̓��[�h
 */
typedef enum {
	CRIFS_LOGOUTPUT_MODE_DEFAULT,
	/* enum be 4bytes */
	CRIFS_LOGOUTPUT_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLogOutputMode;

/*JP
 * \brief ���O�o�͊֐�
 */
typedef void (CRIAPI *CriFsLogOutputFunc)(void *obj, const char* format, ...);

/*==========================================================================
 *      CriFsStdio API
 *=========================================================================*/
/*JP
 * \brief CriFsStdio�n���h��
 */
struct CriFsStdioObjTag;
typedef struct CriFsStdioObjTag *CriFsStdioHn;

/*JP
 * \brief �t�@�C����̃V�[�N�J�n�ʒu
 */
typedef enum {
	CRIFSSTDIO_SEEK_SET = 0, /*JP< �t�@�C���̐擪 */
	CRIFSSTDIO_SEEK_CUR = 1, /*JP< ���݂̓Ǎ��ʒu */
	CRIFSSTDIO_SEEK_END = 2, /*JP< �t�@�C���̏I�[ */
	/* enum be 4bytes */
	CRIFSSTDIO_SEEK_ENUM_BE_SINT32 = 0x7FFFFFFF
} CRIFSSTDIO_SEEK_TYPE;

/*JP
 * \brief �t�@�C���폜����
 */
typedef enum {
	CRIFSSTDIO_NOT_EXECUTED = 0,		/*JP< �폜���삪�s���Ȃ�����	*/
	CRIFSSTDIO_FILE_REMOVED = 1,		/*JP< ����I��					*/
	CRIFSSTDIO_IO_ERROR_OCCURRD =2,		/*JP< I/O�G���[������			*/
	/* enum is 4bytes */
	CRIFSSTDIO_REMOVE_RESULT_ENUM_IS_4BYTE = 0x7FFFFFFF
} CriFsStdioRemoveResult;


/*==========================================================================
 *      Load Limiter API
 *=========================================================================*/
/*JP
 * \brief ���[�h���~�b�^�ԍ�
 * \par ����:
 * �@�f�t�H���g�̏�Ԃł́A�S�Ẵ��[�_�n���h�������~�b�^�O�ԁi���~�b�^�����Ȃ��j�Ɋ��蓖�Ă��Ă��܂��B<br>
 * �@���~�b�^�𗘗p����ꍇ�A�����������郍�[�_�A�O���[�v���[�_�A�o�b�`���[�_�̃n���h���Ƀ��~�b�^�P�Ԃ�ݒ肵�Ă��������B<br>
 * �@�����āA���~�b�^�P�Ԃ̃��~�b�^�T�C�Y��ݒ肵�Ă��������B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B<br>
 */
typedef enum {
	CRIFS_LOADLIMITER_NO_0_DEFAULT		= 0,	/* ���[�h���~�b�^�ԍ��O�� (���~�b�^�����Ȃ��A�f�t�H���g) */
	CRIFS_LOADLIMITER_NO_1				= 1,	/* ���[�h���~�b�^�ԍ��P�� */
	/* enum be 4bytes */
	CRIFS_LOADLIMITER_NO_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoadLimiterNo;

/*JP
 * \brief ���[�h���~�b�^�T�C�Y�́u���~�b�^�����Ȃ��v���������ʒl
 * \par ����:
 * �@���~�b�^�O�Ԃ̃��~�b�^�T�C�Y�́A�Œ�I�Ɂu���~�b�^�����Ȃ��v�ƂȂ��Ă��܂��B<br>
 * �@���~�b�^�P�Ԃ̃��~�b�^�T�C�Y�́A�����l���u���~�b�^�����Ȃ��v�ƂȂ��Ă��܂��B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B<br>
 */
#define CRIFS_LOADLIMITER_SIZE_UNLIMITED	0x7FFFFFFF

/*JP
 * \brief ���[�h���~�b�^�T�C�Y�̃f�t�H���g�l�i���~�b�^�����Ȃ��j
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B<br>
 */
#define CRIFS_LOADLIMITER_SIZE_DEFAULT		CRIFS_LOADLIMITER_SIZE_UNLIMITED

/*JP
 * \brief ���[�h�v���񐔂́u�����Ȃ��v���������ʒl�i�f�t�H���g�l�j
 */
#define CRIFS_READ_REQUEST_NUM_UNLIMITED        0x7FFFFFFF

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

/*==========================================================================
 *      CRI File System API
 *=========================================================================*/
/*JP
 * \brief �f�t�H���g�R���t�B�M�����[�V�����̃Z�b�g
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	�R���t�B�M�����[�V����
 * \par ����:
 * ::criFs_InitializeLibrary �֐��ɐݒ肷��R���t�B�M�����[�V�����i ::CriFsConfig �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \par �⑫:
 * �R���t�B�M�����[�V�����ɐݒ肷��e�p�����[�^���A�A�v���P�[�V�����Ŏg�p����n���h���̐��ɉ����Ē��߂��邱�ƂŁA
 * ���C�u�������K�v�Ƃ��郁�����T�C�Y���������}���邱�Ƃ��\�ł��B<br>
 * �������A�A�v���P�[�V�������Ŏg�p����n���h���̐������m�łȂ��J�������i�K��A�������T�C�Y���^�C�g�ł͂Ȃ��P�[�X�ł́A
 * �{�}�N�����g�p���邱�Ƃɂ��ŁA�������������ȗ������邱�Ƃ��\�ł��B<br>
 * \attention:
 * �{�}�N���ł́A�قƂ�ǂ̃P�[�X�ŕK�v�[���Ȑ��̃n���h�����m�ۂł���悤�A�R���t�B�M�����[�V�����̊e�p�����[�^�ɑ傫�߂̒l���Z�b�g���܂��B<br>
 * ���̂��߁A�{�}�N�����g�p�����ꍇ�A���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�͑傫���Ȃ�܂��̂ŁA�����ӂ��������B<br>
 * �i�������T�C�Y���^�C�g�ȃP�[�X�ł́A�{�}�N���ŃR���t�B�M�����[�V������������������A�e�p�����[�^���ʂɒ��߂��邱�Ƃ��I�X�X���������܂��B�j<br>
 * \sa
 * CriFsConfig
*/
#define criFs_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model		= CRIFS_CONFIG_DEFAULT_THREAD_MODEL;\
	(p_config)->num_binders			= CRIFS_CONFIG_DEFAULT_NUM_BINDERS;\
	(p_config)->num_loaders			= CRIFS_CONFIG_DEFAULT_NUM_LOADERS;\
	(p_config)->num_group_loaders	= CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS;\
	(p_config)->num_stdio_handles	= CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES;\
	(p_config)->num_installers		= CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS;\
	(p_config)->max_binds			= CRIFS_CONFIG_DEFAULT_MAX_BINDS;\
	(p_config)->max_files			= CRIFS_CONFIG_DEFAULT_MAX_FILES;\
	(p_config)->max_path			= CRIFS_CONFIG_DEFAULT_MAX_PATH;\
	(p_config)->version				= CRI_FS_VERSION;\
}

/*JP
 * \brief ���[�N�̈�T�C�Y�̌v�Z
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	�R���t�B�M�����[�V����
 * \param[out]	nbyte	���[�N�̈�T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���[�N�̈�̃T�C�Y�̓R���t�B�M�����[�V�����i ::CriFsConfig �j�̓��e�ɂ���ĕω����܂��B<br>
 * ���C�u�����Ɋ��蓖�Ă郁�����T�C�Y���팸�������ꍇ�ɂ́A�R���t�B�M�����[�V�����̃p�����[�^��K�X���߂��Ă��������B<br>
 * config �� NULL ���w�肵���ꍇ�A�f�t�H���g�̃R���t�B�M�����[�V�������K�p����܂��B
 * \sa CriFsConfig
 */
CriError CRIAPI criFs_CalculateWorkSizeForLibrary(const CriFsConfig *config, CriSint32 *nbyte);

/*JP
 * \brief CRI File System�̏�����
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	�R���t�B�M�����[�V����
 * \param[in]	buffer	���[�N�̈�
 * \param[in]	size	���[�N�̈�T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criFs_FinalizeLibrary �֐������s����܂ł̊ԁA���p�\�ł��B�j<br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���[�N�̈���m�ۂ�����@�ɂ́A�ȉ���2�ʂ�̕��@������܂��B<br>
 * <b>(a) User Allocator����</b>�F�������̊m�ہ^����ɁA���[�U���p�ӂ����֐����g�p������@�B<br>
 * <b>(b) Fixed Memory����</b>�F�K�v�ȃ������̈�𒼐ڃ��C�u�����ɓn�����@�B<br>
 * <br>
 * User Allocator������p����ꍇ�A���[�U��CRI File System���C�u�����Ƀ������m�ۊ֐���o�^���Ă����܂��B<br>
 * work��NULL�Asize��0���w�肵�Ė{�֐����Ăяo�����ƂŁA
 * ���C�u�����͓o�^�ς݂̃������m�ۊ֐����g�p���ĕK�v�ȃ������������I�Ɋm�ۂ��܂��B<br>
 * ���[�U�����[�N�̈��p�ӂ���K�v�͂���܂���B<br>
 * ���������Ɋm�ۂ��ꂽ�������́A�I���������i ::criFs_FinalizeLibrary �֐����s���j�ɉ������܂��B<br>
 * <br>
 * Fixed Memory������p����ꍇ�A���[�N�̈�Ƃ��ĕʓr�m�ۍς݂̃������̈��{�֐���
 * �ݒ肷��K�v������܂��B<br>
 * ���[�N�̈�̃T�C�Y�� ::criFs_CalculateWorkSizeForLibrary �֐��Ŏ擾�\�ł��B<br>
 * �����������̑O�� ::criFs_CalculateWorkSizeForLibrary �֐��Ŏ擾�����T�C�Y���̃�������\��
 * �m�ۂ��Ă����A�{�֐��ɐݒ肵�Ă��������B<br>
 * ���AFixed Memory������p�����ꍇ�A���[�N�̈�̓��C�u�����̏I�������i ::criFs_FinalizeLibrary �֐��j
 * ���s�Ȃ��܂ł̊ԁA���C�u�������ŗ��p���ꑱ���܂��B<br>
 * ���C�u�����̏I���������s�Ȃ��O�ɁA���[�N�̈�̃�������������Ȃ��ł��������B<br>
 * \par ��:
 * �yUser Allocator�����ɂ�郉�C�u�����̏������z<br>
 * User Allocator������p����ꍇ�A���C�u�����̏������^�I���̎菇�͈ȉ��̒ʂ�ł��B<br>
 * 	-# �������������s�O�ɁA ::criFs_SetUserMallocFunction �֐���
 * ::criFs_SetUserFreeFunction �֐���p���ă������m�ہ^����֐���o�^����B<br>
 * 	-# �������p�R���t�B�O�\���̂Ƀp�����[�^���Z�b�g����B<br>
 * 	-# ::criFs_InitializeLibrary �֐��ŏ������������s���B<br>
 * �iwork�ɂ�NULL�Asize�ɂ�0���w�肷��B�j<br>
 * 	-# �A�v���P�[�V�����I������ ::criFs_FinalizeLibrary �֐��ŏI���������s�Ȃ��B<br>
 * 	.
 * <br>��̓I�ȃR�[�h�͈ȉ��̂Ƃ���ł��B<br>
 * \code
 * // �Ǝ��̃������m�ۊ֐�
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	// �������̊m��
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * // �Ǝ��̃���������֐���p��
 * void user_free(void *obj, void *mem)
 * {
 * 	// �������̉��
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 	CriFsConfig config;	// ���C�u�����������p�R���t�B�O�\����
 * 		:
 * 	// �Ǝ��̃������m�ۊ֐���o�^
 * 	criFs_SetUserMallocFunction(user_malloc, NULL);
 *
 * 	// �Ǝ��̃���������֐���o�^
 * 	criFs_SetUserFreeFunction(user_free, NULL);
 *
 * 	// ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * 	criFs_SetDefaultConfig(&config);
 *
 * 	// ���C�u�����̏�����
 * 	// ���[�N�̈�ɂ�NULL��0���w�肷��B
 * 	// ���K�v�ȃ������́A�o�^�����������m�ۊ֐����g���Ċm�ۂ����B
 * 	criFs_InitializeLibrary(&config, NULL, 0);
 * 		:
 * 	// �A�v���P�[�V�����̃��C������
 * 		:
 * 	// �A�v���P�[�V�������I������ۂɏI���������s��
 * 	// �����������Ɋm�ۂ��ꂽ�������́A�o�^��������������֐����g���ĉ�������B
 * 	criFs_FinalizeLibrary();
 * 		:
 * }
 * \endcode
 * <br>
 * �yFixed Memory�����ɂ�郉�C�u�����̏������z<br>
 * Fixed Memory������p����ꍇ�A���C�u�����̏������^�I���̎菇�͈ȉ��̈ȉ��̒ʂ�ł��B<br>
 * 	-# �������p�R���t�B�O�\���̂Ƀp�����[�^���Z�b�g����B<br>
 * 	-# ���C�u�����̏������ɕK�v�ȃ��[�N�̈�̃T�C�Y���A ::criFs_CalculateWorkSizeForLibrary
 * �֐����g���Čv�Z����B<br>
 * 	-# ���[�N�̈�T�C�Y���̃��������m�ۂ���B<br>
 * 	-# ::criFs_InitializeLibrary �֐��ŏ������������s���B<br>
 * �iwork�ɂ͊m�ۂ����������̃A�h���X���Asize�ɂ̓��[�N�̈�̃T�C�Y���w�肷��B�j<br>
 * 	-# �A�v���P�[�V�����I������ ::criFs_FinalizeLibrary �֐��ŏI���������s�Ȃ��B<br>
 * 	-# ���[�N�̈�̃��������������B<br>
 * 	.
 * <br>��̓I�ȃR�[�h�͈ȉ��̂Ƃ���ł��B<br>
 * \code
 * main()
 * {
 * 	CriFsConfig config;	// ���C�u�����������p�R���t�B�O�\����
 * 	void *work;				// ���[�N�̈�A�h���X
 * 	CriSint32 size;		// ���[�N�̈�T�C�Y
 * 		:
 * 	// ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * 	criFs_SetDefaultConfig(&config);
 *
 * 	// ���C�u�����̏������ɕK�v�ȃ��[�N�̈�̃T�C�Y���v�Z
 * 	criFs_CalculateWorkSizeForLibrary(&config, &size);
 *
 * 	// ���[�N�̈�p�Ƀ��������m��
 * 	work = malloc((size_t)size);
 *
 * 	// ���C�u�����̏�����
 * 	// ���m�ۍς݂̃��[�N�̈���w�肷��B
 * 	criFs_InitializeLibrary(&config, work, size);
 * 		:
 * 	// �A�v���P�[�V�����̃��C������
 * 	// �����̊ԁA�m�ۂ����������͕ێ���������B
 * 		:
 * 	// �A�v���P�[�V�������I������ۂɏI���������s��
 * 	criFs_FinalizeLibrary();
 *
 * 	// �K�v�Ȃ��Ȃ������[�N�̈���������
 * 	free(work);
 * 		:
 * }
 * \endcode

 * \par ���l:
 * ���C�u�����g�p���Ɋm�ۂł���n���h���̐��iCriFsBinder��CriFsLoader�̐��j�́A
 * �������ݒ�R���t�B�M�����[�V�����i������config�j�Ŏw�肵�܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y���A�R���t�B�M�����[�V�������e�ɉ����ĕω����܂��B<br>
 * �i�n���h�����𑝂₹�΁A�K�v�ȃ������̃T�C�Y���傫���Ȃ�܂��B�j<br>
 * config �� NULL ���w�肵���ꍇ�A�f�t�H���g�̃R���t�B�M�����[�V�������K�p����܂��B
 * \attention
 * �{�֐������s��A�K���΂ɂȂ� ::criFs_FinalizeLibrary �֐������s���Ă��������B<br>
 * �܂��A ::criFs_FinalizeLibrary �֐������s����܂ł́A�{�֐����ēx���s���邱�Ƃ͂ł��܂���B<br>
 * \sa CriFsConfig, criFs_CalculateWorkSizeForLibrary, criFs_FinalizeLibrary
 * \sa criFs_SetUserMallocFunction, criFs_SetUserFreeFunction
 */
/*EN
 * \brief Initialize the CRI File System
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	Configuration
 * \param[in]	buffer	Work area
 * \param[in]	size	Size of work area
 * \return	CriError	Error information
 * \par
 * Initialize the CRI File System<br>
 * \sa criFs_FinalizeLibrary
 */
CriError CRIAPI criFs_InitializeLibrary(const CriFsConfig *config, void *buffer, CriSint32 size);

/*JP
 * \brief CRI File System�̏I��
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�������I�����܂��B<br>
 * \attention
 * ::criFs_InitializeLibrary �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criFs_InitializeLibrary
 */
/*EN
 * \brief Finalize the CRI File System
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error information
 * \par
 * Finalize the CRI File System<br>
 * \sa criFs_InitializeLibrary
 */
CriError CRIAPI criFs_FinalizeLibrary(void);

/*JP
 * \brief �������m�ۊ֐��̓o�^
 * \ingroup FSLIB_CRIFS
 * \param[in]	func		�������m�ۊ֐�
 * \param[in]	obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * CRI File System���C�u�����Ƀ������m�ۊ֐���o�^���܂��B<br>
 * CRI File System���C�u�����������C�u�������ōs�Ȃ��������m�ۏ������A
 * ���[�U�Ǝ��̃������m�ۏ����ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * <br>
 * �{�֐��̎g�p�菇�͈ȉ��̂Ƃ���ł��B<br>
 * (1) ::CriFsMallocFunc �C���^�[�t�F�[�X�ɕ������������m�ۊ֐���p�ӂ���B<br>
 * (2) ::criFs_SetUserMallocFunction �֐����g�p���ACRI File System���C�u�����ɑ΂���
 * �������m�ۊ֐���o�^����B<br>
 * <br>
 * ��̓I�ȃR�[�h�̗�͈ȉ��̂Ƃ���ł��B
 * \par ��:
 * \code
 * // �Ǝ��̃������m�ۊ֐���p��
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	// �������̊m��
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * main()
 * {
 * 		:
 * 	// �������m�ۊ֐��̓o�^
 * 	criFs_SetUserMallocFunction(user_malloc, NULL);
 * 		:
 * }
 * \endcode
 * \par ���l:
 * ������ obj �Ɏw�肵���l�́A ::CriFsMallocFunc �Ɉ����Ƃ��ēn����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g��{�֐��̈����ɃZ�b�g���Ă����A�R�[���o�b�N�֐��ň������o�R
 * ���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * �������m�ۊ֐���o�^����ۂɂ́A���킹�ă���������֐��i ::CriFsFreeFunc �j��
 * �o�^����K�v������܂��B
 * \sa CriFsMallocFunc, criFs_SetUserFreeFunction
 */
void CRIAPI criFs_SetUserMallocFunction(CriFsMallocFunc func, void *obj);

/*JP
 * \brief ����������֐��̓o�^
 * \ingroup FSLIB_CRIFS
 * \param[in]	func		����������֐�
 * \param[in]	obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * CRI File System���C�u�����Ƀ���������֐���o�^���܂��B<br>
 * CRI File System���C�u�����������C�u�������ōs�Ȃ�����������������A
 * ���[�U�Ǝ��̃�������������ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * <br>
 * �{�֐��̎g�p�菇�͈ȉ��̂Ƃ���ł��B<br>
 * (1) ::CriFsFreeFunc �C���^�[�t�F�[�X�ɕ���������������֐���p�ӂ���B<br>
 * (2) ::criFs_SetUserFreeFunction �֐����g�p���ACRI File System���C�u�����ɑ΂���
 * ����������֐���o�^����B<br>
 * <br>
 * ��̓I�ȃR�[�h�̗�͈ȉ��̂Ƃ���ł��B
 * \par ��:
 * \code
 * // �Ǝ��̃���������֐���p��
 * void user_free(void *obj, void *mem)
 * {
 * 	// �������̉��
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 		:
 * 	// ����������֐��̓o�^
 * 	criFs_SetUserFreeFunction(user_free, NULL);
 * 		:
 * }
 * \endcode
 * \par ���l:
 * ������ obj �Ɏw�肵���l�́A ::CriFsFreeFunc �Ɉ����Ƃ��ēn����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g��{�֐��̈����ɃZ�b�g���Ă����A�R�[���o�b�N�֐��ň������o�R
 * ���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * ����������֐���o�^����ۂɂ́A���킹�ă������m�ۊ֐��i ::CriFsMallocFunc �j��
 * �o�^����K�v������܂��B
 * \sa CriFsFreeFunc, criFs_SetUserMallocFunction
 */
void CRIAPI criFs_SetUserFreeFunction(CriFsFreeFunc func, void *obj);

/*JP
 * \brief �T�[�o�����̎��s
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�����̓�����Ԃ��X�V���܂��B<br>
 * �A�v���P�[�V�����́A���̊֐������I�i���t���[��1����x�j�Ɏ��s����K�v������܂��B<br>
 * \attention
 * criFs_ExecuteMain �����s���Ȃ��ꍇ�A�t�@�C���̃��[�h���i�܂Ȃ����̖�肪��������\��������܂��B<br>
 */
CriError CRIAPI criFs_ExecuteMain(void);

/*JP
 * \brief �t�@�C���A�N�Z�X�����̎��s�i��X���b�h���������j
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�����̃t�@�C���A�N�Z�X���������s���܂��B<br>
 * \attention
 * ���̊֐��́A�X���b�h���g�p���Ȃ�����CRI File System���C�u�������g�p����ꍇ�ɌĂяo���K�v������܂��B<br>
 * �X���b�h���g�p������ł́A���̊֐��̑���ɁA criFs_ExecuteMain �֐������s���Ă��������B<br>
 * \sa
 * criFs_ExecuteMain()
 */
CriError CRIAPI criFs_ExecuteFileAccess(void);

/*JP
 * \brief �f�[�^�W�J�����̎��s�i��X���b�h���������j
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�����̃f�[�^�W�J���������s���܂��B<br>
 * \attention
 * ���̊֐��́A�X���b�h���g�p���Ȃ�����CRI File System���C�u�������g�p����ꍇ�ɌĂяo���K�v������܂��B<br>
 * �X���b�h���g�p������ł́A���̊֐��̑���ɁA criFs_ExecuteMain �֐������s���Ă��������B<br>
 * \sa
 * criFs_ExecuteMain()
 */
CriError CRIAPI criFs_ExecuteDataDecompression(void);

/*JP
 * \brief �t�@�C���I�[�v���G���[�������̃��g���C���@�̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	mode	���g���C���@
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���̃I�[�v���Ɏ��s�����ꍇ�ɁACRI File System���C�u�������ŃI�[�v���̃��g���C���s�Ȃ����ǂ������w�肵�܂��B<br>
 * ���g���C���@�� CRIFS_OPEN_RETRY_INFINITE ���w�肵���ꍇ�A�t�@�C�����I�[�v���ł���܂�CRI File System���C�u�����̓I�[�v�����������g���C�������܂��B<br>
 * CRIFS_OPEN_RETRY_NONE ���w�肵���ꍇ�ACRI File System���C�u�����̓��g���C�������s�Ȃ킸�A�n���h���̃X�e�[�^�X���G���[��ԂɑJ�ڂ��܂��B
 */
CriError CRIAPI criFs_SetOpenRetryMode(CriFsOpenRetryMode mode);

/*JP
 * \brief �t�@�C�����[�h�G���[�������̃��g���C���@�̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	mode	���g���C���@
 * \return	CriError	�G���[�R�[�h
 * �t�@�C���̃��[�h�Ɏ��s�����ꍇ�ɁACRI File System���C�u�������Ń��[�h�̃��g���C���s�Ȃ����ǂ������w�肵�܂��B<br>
 * ���g���C���@�� CRIFS_READ_RETRY_INFINITE ���w�肵���ꍇ�A�t�@�C�������[�h�ł���܂�CRI File System���C�u�����̓��[�h���������g���C�������܂��B<br>
 * CRIFS_READ_RETRY_NONE ���w�肵���ꍇ�ACRI File System���C�u�����̓��g���C�������s�Ȃ킸�A�n���h���̃X�e�[�^�X���G���[��ԂɑJ�ڂ��܂��B
 */
CriError CRIAPI criFs_SetReadRetryMode(CriFsReadRetryMode mode);

/*JP
 * \brief �O���[�v�D���Ԃ̊J�n
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \param[in]	groupname	�O���[�v��
 * \param[in]	attrname	�A�g���r���[�g��
 * \par ����:
 * �O���[�v�D���Ԃ��J�n���܂��B<br>
 * �{�֐����s��A ::criFs_EndGroup �֐������s����܂ł̊ԁA�w�肵���O���[�v���̃t�@�C�����D��I�Ƀ��[�h�����悤�ɂȂ�܂��B<br>
 * �i�o�C���_���ɓ������O�̃t�@�C�����������݂���ꍇ�ł��A�w�肵���O���[�v���̃t�@�C�����D�悵�đI������܂��B�j<br>
 * �{�֐����g�p���邱�Ƃɂ��A�ʏ�̃��[�_���g�p����ꍇ�ł��A�O���[�v���̉��b���󂯂邱�Ƃ��\�ɂȂ�܂��B<br>
 * \attention
 * �����̃O���[�v�D���Ԃ��d�������邱�Ƃ͂ł��܂���B<br>
 * �{�֐������s��A�K���΂ɂȂ� ::criFs_EndGroup �֐������s���Ă��������B
 * �{�֐��� ::criFs_BeginLoadRegion �֐��𕹗p���邱�Ƃ͂ł��܂���B<br>
 * �iCRI File System Ver.2.02.00���A ::criFs_BeginLoadRegion �֐��͖{�֐����Ăяo���}�N���ɕύX����܂����B�j<br>
 * \sa criFs_EndGroup, criFs_BeginLoadRegion
 */
CriError CRIAPI criFs_BeginGroup(const CriChar8 *groupname, const CriChar8 *attrname);

/*JP
 * \brief �O���[�v�D���Ԃ̏I��
 * \ingroup FSLIB_CRIFS
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �O���[�v�D���Ԃ��I�����܂��B<br>
 * \attention
 * �{�֐��� ::criFs_EndLoadRegion �֐��𕹗p���邱�Ƃ͂ł��܂���B<br>
 * �iCRI File System Ver.2.02.00���A ::criFs_EndLoadRegion �֐��͖{�֐����Ăяo���}�N���ɕύX����܂����B�j<br>
 * \sa criFs_BeginGroup
 */
CriError CRIAPI criFs_EndGroup(void);

/*JP
 * \brief �o�C���_�g�p���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���ݎg�p���̃o�C���_�̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɗ��p�����o�C���_�̐�
 * \param[out]	limit		���p�\�ȃo�C���_�̏����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �o�C���_�̎g�p���Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumUsedBinders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief ���[�_�g�p���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���ݎg�p���̃��[�_�̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɗ��p�������[�_�̐�
 * \param[out]	limit		���p�\�ȃ��[�_�̏����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�_�̎g�p���Ɋւ�������擾���܂��B<br>
 * \par ���l
 * �o�C���_��C���X�g�[�����͓����I�Ƀ��[�_���g�p���܂��B<br>
 * ���̂��߁ACRI File System���C�u�����́A���������ɃR���t�B�M�����[�V�����i ::CriFsConfig �j
 * �Ŏw�肳�ꂽ���ȏ�̃��[�_���쐬����ꍇ������܂��B<br>
 * ���̂��߁A�{�֐��Ŏ擾���郍�[�_�̏�����ilimit�j�́A���������Ɏw�肵���l�ƈقȂ�ꍇ������܂��B<br>
 */
CriError CRIAPI criFs_GetNumUsedLoaders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief �O���[�v���[�_�g�p���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���ݎg�p���̃O���[�v���[�_�̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɗ��p�����O���[�v���[�_�̐�
 * \param[out]	limit		���p�\�ȃO���[�v���[�_�̏����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �O���[�v���[�_�̎g�p���Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumUsedGroupLoaders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief CriFsStdio�n���h���g�p���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���ݎg�p����CriFsStdio�n���h���̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɗ��p����CriFsStdio�n���h���̐�
 * \param[out]	limit		���p�\��CriFsStdio�n���h���̏����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CriFsStdio�n���h���̎g�p���Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumUsedStdioHandles(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief �C���X�g�[���g�p���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���ݎg�p���̃C���X�g�[���̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɗ��p�����C���X�g�[���̐�
 * \param[out]	limit		���p�\�ȃC���X�g�[���̏����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[���̎g�p���Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumUsedInstallers(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief �o�C���h���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���݃o�C���h���̐�
 * \param[out]	max_num		�ߋ��ɍő哯���Ƀo�C���h������
 * \param[out]	limit		�o�C���h�\�񐔂̏���l
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �o�C���h���Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumBinds(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief �I�[�v�����ꂽ�t�@�C�����̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		���݃I�[�v�����̃t�@�C���̐�
 * \param[out]	max_num		�ߋ��ɍő哯���ɃI�[�v�������t�@�C���̐�
 * \param[out]	limit		�I�[�v���\�ȃt�@�C���̏���l
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���̃I�[�v�����Ɋւ�������擾���܂��B<br>
 */
CriError CRIAPI criFs_GetNumOpenedFiles(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*JP
 * \brief I/O�I���R�[���o�b�N�̓o�^
 * \ingroup FSLIB_CRIFS
 * \param[in]	func	I/O�I���R�[���o�b�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * I/O�I���R�[���o�b�N�֐��i ::CriFsSelectIoCbFunc �j��o�^���܂��B<br>
 * CRI File System���C�u�����̓t�@�C���ɃA�N�Z�X����ہA�܂����߂ɁA���̃t�@�C�������݂���f�o�C�X��ID�i ::CriFsDeviceId �j�ƁA
 * �f�o�C�X�ɃA�N�Z�X���邽�߂�I/O�C���^�[�t�F�[�X�i ::CriFsIoInterface �j��I�����܂��B<br>
 * �f�t�H���g��Ԃł́A�f�o�C�XID��I/O�C���^�[�t�F�[�X�̑I���̓��C�u�������ňÖٓI�ɍs�Ȃ��܂����A
 * �{�֐����g�p���邱�ƂŁA�f�o�C�XID��I/O�C���^�[�t�F�[�X�����[�U�����R�Ɏw�肷�邱�Ƃ��\�ɂȂ�܂��B<br>
 * ����ɂ��A���[�U���Ǝ��ɍ쐬����I/O�C���^�[�t�F�[�X���g�p���ăt�@�C���ɃA�N�Z�X���邱�Ƃ��\�ɂȂ�܂��B<br>
 * \code
 * // �Ǝ���I/O�C���^�[�t�F�[�X���`
 * // ���l�j�\���̂̃����o�֐��̓��[�U���Ǝ��Ɏ����B
 * static CriFsIoInterface g_userIoInterface = {
 * 	userExists,
 * 	userRemove,
 * 	userRename,
 * 	userOpen,
 * 	userClose,
 * 	userGetFileSize,
 * 	userRead,
 * 	userIsReadComplete,
 * 	userGetReadSize,
 * 	userWrite,
 * 	userIsWriteComplete,
 * 	userGetWriteSize,
 * 	userFlush,
 * 	userResize,
 * 	userGetNativeFileHandle
 * };
 *
 * // I/O�I���R�[���o�b�N�֐�
 * CriError user_select_io_callback(
 * 	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif)
 * {
 * 	// �p�X����͂��A�f�o�C�X��ID����肷��
 * 	if (strncmp(path, �c) == 0) {
 * 		(*device_id) = CRIFS_DEVICE_�`;
 * 	} else {
 * 		(*device_id) = CRIFS_DEFAULT_DEVICE;
 * 	}
 *
 * 	// �t�@�C���A�N�Z�X�Ɏg�p����I/O�C���^�[�t�F�[�X���w�肷��
 * 	(*ioif) = g_userIoInterface;
 *
 * 	return (CRIERR_OK);
 * }
 *
 * int main(�c)
 * {
 * 		�F
 * 	// I/O�I���R�[���o�b�N��o�^
 * 	criFs_SetSelectIoCallback(user_select_io_callback);
 * 		�F
 * }
 * \endcode
 * \attention
 * �R�[���o�b�N�֐���1�����o�^�ł��܂���B<br>
 * �o�^����𕡐���s�����ꍇ�A���ɓo�^�ς݂̃R�[���o�b�N�֐����A
 * �ォ��o�^�����R�[���o�b�N�֐��ɂ��㏑������Ă��܂��܂��B<br>
 * <br>
 * func��NULL���w�肷��Ƃ��Ƃœo�^�ς݊֐��̓o�^�������s���܂��B<br>
 * \sa CriFsSelectIoCbFunc, criFs_GetDefaultIoInterface
 */
CriError CRIAPI criFs_SetSelectIoCallback(CriFsSelectIoCbFunc func);

/*JP
 * \brief �f�t�H���gI/O�C���^�[�t�F�[�X�̎擾
 * \ingroup FSLIB_CRIFS
 * \param[out]	ioif	I/O�C���^�[�t�F�[�X
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�������f�t�H���g�ŗ��p����I/O�C���^�[�t�F�[�X���擾���܂��B<br>
 * I/O�I���R�[���o�b�N�i::CriFsSelectIoCbFunc�j���Ńf�t�H���g�̏��������������ꍇ�ɂ́A
 * �{�֐��Ŏ擾����I/O�C���^�[�t�F�[�X���A�o�͒l�Ƃ��ĕԂ��Ă��������B<br>
 * \code
 * // �Ǝ���I/O�C���^�[�t�F�[�X���`
 * // ���l�j�\���̂̃����o�֐��̓��[�U���Ǝ��Ɏ����B
 * static CriFsIoInterface g_userIoInterface = {
 * 	userExists,
 * 	userRemove,
 * 	userRename,
 * 	userOpen,
 * 	userClose,
 * 	userGetFileSize,
 * 	userRead,
 * 	userIsReadComplete,
 * 	userGetReadSize,
 * 	userWrite,
 * 	userIsWriteComplete,
 * 	userGetWriteSize,
 * 	userFlush,
 * 	userResize,
 * 	userGetNativeFileHandle
 * };
 *
 * // I/O�I���R�[���o�b�N�֐�
 * CriError user_select_io_callback(
 * 	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif)
 * {
 * 	// �p�X����͂��A�f�o�C�X��ID����肷��
 * 	if (strncmp(path, �c) == 0) {
 * 		(*device_id) = CRIFS_DEVICE_�`;
 * 	} else {
 * 		(*device_id) = CRIFS_DEFAULT_DEVICE;
 * 	}
 *
 * 	// sample.bin�݂̂�Ǝ��C���^�[�t�F�[�X�ŏ�������
 * 	if (strcmp(path, "sample.bin") == 0) {
 * 		(*ioif) = g_userIoInterface;
 * 	} else {
 * 		// ���̃t�@�C���̓f�t�H���gI/O�C���^�[�t�F�[�X�ŏ���
 * 		criFs_GetDefaultIoInterface(ioif);
 * 	}
 *
 * 	return (CRIERR_OK);
 * }
 *
 * int main(�c)
 * {
 * 		�F
 * 	// I/O�I���R�[���o�b�N��o�^
 * 	criFs_SetSelectIoCallback(user_select_io_callback);
 * 		�F
 * }
 * \endcode
 * \sa CriFsSelectIoCbFunc, criFs_SetSelectIoCallback
 */
CriError CRIAPI criFs_GetDefaultIoInterface(CriFsIoInterfacePtr *ioif);

/*JP
 * \brief �f�o�C�X���̎擾
 * \ingroup FSLIB_CRIFS
 * \param[in]	id		�f�o�C�XID
 * \param[out]	info	�f�o�C�X���
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肵���f�o�C�X�̏����擾���܂��B<br>
 * �w�肵���f�o�C�X���t�@�C���̏������݂ɑΉ����Ă��邩�ǂ�����A
 * �ǂݏ����Ɏg�p����o�b�t�@�̃A���C�����g�������K�v���ǂ������m�F���邱�Ƃ��\�ł��B<br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_SetDeviceInfo
 */
CriError CRIAPI criFs_GetDeviceInfo(CriFsDeviceId id, CriFsDeviceInfo *info);

/*JP
 * \brief �f�o�C�X���̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	id		�f�o�C�XID
 * \param[in]	info	�f�o�C�X���
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肵���f�o�C�X�̏���ύX���܂��B<br>
 * I/O���C�������ւ����AI/O���C�����Ńf�o�C�X�̐������ɘa�ł���ꍇ���Ɏg�p���܂��B<br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_GetDeviceInfo
 */
CriError CRIAPI criFs_SetDeviceInfo(CriFsDeviceId id, CriFsDeviceInfo info);

/*JP
 * \brief �������t�@�C���p�X�̍쐬
 * \ingroup FSLIB_CRIFS
 * \param[in]	buffer		�f�[�^�A�h���X
 * \param[in]	buffer_size	�f�[�^�T�C�Y
 * \param[out]	path		�p�X������i�[�̈�
 * \param[in]	length		�p�X������i�[�̈�T�C�Y�i�P�ʂ̓o�C�g�j
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ��������ɔz�u���ꂽ�f�[�^���t�@�C���Ƃ��ăA�N�Z�X���邽�߂̃p�X��������쐬���܂��B<br>
 * ��1�����i buffer �j�Ƒ�2�����i buffer_size �j�Ƀf�[�^�̊i�[�A�h���X�ƃf�[�^�T�C�Y���w�肷�邱�ƂŁA
 * ���Y�f�[�^���t�@�C���Ƃ��Ĉ������߂̃p�X����3�����i path �j�Ɋi�[����܂��B<br>
 * ���A�p�X��������i�[����̈�̃T�C�Y�́A��4�����i length �j�Ŏw�肵�܂��B<br>
 * \par ���l:
 * �{�֐��́A��������Ƀ��[�h���ꂽCPK�t�@�C�����o�C���h����ۂɗ��p���܂��B<br>
 * CPK�t�@�C������������Ƀ��[�h��A���[�h�����̈�̃A�h���X�ƃT�C�Y��{�֐��Ńp�X������ɕϊ����邵�A
 * ::criFsBinder_BindCpk �֐����Ɏw�肷�邱�ƂŁA�I��������CPK�f�[�^�̃o�C���h���\�ɂȂ�܂��B<br>
 * \par ��:
 * \code
 * 		�F
 * 	// CPK�t�@�C������������Ƀ��[�h
 * 	criFsLoader_Load(loader_hn, NULL, "sample.cpk"
 * 		0, cpk_file_size, buffer, buffer_size);
 *
 * 	// �t�@�C���ǂݍ��݊����҂�
 * 	for (;;) {
 * 		criFsLoader_GetStatus(loader_hn, &loader_status);
 * 		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
 * 			break;
 * 		}
 * 			�F
 * 	}
 *
 * 	// �I��������CPK�f�[�^�̃A�h���X�ƃT�C�Y���p�X������ɕϊ�
 * 	criFs_AddressToPath(buffer, buffer_size, path, length);
 *
 * 	// �I��������CPK�̃o�C���h
 * 	criFsBinder_BindCpk(binder_hn, NULL, path,
 * 		bind_work, bind_work_size, &bind_id);
 * 		�F
 * \endcode
 * \attention
 * �p�X������̊i�[�̈�T�C�Y���������ꍇ�A�{�֐��͎��s���A�G���[��Ԃ��܂��B<br>
 * ����A32bit��������Ԃ݂̂̊��ł́A�p�X������̊i�[�̈�� 28 �o�C�g�K�v�ł��B<br>
 * 64bit��������Ԃ̊��ł́A �p�X������̊i�[�̈�� 44 �o�C�g�K�v�ł��B<br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_GetDeviceInfo
 */
CriError CRIAPI criFs_AddressToPath(
	const void *buffer, CriSint64 buffer_size, CriChar8 *path, CriSint32 length);

/*JP
 * \brief �������t�@�C���V�X�e���p�����R�s�[�T�C�Y����̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	limit	�����R�s�[�T�C�Y���
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���T�C�Y�ȉ��̃������R�s�[�������A���C���X���b�h���Ŏ��s����悤�ݒ肵�܂��B<br>
 * <br>
 * �������t�@�C���V�X�e�����g�p����ꍇ�i ::criFs_AddressToPath
 * �֐��ō쐬�����p�X�փA�N�Z�X����ꍇ�j�A�f�[�^�̓]���i���������R�s�[�����j
 * �͒�v���C�I���e�B�̃������R�s�[��p�X���b�h��ōs�Ȃ��܂��B<br>
 * �i�}���`�X���b�h���f���ȊO�̏ꍇ�A�T�[�o�������ŃR�s�[�������s���܂��B�j<br>
 * <br>
 * ���̎d�g�݂ɂ��A����ȃf�[�^���R�s�[����ꍇ�ł��R�s�[������CPU���Ԃ���L����邱�Ƃ��Ȃ��Ȃ邽�߁A
 * �R�s�[�����ɂ�胁�C�����[�v���u���b�N����Ă��܂��A�Ƃ��������ۂ�h�~���邱�Ƃ��ł��܂��B<br>
 * ���ʁA�ʃX���b�h�ōs����R�s�[�������|�[�����O����`�ɂȂ邽�߁A
 * �����ȃf�[�^���R�s�[����ۂł��A�|�[�����O�Ԋu�Ɉˑ������x�����������邱�ƂɂȂ�܂��B<br>
 * <br>
 * �{�֐��œ����R�s�[�T�C�Y�����ݒ肷��ƁA�ݒ肳�ꂽ�T�C�Y�ȉ��̃f�[�^���R�s�[����ہA
 * �ʃX���b�h�ŃR�s�[�������s�킸�A���̏�ŃR�s�[���������s����悤���삪�ύX����܂��B<br>
 * �i���C���X���b�h�ɃR�s�[�������̕��ׂ�������܂����A���[�h�����܂ł̎��Ԃ��Z�k����܂��B�j<br>
 * \par ���l:
 * �f�t�H���g�ݒ�ł͑S�ẴR�s�[�������ʃX���b�h�Ŏ��s����܂��B<br>
 * <br>
 * �{�֐��œ����R�s�[�������L���ɂȂ�ƁA�e���W���[���̓���͈ȉ��̂悤�ɕω����܂��B<br>
 * <br>
 * �ECriFsLoader<br>
 * ::criFsLoader_Load �֐����s����Ƀ��[�_�̃X�e�[�^�X�� CRIFSLOADER_STATUS_COMPLETE �ɑJ�ڂ��܂��B<br>
 * �i ::criFsLoader_Load �֐����ŃR�s�[�������s���܂��B�j<br>
 * <br>
 * �ECriFsStdio<br>
 * ::criFsStdio_ReadFile �֐����ŃX���[�v���Ȃ��Ȃ�܂��B<br>
 * �i ::criFsStdio_ReadFile �֐����ŃR�s�[�������s���܂��B�j<br>
 * \attention
 * ����l��傫���ݒ肵����Ԃŋ���ȃt�@�C�������[�h����ƁA
 * ::criFsLoader_Load �֐����Œ����ԏ������u���b�N����鋰�ꂪ����܂��B<br>
 * <br>
 * 臒l�̔���̓��[�h�v���T�C�Y�ɑ΂��čs���Ă��܂��B<br>
 * ���̂��߁A���ۂɃR�s�[�ł���T�C�Y���w�肳�ꂽ���~�b�g�ȉ��̃T�C�Y�ł����Ă��A
 * ::criFsLoader_Load �֐��� ::criFsStdio_ReadFile
 * �֐��Ɏw�肵�����[�h�v���T�C�Y�����~�b�g�𒴂��Ă���ꍇ�A�ʃX���b�h�ŏ�������܂��B<br>
 * \sa
 * criFs_AddressToPath
 */
CriError CRIAPI criFs_SetMemoryFileSystemSyncCopyLimit(CriSint64 limit);

/*JP
 * \brief ���[�h���~�b�^�̃T�C�Y�̐ݒ�
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in]	limiter_no		���[�h���~�b�^�ԍ�
 * \param[in]	limiter_size	���[�h���~�b�^�T�C�Y�ibyte/1�T�[�o�����j
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * �P�T�[�o����������̓ǂݍ��݃T�C�Y�̐����l��ݒ肵�܂��B<br>
 * ���ʂ̃��~�b�^�ԍ������蓖�Ă��S�Ẵ��[�_�A�O���[�v���[�_�A�o�b�`���[�_�̍��v�ǂݍ��݃T�C�Y���A�����Őݒ肷��T�C�Y�ɐ�������܂��B<br>
 * �����ɒB�������~�b�^�ԍ��̃��[�h�����͈ꎞ�ۗ�����A����̃T�[�o�����Ŏ����I�ɍĊJ���܂��B<br>
 * ���~�b�^�Ɍv�シ�鐔�l�́A���[�h���~�b�^�̒P�ʃT�C�Y�ɐ؂�グ�ĐώZ���܂��B<br>
 * ���k�f�[�^��ǂݍ��ޏꍇ�A�I���W�i���f�[�^�T�C�Y�ł͂Ȃ��A���k�f�[�^�T�C�Y�����~�b�^�Ɍv�サ�܂��B<br>
 * ���k�t�@�C���𕪊��ǂݍ��݂ł��Ȃ����ł́A���k�t�@�C����ǂݍ��ނƂ����~�b�^�̐������z����ꍇ������܂��B���̂悤�Ȋ��ł́A����Ȉ��k�t�@�C���ɑ΂��Ă͎����I�Ƀ��~�b�^�̐��䂪�����Ȃ����Ƃɂ����ӂ��������B<br>
 * �ǂݍ��ݓr���ł����~�b�^�T�C�Y��ύX���邱�Ƃ��ł��܂��B���~�b�^�T�C�Y���[���Ƃ��Ĉꎞ��~���邱�Ƃ��ł��܂��B <br>
 * ���~�b�^�O�Ԃ̃T�C�Y�͐ݒ�ł��܂���B�O�Ԃ͐����̂Ȃ��ʏ�̃��[�h�����Ɋ��蓖�Ă��܂��B <br>
 * ����̓��~�b�^�P�Ԃ������ݒ�\�ł��B<br>
 * ���~�b�^�T�C�Y�̃f�t�H���g�l�� CRIFS_LOADLIMITER_SIZE_DEFAULT �i���~�b�^�����Ȃ��j�ƂȂ��Ă��܂��B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFs_SetLoadLimiterSize(CriFsLoadLimiterNo limiter_no, CriSint32 limiter_size);

/*JP
 * \brief ���[�h���~�b�^�̒P�ʃT�C�Y�̐ݒ�
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in]	limiter_no		���[�h���~�b�^�ԍ�
 * \param[in]	limiter_unit	���[�h���~�b�^�P�ʃT�C�Y�ibyte�j
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * DMA�]���P�ʃT�C�Y��ROM�y�[�W�T�C�Y�ȂǁA�����ǂݍ��݂����e����ŏ��̃T�C�Y��ݒ肵�Ă��������B<br>
 * ���~�b�^�O�Ԃ̒P�ʃT�C�Y�͐ݒ�ł��܂���B�O�Ԃ͐����̂Ȃ��ʏ�̃��[�h�����Ɋ��蓖�Ă��܂��B <br>
 * ����̓��~�b�^�P�Ԃ������ݒ�\�ł��B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFs_SetLoadLimiterUnit(CriFsLoadLimiterNo limiter_no, CriSint32 limiter_unit);

/*JP
 * \brief ���[�h�v���񐔂̐���
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in] limit_num_read_request  �P�T�[�o����������̃��[�h�v���񐔂̏��
 * \return  CriError �G���[�R�[�h
 * \par �����F
 * �P�T�[�o����������̃��[�h�v���񐔂̏����ݒ肵�܂��B<br>
 * �f�t�H���g�l�� CRIFS_READ_REQUEST_NUM_UNLIMITED�i�����Ȃ��j�ƂȂ��Ă��܂��B<br>
 * ���[�h�v�����ɂ�����CPU���ׂ������v���b�g�z�[���ɂ����āA���̊֐��𗘗p����
 * ���ƂŃt�@�C���V�X�e���������CPU���Ԃ𐧌����āA���̕��ׂ����������̂���
 * ��CPU���Ԃ��m�ۂ��邱�Ƃ��ł��܂��B<br>
 * ���̊֐��𗘗p�����ꍇ�A����p�Ƃ��āA�����̏����ȃt�@�C����ǂݍ��ޏꍇ��
 * �X���[�v�b�g���ቺ���܂��B<br>
 */
CriError CRIAPI criFs_LimitNumReadRequest(CriSint32 limit_num_read_request);

/*JP
 * \brief �f�t�H���g�p�X��؂蕶���̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	default_path_separator	�f�t�H���g�p�X��؂蕶���ݒ�
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u���������ŕW���Ƃ��Ĉ����p�X��؂蕶����ݒ肵�܂��B<br>
 * ::CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE ��ݒ肷��ƁA�p�X��؂蕶���������I��
 * ���̃v���b�g�t�H�[���ŕW���Ƃ����p�X��؂蕶���ւƕϊ����ď������܂��B<br>
 * ::CRIFS_DEFAULT_PATH_SEPARATOR_NONE ��ݒ肷��ƁA�p�X��؂蕶���̕ϊ��͍s�킸�A
 * �^����ꂽ�p�X�����̂܂܎g�p����悤�ɂȂ�܂��B<br>
 * ���ݒ莞�iCRI File System���C�u�����̃f�t�H���g�ݒ�j��::CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE �ł��B
 * \sa CriFsDefaultPathSeparator
 */
CriError CRIAPI criFs_SetDefaultPathSeparator(CriFsDefaultPathSeparator default_path_separator);

/*JP
 * \brief �t�@�C��I/O���[�h�̐ݒ�
 * \ingroup FSLIB_CRIFS
 * \param[in]	io_mode �t�@�C��I/O���[�h	
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * CRI File System���C�u�����S�̂̃t�@�C��I/O���[�h��ݒ肵�܂��B<br>
 * ::CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE ��ݒ肷��ƁA�t�@�C���n���h�������C�u���������ŋ��L
 * ���A�t�@�C���A�N�Z�X�������ǂ��s���܂��B<br>
 * ��̓I�ɂ́A::criFsBinder_BindCpk �֐��A::criFsBinder_BindFile �֐����Ăяo�����ɍ쐬
 * �����t�@�C���n���h���̓A���o�C���h����܂Ń��C�u���������ŕێ����A�ێ����̃t�@�C���ɑ΂���A�N�Z�X�ł�
 * �t�@�C���I�[�v�����������܂���B<br>
 * <br>
 * ::CRIFS_FILE_IO_MODE_OPEN_EVERY_TIME ��ݒ肷��ƁA�t�@�C���n���h���̋��L���s�킸�Ƀt�@�C��
 * �A�N�Z�X�̂��тɃt�@�C���I�[�v�����s���܂��B<br>
 * �t�@�C���I�[�v�����ׂ̕������t�@�C���ǂݍ��݂̐��\�͗����܂����A�t�@�C���A�N�Z�X���K�v�Ȏ��̂�
 * �t�@�C���n���h�����쐬���邽�߁A�t�@�C���f�B�X�N���v�^�Ȃǂ̃��\�[�X������ŏ����ɗ}���邱�Ƃ��\�ł��B<br>
 * <br>
 * ���ݒ莞�iCRI File System���C�u�����̃f�t�H���g�ݒ�j�́A�@�킲�ƂɈقȂ�܂��B<br>
 * �@��ŗL�}�j���A���ɋL�ڂ��Ȃ�����A�f�t�H���g�ݒ�� ::CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE �ł��B<br>
 * \par ���ӁF
 * �{�֐��̓��C�u�����������O�ɌĂяo���Ă��������B<br>
 * ���C�u������������ɌĂяo�����Ƃ͏o���܂���B
 *
 * \sa CriFsFileIoMode
 */
CriError CRIAPI criFs_ControlFileIoMode(CriFsFileIoMode io_mode);

/*==========================================================================
 *      CriFsIo API
 *=========================================================================*/

/*==========================================================================
 *      CriFsBinder API
 *=========================================================================*/
/*JP
 * \brief CRI File System - Binder �I�u�W�F�N�g
 * \ingroup FSLIB_BINDER
 * \par ����:
 * CriFsBinder�Ƃ̓t�@�C���f�[�^���f�[�^�x�[�X�����邽�߂̃��W���[���ł��B
 */

/*JP
 * \brief �o�C���_���W���[���֐��Ŏg�p����郁�����Ǘ��֐��̓o�^�^�폜
 * \ingroup FSLIB_BINDER
 * \param[in]	allocfunc	�������m�ۊ֐�
 * \param[in]	freefunc	����������֐�
 * \param[in]	obj			�������Ǘ��I�u�W�F�N�g
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * CriFsBinder�֐��̈����Ŏw�肷�郏�[�N�̈�� NULL ���w�肵���ꍇ�A��������Ă΂�郁�����Ǘ��֐���o�^���܂��B<br>
 * CriFsBinder�֐��� NULL �ȊO���w�肵���ꍇ�́A�n���ꂽ�̈�𗘗p���܂��B<br>
 * <br>
 * �{�֐��ɂ��ACriFsBinder�֐��ɕK�v�ȃ��[�N�̈�̊Ǘ������[�U�[�Ǝ��̃������Ǘ��֐��œ��I�ɍs�����Ƃ��\�ɂȂ�܂��B<br>
 * �{�֐��ɂ�胁�����Ǘ��֐���ݒ肷��ꍇ�́AcriFs_InitializeLibrary�֐��̒���ɖ{�֐����Ăяo���Ă��������B<br>
 * �{�֐��̈���allocfunc, freefunc��NULL�̏ꍇ�A�o�^���ꂽ�������Ǘ��֐����폜���܂��B<br>
 * CriFsBinder�֐��́A���ݓo�^����Ă��郁�����Ǘ��֐����g�p���܂��̂ŁA��U�o�^���ꂽ�������Ǘ��֐����폜�^�ύX����ꍇ�́A
 * �o�^���ꂽ�������Ǘ��֐��𗘗p���Ċm�ۂ��ꂽ�������̈悪�������Ƃ��m�F����悤�ɂ��Ă��������B<br>
 * \par ::criFs_SetUserMallocFunction �֐��Ƃ̊֌W�F
 * �{�֐��œo�^����郁�����Ǘ��֐���CriFsBinder�֐��ł̎g�p�Ɍ��肳��܂��B<br>
 * �{�֐��Ń������Ǘ��֐���o�^�����A::criFs_SetUserMallocFunction �֐��Ŋ֐����o�^����Ă���ꍇ�́A
 * ::criFs_SetUserMallocFunction �֐��œo�^���ꂽ�֐����������m�ێ��Ɍďo����܂��B<br>
 * �{�֐��œo�^���ꂽ�֐�������ꍇ�́A�{�֐��œo�^���ꂽ�������m�ۊ֐����ďo����܂��B<br>
 * \par CPK�o�C���h�ɂ��āF
 * CPK�o�C���h���ɂ́AcriFsBinder_GetWorkSizeForBindCpk�֐��̍��ɂ��L����Ă�ʂ�ACPK��͂ɕK�v�ȃ��[�N�̈�̃T�C�Y��
 * CPK�̍\���Ɉ˂��Ă��܂��̂ŁA���O�ɕK�v�ȃ��[�N�T�C�Y�����ς邱�Ƃ�����ł��B<br>
 * �{�֐��ɂ��ACPK��̓G���W�����v�����郁�����̊Ǘ������[�U�[�Ǝ��̃������Ǘ��֐��ōs�����Ƃ��\�ɂȂ�܂��B<br>
 * \par ��F
 * \code
 * void *u_alloc(void *obj, CriUint32 size)
 * {
 *   :
 * }
 * void u_free(void *obj, void *ptr)
 * {
 *   :
 * }
 * void bind_cpk(void)
 * {
 *  CriFsBindId id;
 *  CriSint32 wksize;
 *  void *work;
 *  // �������Ǘ��֐��̓o�^
 *  criFsBinder_SetUserHeapFunc(u_alloc, u_free, u_mem_obj);
 *
 *  // CPK �o�C���h
 *  criFsBinder_BindCpk(NULL, NULL, "sample.cpk", NULL, 0, &id);
 *    :
 *
 *  // ���[�N���w�肵���ꍇ�A�w�肳�ꂽ���[�N���g�p���܂��B
 *  criFsBinder_GetWorkSizeForBindFile(NULL, "sample.cpk", &wksize);
 *  work = malloc(wksize);
 *  criFsBinder_BindFile(NULL, NULL, "sample.cpk", work, wksize, &id);
 *    :
 *
 *  // CPK�o�C���h���AcriFsBinder_GetWorkSizeForBindCpk �� CPK��͈ȊO��
 *  // �o�C���h�ɕK�v�ȍŒ���K�v�ȃ��[�N�̃T�C�Y��Ԃ��܂��̂ŁA
 *  // ���m��ȗ̈悾���𓮓I�Ɋm�ۂ���悤�Ȏg���������\�ł��B
 *  criFsBinder_GetWorkSizeForBindCpk(NULL, "sample.cpk", &wksize);
 *  work = malloc(wksize);
 *  // CPK �o�C���h
 *  criFsBinder_BindCpk(NULL, NULL, "sample.cpk", work, wksize, &id);
 *    :
 * }
 * \endcode
 */
CriError CRIAPI criFsBinder_SetUserHeapFunc(CriFsMallocFunc allocfunc, CriFsFreeFunc freefunc, void *obj);

/*JP
 * \brief �o�C���_�̐���
 * \ingroup FSLIB_BINDER
 * \param[out]	bndrhn		�o�C���_�n���h��
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���_�𐶐����A�o�C���_�n���h����Ԃ��܂��B<br>
 * \par ��F
 * \code
 * CriFsBinderHn bndrhn;
 * criFsBinder_Create(&bndrhn);
 * 		:
 * criFsBinder_Destroy(bndrhn);
 * \endcode
 * \sa criFsBinder_Destroy()
 */
CriError CRIAPI criFsBinder_Create(CriFsBinderHn *bndrhn);

/*JP
 * \brief �o�C���_�̔j��
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���_��j�����܂��B<br>
 * \par ���ӁF
 * �j������o�C���_�Ƀo�C���h����Ă���o�C���hID�������ɔj������܂��B<br>
 * �{�֐��Ŕj���ł���̂́A::criFsBinder_Create �֐��ɂ�萶�����ꂽ�o�C���_�n���h���݂̂ł��B<br>
 * ::criFsBinder_GetHandle �֐��ɂ�� CriFsBindId ����擾���ꂽ�o�C���_�n���h���͔j���ł��܂���B<br>
 * CriFsBindId �ɂ��Ă� ::criFsBinder_Unbind �֐������g�p���������B
 *
 * \sa criFsBinder_Create() criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_Destroy(CriFsBinderHn bndrhn);

/*JP
 * \brief CPK�t�@�C���o�C���h�̃��[�N�T�C�Y�擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	�o�C���h����CPK�t�@�C���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	path		�o�C���h����CPK�t�@�C���̃p�X��
 * \param[out]	worksize	�K�v���[�N�T�C�Y�i�o�C�g�j
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * criFsBinder_BindCpk�֐��Ɏw�肷�郏�[�N�T�C�Y���擾���܂��B<br>
 * �{�֐��ł́ACPK�̏�����͂��邽�߂ɍŒ���K�v�Ƃ���郏�[�N�T�C�Y���擾�ł��܂��B<br>
 * �R���e���c�t�@�C�����̏���CPK�t�@�C���ł���΁A�{�֐��œ����鐔�l�̂܂܂ł�CPK���o�C���h�ł���\��������܂��B<br>
 * CPK�o�C���h���Ƀ��[�N���������s�������ꍇ�A�G���[�R�[���o�b�N�֐��ŕs�����̗e�ʂ�������܂��B<br>
 * <br>
 * *** CPK�o�C���h�ɕK�v�ȃ��[�N�T�C�Y�̎擾����ɂ́A�ȉ��̕��@������܂��B ***<br><br>
 * �P. �G���[�R�[���o�b�N�𗘗p����B<br>
 * CPK�o�C���h���Ƀ��[�N���������s�������ꍇ�A�G���[�R�[���o�b�N�֐��ɂ��s�����̃T�C�Y��������܂��B<br>
 * ���݊m�ۂ��Ă��郏�[�N�̈�̃T�C�Y�ɁA�G���[�R�[���o�b�N�œ�����T�C�Y�����Z���ă��[�N�̈���Ċm�ۂ��ACPK�o�C���h�����Ȃ����܂��B<br>
 * CPK�o�C���h�����Ȃ����ꍇ�A�������s���G���[�R�[���o�b�N���N�������o�C���_�[ID���A���o�C���h����K�v������܂��B<br>
 * <br>
 * �Q. �������m�ہ^����R�[���o�b�N�֐�( ::criFsBinder_SetUserHeapFunc )�𗘗p����B<br>
 * CPK�o�C���h���Ƀ��[�N�������̊m�ہ^������K�v�ȍۂɌďo�����R�[���o�b�N�֐���o�^���܂��B<br>
 * �o�C���h���ɓK���������m�ۃR�[���o�b�N�֐����ďo���ꂽ�ꍇ�A�v�����ꂽ���������m�ۂ��ăG���[�R�[���o�b�N�֐��̕Ԓl�Ƃ��ĕԂ��܂��B<br>
 * <br>
 * �R. �K�v���[�N�T�C�Y�擾API�i ::criFsBinder_AnalyzeWorkSizeForBindCpk �j�𗘗p����B<br>
 * �o�C���h����CPK��������擾���A�K�v�ƂȂ郏�[�N�T�C�Y���Z�o����֐��𗘗p���܂��B<br>
 * ���̊֐��͊������A�֐��ŁA�֐�������CPK�t�@�C���������ǂݏo���Ă��܂��B���̂��ߊ֐��I���܂łɎ��Ԃ�������܂��B<br>
 * <br>
 * �S. CPK�p�b�L���O�c�[���𗘗p����B<br>
 * �p�b�L���O�c�[����CPK�t�@�C�����h���b�O���h���b�v���ACPK�t�@�C���r���[�A�m�ڍׁn�e�L�X�g�{�b�N�X��
 * �uEnable Filename info.�v�uEnable ID info.�v[Enable Group info.]���ڂɕ\�������o�C�g�����A
 * �{�֐��Ŏ擾�����K�v���[�N�T�C�Y�ɉ��Z���܂��B<br>
 * �������A���̕��@�œ����郏�[�N�T�C�Y�͖ڈ��ł��̂ŁA�������s���G���[�R�[���o�b�N���N����\��������܂��B<br>
 * \sa criFsBinder_BindCpk() criFsBinder_SetUserHeapFunc() criFsBinder_AnalyzeWorkSizeForBindCpk()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindCpk(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

 /*JP
 * \brief CPK�o�C���h�ɕK�v�ȃ��[�N�̈�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	�o�C���_�[�n���h��
 * \param[in]	path		CPK�t�@�C���̃p�X
 * \param[in]	work		CPK�w�b�_��͗p�̃��[�N�̈�
 * \param[in]	wksize	 	CPK�w�b�_��͗p�̃��[�N�̈�̃T�C�Y
 * \param[out]	rqsize		CPK�o�C���h�ɕK�v�ȃ��[�N�̈�̃T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * srcbndrhn �� path �Ŏw�肳�ꂽCPK�t�@�C������͂��ACPK�o�C���h�ɕK�v�ȃ��[�N�̈��
 * �T�C�Y���擾���܂��B<br>
 * �{�֐��͊������A�֐��ł��B<br>
 * �{�֐��́A�w�肳�ꂽCPK�t�@�C���̃w�b�_����ǂݍ���ŉ�͂��Ă��܂��B���̂��߁A
 * �����œǍ��҂����s���Ă��܂��B
 * �{�֐��ɓn�����[�N�̈�́AcriFsBinder_GetWorkSizeForBindCpk�֐��œ���ꂽ�T�C�Y��
 * ���[�N�̈���m�ۂ��ēn���Ă��������B
 * \par ��F
 * \code
 * // ---- CPK��͂ɍŒ���K�v�ȃ������̊m��
 * criFsBinder_GetWorkSizeForBindCpk(bndrhn, path, &wksz)
 * work = malloc(wksz);
 * // CPK�o�C���h�ɕK�v�ȃ������e�ʂ����
 * criFsBinder_AnalyzeWorkSizeForBindCpk(bndrhn, path, work, wksz, &nbyte);
 * free(work);
 * // ----
 * // CPK�o�C���h�p�������̊m��
 * bindwork = malloc(nbyte);
 * // CPK�o�C���h
 * criFsBinder_BindCpk(srcbndr, path, bindwork, nbyte, &bndrid);
 * \endcode
 */
CriError CRIAPI criFsBinder_AnalyzeWorkSizeForBindCpk(
	CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 wksize, CriSint32 *rqsize);

/*UNDESCRIBED
 * \brief CPK�o�C���h�ɕK�v�ȃ��[�N�̈�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	tocsize     CPK�t�@�C����TOC���̃T�C�Y(CPK_TOC_INFO_SIZE)
 * \param[in]	itocsize    CPK�t�@�C����ITOC���̃T�C�Y(CPK_ITOC_INFO_SIZE)
 * \param[in]	gtocsize    CPK�t�@�C����GTOC���̃T�C�Y(CPK_GTOC_INFO_SIZE)
 * \param[out]	rqsize		CPK�o�C���h�ɕK�v�ȃ��[�N�̈�̃T�C�Y(�o�C�g)
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * CPK�t�@�C���o�C���h�ɕK�v�ȃ��[�N�̈�̃T�C�Y���擾���܂��B<br>
 * �{�֐��̈����́ACPK�r���h�̍ۂɏo�͂����CPK�w�b�_�t�@�C���̃V���{��
 * CPK_TOC_INFO_SIZE�ACPK_ITOC_INFO_SIZE�ACPK_GTOC_INFO_SIZE �Œ�`����Ă��鐔�l��
 * �w�肵�܂��B<br>
 * ��`����Ă��Ȃ��V���{���͂O���w�肵�܂��B<br>
 * �Ⴆ�΁AID�̂�CPK�ł�CPK_TOC_INFO_SIZE�ACPK_GTOC_INFO_SIZE����`����Ă��܂���̂ŁA
 * tocsize��gtosize�ɂ͂O���w�肵�܂��B<br>
 * \par ��F
 * \code
 *
 * // CPK�o�C���h�ɕK�v�ȃ������e�ʂ����
 * criFsBinder_CalculateWorkSizeForBindCpk(CPK_TOC_INFO_SIZE, CPK_ITOC_INFO_SIZE, CPK_GTOC_INFO_SIZE,&nbyte);
 * // ----
 * // CPK�o�C���h�p�������̊m��
 * bindwork = malloc(nbyte);
 * // CPK�o�C���h
 * criFsBinder_BindCpk(srcbndr, path, bindwork, nbyte, &bndrid);
 * \endcode
 */
CriError CRIAPI criFsBinder_CalculateWorkSizeForBindCpk(CriSint32 tocsize, CriSint32 itocsize, CriSint32 gtocsize, CriSint32 *rqsize);

/*JP
 * \brief �t�@�C���o�C���h�̃��[�N�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	�o�C���h����t�@�C���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	path		�o�C���h����t�@�C���̃p�X��
 * \param[out]	worksize	�K�v���[�N�T�C�Y�i�o�C�g�j
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * criFsBinder_BindFile�֐��Ɏw�肷�郏�[�N�T�C�Y���擾���܂��B
 * \sa criFsBinder_BindFile()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFile(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

/*JP
 * \brief �����t�@�C���o�C���h�̃��[�N�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	�o�C���h����t�@�C���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	filelist	�o�C���h����t�@�C�����̃��X�g�i�Z�p���[�^�F',''\\t''\\n'  �^�[�~�l�C�^:'\\0'�j
 * \param[out]	worksize	�K�v���[�N�T�C�Y�i�o�C�g�j
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * criFsBinder_BindFiles�֐��Ɏw�肷�郏�[�N�T�C�Y���擾���܂��B
 * \sa criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFiles(CriFsBinderHn srcbndrhn, const CriChar8 *filelist, CriSint32 *worksize);

/*JP
 * \brief �t�@�C���Z�N�V�����o�C���h�̃��[�N�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn		�o�C���h����t�@�C���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	path			�o�C���h����t�@�C���̃p�X��
 * \param[in]	section_name	�Z�N�V������
 * \param[out]	worksize		�K�v���[�N�T�C�Y�i�o�C�g�j
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * criFsBinder_BindFileSection�֐��Ɏw�肷�郏�[�N�T�C�Y���擾���܂��B
 * \sa criFsBinder_BindFileSection()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFileSection(
	CriFsBinderHn srcbndrhn, const CriChar8 *path,
	const CriChar8 *section_name, CriSint32 *worksize);

/*JP
 * \brief �f�B���N�g���o�C���h�̃��[�N�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	�o�C���h����f�B���N�g���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	path		�o�C���h����f�B���N�g���̃p�X��
 * \param[out]	worksize	�K�v���[�N�T�C�Y�i�o�C�g�j
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * criFsBinder_BindDirectory�֐��Ɏw�肷�郏�[�N�T�C�Y���擾���܂��B
 * \sa criFsBinder_BindDirectory()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindDirectory(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

/*JP
 * \brief Cpk�t�@�C���̃o�C���h
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���h��̃o�C���_�n���h��
 * \param[in]	srcbndrhn	�o�C���h����CPK�t�@�C���ɃA�N�Z�X���邽�߂̃o�C���_�n���h��
 * \param[in]	path		�o�C���h���� CPK�t�@�C���̃p�X��
 * \param[in]	work		�o�C���h�p�i���CPK��́j���[�N�̈�
 * \param[in]	worksize	���[�N�̈�̃T�C�Y�i�o�C�g�j
 * \param[out]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * CPK�t�@�C���𗘗p����ɂ́ACPK�t�@�C�����o�C���h����K�v������܂��B<br>
 * �{�֐��́A�o�C���_(bndrhn)��CPK�t�@�C��(path)���o�C���h���A�o�C���hID(bndrid)��Ԃ��܂��B<br>
 * srcbndrhn�ɂ́ACPK�t�@�C�����������邽�߂̃o�C���_���w�肵�܂��B
 * ���ꂪNULL�̏ꍇ�A�f�t�H���g�f�o�C�X���g�p���܂��B<br>
 * ���[�N�̈�(work)�̃T�C�Y�́AcriFsBinder_GetWorkSizeForBindCpk�Ŏ擾�ł��܂��B
 * ���[�N�̈�́A�o�C���hID���j�������܂ŕێ����Ă��������B<br>
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * �o�C���h���J�n�ł��Ȃ��ꍇ�A�o�C���hID�� CRIFSBINDER_BID_NULL ���Ԃ���܂��B<br>
 * �o�C���hID�� CRIFSBINDER_BID_NULL �ȊO���Ԃ��ꂽ�ꍇ�͓������\�[�X���m�ۂ��Ă��܂��̂ŁA
 * �o�C���h�̐����^���s�Ɋւ炸�A�s�v�ɂȂ����o�C���hID�̓A���o�C���h���Ă��������B<br><br>
 * �o�C���h����CPK�t�@�C���̓I�[�v����Ԃŕێ�����܂��B
 * ���̂��߁A�o�C���_������CriFsLoader���쐬���Ă��܂��B<br><br>
 * �{�֐��͑������A�֐��ł��B�{�֐����畜�A��������́ACPK�̃o�C���h�͂܂��������Ă��炸�A
 * CPK�̃R���e���c�t�@�C���ւ̃A�N�Z�X�͍s���܂���B<br>
 * �o�C���h��Ԃ������i CRIFSBINDER_STATUS_COMPLETE �j�ƂȂ�����ɁACPK�͗��p�\�ƂȂ�܂��B<br>
 * �o�C���h��Ԃ� criFsBinder_GetStatus �֐��Ŏ擾���܂��B<br>
 * \par ��F
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindCpk(NULL, "smp.cpk",  &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindCpk(bndrhn, NULL, "smp.cpk", work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindCpk(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
*/
CriError CRIAPI criFsBinder_BindCpk(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*JP
 * \brief �t�@�C���̃o�C���h
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn	�t�@�C���o�C���h������o�C���_�n���h��
 * \param[in]	srcbndrhn	�o�C���h�Ώۂ̃t�@�C�����������邽�߂̃o�C���_�n���h��
 * \param[in]	path		�o�C���h����t�@�C���̃p�X��
 * \param[in]	work		�o�C���h�p���[�N�̈�
 * \param[in]	worksize	���[�N�̈�̃T�C�Y�i�o�C�g�j
 * \param[out]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �t�@�C�����o�C���h���A�o�C���hID��Ԃ��܂��B<br>
 * srcbndrhn�̃o�C���_����path�Ŏw�肳�ꂽ�t�@�C�����������Abndrhn�Ƀo�C���h���܂��B
 * srcbndrhn��NULL�̏ꍇ�A�f�t�H���g�f�o�C�X��̃t�@�C�����������܂��B<br>
 * ���[�N�̈�(work)�̃T�C�Y�́AcriFsBinder_GetWorkSizeForBindFile�Ŏ擾�ł��܂��B
 * ���[�N�̈�́A�o�C���hID���j�������܂ŕێ����ĉ������B<br>
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * �o�C���h���J�n�ł��Ȃ��ꍇ�A�o�C���hID�� CRIFSBINDER_BID_NULL ���Ԃ���܂��B
 * �o�C���hID�� CRIFSBINDER_BID_NULL �ȊO���Ԃ��ꂽ�ꍇ�͓������\�[�X���m�ۂ��Ă��܂��̂ŁA
 * �o�C���h�̐����^���s�Ɋւ炸�A�s�v�ɂȂ����o�C���hID�̓A���o�C���h���Ă��������B<br><br>
 * �o�C���h���ꂽ�t�@�C���̓t�@�C���I�[�v����Ԃŕێ����܂��B
 * ���̂��߁A�����I��CriFsLoader���쐬���Ă��܂��B<br><br>
 * �{�֐��͑������A�֐��ł��B�{�֐����畜�A��������́A�t�@�C���̃o�C���h�͂܂��������Ă��炸�A
 * �o�C���hID�𗘗p�����t�@�C���ւ̃A�N�Z�X�͍s���܂���B<br>
 * �o�C���hID�̃o�C���h��Ԃ������i CRIFSBINDER_STATUS_COMPLETE �j�ƂȂ�����ɁA
 * �t�@�C���͗��p�\�ƂȂ�܂��B<br>
 * �o�C���h��Ԃ� criFsBinder_GetStatus �֐��Ŏ擾���܂��B<br>
 * \par ��F
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindFile(NULL, "sample.txt", &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindFile(bndrhn, NULL, "sample.txt", work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * // �f�[�^�̃��[�h (�t�@�C���I�[�v����Ԃł̃A�N�Z�X)
 * criFsBinder_GetFileSize(binder, "sample.txt", &fsize); 
 * criFsLoader_Load(loader, binder, "sample.txt", 0, fsize, buffer, buffer_size); 
 * // ���[�h�҂�... 
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_BindFile(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*JP
 * \brief �����t�@�C���̃o�C���h
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn	�t�@�C���o�C���h������o�C���_�n���h��
 * \param[in]	srcbndrhn	�o�C���h�Ώۂ̃t�@�C�����������邽�߂̃o�C���_�n���h��
 * \param[in]	filelist	�o�C���h����t�@�C�����̃��X�g�i�Z�p���[�^�F',''\\t''\\n'  �^�[�~�l�C�^:'\\0'�j
 * \param[in]	work		�o�C���h�p���[�N�̈�
 * \param[in]	worksize	���[�N�̈�̃T�C�Y
 * \param[out]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �t�@�C�����X�g(filelist)�ɗ�L���ꂽ�t�@�C�����o�C���h���܂��B<br>
 * �t�@�C����srcbndrhn���猟������܂����Asrcbndrhn��NULL�̏ꍇ�A�f�t�H���g�f�o�C�X���g�p����܂��B<br>
 * ���[�N�̈�̃T�C�Y�́AcriFsBinder_GetWorkSizeForBindFiles �Ŏ擾�ł��܂��B
 * ���[�N�̈�́A�o�C���hID���j�������܂ŕێ����ĉ������B<br><br>
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * �o�C���h���J�n�ł��Ȃ��ꍇ�A�o�C���hID�� CRIFSBINDER_BID_NULL ���Ԃ���܂��B
 * �o�C���hID�� CRIFSBINDER_BID_NULL �ȊO���Ԃ��ꂽ�ꍇ�͓������\�[�X���m�ۂ��Ă��܂��̂ŁA
 * �o�C���h�̐����^���s�Ɋւ炸�A�s�v�ɂȂ����o�C���hID�̓A���o�C���h���Ă��������B<br><br>
 * �o�C���h�����t�@�C���̓t�@�C���I�[�v����Ԃŕێ����܂��B
 * �����I�ɂ� CriFsLoader ���o�C���hID�ɂP�쐬����A�t�@�C���n���h�����o�C���h����t�@�C�������g�p����܂��B<br><br>
 * �{�֐��͑������A�֐��ł��B�{�֐����畜�A��������́A�t�@�C���̃o�C���h�͂܂��������Ă��炸�A
 * �o�C���_�𗘗p�����t�@�C���ւ̃A�N�Z�X�͍s���܂���B<br>
 * �o�C���h��Ԃ������i CRIFSBINDER_STATUS_COMPLETE �j�ƂȂ�����ɁA�t�@�C���͗��p�\�ƂȂ�܂��B<br>
 * �o�C���h��Ԃ� criFsBinder_GetStatus �֐��Ŏ擾���܂��B<br>
 * \par ��F
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * CriChar8 *flist = "a.txt,b.txt,c.txt";
 * criFsBinder_GetWorkSizeForBindFiles(NULL, flist, &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindFiles(bndrhn, NULL, flist, work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFiles(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_BindFiles(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *filelist, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*JP
 * \brief �t�@�C���Z�N�V�����̃o�C���h
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn		�t�@�C���Z�N�V�����o�C���h������o�C���_�n���h��
 * \param[in]	srcbndrhn		�o�C���h�Ώۂ̃t�@�C�����������邽�߂̃o�C���_�n���h��
 * \param[in]	path			�o�C���h����t�@�C���̃p�X��
 * \param[in]	offset			�f�[�^�̊J�n�ʒu�i�o�C�g�j
 * \param[in]	size			�f�[�^�T�C�Y�i�o�C�g�j
 * \param[in]	section_name	�Z�N�V������
 * \param[in]	work			�o�C���h�p���[�N�̈�
 * \param[in]	worksize		���[�N�̈�̃T�C�Y�i�o�C�g�j
 * \param[out]	bndrid			�o�C���hID
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �t�@�C���̈ꕔ�����o�C���h���A���̉ӏ������z�I�ȃt�@�C���Ƃ��Ĉ�����悤�ݒ肵�܂��B<br>
 * srcbndrhn�̃o�C���_����path�Ŏw�肳�ꂽ�t�@�C�����������ăo�C���h���܂��B
 * srcbndrhn��NULL�̏ꍇ�A�f�t�H���g�f�o�C�X���g�p���܂��B<br>
 * ���[�N�̈�(work)�̃T�C�Y�́AcriFsBinder_GetWorkSizeForBindFileSection�Ŏ擾�ł��܂��B
 * ���[�N�̈�́A�o�C���hID���j�������܂ŕێ����ĉ������B<br>
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * �o�C���h���J�n�ł��Ȃ��ꍇ�A�o�C���hID�� CRIFSBINDER_BID_NULL ���Ԃ���܂��B
 * �o�C���hID�� CRIFSBINDER_BID_NULL �ȊO���Ԃ��ꂽ�ꍇ�͓������\�[�X���m�ۂ��Ă��܂��̂ŁA
 * �o�C���h�̐����^���s�Ɋւ炸�A�s�v�ɂȂ����o�C���hID�̓A���o�C���h���Ă��������B<br><br>
 * �o�C���h���ꂽ�t�@�C���̓t�@�C���I�[�v����Ԃŕێ����܂��B
 * ���̂��߁A�����I��CriFsLoader���쐬���Ă��܂��B<br><br>
 * �{�֐��͑������A�֐��ł��B�{�֐����畜�A��������́A�t�@�C���̃o�C���h�͂܂��������Ă��炸�A
 * �o�C���hID�𗘗p�����t�@�C���ւ̃A�N�Z�X�͍s���܂���B<br>
 * �o�C���hID�̃o�C���h��Ԃ������i CRIFSBINDER_STATUS_COMPLETE �j�ƂȂ�����ɁA
 * �t�@�C���͗��p�\�ƂȂ�܂��B<br>
 * �o�C���h��Ԃ� criFsBinder_GetStatus �֐��Ŏ擾���܂��B<br>
 * \par ��F
 * \code
 * CriFsBindId binder_id;
 * CriFsBinderStatus status;
 * 	�F
 * // sample.txt��100�o�C�g�ڂ���5000�o�C�g����STAGE1�Ƃ������O�Ńo�C���h
 * // ���l�j�A���P�[�^�����O�ɓo�^�ς݂ł���΃��[�N�̈�T�C�Y�̎w��͕s�v�B
 * criFsBinder_BindFileSection(binder_hn, NULL, "sample.txt", 100, 5000, "STAGE1", NULL, 0, &binder_id);
 *
 * // �o�C���h�����҂�
 * for (;;) {
 * 	// �o�C���h��Ԃ̃`�F�b�N
 * 	criFsBinder_GetStatus(binder_id, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 *
 * 	// �T�[�o�����̎��s
 * 	criFs_ExecuteMain();
 *
 * 	// Vsync�҂���
 * 	�c
 * }
 *
 * // �o�C���h�ς݂̃Z�N�V�����̃f�[�^��ǂݍ���
 * // ���l�j���[�h���̃p�X�ɂ̓Z�N�V���������w�肷��B
 * criFsLoader_Load(loader_hn, binder_hn, "STAGE1", 0, 5000, buffer, buffer_size);
 * 	�F
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFileSection, criFsBinder_GetStatus, criFsBinder_Unbind
 */
CriError CRIAPI criFsBinder_BindFileSection(
	CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path,
	CriUint64 offset, CriSint32 size, const CriChar8 *section_name,
	void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*JP
 * \brief �f�B���N�g���p�X�̃o�C���h
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	srcbndrhn	�o�C���h�����f�B���N�g�����Ńt�@�C���ɃA�N�Z�X����ۂ̃o�C���_
 * \param[in]	path		�o�C���h����f�B���N�g���p�X��
 * \param[in]	work		�o�C���h�p���[�N�̈�
 * \param[in]	worksize	���[�N�̈�̃T�C�Y�i�o�C�g�j
 * \param[out]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �f�B���N�g���p�X�����o�C���h���܂��B<br>
 * �o�C���h����f�B���N�g�����͐�΃p�X�Ŏw�肵�Ă��������B
 * �o�C���h���Ɏw�肳�ꂽ�f�B���N�g�������݂��邩�ۂ��̓`�F�b�N���Ă��܂���B<br>
 * �o�C���h�����̂̓f�B���N�g���p�X�����ŁA�w�肳�ꂽ�f�B���N�g�����̃t�@�C����
 * �I�[�v����Ԃɂ�����̂ł͂���܂���B����ăo�C���h�Ɏ��s���Ȃ�����A�{�֐����畜�A���ɂ�
 * �o�C���hID�̃o�C���h��Ԃ͊����i CRIFSBINDER_STATUS_COMPLETE �j�ƂȂ�܂��B<br>
 * srcbndrhn�ɂ́A�{�֐��Ńo�C���h�����f�B���N�g����p���ăt�@�C������������ۂɁA
 * �����ΏۂƂȂ�o�C���_���w�肵�܂��B<br>
 * ���[�N�̈�(work)�̃T�C�Y�́AcriFsBinder_GetWorkSizeForBindDirectory�Ŏ擾�ł��܂��B
 * ���[�N�̈�́A�o�C���hID���j�������܂ŕێ����ĉ������B<br>
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * �o�C���h���J�n�ł��Ȃ��ꍇ�A�o�C���hID�� CRIFSBINDER_BID_NULL ���Ԃ���܂��B
 * �o�C���hID�� CRIFSBINDER_BID_NULL �ȊO���Ԃ��ꂽ�ꍇ�͓������\�[�X���m�ۂ��Ă��܂��̂ŁA
 * �o�C���h�̐����^���s�Ɋւ炸�A�s�v�ɂȂ����o�C���hID�̓A���o�C���h���Ă��������B<br>
 * \par ���l�F
 * �ő哯���Ƀo�C���h�\�ȃf�B���N�g�����ɂ͐���������܂��B<br>
 * ��̓I�ɂ́ACriFsConfig �� num_binders �� max_binds �̒l���[���ł����Ă��A
 * ����͍ő�16�iPC�̂�64�j�܂ł����f�B���N�g�����o�C���h���邱�Ƃ��ł��܂���B<br>
 * \attention
 * �{�֐��͊J���x���p�̃f�o�b�O�֐��ł��B<br>
 * �{�֐����g�p�����ꍇ�A�ȉ��̖�肪��������\��������܂��B<br>
 * - criFsLoader_Load�֐���criFsBinder_GetFileSize�֐����ŏ����������ԃu���b�N�����B<br>
 * - �o�C���h�����f�B���N�g�����̃t�@�C���ɃA�N�Z�X����ہA�����⃀�[�r�[�̃X�g���[���Đ����r�؂��B<br>
 * .
 * <br>
 * �}�X�^�[�A�b�v���ɂ͖{�֐����A�v���P�[�V�������Ŏg�p���Ȃ��悤�����ӂ��������B<br>
 * �i�f�B���N�g�����̃f�[�^��CPK�t�@�C��������criFsBinder_BindCpk�֐��Ńo�C���h���邩�A�܂��̓f�B���N�g�����̃t�@�C����S��criFsBinder_BindFiles�֐��Ńo�C���h���Ă��������B�j<br>
 * \par ��F
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindDirectory(bndrhn, "/cri/samples/", &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindDirectory(bndrhn, bndrhn, "/cri/samples/", work, wksz, &bndrid);
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindDirectory(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind(), criFsBinder_BindCpk(), criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_BindDirectory(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*JP
 * \brief �o�C���hID�̍폜�i�A���o�C���h�j�F�������A�֐�
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���hID���o�C���_����폜���܂��B<br>
 * �{�֐��͊������A�֐��ł��B
 * �w�肳�ꂽ�o�C���hID���폜�ł��Ȃ��ꍇ�ACRIERR_NG��Ԃ��܂��B<br>
 * \par �⑫�F
 * �K�v�ɉ����ăt�@�C���̃N���[�Y�������s���܂��̂ŁA���s���ɂ�萔msec������ꍇ������܂��B<br>
 * �A���o�C���h����o�C���hID�Ɉˑ����Ă��鑼�̃o�C���hID�������ɃA���o�C���h����܂��i�ÖٓI�A���o�C���h�j�B<br>
 * �Ⴆ�΁ACPK�o�C���hID�̃R���e���c�t�@�C����FILE�o�C���h���Ă���o�C���hID�́A
 * �Q�ƌ���CPK�o�C���hID���A���o�C���h�����ƁA�ÖٓI�A���o���h����܂��B
 * �ÖٓI�ɃA���o�C���h���ꂽ���ڂ́A�ÖٓI�A���o�C���h���X�g�ɒǉ�����܂��B<br>
 * �ÖٓI�A���o�C���h���ꂽ�o�C���hID�́A�ʏ�ǂ����criFsBinder_Unbind�֐��ŃA���o�C���h���邩�A
 * criFsBinder_CleanImplicitUnbindList�֐��ňÖٓI�A���o�C���h���X�g���N���A����K�v������܂��B
 * \par ��F
 * \code
 * // CPK�t�@�C���̃o�C���h
 * criFsBinder_BindCpk(bndrhn, NULL, cpkpath, cpkwk, cpkwksz, &cpkid);
 * 	:
 * // fileid�́Acpkid�̃R���e���c�t�@�C�����o�C���h
 * criFsBinder_BindFile(bndrhn, bndrhn, cntspath, filewk, filewksz, &fileid);
 * 	:
 * // CPK�o�C���hID�̃A���o�C���h
 * criFsBinder_Unbind(cpkid);	// ������fileid�͈ÖٓI�A���o�C���h�����B
 * // File�o�C���hID�̃A���o�C���h
 * criFsBinder_Unbind(fileid);
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_CleanImplicitUnbindList()
 */
CriError CRIAPI criFsBinder_Unbind(CriFsBindId bndrid);

/*JP
 * \brief �o�C���hID�̍폜�i�A���o�C���h�j�F�������A�֐�
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \return		CriError	�G���[�R�[�h
 *
 * \par �����F
 * �o�C���hID���o�C���_����폜���܂��B<br>
 * �{�֐��͑������A�֐��ł��B<br>
 * �w�肳�ꂽ�o�C���hID���폜�ł��Ȃ��ꍇ�ACRIERR_NG��Ԃ��܂��B<br>
 * �A���o�C���h������i�s������ɂ́A�T�[�o���� criFsExecuteMain �֐��ƁAcriFsBinder_GetStatus �֐���
 * �Ăяo�����K�v�ł��B<br>
 *
 * \par �A���o�C���h�����̌��m�F
 * �A���o�C���h�����̊����� criFsBinder_GetStatus �֐��Ŏ擾�����X�e�[�^�X�ɂ�蔻�f���܂��B<br>
 * �A���o�C���h�������̃X�e�[�^�X�� CRIFSBINDER_STATUS_UNBIND �ɂȂ�܂��B<br>
 * �A���o�C���h������̃X�e�[�^�X�� CRIFSBINDER_STATUS_REMOVED �ƂȂ�܂��B<br>
 *
 * \par �⑫�F
 * �o�C���hID�Ƃ��Ď�蓾��l�ŁA���̎��_�ɂ����Ďg�p����Ă��Ȃ��l���w�肵���ꍇ�A�擾�����X�e�[�^�X��
 * CRIFSBINDER_STATUS_REMOVED�ɂȂ�܂��B<br>
 * �A���o�C���h����o�C���hID�Ɉˑ����Ă��鑼�̃o�C���hID�������ɃA���o�C���h����܂��i�ÖٓI�A���o�C���h�j�B<br>
 * �Ⴆ�΁ACPK�o�C���hID�̃R���e���c�t�@�C����FILE�o�C���h���Ă���o�C���hID�́A
 * �Q�ƌ���CPK�o�C���hID���A���o�C���h�����ƁA�ÖٓI�A���o���h����܂��B<br>
 * �ÖٓI�ɃA���o�C���h���ꂽ���ڂ́A�ÖٓI�A���o�C���h���X�g�ɒǉ�����܂��B<br>
 * �ÖٓI�A���o�C���h���ꂽ�o�C���hID�́A�ʏ�ǂ����criFsBinder_Unbind�֐��ŃA���o�C���h���邩�A
 * criFsBinder_CleanImplicitUnbindList�֐��ňÖٓI�A���o�C���h���X�g���N���A����K�v������܂��B<br>
 *
 * \par ��F
 * \code
 * // CPK�t�@�C���̃o�C���h
 * criFsBinder_BindCpk(bndrhn, NULL, cpkpath, cpkwk, cpkwksz, &bndrid);
 * 	:
 * // CPK�o�C���hID�̃A���o�C���h
 * criFsBinder_UnbindAsync(bndrid);
 * // �A���o�C���h�����҂�
 * while (1) {
 *   CriFsBinderStatus status;
 *   criFsBinder_GetStatus(bndrid, &status);
 *   // �A���o�C���h����
 *   if (status==CRIFSBINDER_STATUS_REMOVED)
 *      break;
 *   // �T�[�o�����̎��s
 *   criFs_ExecuteMain();
 * }
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_CleanImplicitUnbindList()
 */
CriError CRIAPI criFsBinder_UnbindAsync(CriFsBindId bndrid);

/*JP
 * \brief �ÖٓI�A���o�C���h���X�g�̃N���A
 * \ingroup FSLIB_BINDER
 * \return	CriError	�G���[�R�[�h
 * \par �����F
 * �ÖٓI�A���o�C���h���X�g�ɓo�^����Ă���S�Ẵo�C���hID�𖢎g�p���X�g�֖߂��܂��B<br>
 * �ÖٓI�A���o�C���h�����̃o�C���hID�́A���̗l�ȏꍇ�ł��B<br>
 *  �E���̃o�C���hID�Ɉˑ������t�@�C�����o�C���h���Ă���ꍇ�iCPK�̃R���e���c�t�@�C���Ȃǁj�B<br>
 *  �E�e�o�C���hID���A���o�C���h���ꂽ�ꍇ�B
 * \sa criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_CleanImplicitUnbindList(void);

/*JP
 * \brief �o�C���h��Ԃ̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid	�o�C���hID
 * \param[out]	status	CriFsBinderStatus�o�C���_�X�e�[�^�X
 * \return	CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�o�C���hID�̃o�C���h��Ԃ��擾���܂��B <br>
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ɂȂ�܂ł́A
 * ���̃o�C���hID�ɂ��t�@�C���A�N�Z�X���s���܂���B<br>
 * \par ��F
 * \code
 * CriFsBinderStatus status;
 * criFsBinder_GetStatus(bndrid, &status);
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_GetStatus(CriFsBindId bndrid, CriFsBinderStatus *status);

/*JP
 * \brief �t�@�C�����̎擾�i�t�@�C�����w��j
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	filepath	�t�@�C���̃t���p�X
 * \param[out]	finfo		�t�@�C�����\����
 * \param[out]	exist		�t�@�C���������ʁiCRI_TRUE:�擾�����@CRI_FALSE:�擾���s�j
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C�����o�C���_���猟�����A���̏���Ԃ��܂��B<br>
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���o�C���hID�݂̂������ΏۂƂ��܂��B<br>
 * �t�@�C�������t�������ꍇ�� exist��CRI_TRUE���A�t�@�C�����\����(finfo)�Ƀt�@�C�������Z�b�g���܂��B<br>
 * �t�@�C�������t����Ȃ��ꍇ�Aexist��CRI_FALSE���Z�b�g���܂��B<br>
 * finfo��NULL�̏ꍇ�Aexist�Ƀt�@�C���̌������ʂ݂̂��Z�b�g���܂��B
 * \par ��F
 * \code
 * CriFsBinderFileInfo finfo;
 * CriBool exist;
 * criFsBinder_Find(bndrhn, "a.txt", &finfo, &exist);
 * if (exist == CRI_TRUE) { // File is found.
 * }
 * else {// File cannot found.
 * }
 * \endcode
 * * \sa criFsBinder_GetStatus()
*/
CriError CRIAPI criFsBinder_Find(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriFsBinderFileInfo *finfo, CriBool *exist);

/*JP
 * \brief �t�@�C�����̎擾�iID�w��j
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	id			CPK�R���e���c�t�@�C��ID
 * \param[out]	finfo		�t�@�C�����\����
 * \param[out]	exist		�t�@�C���������ʁiCRI_TRUE:�擾�����@CRI_FALSE:�擾���s�j
 * \return		CriError 	�G���[�R�[�h
 * \par �����F
 * �o�C���_�n���h������A�w�肳�ꂽID�̃t�@�C�����������A���̏���Ԃ��܂��B<br>
 * ID����CPK�t�@�C�����o�C���h���Ă���K�v������܂��B<br>
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���o�C���hID�݂̂������ΏۂƂ��܂��B<br>
 * �t�@�C�������t�������ꍇ�� exist��CRI_TRUE���Z�b�g���A�t�@�C�����\����(finfo)�Ƀt�@�C�������Z�b�g���܂��B<br>
 * �t�@�C�������t����Ȃ��ꍇ�Aexist��CRI_FALSE���Z�b�g���܂��B<br>
 * finfo��NULL�̏ꍇ�Aexist�Ƀt�@�C���̌�������(CRI_TRUE/CRI_FALSE)�݂̂��Z�b�g���܂��B
 * \par ��F
 * \code
 * CriFsBinderFileInfo finfo;
 * CriBool exist;
 * criFsBinder_FindById(bndrhn, 10, &finfo, &exist);
 * if (exist == CRI_TRUE) { // File is found.
 * }
 * else { // File cannot found.
 * }
 * \endcode
 * \sa criFsBinder_GetStatus() criFsBinder_BindCpk()
*/
CriError CRIAPI criFsBinder_FindById(CriFsBinderHn bndrhn, CriFsFileId id, CriFsBinderFileInfo *finfo, CriBool *exist);

/*JP
 * \brief CriFsBinderHn�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[out]	bndrhn		�o�C���_�n���h��
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * CriFsBindId��CriFsBinderHn�ɕϊ����܂��B<br>
 * �V����CriFsBinderHn�𐶐�������̂ł͂Ȃ��A�^�ϊ����s�����̂ƍl���Ă��������B <br>
 * ����āA���̂Ƃ��Ă͓������̂��w���Ă���A�{�֐���CriFsBinderHn�̃��\�[�X������邱�Ƃ͂���܂���B<br>
 * ����CriFsBindId�����̂܂� CriFsBindId �Ƃ��Ďg�p�ł��܂��B<br>
 * �o�C���h���ꂽ�t�@�C���̏��𓾂�ꍇ�A�o�C���h���ꂽ�o�C���hID�����Ɍ�������܂��B<br>
 * ���̂��߁A����̃o�C���hID�ɂ���t�@�C���ɃA�N�Z�X�������ꍇ�A�ړI�̃o�C���hID����
 * �o�C���_�n���h�����擾���Ďg�p���邱�ƂŁA�����I�Ȍ������s�����Ƃ��\�ɂȂ�܂��B<br>
 * \par ���ӁF
 * �{�֐��ɂ��擾���ꂽ CriFsBinderHn �� ::criFsBinder_Destroy �֐��ł͔j���ł��܂���B
 * ���ƂȂ� CriFsBindId �� ::criFsBinder_Unbind �֐��ŃA���o�C���h���Ă��������B<br>
 * \par ��F
 * \code
 * // CPK���o�C���h����
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // �o�C���hID ����o�C���_�n���h���𓾂�
 * criFsBinder_GetHandle(cpk_bndrid, &cpk_bndrhn);
 * // ���̃n���h����p���ăt�@�C�������擾����
 * criFsBinder_Find(cpk_bndrhn, filepath, &finfo, &exist);
 *  :
 * // �o�C���hID���A���o�C���h����B�擾���ꂽ�o�C���_�n���h�����g�p�ł��Ȃ��Ȃ�
 * criFsBinder_Unbind(cpk_bndrid);
 * \endcode
 * \sa criFsBinder_Unbind
 */
CriError CRIAPI criFsBinder_GetHandle(CriFsBindId bndrid, CriFsBinderHn *bndrhn);

/*JP
 * \brief �t�@�C���T�C�Y�̎擾�i�t�@�C�����w��j
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	filepath	�t�@�C���̃t���p�X
 * \param[out]	size		�t�@�C���̃T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C���̃t�@�C���T�C�Y���擾���܂��B<br>
 * �܂��Abndrhn �̃o�C���_����ړI�̃t�@�C�����������܂��B <br>
 * bndrhn �ɖړI�̃t�@�C�������݂��Ȃ��ꍇ�A�f�t�H���g�f�o�C�X��filepath�̃t�@�C����T���܂��B
 * ���̂Ƃ��A�t�@�C�����I�[�v���҂�������ꍇ������܂��B<br>
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���o�C���hID�������ΏۂƂ��܂��B<br>
 * �w�肳�ꂽ�t�@�C�������݂��Ȃ��ꍇ�Asize�ɂ͕��l���ݒ肳��܂��B
 * \par ���l:
 * �{�֐��́A�����I�� ::criFsBinder_Find �֐������s���A
 * �t�@�C�����o�C���_�ɓo�^����Ă��Ȃ���΃t�@�C��I/O�ɃA�N�Z�X���ăt�@�C���̗L���𒲂ׂ�A
 * �Ƃ��������ɂȂ��Ă��܂��B<br>
 * �i�o�C���_�ɓo�^����Ă��Ȃ��t�@�C����A���݂��Ȃ��t�@�C���ɑ΂��Ė{�֐������s�����ꍇ�A
 * �t�@�C��I/O�ւ̃A�N�Z�X���������A�����ԏ������u���b�N�����\��������܂��B�j<br>
 * <br>
 * �t�@�C�����o�C���_�ɓo�^����Ă��邩�ǂ������`�F�b�N�������ꍇ�ɂ́A
 * �{�֐��̑���ɁA ::criFsBinder_Find �֐��������p���������B<br>
 * \attention
 * �ȉ��̃P�[�X�ł́A�{�֐����Œ����ԏ������u���b�N�����ꍇ������܂��B
 * 	- �o�C���_�n���h����NULL���w�肵���ꍇ
 * 	- �o�C���_�ɓo�^����Ă��Ȃ��t�@�C�����w�肵���ꍇ
 * 	- �����ȃp�X�i���݂��Ȃ��t�@�C���j���w�肵���ꍇ
 * 	- criFsBinder_BindDirectory�֐��Ńf�B���N�g�����o�C���h�����n���h�����w�肵���ꍇ
 * 	.
 * \sa criFsBinder_GetFileSizeById, criFsBinder_Find
 */
CriError CRIAPI criFsBinder_GetFileSize(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriSint64 *size);

/*JP
 * \brief �t�@�C���T�C�Y�̎擾�iID�w��j
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	id			�t�@�C����ID
 * \param[out]	size		�t�@�C���̃T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �t�@�C���T�C�Y���擾���܂��B<br>
 * ID����CPK�t�@�C�����o�C���h����Ă���K�v������܂��B<br>
 * bndrhn �̃o�C���_����ړI�̃t�@�C�����������܂��B
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���CPK�o�C���hID�݂̂������ΏۂƂ��܂��B<br>
 * \sa criFsBinder_GetFileSize
 */
CriError CRIAPI criFsBinder_GetFileSizeById(CriFsBinderHn bndrhn, CriFsFileId id, CriSint64 *size);

/*JP
 * \brief ROM�A�h���X�̎擾�i�t�@�C�����w��j
 * \ingroup FSLIB_BINDER_EMB
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	filepath	�t�@�C���̃t���p�X
 * \param[out]	rom_address	ROM�A�h���X
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C����ROM�A�h���X���擾���܂��B<br>
 * bndrhn �̃o�C���_����ړI�̃t�@�C�����������܂��B <br>
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���o�C���hID�������ΏۂƂ��܂��B<br>
 * �o�C���_�̎g�p�͕K�{�ł��B�o�C���_�n���h���ɂ�NULL�͎w��ł��܂���B
 * �f�B���N�g���o�C���h�̓T�|�[�g���܂���BcriFsBinder_BindDirectory �Ŏg�p�����n���h���͎w��ł��܂���B
 * �w�肳�ꂽ�t�@�C�������݂��Ȃ��ꍇ�Arom_address �ɂ� CRIFS_ROM_ADDRESS_INVALID ���ݒ肳��܂��B
 * \attention
 * �Q�[���@�����ł͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa criFsBinder_GetRomAddress() criFsBinder_GetRomAddressById()
 */
CriError CRIAPI criFsBinder_GetRomAddress(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriUint64Adr *rom_address);

/*JP
 * \brief ROM�A�h���X�̎擾�iID�w��j
 * \ingroup FSLIB_BINDER_EMB
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	id			�t�@�C����ID
 * \param[out]	rom_address	ROM�A�h���X
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C����ROM�A�h���X���擾���܂��B<br>
 * ID����CPK�t�@�C�����o�C���h����Ă���K�v������܂��B<br>
 * bndrhn �̃o�C���_����ړI�̃t�@�C�����������܂��B
 * �o�C���h��Ԃ� CRIFSBINDER_STATUS_COMPLETE �ł���CPK�o�C���hID�݂̂������ΏۂƂ��܂��B<br>
 * �w�肳�ꂽ�t�@�C��ID�����݂��Ȃ��ꍇ�Arom_address �ɂ� CRIFS_ROM_ADDRESS_INVALID ���ݒ肳��܂��B
 * \attention
 * �Q�[���@�����ł͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa criFsBinder_GetRomAddress() criFsBinder_GetRomAddressById()
 */
CriError CRIAPI criFsBinder_GetRomAddressById(CriFsBinderHn bndrhn, CriFsFileId id, CriUint64Adr *rom_address);

/*JP
 * \brief �v���C�I���e�B�l�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[out]	priority	�v���C�I���e�B�l
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���hID�̃v���C�I���e�B�l���擾���܂��B<br>
 * �v���C�I���e�B�ɂ��A�o�C���_�n���h�����ɂ�����A�o�C���hID�̌������𐧌�ł��܂��B<br>
 * �o�C���h���̃v���C�I���e�B�l�͂O�ŁA�������͓��v���C�I���e�B���̃o�C���h���ɂȂ�܂��B<br>
 * �v���C�I���e�B�l�̑傫���������v���C�I���e�B�ƂȂ�A�������������Ȃ�܂��B
 * \sa criFsBinder_SetPriority()
 */
CriError CRIAPI criFsBinder_GetPriority(CriFsBindId bndrid, CriSint32 *priority);

/*JP
 * \brief �v���C�I���e�B�l�̐ݒ�
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[in]	priority	�v���C�I���e�B�l
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���hID�Ƀv���C�I���e�B��ݒ肵�܂��B <br>
 * �v���C�I���e�B�ɂ��A�o�C���_�n���h�����ɂ�����A�o�C���hID�̌������𐧌�ł��܂��B<br>
 * �o�C���h���̃v���C�I���e�B�l�͂O�ŁA�������͓��v���C�I���e�B���̃o�C���h���ɂȂ�܂��B<br>
 * �v���C�I���e�B�l�̑傫���������v���C�I���e�B�ƂȂ�A�������������Ȃ�܂��B
 * \par ��F
 * \code
 * // a.cpk(a_id), b.cpk(b_id) �̏��Ƀo�C���h
 * criFsBinder_BindCpk(bndrhn, NULL, "a.cpk", a_wk, a_wksz, a_id);
 * criFsBinder_BindCpk(bndrhn, NULL, "b.cpk", a_wk, a_wksz, b_id);
 * // ���̎��_�ł� a_id, b_id�̏��Ɍ��������B
 * 	:
 * criFsBinder_SetPriority(b_id, 1);
 * // b_id �̃v���C�I���e�B���f�t�H���g�l�����グ���̂ŁA
 * // �������� b_id, a_id �ƂȂ�B
 * \endcode
 * \sa criFsBinder_GetPriority()
*/
CriError CRIAPI criFsBinder_SetPriority(CriFsBindId bndrid, CriSint32 priority);

/*JP
 * \brief �J�����g�f�B���N�g���̐ݒ�
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrId		�o�C���hID
 * \param[in]	path		�J�����g�f�B���N�g��
 * \param[in]	work		�J�����g�f�B���N�g�����ۑ��p���[�N�̈�
 * \param[in]	worksize	�J�����g�f�B���N�g�����ۑ��p���[�N�̈�T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �o�C���hID�ɃJ�����g�f�B���N�g����ݒ肵�܂��B<br>
 * �K�v�ȃ��[�N�̈悪�m�ۂł��Ȃ��ꍇ�A�J�����g�f�B���N�g���̐ݒ�Ɏ��s���܂��B<br>
 * ���̏ꍇ�A���ɐݒ肳��Ă���J�����g�f�B���N�g���ݒ�͔j������܂��B<br>
 * �o�C���hID�𗘗p���ăt�@�C�����Q�Ƃ���ۂɁA�J�����g�f�B���N�g�����p�X���̑O�ɕt������܂��B<br>
 * �w�肷�郏�[�N�̈�̃T�C�Y�́A�ݒ肷��J�����g�f�B���N�g�������i�[���邽�߂Ɏg�p����܂��B<br>
 * �Œ�ł��Astrlen(path)+1 �o�C�g�̗̈���m�ۂ��ēn���Ă��������B
 * �������m�ہ^����R�[���o�b�N�֐����o�^����Ă���ꍇ�A���[�N�̈��NULL(���[�N�T�C�Y�͂O�j��ݒ肷��ƁA
 * �K�v�ȃ��[�N�̈���������m�ہ^����R�[���o�b�N�֐����g�p���ē��I�Ɋm�ۂ��܂��B<br>
 * \par ��F
 * \code
 * // �o�C���h����́A�J�����g�f�B���N�g���͐ݒ肳��Ă��Ȃ��B
 * criFsBinder_BindCpk(bndrhn, NULL, "cpk.cpk", wk, wksz, bndrid);
 * 	:
 * criFsBinder_Find(bndrhn, "a.txt", NULL, &exist);�@// "a.txt" �Ō��������
 * 	:
 * // �J�����g�f�B���N�g��"/folder/"��ݒ�
 * worksz = strlen("/folder/")+1;
 * work = malloc(worksz);
 * criFsBinder_SetCurrentDirectory(bndrid, "/folder/", work, worksz);
 * criFsBinder_Find(bndrhn, "a.txt", NULL, &exist);�@// "/folder/a.txt" �Ō��������
 * \endcode
 * \sa criFsBinder_SetUserHeapFunc()
 */
CriError CRIAPI criFsBinder_SetCurrentDirectory(CriFsBindId bndrId, const CriChar8 *path, void *work, CriSint32 worksize);

/*JP
 * \brief CPK�R���e���c�t�@�C�����̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	path	    �R���e���c�t�@�C���p�X��
 * \param[out]	cfinf		CriFsBinderContentsFileInfo�\���̂ւ̃|�C���^
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �t�@�C�������t��CPK�t�@�C������A�w�肳�ꂽ�R���e���c�t�@�C�����̃t�@�C�������擾���܂��B<br>
 * �w�肳�ꂽ�R���e���c�t�@�C�����i�[���Ă���CPK���A�t�@�C�������tCPK�ł���K�v������܂��B<br>
 * �w�肵���o�C���_�n���h���ɁA�������O�̃t�@�C�����������݂���ꍇ�A�ŏ��Ɍ��t�����t�@�C����
 * �i�[���Ă���CPK���I������܂��B<br>
 * �����CPK�t�@�C���𒼐ڎw�肵�����ꍇ�AcriiFsBinder_GetHandle�֐��ɂ��A����CPK�̃o�C���_ID����
 * �o�C���_�n���h�����擾���A�{�֐��̈����Ƃ��Ă��������B<br>
 * \par ���ӁF
 * �{�@�\���g�p����ɂ́A�wCPK File Builder Ver.1.03�ȍ~�x���g�p���č쐬�����A�t�@�C�������tCPK��
 * �p����K�v������܂��B
 * \par ��F
 * \code
 * CriFsBinderContentsFileInfo cfinf;
 * // CPK���o�C���h
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // �R���e���c�t�@�C���̏����擾
 * criFsBinder_GetContentsFileInfo(parent_bndrhn, CPK_CONTENTS_FILENAME, &cfinf);
 * \endcode
 */
CriError criFsBinder_GetContentsFileInfo(CriFsBinderHn bndrhn, const CriChar8 *path, CriFsBinderContentsFileInfo *cfinf);

/*JP
 * \brief CPK�R���e���c�t�@�C�����̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���_�n���h��
 * \param[in]	id			�t�@�C��ID
 * \param[out]	cfinf		CriFsBinderContentsFileInfo�\���̂ւ̃|�C���^
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * ID+�t�@�C�������t��CPK�t�@�C������A�w�肳�ꂽ�t�@�C��ID�̃t�@�C�������擾���܂��B<br>
 * �w�肳�ꂽ�t�@�C�����i�[���Ă���CPK���AID+�t�@�C�������tCPK�ł���K�v������܂��B<br>
 * �w�肵���o�C���_�n���h���ɁA����ID�̃t�@�C�����������݂���ꍇ�A�ŏ��Ɍ��t�����t�@�C����
 * �i�[���Ă���CPK���I������܂��B<br>
 * �����CPK�t�@�C���𒼐ڎw�肵�����ꍇ�AcriiFsBinder_GetHandle�֐��ɂ��A����CPK�̃o�C���hID����
 * �o�C���_�n���h�����擾���A�{�֐��̈����Ƃ��Ă��������B<br>
 * \par ���ӁF
 * �{�@�\���g�p����ɂ́A�wCPK File Builder Ver.1.03�ȍ~�x���g�p���č쐬�����AID+�t�@�C�������tCPK��
 * �p����K�v������܂��B
 * \par ��F
 * \code
 * CriFsBinderContentsFileInfo cfinf;
 * // CPK���o�C���h
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // ID 0x00000010 �̃t�@�C�������擾
 * criFsBinder_GetContentsFileInfoById(parent_bndrhn, 0x00000010, &cfinf);
 * \endcode
 */
CriError CRIAPI criFsBinder_GetContentsFileInfoById(CriFsBinderHn bndrhn, CriFsFileId id, CriFsBinderContentsFileInfo *cfinf);

/*JP
 * \brief Index�w��ɂ��CPK�R���e���c�t�@�C�����̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		�o�C���hID
 * \param[in]	index		�����擾����R���e���c�t�@�C���̐擪INDEX
 * \param[out]	cfinf		CriFsBinderContentsFileInfo�\���̔z��
 * \param[in]   n           �����擾����R���e���c�t�@�C���̐�
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * CPK�t�@�C���̃R���e���c�t�@�C���Aindex����n���̃t�@�C�������擾���܂��B<br>
 * index��CPK�쐬���A�R���e���c�t�@�C���ɑ΂��ĂO���犄�t���܂��B<br>
 * index, n�̏���l��criFsBinder_GetBinderIdInfo�֐��Ŏ擾�����t�@�C�����ƂȂ�܂��B
 *
 * \par ��FCPK�̑S�R���e���c�t�@�C�������擾����
 * \code
 * CriFsBinderInfo binf;
 * CriFsBinderContentsFileInfo *cfinf;
 * // CPK���o�C���h
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 *  : // CPK�o�C���h������҂B
 *  :
 * // CPK�̃R���e���c�t�@�C�������擾����B
 * criFsBinder_GetBinderIdInfo(cpk_bndrid, &binf);
 * // �R���e���c�t�@�C�����S�Ă̏����擾���邽�߂̏��i�[�̈���m�ۂ���B
 * cfinf = malloc(sizeof(CriFsBinderContentsFileInfo)*binf.nfiles);
 * // CPK�̑S�R���e���c�t�@�C���̏����擾����
 * criFsBinder_GetContentsFileInfoByIndex(cpk_bndrid, 0, cfinf, binf.nfiles);
 * \endcode
 * \par ��FCPK�̈ꕔ�R���e���c�t�@�C���iIndex5�Ԃ���10�t�@�C�����j�̏����擾����
 * \code
 * #define CNTNTS_INDX (5)  // INDEX 5����
 * #define CNTNTS_N (10)  // 10�R���e���c�t�@�C��
 * CriFsBinderInfo binf;
 * CriFsBinderContentsFileInfo *cfinf;
 * // CPK���o�C���h
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 *  : // CPK�o�C���h������҂B
 *  :
 * // �擾����R���e���c�t�@�C�������̏����擾���邽�߂̏��i�[�̈���m�ۂ���B
 * cfinf = malloc(sizeof(CriFsBinderContentsFileInfo)*CNTNTS_N);
 * // CPK�̑S�R���e���c�t�@�C���̏����擾����
 * criFsBinder_GetContentsFileInfoByIndex(cpk_bndrid, CNTNTS_INDX, cfinf, CNTNTS_N);
 * \endcode
 * \par ���l�F
 * ���擾�Ɏ��s�����ꍇ�ł����Ă��A�{�֐��̓G���[�l��Ԃ��Ȃ��ꍇ������܂��B<br>
 * �������A���̏ꍇ�ł����Ă��A�R���e���c�t�@�C�����̃t�@�C������ID���s���Ȓl�ɂȂ��Ă��鎖����A
 * ���擾�Ɏ��s�������𔻒�\�ł��B<br>
 */
CriError CRIAPI criFsBinder_GetContentsFileInfoByIndex(CriFsBindId bndrid, CriSint32 index, CriFsBinderContentsFileInfo *cfinf, CriSint32 n);

/*JP
 * \brief �o�C���hID���̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[out]	binf		�擾���
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�o�C���hID�̃o�C���_��ʁiCPK/�t�@�C��/�f�B���N�g�����j��o�C���h�����t�@�C�����A�v���C�I���e�B�ݒ�Ȃǂ�
 * �����擾���܂��B<br>
 */
CriError CRIAPI criFsBinder_GetBinderIdInfo(CriFsBindId bndrid, CriFsBinderInfo *binf);

/*JP
 * \brief �O���[�v�t�@�C�����̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[in]	groupname	�O���[�v��
 * \param[in]	attrname	�A�g���r���[�g��
 * \param[out]	groupfiles	�O���[�v�t�@�C����
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肵���o�C���hID�A�O���[�v���A�A�g���r���[�g���ɓK������t�@�C���̐����擾���܂��B<br>
 * �K������t�@�C�������݂��Ȃ��ꍇ�A�t�@�C�����͂O�ɂȂ�܂��B<br>
 * �O���[�v���t����CPK�t�@�C�����o�C���h�����o�C���hID���w�肷��K�v������܂��B<br>
 * �����ȃo�C���hID���w�肵���ꍇ�A�G���[�R�[���o�b�N���N���܂��B<br>
 * �A�g���r���[�g����NULL���w�肵���ꍇ�A�w��O���[�v�ɑ�����S�Ẵt�@�C�����O���[�v���[�h�̑ΏۂƂȂ�܂��B<br>
 * �܂��A�p�b�L���O�c�[���̃A�g���r���[�g�w����unone�v�Ƃ����ꍇ���A�A�g���r���[�g����NULL���w�肵�Ă��������B<br>
 */
CriError CRIAPI criFsBinder_GetNumberOfGroupFiles(CriFsBindId bndrid, const CriChar8 *groupname, const CriChar8 *attrname, CriSint32 *groupfiles);

/*JP
 * \brief �O���[�v���[�h�T�C�Y�̎擾
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		�o�C���hID
 * \param[in]	groupname	�O���[�v��
 * \param[in]	attrname	�A�g���r���[�g��
 * \param[out]	datasize    �O���[�v���[�h�T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肵���o�C���hID�A�O���[�v���A�A�g���r���[�g���ɓK������O���[�v�̃��[�h�ɕK�v�ȓǍ��̈�̃T�C�Y���擾���܂��B<br>
 * �A���C�����g�Ȃǂ��������ꂽ�f�[�^�T�C�Y�ƂȂ�܂��B<br>
 * �K������t�@�C�������݂��Ȃ��ꍇ�A�O���[�v���[�h�T�C�Y�͂O�ɂȂ�܂��B<br>
 * �O���[�v���t����CPK�t�@�C�����o�C���h�����o�C���hID���w�肷��K�v������܂��B<br>
 * �����ȃo�C���hID���w�肵���ꍇ�A�G���[�R�[���o�b�N���N���܂��B<br>
 * �A�g���r���[�g����NULL���w�肵���ꍇ�A�w��O���[�v�ɑ�����S�Ẵt�@�C�����O���[�v���[�h�̑ΏۂƂȂ�܂��B<br>
 * �܂��A�p�b�L���O�c�[���̃A�g���r���[�g�w����unone�v�Ƃ����ꍇ���A�A�g���r���[�g����NULL���w�肵�Ă��������B<br>
 */
CriError CRIAPI criFsBinder_GetTotalGroupDataSize(CriFsBindId bndrid, const CriChar8 *groupname, const CriChar8 *attrname, CriSint64 *datasize);

/*JP
 * \brief ID���tCPK�̃A�N�Z�X���e�[�u���쐬�p���[�N�T�C�Y�擾
 * \ingroup FSLIB_BINDER
 * \param[in]	binderid	�o�C���hID
 * \param[in]	steps		�A�N�Z�X���e�[�u���쐬�̍쐬�Ԋu
 * \param[out]	worksize 	�A�N�Z�X���e�[�u���쐬�p���[�N�̈�̃T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * ID���tCPK�̃A�N�Z�X���e�[�u���̍쐬�ɕK�v�ȃ��[�N�̈�̃T�C�Y���擾���܂��B<br>
 * �A�N�Z�X���e�[�u���Ƃ́ACPK�̃R���e���c�t�@�C���ɃA�N�Z�X����ۂ̏�����O�����čs�����ƂŁA
 * �A�N�Z�X���x�����コ���邽�߂̂��̂ł��B<br>
 * ID���̂Ȃ�CPK�ł̓A�N�Z�X�e�[�u���͕K�v����܂���B
 * �{�֐���ID���tCPK�ɑ΂��Ă̂ݗL���ł��B<br>
 * �{�֐��͊������A�֐��ł��B<br>
 * �A�N�Z�X���e�[�u���̗̈�́A�Y��CPK���o�C���h����Ă���Ԃ͉��������A���֓]�p���Ȃ��ł��������B<br>
 * \par �A�N�Z�X���e�[�u���̍쐬�Ԋu�ɂ���
 * steps�ɂP���w�肵���ꍇ�A�S�ẴR���e���c�t�@�C���ɑ΂���A�N�Z�X���e�[�u�����쐬����܂��B
 * ���̏ꍇ�A�A�N�Z�X���e�[�u���̗v�f���̓R���e���c�t�@�C�����Ɠ����ɂȂ�܂��B<br>
 * steps�ɂP���傫���l���w�肵���ꍇ�́A�w��steps�����̃R���e���c�t�@�C���ɑ΂���A�N�Z�X���e�[�u�����쐬����܂��B
 * �A�N�Z�X���e�[�u���̗v�f����steps�ɉ����ĕω����܂��B<br>
 * �S�ẴR���e���c�t�@�C���ɑ΂���e�[�u�����������Ȃ��̂ŁAsteps��1��ݒ肵���Ƃ��ɔ�ׂāA
 * �t�@�C���A�N�Z�X���̏�����������܂����A�A�N�Z�X���e�[�u���̗̈���������ł��܂��B
 */
CriError CRIAPI criFsBinder_GetWorkSizeForCpkIdAccessTable(CriFsBindId bindrid, CriSint32 steps, CriSint32 *worksize);

/*JP
 * \brief ID���tCPK �A�N�Z�X���e�[�u���̍쐬
 * \ingroup FSLIB_BINDER
 * \param[in]	binderid	�o�C���hID
 * \param[in]	steps		�A�N�Z�X���e�[�u���쐬�̍쐬�Ԋu
 * \param[in]	work		�A�N�Z�X���e�[�u���쐬�p���[�N�̈�
 * \param[in]	worksize 	�A�N�Z�X���e�[�u���쐬�p���[�N�̈�̃T�C�Y
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * ID���tCPK�̃A�N�Z�X���e�[�u�����쐬���܂��B<br>
 * �A�N�Z�X���e�[�u�����쐬�����ꍇ�A�Y��CPK�̃R���e���c�ւ̃A�N�Z�X�������ɂȂ�܂��B
 * �{�֐��͊������A�֐��ł��B�R���e���c�t�@�C�����������ꍇ�A���A�܂łɎ��Ԃ�������ꍇ������܂��B<br>
 * ID���̂Ȃ�CPK�ł̓A�N�Z�X�e�[�u���͍쐬����܂���B<br>
 * �{�֐���ID���tCPK�ɑ΂��Ă̂ݗL���ł��B<br>
 * �A�N�Z�X���e�[�u���̗̈�́A�Y��CPK���o�C���h����Ă���Ԃ͉��������A���֓]�p���Ȃ��ł��������B<br>
 * �A�N�Z�X���e�[�u���̗̈�́A�Y��CPK���A���o�C���h������ɉ�����Ă��������B<br>
 */
CriError CRIAPI criFsBinder_SetupCpkIdAccessTable(CriFsBindId binderid, CriSint32 steps, void *work, CriSint32 worksize);

/*JP
 * \brief �o�C���h���̃t�@�C���̈ꎞ�N���[�Y
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					�o�C���hID
 * \param[out]	internal_loader_status	�������[�_�X�e�[�^�X
 * \return		CriError				�G���[�R�[�h
 * \par �����F
 * �o�C���h���̃t�@�C������U�N���[�Y���܂��B<br>
 * ::criFsBinder_Unbind �֐��ƈقȂ�A
 * CPK�t�@�C����TOC������������Ɏc�����܂܃t�@�C���݂̂��N���[�Y���܂��B<br>
 * �i�o�C���hID�ɕR�t�����Ă���l�C�e�B�u�t�@�C���̃n���h�����N���[�Y����܂��B�j<br>
 * \par ���l:
 * �{�֐��́ACPK�t�@�C���̓o�C���h������Ԃɂ��Ă����������A
 * ���̃t�@�C�����I�[�v�����邽�߁A�ꎞ�I�Ƀt�@�C���n���h��������������ꍇ���Ɏg�p���܂��B<br>
 * <b>���t�@�C���n���h�����̃n�[�h�E�F�A���\�[�X���v���b�g�t�H�[���ŗ��p�\�ȏ�����ɒB���Ȃ�����A
 * �{�֐����g�p����K�v�͂���܂���B</b><br>
 * <br>
 * �{�֐��͓���API�ł��B<br>
 * �{�֐������s����ƁA�t�@�C���̃I�[�v�������܂ŏ������u���b�N����܂��B<br>
 * �I�[�v��������񓯊��ɍs�������ꍇ�ɂ́A�{�֐��̑����
 * ::criFsBinder_CloseFileAsync �֐������g�p���������B<br>
 * \attention
 * �{�֐��ŃN���[�Y����CPK�t�@�C���ɑ΂��ăA�N�Z�X����ƁA���[�h�G���[���������܂��B<br>
 * �{�֐����s��A ::criFsBinder_ReopenFile �֐������s����܂ł̊ԁA
 * ���YCPK�t�@�C���ɑ΂���A�N�Z�X���������Ȃ��悤���䂷��K�v������܂��B<br>
 * <br>
 * �{�֐��́ACPK�t�@�C���𒼐ڃo�C���h���Ă���P�[�X�ł̂ݗ��p�\�ł��B<br>
 * �f�B���N�g���o�C���h���g�p���Ă���P�[�X��A�t�@�C���o�C���h���g�p���Ă���P�[�X�A
 * CPK�t�@�C�����̃R���e���c���o�C���h���Ă���P�[�X�ł́A�{�֐��͎g�p�ł��܂���B<br>
 * \sa criFsBinder_ReopenFile
 */
CriError CRIAPI criFsBinder_CloseFile(
	CriFsBindId bind_id, CriFsLoaderStatus *internal_loader_status);

/*JP
 * \brief �ꎞ�N���[�Y�t�@�C���̍ăI�[�v��
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					�o�C���hID
 * \param[out]	internal_loader_status	�������[�_�X�e�[�^�X
 * \return		CriError				�G���[�R�[�h
 * \par �����F
 * ::criFsBinder_CloseFile �֐����ŃN���[�Y�����t�@�C�����ēx�I�[�v���������܂��B<br>
 * \par ���l:
 * �{�֐��͓���API�ł��B<br>
 * �{�֐������s����ƁA�t�@�C���̃I�[�v�������܂ŏ������u���b�N����܂��B<br>
 * �I�[�v��������񓯊��ɍs�������ꍇ�ɂ́A�{�֐��̑����
 * ::criFsBinder_ReopenFileAsync �֐������g�p���������B<br>
 * \attention
 * ���[�h�G���[���ɂ��t�@�C���̍ăI�[�v���Ɏ��s�����ꍇ�A
 * �� 2 �����i internal_loader_status �j�� ::CRIFSLOADER_STATUS_ERROR �ɂȂ�܂��B<br>
 * \sa criFsBinder_CloseFile
 */
CriError CRIAPI criFsBinder_ReopenFile(
	CriFsBindId bind_id, CriFsLoaderStatus *internal_loader_status);

/*JP
 * \brief �o�C���h���̃t�@�C���̈ꎞ�N���[�Y
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id				�o�C���hID
 * \param[out]	internal_loader		�������[�_�n���h��
 * \return		CriError			�G���[�R�[�h
 * \par �����F
 * �o�C���h���̃t�@�C������U�N���[�Y���܂��B<br>
 * �������񓯊��ȓ_�������A ::criFsBinder_CloseFile �֐��Ɠ��l�̑�����s���܂��B<br>
 * \par ���l�F
 * �{�֐��͔񓯊������p��API�ł��B<br>
 * �{�֐������s����ƁA�t�@�C���̃N���[�Y������҂��ƂȂ����������A���܂��B<br>
 * <br>
 * �t�@�C���̃N���[�Y�������������ǂ����́A�� 2 �����i internal_loader �j
 * �ŕԂ���郍�[�_�n���h�����g�p���ă`�F�b�N���܂��B<br>
 * �i�N���[�Y���������������^�C�~���O�ŁA���[�_�n���h���̃X�e�[�^�X��
 * ::CRIFSLOADER_STATUS_COMPLETE �ɑJ�ڂ��܂��B�j<br>
 * \attention
 * �� 2 �����i internal_loader �j�ŕԂ���郍�[�_�n���h���́A
 * ���C�u�������Ńt�@�C���A�N�Z�X�̂��߂Ɏg�p�����������\�[�X�ł��B<br>
 * ���̃n���h�����A�v���P�[�V�������Ŕj�����Ȃ��ł��������B<br>
 * \sa criFsBinder_CloseFile
 */
CriError CRIAPI criFsBinder_CloseFileAsync(
	CriFsBindId bind_id, CriFsLoaderHn *internal_loader);

/*JP
 * \brief �ꎞ�N���[�Y�t�@�C���̍ăI�[�v��
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id				�o�C���hID
 * \param[out]	internal_loader		�������[�_�n���h��
 * \return		CriError			�G���[�R�[�h
 * \par �����F
 * ::criFsBinder_CloseFile �֐����ŃN���[�Y�����t�@�C�����ēx�I�[�v���������܂��B<br>
 * �������񓯊��ȓ_�������A ::criFsBinder_ReopenFile �֐��Ɠ��l�̑�����s���܂��B<br>
 * \par ���l�F
 * �{�֐��͔񓯊������p��API�ł��B<br>
 * �{�֐������s����ƁA�t�@�C���̃I�[�v��������҂��ƂȂ����������A���܂��B<br>
 * <br>
 * �t�@�C���̃I�[�v���������������ǂ����́A�� 2 �����i internal_loader �j
 * �ŕԂ���郍�[�_�n���h�����g�p���ă`�F�b�N���܂��B<br>
 * �i�I�[�v�����������������^�C�~���O�ŁA���[�_�n���h���̃X�e�[�^�X��
 * ::CRIFSLOADER_STATUS_COMPLETE �ɑJ�ڂ��܂��B�j<br>
 * �t�@�C���I�[�v���̊������m�F������A::criFsBinder_CompleteAsyncFileReopen �֐����g���A<br>
 * �o�C���hID�ɑ΂��ăt�@�C���̍ăI�[�v�����������Ă��������B
 * \attention
 * �� 2 �����i internal_loader �j�ŕԂ���郍�[�_�n���h���́A
 * ���C�u�������Ńt�@�C���A�N�Z�X�̂��߂Ɏg�p�����������\�[�X�ł��B<br>
 * ���̃n���h�����A�v���P�[�V�������Ŕj�����Ȃ��ł��������B<br>
 * <br>
 * ���[�h�G���[���ɂ��t�@�C���̍ăI�[�v���Ɏ��s�����ꍇ�A
 * �� 2 �����i internal_loader_status �j�ŕԂ��ꂽ���[�_�n���h���̃X�e�[�^�X��
 * ::CRIFSLOADER_STATUS_ERROR �ɂȂ�܂��B<br>
 * \sa criFsBinder_ReopenFile
 */
CriError CRIAPI criFsBinder_ReopenFileAsync(
	CriFsBindId bind_id, CriFsLoaderHn *internal_loader);

/*JP
 * \brief �ꎞ�N���[�Y�t�@�C���̍ăI�[�v�����f
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id				�o�C���hID
 * \return		CriError			�G���[�R�[�h
 * \par �����F
 * ::criFsBinder_ReopenFileAsync �֐��ɂ��t�@�C���̍ăI�[�v�������A<br>
 * �o�C���hID�ɔ��f�����A�ăI�[�v���������������܂��B<br>
 * ::criFsBinder_ReopenFileAsync �֐��̎��s�Ŏ擾�������[�_�n���h���̃X�e�[�^�X��<br>
 * ::CRIFSLOADER_STATUS_COMPLETE�ɑJ�ڂ��������m�F���Ă�����s���Ă��������B<br>
 * �t�@�C�����ăI�[�v�������o�C���hID�ɑ΂��āA<br>
 * �{�֐������s�����Ƀ��[�h�����s����ƁA���[�h�Ɏ��s���܂��B
 * \par
 * ::criFsBinder_ReopenFile �֐��ɑ΂��Ă͖{�֐������s����K�v�͂���܂���B<br>
 * \attention
 * �t�@�C���ăI�[�v���p���[�_�n���h���̃X�e�[�^�X��<br>
 * ::CRIFSLOADER_STATUS_COMPLETE �ȊO�̏�ԂŖ{�֐������s����ƁA<br>
 * �{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFsBinder_CompleteAsyncFileReopen(CriFsBindId bind_id);

/*JP
 * \brief �����t�@�C���o�C���h�p�p�X�Z�p���[�^�̎w��
 * \ingroup FSLIB_BINDER
 * \param[in]	filter				�Z�p���[�^�Ƃ��Ďg�p���镶���̈ꗗ
 * \return		CriError			�G���[�R�[�h
 * \par �����F
 * ::criFsBinder_BindFiles �֐����Z�p���[�^�Ƃ��ĉ��߂��镶����ύX���܂��B<br>
 * <br>
 * ::criFsBinder_BindFiles �֐����g���ĕ����̃t�@�C�����o�C���h����ꍇ�A
 * �t�@�C���p�X���Z�p���[�^�Ō���������������w�肷��K�v������܂��B<br>
 * �f�t�H���g��Ԃł́ACRI File System���C�u�����́u,�v�u\\t�v�u\\n�v
 * ��3���Z�p���[�^�Ƃ��Ĉ����܂��B<br>
 * �Z�p���[�^�ɏ�L�ȊO�̕������g�p�������ꍇ�A
 * �{�֐��ŃZ�p���[�^�ɊY�����镶����ύX���邱�Ƃ��\�ł��B<br>
 * <br>
 * �������� filter �ɂ́A
 * �Z�p���[�^�Ƃ��Ďg�p���镶���̈ꗗ���i�[������������w�肵�܂��B<br>
 * �Ⴆ�΁A "@+-*" ���w�肵���ꍇ�A
 * �u@�v�u+�v�u-�v�u*�v��4��ނ̕������Z�p���[�^�Ƃ��Ĉ����܂��B<br>
 * \par ���l�F
 * filter �ɋ󕶎���i""�j���w�肵���ꍇ�A�Z�p���[�^�������ɂȂ�܂��B<br>
 * filter �� NULL ���w�肵���ꍇ�A�ݒ肪�f�t�H���g��Ԃɖ߂�܂��B<br>
 * \attention
 * ::criFsBinder_BindFiles �֐��ȊO�̊֐��ɃZ�p���[�^���܂ރp�X��n�����ꍇ�A
 * CRI File System���C�u�����͕s���ȃp�X�Ƃ��ď�������܂��B<br>
 * �i�Z�p���[�^�ȍ~�̃p�X�������ɂȂ�܂��B�j<br>
 * ::criFsBinder_BindFiles �֐����g�p���Ȃ��ꍇ�ł��A
 * �A�v���P�[�V�������Łu,�v�u\\t�v�u\\n�v���܂ރp�X�������ꍇ�ɂ́A
 * �{�֐��Ŏ��O�ɃZ�p���[�^�ɕύX���Ă����K�v������܂��B<br>
 * <br>
 * �t�B���^�Ɏw��ł��镶���̍ő吔�́A���� 7 �����܂łł��B<br>
 */
CriError CRIAPI criFsBinder_SetPathSeparatorForBindFiles(const CriChar8 *filter);

/*==========================================================================
 *      CriFsLoader API
 *=========================================================================*/
/*JP
 * \brief CRI File System - Loader �I�u�W�F�N�g
 * \ingroup FSLIB_BASIC
 * \par ����:
 * CriFsLoader�Ƃ̓t�@�C���f�[�^���ȒP�ɓǂݏo�����߂̃��W���[���ł��B
 */
/*EN
 * \brief CRI File System - Loader Object
 * \ingroup FSLIB_BASIC
 * \par
 * CriFsLoader is loading module. It is very simple and easy.
 */

/*JP
 * \brief CriFsLoader�̍쐬
 * \ingroup FSLIB_BASIC
 * \param[out]	loader	CriFsLoader�n���h��
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CriFsLoader���쐬���܂��B
 */
/*EN
 * \brief Create a CriFsLoader
 * \ingroup FSLIB_BASIC
 * \param[out]	loader	CriFsLoader handle
 * \return	CriError	Error information
 * \par
 * This function creates a CriFsLoader.
 */
CriError CRIAPI criFsLoader_Create(CriFsLoaderHn *loader);

/*JP
 * \brief CriFsLoader�̔j��
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * CriFsLoader��j�����܂��B
 * \attention
 * �{�֐������[�h�����R�[���o�b�N���Ŏ��s���Ȃ��ł��������B
 * \sa criFsLoader_Create
 */
/*EN
 * \brief Destroy CriFsLoader
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \return	CriError	Error information
 * \par
 * This function deletes the CriFsLoader.
 * \atteniton
 * Do not call this function in the load end callback function.
 * ( ::CriFsLoaderLoadEndCbFunc ) <br>
 * \sa criFsLoader_Create
 */
CriError CRIAPI criFsLoader_Destroy(CriFsLoaderHn loader);

/*JP
 * \brief ���[�h�����R�[���o�b�N�̓o�^
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	func	�R�[���o�b�N�֐�
 * \param[in]	obj		�R�[���o�b�N�֐��֓n������
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h�������Ɏ��s�����R�[���o�b�N�֐���o�^���܂��B<br>
 * ���[�h�����R�[���o�b�N�́A���[�_�̃X�e�[�^�X�� CRIFSLOADER_STATUS_LOADING ����
 * ���̃X�e�[�^�X�ɑJ�ڂ�������ɌĂяo����܂��B<br>
 * �i CRIFSLOADER_STATUS_COMPLETE �ȊO�ɂ��A CRIFSLOADER_STATUS_STOP ��
 * CRIFSLOADER_STATUS_ERROR �ɑJ�ڂ���ۂɂ��R�[���o�b�N�͎��s����܂��B�j<br>
 * \par ���l:
 * �����ɂ́A�X�e�[�^�X�J�ځ`�R�[���o�b�N���s�܂ł̊Ԃɑ��̏��������荞�݂œ��삷��
 * �]�n�����邽�߁A�X�e�[�^�X�J�ڂƃR�[���o�b�N���s�̃^�C�~���O���Y����\��������܂��B<br>
 * \attention
 * ���[�h�����R�[���o�b�N�́A ::criFsLoader_Load �֐��� CRIERR_OK
 * ��Ԃ��ꍇ�ɂ̂݌Ăяo����܂��B<br>
 * ::criFsLoader_Load �֐��ɕs���Ȉ�����n�����ꍇ���A
 * ���[�h�������̂��J�n����Ȃ��ꍇ�i���[�_�̃X�e�[�^�X�� CRIFSLOADER_STATUS_LOADING
 * �ɂȂ�Ȃ��ꍇ�j�ɂ́A���[�h�����R�[���o�b�N���̂����s����܂���B<br>
 * <br>
 * ���[�h�����⃍�[�h�����R�[���o�b�N�̌Ăяo���́A ::criFsLoader_Load
 * �֐������s�����X���b�h�Ƃ͕ʂ̃X���b�h�Ŏ��s�����\��������܂��B<br>
 * �قƂ�ǂ̏ꍇ�A���X���b�h�ł̃t�@�C���ǂݍ��݂���������O�� ::criFsLoader_Load �֐����珈���͕��A���܂����A
 * ���炵���̗��R�� ::criFsLoader_Load �֐������s����X���b�h�̓��삪�x�ꂽ�i�܂��͕ʃX���b�h�ł̏������u���Ɋ��������j�ꍇ�A
 * ::criFsLoader_Load �֐����畜�A����O�Ƀ��[�h�����R�[���o�b�N���Ăяo�����`�ɂȂ�܂��B<br>
 * <br>
 * ���[�h������ɌĂяo����郍�[�h�����R�[���o�b�N�֐��́A
 * �w���[�h�J�n���_�œo�^�ς݂̃R�[���o�b�N�֐��x�ł��B<br>
 * ���̂��߁A���[�h�����J�n�`���[�h�����܂ł̊ԂɃ��[�h�����R�[���o�b�N��o�^���������Ƃ��Ă��A
 * �Ăяo�����֐��͕ύX����܂���B<br>
 * �i�o�^�����������[�h�����R�[���o�b�N�֐����g�p�����̂́A���񃍁[�h�������s���ƂȂ�܂��B�j<br>
 * <br>
 * ���[�h�����R�[���o�b�N���ŎQ�Ƃ����I�u�W�F�N�g�́A
 * ���[�_�̃X�e�[�^�X��������ԁi�܂��͒�~��ԁj�ɂȂ����ꍇ�ł��A
 * ���[�h�����R�[���o�b�N�����s�����܂ł͉�����Ȃ��ł��������B<br>
 * �i�X�e�[�^�X�J�ڌ�A���[�h�����R�[���o�b�N�����s�����܂ł́A
 * �o�^�ς݂̃R�[���o�b�N�p�����[�^���Q�Ƃ����\��������܂��B�j<br>
 * <br>
 * �R�[���o�b�N��o�^������ԂŃ��[�h�������s���Ă��郍�[�_��
 * ::criFsLoader_Destroy �֐��Ŕj�������ꍇ�A ::criFsLoader_Destroy
 * �֐����Ń��[�h�����R�[���o�b�N�����s�����\��������܂��B<br>
 * <br>
 * ���[�h�����R�[���o�b�N�����s���Ă���ԁA���̃t�@�C���̃��[�h���u���b�N����܂��B<br>
 * ���̂��߁A���[�h�����R�[���o�b�N���ŕ��ׂ̍����������s�Ȃ�Ȃ��悤�A�����ӂ��������B<br>
 * <br>
 * ���[�h�����R�[���o�b�N���Ń��[�_�̃X�e�[�^�X�J�ڂ�҂������s��Ȃ��ł��������B<br>
 * ���[�_�̃X�e�[�^�X�X�V�́A���[�h�����R�[���o�b�N�Ɠ���̃X���b�h��ōs���܂��B<br>
 * ���̂��߁A���[�h�����R�[���o�b�N���ŃX�e�[�^�X�J�ڂ�҂������s���ƁA
 * �f�b�h���b�N���������A�������i�܂Ȃ��Ȃ�܂��B<br>
 * <br>
 * �R�[���o�b�N�֐��̓��[�_���̃������̈�ɑ΂��ēo�^����܂��B<br>
 * ���̂��߁A���[�h�����R�[���o�b�N���Ń��[�_��j�����邱�Ƃ͂ł��܂���B<br>
 * �i���[�h�����R�[���o�b�N���� ::criFsLoader_Destroy �֐������s����ƁA
 * �G���[���������܂��B�j<br>
 * <br>
 * �R�[���o�b�N�֐���1�����o�^�ł��܂���B<br>
 * �o�^����𕡐���s�����ꍇ�A���ɓo�^�ς݂̃R�[���o�b�N�֐����A
 * �ォ��o�^�����R�[���o�b�N�֐��ɂ��㏑������Ă��܂��܂��B<br>
 * <br>
 * func��NULL���w�肷��Ƃ��Ƃœo�^�ς݊֐��̓o�^�������s���܂��B<br>
 * \sa criFsLoader_Destroy
 */
CriError CRIAPI criFsLoader_SetLoadEndCallback(
	CriFsLoaderHn loader, CriFsLoaderLoadEndCbFunc func, void *obj);

/*JP
 * \brief �Í��������R�[���o�b�N�̓o�^
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	func	�R�[���o�b�N�֐�
 * \param[in]	obj		�R�[���o�b�N�֐��֓n�����[�U�[�f�[�^
 * \return	CriError	�G���[�R�[�h
 *
 * \par ����:
 * ���[�h�������ɃR�[���o�b�N�����Í��������֐���o�^���܂��B<br>
 * �Í��������֐����o�^�����ƁA
 * ���[�_�̓��[�h�����S�Ẵt�@�C���ɑ΂��ĈÍ��������֐�����x���R�[���o�b�N���܂��B<br>
 * �A�v���P�[�V�������ł́A�Í��������֐��ɓn���ꂽ data �̈�ɑ΂��āA
 * �K�v�ł���ΈÍ����������{���A���̌��ʂ� data �̈�ɏ㏑�����Ă��������B<br>
 *
 * \par ���l:
 * ���[�h���̃t�@�C������t�@�C�����I�t�Z�b�g�Ƃ���������
 * �Í��������֐��ɓ`�������ꍇ�́A<br>
 * obj �Ƀ��[�U�[�f�[�^�Ƃ��ēo�^���Ă��������B
 * <br>
 * func��NULL���w�肷��Ƃ��Ƃœo�^�ς݊֐��̓o�^�������s���܂��B<br>
 * 
 * \attention
 * �Í��������֐��́A�����̃X���b�h�A�R�A����Ăяo�����\��������܂��B<br>
 * ���̂��߁A�A�v���P�[�V�����͈Í��������֐���
 * �}���`�X���b�h�Z�[�t�^�}���`�R�A�Z�[�t�Ɏ�������K�v������܂��B<br>
 * ���ɁA�Í��������Ɉꎞ�̈悪�K�v�Ńq�[�v����̈���m�ۂ���ꍇ�A
 * �q�[�v�ւ̃A�N�Z�X���}���`�X���b�h�Z�[�t���ǂ����Ƃ����_�ɒ��ӂ��Ď������Ă��������B<br>
 * �Í��������̗L���ɂ�����炸�A
 * �Í��������֐�����CRIERR_OK���Ԃ����ƁA
 * ���[�_�͈Í������������������O��ŏ������p�����܂��B<br>
 * �Í����ς݂̃f�[�^�ɑ΂��ĈÍ����������s�킸�Ƀf�[�^�W�J�����܂Ői��ł��܂��ƁA
 * �s���ȃf�[�^��W�J���悤�Ƃ��ăf�[�^�A�N�Z�X�ᔽ����������\��������܂��B<br>
 * ����āA�Í����ς݃f�[�^�̈Í��������������m���Ɏ��s����悤�ɂ��Ă��������B<br>
 * �Ȃ��A�Í��������Ɏ��s�����ꍇ�́ACRIERR_NG��Ԃ��Ă��������B<br>
 * CRIERR_NG��Ԃ����Ń��[�_���G���[��ԂɑJ�ڂ����鎖���ł��A
 * �A�v���P�[�V�������ŃG���[�n���h�����O�ł��܂��B<br>
 * \sa CriFsInplaceDecryptionCbFunc
 */
CriError CRIAPI criFsLoader_SetInplaceDecryptionCbFunc(
	CriFsLoaderHn loader, CriFsInplaceDecryptionCbFunc func, void *obj);

/*JP
 * \brief �f�[�^�̃��[�h
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	binder	CriFsBinder�n���h��
 * \param[in]	path	�t�@�C���p�X��
 * \param[in]	offset	�t�@�C���̐擪����̃I�t�Z�b�g�ʒu
 * \param[in]	load_size	���[�h�T�C�Y
 * \param[in]	buffer	�o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size	�o�b�t�@�̃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肳�ꂽ�o�C���_�ƃt�@�C�����ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
 * �t�@�C������ offset �o�C�g�ڂ���Aload_size �o�C�g���ǂݍ��݂܂��B<br>
 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� criFsLoader_GetStatus�֐����g�p���Ă��������B<br>
 * \sa criFsLoader_GetStatus
 */
/*EN
 * \brief Loading File Data
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	path 	File path
 * \param[in]	offset	Seek position from top of file
 * \param[in]	load_size	Loading size
 * \param[in]	buffer	buffer
 * \param[in]	buffer_size Size of buffer
 * \return	CriError	Error information
 * \par
 * This function starts loading of data by appointed File path and the binder.<br>
 * This function is return immediately.
 * You use an criFsLoader_GetStatus function to examine loading completion.<br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_Load(CriFsLoaderHn loader,
	CriFsBinderHn binder, const CriChar8 *path, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*JP
 * \brief �f�[�^�̃��[�h (CPK�t�@�C�����̃t�@�C��ID���w��)
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	binder	CriFsBinder�n���h��
 * \param[in]	id �t�@�C��ID
 * \param[in]	offset	�t�@�C���̐擪����̃I�t�Z�b�g�ʒu
 * \param[in]	load_size	���[�h�T�C�Y
 * \param[in]	buffer	�o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size	�o�b�t�@�̃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肳�ꂽ�o�C���_�ƃt�@�C��ID�ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
 * �t�@�C������ offset �o�C�g�ڂ���Aload_size �o�C�g���ǂݍ��݂܂��B<br>
 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� criFsLoader_GetStatus�֐����g�p���Ă��������B<br>
 * \sa criFsLoader_GetStatus
 */
/*EN
 * \brief Loading File Data (Using File ID in CPK File)
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	id	File ID
 * \param[in]	offset	Seek position from top of file
 * \param[in]	load_size	Loading size
 * \param[in]	buffer	buffer
 * \param[in]	buffer_size Size of buffer
 * \return	CriError	Error information
 * \par
 * This function starts loading of data by appointed File ID and the binder.<br>
 * This function is return immediately.
 * You use an criFsLoader_GetStatus function to examine loading completion.<br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadById(CriFsLoaderHn loader,
	CriFsBinderHn binder, CriFsFileId id, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*JP
 * \brief ���k�f�[�^��W�J�����Ƀ�������Ƀ��[�h
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	binder	CriFsBinder�n���h��
 * \param[in]	path	�t�@�C���p�X��
 * \param[in]	offset	�t�@�C���̐擪����̃I�t�Z�b�g�ʒu
 * \param[in]	load_size	���[�h�T�C�Y
 * \param[in]	buffer	�o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size	�o�b�t�@�̃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肳�ꂽ�o�C���_�ƃt�@�C�����ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
 * ::criFsLoader_Load �֐��ƈقȂ�A�f�[�^�����k����Ă���ꍇ�ł��A
 * �f�[�^��W�J�����Ƀ�������Ƀ��[�h���܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * ���[�h�̊�����Ԃ��擾����ɂ� criFsLoader_GetStatus�֐����g�p���Ă��������B<br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadWithoutDecompression(CriFsLoaderHn loader,
	CriFsBinderHn binder, const CriChar8 *path, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*JP
 * \brief ���k�f�[�^��W�J�����Ƀ�������Ƀ��[�h�iCPK�t�@�C�����̃t�@�C��ID���w��j
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	binder	CriFsBinder�n���h��
 * \param[in]	id �t�@�C��ID
 * \param[in]	offset	�t�@�C���̐擪����̃I�t�Z�b�g�ʒu
 * \param[in]	load_size	���[�h�T�C�Y
 * \param[in]	buffer	�o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size	�o�b�t�@�̃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �w�肳�ꂽ�o�C���_�ƃt�@�C��ID�ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
 * ::criFsLoader_Load �֐��ƈقȂ�A�f�[�^�����k����Ă���ꍇ�ł��A
 * �f�[�^��W�J�����Ƀ�������Ƀ��[�h���܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * ���[�h�̊�����Ԃ��擾����ɂ� criFsLoader_GetStatus�֐����g�p���Ă��������B<br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadWithoutDecompressionById(CriFsLoaderHn loader,
	CriFsBinderHn binder, CriFsFileId id, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*JP
 * \brief ��������ɔz�u���ꂽ���k�f�[�^�̓W�J
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	src	���k�f�[�^�A�h���X
 * \param[in]	src_size	���k�f�[�^�T�C�Y
 * \param[in]	dst	�W�J�惁�����A�h���X
 * \param[in]	dst_size	�W�J�惁�����̈�T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ��������ɔz�u���ꂽ���k�f�[�^���A�ʂ̃������̈�ɓW�J���܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * ���[�h�̊�����Ԃ��擾����ɂ� criFsLoader_GetStatus�֐����g�p���Ă��������B<br>
 * \par ���l:
 * ���̓f�[�^�����k����Ă��Ȃ��ꍇ�A
 * �{�֐��͓��̓f�[�^���o�̓A�h���X�ւ��̂܂܃R�s�[���܂��B<br>
 * \attention
 * �{�֐����g�p����ɂ́AVer.2.19.21�ȍ~��CRI File System
 * Tools���g�p���ăf�[�^���쐬����K�v������܂��B<br>
 * �i�f�[�^���쐬�����c�[�����Â��ꍇ�A�f�[�^���W�J����܂���B�j<br>
 * <br>
 * �{�֐��́ACRI�Ǝ��̃\�t�g�E�F�A���k�R�[�f�b�N�ɂ����Ή����Ă��܂���B<br>
 * �n�[�h�E�F�A�f�R�[�_���g�p����ꍇ��A�v���b�g�t�H�[���ŗL�̃R�[�f�b�N���g�p���Ă���ꍇ�A
 * �{�֐��ł̓f�[�^��W�J�ł��܂���B<br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_DecompressData(CriFsLoaderHn loader,
	void *src, CriSint64 src_size, void *dst, CriSint64 dst_size);

/*JP
 * \brief ���[�h�̒�~
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h���~���܂��B<br>
 * �{�֐��͑������A�֐��ł��B��~��Ԃ��擾����ɂ� ::criFsLoader_GetStatus �֐����g�p���Ă��������B<br>
 * \attention
 * �{�֐������s���Ă��A���[�_�̃X�e�[�^�X�� CRIFSLOADER_STATUS_STOP �ɕς��܂ł́A�o�b�t�@�ւ̃f�[�^�]���������Ă���\��������܂��B<br>
 * �X�e�[�^�X���X�V�����܂ł́A�f�[�^���[�h��̃o�b�t�@��������Ȃ��ł��������B<br>
 * \sa criFsLoader_GetStatus
 */
/*EN
 * \brief Stop Loading
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \return	CriError	Error information
 * \par
 * This function stops the loading.
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_Stop(CriFsLoaderHn loader);

/*JP
 * \brief ���[�h�X�e�[�^�X�̎擾
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[out]	status	���[�h�X�e�[�^�X
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h�X�e�[�^�X���擾���܂��B
 * \image html fs_state_transition.png �t�@�C���V�X�e�����[�_�̏�ԑJ�ڐ}
 */
/*EN
 * \brief Get Loading status
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	status	Loading status
 * \return	CriError	Error information
 * \par
 * This function returns Loading status.
 * \image html fs_state_transition.png Transition of File System Loader Status
 */
CriError CRIAPI criFsLoader_GetStatus(CriFsLoaderHn loader, CriFsLoaderStatus *status);

/*JP
 * \brief I/O�G���[�R�[�h�̎擾
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[out]	io_err	I/O�G���[�R�[�h
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * I/O�̃G���[�R�[�h���擾���܂��B<br>
 * ::criFsLoader_GetStatus �֐����X�e�[�^�X���G���[��ԂɂȂ����ꍇ�A
 * �{�֐������s���邱�Ƃ�I/O�C���^�[�t�F�[�X����Ԃ��ꂽ�G���[�R�[�h��
 * �擾���邱�Ƃ��\�ł��B
 * \sa criFsLoader_GetStatus
 */
/*EN
 * \brief Get I/O error code
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	io_err	I/O error code
 * \return	CriError	Error information
 * \par
 * This function returns I/O error code.<br>
 * When the ::criFsLoader_GetStatus function returns the error status,
 * the detail of the error is obtainable via this function.
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_GetIoError(CriFsLoaderHn loader, CriFsIoError *io_err);

/*JP
 * \brief ���[�h�T�C�Y�̎擾
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[out]	size	���[�h�T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h���ꂽ�T�C�Y���擾���܂��B<br>
 */
/*EN
 * \brief Get Loading size
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	size	Loading size
 * \return	CriError	Error information
 * \par
 * This function returns Loading size.
 */
CriError CRIAPI criFsLoader_GetLoadSize(CriFsLoaderHn loader, CriSint64 *size);

/*JP
 * \brief ���[�h�i�s�󋵂̎擾
 * \ingroup FSLIB_BASIC
 * \param[in]	loader          CriFsLoader�n���h��
 * \param[out]	progress        ���[�h�i�s�󋵁i�ǂݍ��ݍς݃T�C�Y�j
 * \param[out]	request_size	���[�h�v���T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h�i�s�󋵂��擾���܂��B<br>
 * �{�֐��Ŏ擾�ł���l�́A���[�h�i�s�󋵂̊m�F�A���[�h���s���̃��W���[�������Ȃǂɗ��p�ł��܂��B
 * \sa ::CriFsIoInterface.SetAddReadProgressCallback
 */
/*EN
 * \brief Get Loading size
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	size	Loading size
 * \return	CriError	Error information
 * \par
 * This function gets progress of the loader.
 * \sa ::CriFsIoInterface.SetAddReadProgressCallback
 */
CriError CRIAPI criFsLoader_GetProgress(CriFsLoaderHn loader, CriSint64* progress, CriSint64* request_size);

/*JP
 * \brief �v���C�I���e�B�̎擾
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[out]	priority	�ǂݍ��݃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^���[�h�̃v���C�I���e�B���擾���܂��B
 * \sa criFsLoader_SetPriority
 */
/*EN
 * \brief Get a Priority
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	priority	Priority of loader
 * \return	CriError	Error information
 * \par
 * This function gets priority of the loader.
 */
CriError CRIAPI criFsLoader_GetPriority(CriFsLoaderHn loader, CriFsLoaderPriority *prio);

/*JP
 * \brief �v���C�I���e�B�̐ݒ�
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	priority	�ǂݍ��݃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^���[�h�̃v���C�I���e�B��ݒ肵�܂��B<br>
 * �����̃��[�_�ɑ΂��A������ ::criFsLoader_Load �֐��Ń��[�h�����s�����ꍇ�A
 * �v���C�I���e�B�̍������[�_����ɓǂݍ��݂��s���܂��B<br>
 * �܂��A���ɒ�v���C�I���e�B�̃��[�_������ȃf�[�^��ǂݍ���ł���Œ��ł��A
 * �ォ�獂�v���C�I���e�B�̃��[�_�̓ǂݍ��݂��J�n����΁A��v���C�I���e�B�̃��[�_�̏����Ɋ��荞��ŁA
 * ���v���C�I���e�B�̃��[�_�̓ǂݍ��݂���Ɏ��s����܂��B<br>
 * \per ���l:
 * �����̃��[�_���S�ē���v���C�I���e�B�ł������ꍇ�A
 * �f�[�^�̓ǂݍ��݂� ::criFsLoader_Load �֐������s�������ɏ�������܂��B<br>
 * \attention
 * �t�@�C���̓ǂݍ��݂��s�Ȃ��Ă��Ȃ���ԂŃ��[�h���J�n�����ꍇ�A
 * �v���C�I���e�B�Ɋ֌W�Ȃ��A���̃��[�h�����������ɊJ�n����܂��B<br>
 * ���̂��߁A�t�@�C���̓ǂݍ��݂��s�Ȃ��Ă��Ȃ���ԂŒ�v���C�I���e�B���[�_�̓ǂݍ��݂��s�Ȃ����ꍇ�A
 * ����ɍ��v���C�I���e�B�̃��[�_�œǂݍ��݂��J�n�����Ƃ��Ă��A
 * ��v���C�I���e�B���[�_�̓ǂݍ��݂�������x�s�Ȃ��邱�ƂɂȂ�܂��B<br>
 * �i�P�ʓǂݍ��݃T�C�Y���̃f�[�^����������܂ł́A���̃��[�_�ɏ������X�C�b�`���邱�Ƃ͂���܂���B�j<br>
 * \sa criFsLoader_GetPriority, criFsLoader_Load, criFsLoader_SetReadUnitSize
 */
/*EN
 * \brief Set a Priority
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	priority	Priority of loader
 * \return	CriError	Error information
 * \par
 * This function sets priority of the loader.
 */
CriError CRIAPI criFsLoader_SetPriority(CriFsLoaderHn loader, CriFsLoaderPriority prio);

/*JP
 * \brief �P�ʓǂݍ��݃T�C�Y�̐ݒ�
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader�n���h��
 * \param[in]	unit_size	�P�ʓǂݍ��݃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \param err �G���[�R�[�h
 * \par ����:
 * �P�ʓǂݍ��݃T�C�Y��ݒ肵�܂��B
 * CriFsLoader�́A�傫�ȃT�C�Y�̃��[�h�v������������ہA����𕡐��̏����ȒP�ʂ̃��[�h�����ɕ������ĘA�����s���܂��B<br>
 * ���̊֐����g�p���邱�ƂŒP�ʃ��[�h�����T�C�Y��ύX���邱�Ƃ��\�ł��B<br>
 * ���[�h�v���̃L�����Z����A���v���C�I���e�B�̃��[�h�����̊��荞�ݓ��́A�P�ʃ��[�h�T�C�Y���E�ł̂ݏ�������܂��B<br>
 * ���̂��߁A���j�b�g�T�C�Y���������ݒ肷��ƁAI/O�����̃��X�|���X�����サ�܂��B�t�ɁA���j�b�g�T�C�Y��傫���ݒ肷��ƁA�t�@�C���P�ʂ̓ǂݍ��ݑ��x�����サ�܂��B
 */
/*EN
 * \brief Set Read Unit Size
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	unit_size	The size of read unit
 * \return	CriError	Error information
 * \par
 * When loading large data, CriFsLoader divides it into multiple small unit, and reads them.<br>
 * This function sets the size of read units.<br>
 * Interrupt request, such as cancel of current load process, can be applied only at unit boundary.<br>
 * Therefore, if the unit size is smaller, the response of I/O process becomes better. If the unit size is larger, the speed of single reading becomes better.
 */
CriError CRIAPI criFsLoader_SetReadUnitSize(CriFsLoaderHn loader, CriSint64 unit_size);

/*JP
 * \brief ���[�h���~�b�^�ԍ��̐ݒ�
 * \ingroup FSLIB_BASIC_EMB
 * \param[in]	loader	        CriFsLoader�n���h��
 * \param[in]	limiter_no		���[�h���~�b�^�ԍ�
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * CriFsLoader�n���h���Ƀ��[�h���~�b�^�ԍ������蓖�Ă܂��B<br>
 * ���ʂ̃��~�b�^�ԍ������蓖�Ă��S�Ẵ��[�_�A�O���[�v���[�_�A�o�b�`���[�_�̍��v�ǂݍ��݃T�C�Y����������܂��B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFsLoader_SetLoadLimiter(CriFsLoaderHn loader, CriFsLoadLimiterNo limiter_no);

/*==========================================================================
 *      CriFsGroupLoader API
 *=========================================================================*/
/*JP
 * \brief CRI File System - Group Loader �I�u�W�F�N�g
 * \ingroup FSLIB_GROUPLOADER
 * \par ����:
 * CriFsGroupLoader�Ƃ́ACPK�t�@�C�����ŃO���[�v�Ƃ��Ċ֘A�t����ꂽ��A�̃t�@�C�����A
 * �ꊇ���ēǂݏo�����߂̃��W���[���ł��B
 */

/*JP
 * \brief �O���[�v���[�_�̍쐬
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	binder_id		�o�C���hID
 * \param[in]	groupname		�O���[�v��
 * \param[in]	attrname		�A�g���r���[�g��
 * \param[out]	grouploaderhn	�O���[�v���[�_�n���h��
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �o�C���hID����O���[�v���[�_���쐬���A�O���[�v���[�_�n���h����Ԃ��܂��B<br>
 * �{�֐��͊������A�֐��ł��B<br><br>
 * �O���[�v���t����CPK�t�@�C�����o�C���h�����o�C���hID���K�v�ł��B<br>
 * �w�肳�ꂽ�O���[�v����A�g���r���[�g�������݂��Ȃ��ꍇ�A�O���[�v���[�_���쐬���܂���B<br>
 * �O���[�v���[�_�������O���[�v���ƃA�g���r���[�g���́A�O���[�v���[�_�쐬��ɕύX���邱�Ƃ�
 * �ł��܂���B<br>
 * ���̃O���[�v�{�A�g���r���[�g�������ꍇ�A�ʂ̃O���[�v���[�_���쐬���܂��B<br><br>
 * �A�g���r���[�g����NULL���w�肵���ꍇ�A�w��O���[�v�ɑ�����S�Ẵt�@�C�����O���[�v���[�h�̑ΏۂƂȂ�܂��B<br>
 * �܂��A�p�b�L���O�c�[���̃A�g���r���[�g�w����unone�v�Ƃ����ꍇ���A�A�g���r���[�g����NULL���w�肵�܂��B<br>
 * \par ��F
 * \code
 * CriFsBindId bndrid;
 * CriFsGroupLoaderHn gldrhn;
 * // �O���[�v���t��CPK�t�@�C��"group.cpk"�̃o�C���h
 * criFsBinder_BindCpk(bndrhn, NULL, "group.cpk", wk, wksz, &bndrid);
 * 	:
 * // �O���[�v"GROUP1", �A�g���r���[�g"IMG"�������O���[�v���[�_���쐬�B
 * criFsGroupLoader_Create(bndrid, "GROUP1", "IMG", &gldrhn);
 * \endcode
 * \code
 * // �O���[�v"GROUP"�̑S�Ẵt�@�C���������O���[�v���[�_���쐬�B
 * criFsGroupLoader_Create(bndrid, "GROUP", NULL, &gldrhn);
 * \endcode
 * \sa criFsGroupLoader_Destroy()
 */
CriError CRIAPI criFsGroupLoader_Create(CriFsBindId binder_id, const CriChar8 *groupname, const CriChar8 *attrname, CriFsGroupLoaderHn *grouploaderhn);

/*JP
 * \brief �o�C���_�n���h���Ή��̃O���[�v���[�_�̍쐬
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]     bndrhn        �o�C���_�n���h��(����CPK�t�@�C�����o�C���h���Ă���o�C���_)
 * \param[in]     groupname     �O���[�v��(NULL�w��͕s��)
 * \param[in]     attrname      �A�g���r���[�g��(NULL�w��\)
 * \param[out]    grouploaderhn �O���[�v���[�_�n���h��
 * \return        CriError      �G���[�R�[�h
 * \par ����:
 * �o�C���_�n���h������O���[�v���[�_���쐬���A�O���[�v���[�_�n���h����Ԃ��܂��B<br>
 * ���̊֐��𗘗p����ƁA�O���[�v���[�h�@�\�ƃ}���`�o�C���h�@�\�𕹗p���邱�Ƃ��ł��܂��B<br>
 * �t���r���h����CPK�t�@�C���ƁA�����r���h����CPK�t�@�C�����}���`�o�C���h���邱�ƂŁA�ꕔ�̃R���e���c�t�@�C�����X�V�����ꍇ��CPK�r���h���Ԃ�CPK�t�@�C���]�����Ԃ�ߖ񂷂邱�Ƃ��ł��܂��B<br>
 * �P��̃O���[�v���[�h�́A�ǂꂩ�P��CPK�t�@�C�����ǂݍ��ݑΏۂƂȂ�܂��B���̐���ɂ���āA�O���[�v���[�h�̍ő�̃����b�g�ł���ꊇ�����̓��삪�ێ�����Ă��܂��B<br>
 * ����āA�X�V���ꂽ�R���e���c�t�@�C���ō���CPK�t�@�C�����쐬���ă}���`�o�C���h����ꍇ�́A�O���[�v�P�ʂŁi�ύX�̂Ȃ��R���e���c�t�@�C�����܂߂āj����CPK�t�@�C���Ɋ܂߂Ă����K�v������܂��B<br>
 * ����CPK�t�@�C���̏��ł́A�O���[�v���̑S�t�@�C�����폜���ꂽ���ƂƃO���[�v�ɕύX�������������Ƃ���ʂł��܂���B�폜�⃊�l�[���ŏ������͂��̃O���[�v�ł��A�t���r���hCPK���烍�[�h�������Ă��܂��܂��B���̓��삪�D�܂����Ȃ��ꍇ�A�t���r���hCPK����蒼�����Ƃŉ����ł��܂��B<br>
 * �{�֐��𗘗p����ꍇ�́AcriFsBinder_SetPriority �֐��Ŗ����I�ɗD��x�ݒ���s�����Ƃ𐄏����܂��B�t���r���hCPK�ƍ���CPK���}���`�o�C���h����ꍇ�A����CPK�̃v���C�I���e�B�������ݒ肵�Ă��������B <br>
 */
CriError CRIAPI criFsGroupLoader_CreateFromBinderHn(
					CriFsBinderHn bndrhn, const CriChar8 *groupname, const CriChar8 *attrname, CriFsGroupLoaderHn *grouploaderhn);

/*JP
 * \brief �O���[�v���[�_�̔j��
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_��j�����܂��B<br>
 * �{�֐��͊������A�֐��ł��B<br>
 * �O���[�v���[�h���ɖ{�֐����Ăяo�����ꍇ�̓��[�h�𒆒f���A���[�h�̂��߂ɃO���[�v���[�_�����Ŋm�ۂ��Ă���
 *  ::CriFsLoaderHn ��������܂��B<br>
 * �O���[�v���[�h���̃O���[�v���[�_��j������ꍇ�A������ ::CriFsLoaderHn ����~����̂�҂��܂��̂ŁA
 * �{�֐����畜�A����܂łɎ��Ԃ�������ꍇ������܂��B<br>
 * ������������ɂ́A�O���[�v���[�_�̃X�e�[�^�X�� ::CRIFSLOADER_STATUS_LOADING �łȂ����Ƃ��m�F���Ă���A
 * �{�֐����ďo���܂��B
 * \sa criFsGroupLoader_Create() criFsGroupLoader_GetStatus()
 */
CriError CRIAPI criFsGroupLoader_Destroy(CriFsGroupLoaderHn grouploaderhn);

/*JP
 * \brief ���[�h�J�n�R�[���o�b�N�֐��̐ݒ�
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[in]	func			�O���[�v���[�_�R�[���o�b�N�֐�
 * \param[in]	obj				�O���[�v���[�_�R�[���o�b�N�֐�����
 * \return	CriError			�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�h���{���Ƀt�@�C�����ɌĂяo�����R�[���o�b�N�֐���ݒ肵�܂��B<br>
 * �{�֐��Őݒ肵���R�[���o�b�N�֐��́A���[�h���N�G�X�g���s���O�Ƀt�@�C�����Ɍďo����܂�
 * �i�܂�A�t�@�C�����Ɠ����񐔃R�[���o�b�N�֐����ďo����܂��j�B<br>
 * �O���[�v���[�h�R�[���o�b�N�֐���ݒ肵���ꍇ�A�t�@�C�����ɃR�[���o�b�N�֐����ďo�����߁A
 * �����t�@�C���̈ꊇ���[�h�͍s���܂���B<br>
 * �O���[�v���[�h�R�[���o�b�N�֐���NULL��ݒ肵���ꍇ�A�R�[���o�b�N�֐��̐ݒ�͉�������܂��B<br>
 * <br>
 * ���R�[���o�b�N�֐��ɂ���<br>
 * �R�[���o�b�N�֐��͈����Ƃ��āAobj:���[�U�[���w�肵���I�u�W�F�N�g�ƁAgfinfo:���[�h����t�@�C����
 * ���\���̂��n����܂��B<br>
 * �R�[���o�b�N�֐��̕Ԓl�́A���̃t�@�C����ǂݍ��ރo�b�t�@�ւ̃|�C���^�ƂȂ�܂��B<br>
 * �t�@�C���̓Ǎ����s�������Ȃ��ꍇ�́A NULL ��Ԓl�Ƃ��Ă��������B<br>
 * \attention
 * �R�[���o�b�N�֐���1�����o�^�ł��܂���B<br>
 * �o�^����𕡐���s�����ꍇ�A���ɓo�^�ς݂̃R�[���o�b�N�֐����A
 * �ォ��o�^�����R�[���o�b�N�֐��ɂ��㏑������Ă��܂��܂��B<br>
 * <br>
 * func��NULL���w�肷��Ƃ��Ƃœo�^�ς݊֐��̓o�^�������s���܂��B<br>
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_SetLoadStartCallback(
	CriFsGroupLoaderHn grouploaderhn, CriFsGroupLoaderLoadStartCbFunc func, void *obj);

/*JP
 * \brief �O���[�v�t�@�C�����̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	nfiles			�O���[�v�t�@�C����
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �w��̃O���[�v�ɑ�����t�@�C�������擾���܂��B<br>
 * ::criFsGroupLoader_LoadBulk �֐��̈��� gfinf �̔z��̗v�f���́A�{�֐��Ŏ擾�����
 * �O���[�v�t�@�C�����ƂȂ�܂��B
 * \sa criFsGroupLoader_GetTotalGroupDataSize(), criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetNumberOfGroupFiles(
	CriFsGroupLoaderHn grouploaderhn, CriSint32 *nfiles);

/*JP
 * \brief �O���[�v�f�[�^�T�C�Y�̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	datasize 		�f�[�^�T�C�Y
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�h�ɕK�v�ȓǍ��̈�̃T�C�Y���擾���܂��B<br>
 * �A���C�����g�Ȃǂ��������ꂽ�f�[�^�T�C�Y�ƂȂ�܂��B
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetTotalGroupDataSize(
	CriFsGroupLoaderHn grouploaderhn, CriSint64 *datasize);

/*JP
 * \brief �O���[�v�t�@�C�����̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	gfinf[]			CriFsGroupFileInfo�\���̂̔z��
 * \param[in]	numginf			�z��(gfinf[])�̗v�f��
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v�����ꂽ�����t�@�C���f�[�^�����擾���܂��B<br>
 * �t�@�C�������� ::CriFsGroupFileInfo �\���̂̔z����w�肷��K�v������܂��B<br>
 * �p�b�L���O�c�[���̃A�g���r���[�g�w����unone�v�Ƃ����O���[�v�ɑ΂��ẮA�{�֐��Ɏw�肷��O���[�v
 * ���[�_�쐬���̃A�g���r���[�g���w���NULL�Ƃ��ĉ������B<br>
 * �擾�����O���[�v�t�@�C�����( ::CriFsGroupFileInfo )�̓��Adatapointer�Ŏw�����Ǎ����NULL�ƂȂ�܂��B
 * \par ��F
 * \code
 * CriSint32 nfiles;
 * CriFsGroupFileInfo *gfinf;
 * // �O���[�v�t�@�C�����\���̔z��̈�̊m��
 * criFsGroupLoader_GetNumberOfGroupFiles(gldrhn, &nfiles);
 * gfinf = malloc( sizeof(CriFsGroupFileInfo) * nfiles );
 * // �O���[�v�t�@�C���ǂݍ��ݗ̈�̊m��
 * criFsGroupLoader_GetTotalGroupDataSize(gldrhn, &datasize);
 * databuff = malloc(datasize);
 * // �O���[�v���[�h���̎擾
 * criFsGroupLoader_GetGroupFileInfos(gldrhn, gfinf, nfiles);
 * \endcode
*/
CriError CRIAPI criFsGroupLoader_GetGroupFileInfos(
	CriFsGroupLoaderHn grouploaderhn, CriFsGroupFileInfo gfinf[], CriSint32 numgfinf);

/*JP
 * \brief �O���[�v���[�h�̊J�n
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	buffer			���[�h��o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size		���[�h��o�b�t�@�̃T�C�Y
 * \param[out]	gfinf[]			CriFsGroupInfo�\���̂̔z��
 * \param[in]	numginf			�z��(gfinf[])�̗v�f��
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v�����ꂽ�����t�@�C���f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
 * �t�@�C�������� ::CriFsGroupFileInfo �\���̂̔z����w�肷��K�v������܂��B<br>
 * �w��̃O���[�v�t�@�C����ǂݍ��߂�T�C�Y�̃��[�h�̈悪�K�v�ł��B<br>
 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� ::criFsGroupLoader_GetStatus �֐����g�p���Ă��������B<br><br>
 * �p�b�L���O�c�[���̃A�g���r���[�g�w����unone�v�Ƃ����O���[�v��ǂݍ��ޏꍇ�A�{�֐��Ɏw�肷��O���[�v
 * ���[�_�́A�O���[�v���[�_�쐬���ɃA�g���r���[�g���w���NULL�Ƃ��܂��B<br><br>
 * �O���[�v���[�h�R�[���o�b�N�֐���ݒ肵���ꍇ�A�R�[���o�b�N�֐��̕Ԓl�����[�h�A�h���X�Ƃ��܂��̂ŁA
 * �{�֐��̈��� buffer, buffer_size �͎Q�Ƃ���܂���B<br>
 * �Ȃ��w�肵�� gfinf �̓��[�h��� ::criFsGroupLoader_GetGroupFileInfoIndex�֐����̏��擾�֐��ɂă��C�u��������Q�Ƃ��s���܂��B<br>
 * ���̂��ߊ�{�I�ɂ̓n���h���j���܂ŗ̈�͕ێ����Ă����K�v������܂��B<br><br>
 * �O���[�v���[�_�����ŕ����� ::CriFsLoaderHn �𗘗p���ă��[�h���s���܂��B ::CriFsLoaderHn ���P���쐬
 * �ł��Ȃ��ꍇ�A�G���[�R�[���o�b�N���Ă΂�܂��B�O���[�v���[�_�ō쐬���� ::CriFsLoaderHn �́A
 * �O���[�v���[�h�������ɔj������܂��B
 * \par ��F
 * \code
 * CriSint32 nfiles;
 * CriFsGroupFileInfo *gfinf;
 * CriSint64 datasize;
 * void *databuff;
 * // �O���[�v�t�@�C�����\���̔z��̈�̊m��
 * criFsGroupLoader_GetNumberOfGroupFiles(gldrhn, &nfiles);
 * gfinf = malloc( sizeof(CriFsGroupFileInfo) * nfiles );
 * // �O���[�v�t�@�C���ǂݍ��ݗ̈�̊m��
 * criFsGroupLoader_GetTotalGroupDataSize(gldrhn, &datasize);
 * databuff = malloc(datasize);
 * // �O���[�v���[�h
 * criFsGroupLoader_LoadBulk(gldrhn, databuff, datasize, gfinf, nfiles);
 * // �O���[�v���[�h�����҂�
 * for (;;) {
 * 	CriFsLoaderStatus status;
 * 	criFsGroupLoader_GetStatus(gldrhn, &status);
 * 	if (status == CRIFSLOADER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsGroupLoader_GetStatus() criFsGroupLoader_SetLoadStartCallback()  criFsGroupLoader_Stop() criFsGroupLoader_Create()
 */
CriError CRIAPI criFsGroupLoader_LoadBulk(CriFsGroupLoaderHn gourploaderhn, void *buffer, CriSint64 buffer_size, CriFsGroupFileInfo gfinf[], CriSint32 numgfinf);

/*JP
 * \brief �O���[�v���[�h�̒�~�i���f�j
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_�ł̃t�@�C�����[�h�𒆒f���܂��B<br>
 * �O���[�v���[�h�𒆒f����܂łɃ��[�h���ꂽ�t�@�C������t�@�C���̓��e�͂��̂܂ܕێ�����܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * �O���[�v���[�h�̍ہA�O���[�v���[�_������ ::CriFsLoaderHn ���쐬���ăt�@�C�����[�h���s���܂��B
 * �{�֐����ďo�����ꍇ�A�O���[�v���[�h�Ɏg�p���Ă��� ::CriFsLoaderHn �ɒ��f�iStop�j�̎w�����o����
 * ���A���܂��B<br>
 * ���̂��߁A�{�֐����A���_�ł́A�܂��t�@�C�����[�h���ł���\��������܂��B<br>
 * �O���[�v���[�_�́A�����Ŏg�p���Ă��� ::CriFsLoaderHn �̃��[�h��~�m�F��ɁA���� ::CriFsLoaderHn ��
 * ������A�O���[�v���[�_�̃X�e�[�^�X�� ::CRIFSLOADER_STATUS_STOP �ɂ��܂��B<br>
 * ���̈�A�̏����� ::criFsGroupLoader_GetStatus �֐��Ăяo�����ɍs���܂��̂ŁA�{�֐��Ăяo����́A
 * �O���[�v���[�_�̃X�e�[�^�X�� ::CRIFSLOADER_STATUS_LOADING �łȂ����Ƃ��m�F���Ă��������B<br>
 * �������Ȃ��ꍇ�A�O���[�v���[�_�����Ŏg�p���Ă��� ::CriFsLoaderHn ���������܂���̂ŁA
 * ���̃O���[�v���[�_�� ::CriFsLoaderHn ���m�ۂł��Ȃ��Ȃ�\��������܂��B
 * <br>
 * \sa criFsGroupLoader_GetStatus() criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_Stop(CriFsGroupLoaderHn grouploaderhn);

/*JP
 * \brief ���[�h�X�e�[�^�X�̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	status			CriFsGroupLoaderStatus���[�h�X�e�[�^�X
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_�̃��[�h�X�e�[�^�X��Ԃ��܂��B<br>
 * �O���[�v���[�h�Ώۂ̑S�Ẵt�@�C���̃��[�h�����������ꍇ�A
 * ::CRIFSLOADER_STATUS_COMPLETE ��Ԃ��܂��B
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetStatus(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderStatus *status);

/*JP
 * \brief ���[�h���ꂽ�t�@�C�����̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	nfiles			���[�h���ꂽ�t�@�C����
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * ::criFsGroupLoader_LoadBulk �֐��Ŋ��ɓǂݍ��܂ꂽ�t�@�C���̐���Ԃ��܂��B
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetLoadedFiles(CriFsGroupLoaderHn grouploaderhn, CriSint32 *nfiles);

/*JP
 * \brief �t�@�C���̓Ǎ���Ԃ̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	gfinfo		�Ǎ���Ԃ��擾����t�@�C���� CriFsGroupFileInfo �\���̂ւ̃|�C���^
 * \param[out]	result		�t�@�C���̓Ǎ���ԁiCRI_TRUE�F�Ǎ��� CRI_FALSE:���Ǎ�)
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C�����ǂݍ��܂ꂽ���ǂ������擾���܂��B<br>
 * �Ǎ���Ԃ��擾����t�@�C���� ::CriFsGroupFileInfo �\���̂ւ̃|�C���^��
 * ::criFsGroupLoader_GetGroupFileInfoIndex �֐���
 * ::criFsGroupLoader_GetGroupFileInfo �֐��Ŏ擾���܂��B
 * \sa criFsGroupLoader_GetGroupFileInfoIndex(), criFsGroupLoader_GetGroupFileInfo()
 */
CriError CRIAPI criFsGroupLoader_IsLoaded(const CriFsGroupFileInfo *gfinfo, CriBool *result);

/*JP
 * \brief CriFsGroupFileInfo�\���̂̔z��C���f�N�X�̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[in]	fpath			�t�@�C�����t���p�X
 * \param[out]	index 			�z��C���f�N�X
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C���� ::CriFsGroupFileInfo �\���̂̔z��C���f�N�X���擾���܂��B<br>
 * �t�@�C�����̓t���p�X���Ŏw�肵�܂��B�w�肳�ꂽ�t�@�C���̌����ɂ̓o�C�i���T�[�`���g�p���܂��B<br>
 * �w�肳�ꂽ�t�@�C����������Ȃ��ꍇ�́A�Ԓl��-1�ƂȂ�܂��B<br>
 * �O���[�v���[�h���ꂽ�X�̃t�@�C�������ۂɃ��[�h���ꂽ�A�h���X�́A
 * ::CriFsGroupFileInfo �\���̂ɋL�q����܂��B<br>
 * ���[�h���ꂽ�f�[�^�փA�N�Z�X����ɂ́A::CriFsGroupFileInfo �\���̂��擾����K�v������܂��B<br>
 * ::CriFsGroupFileInfo �\���̂��擾������@�ɂ́A���[�h�����t�@�C���̃t�@�C������������
 * �R���e���c�t�@�C��ID���w�肵�A�Y������\���̗v�f���擾������@�ƁA�{�֐��Ŏ擾�����C���f�N�X�ɂ��
 * �\���̔z��𒼐ڃA�N�Z�X������@�̂Q�ʂ肪����܂��B
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfo()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoIndex(CriFsGroupLoaderHn grouploaderhn,  const CriChar8 *fpath, CriSint32 *index);

/*JP
 * \brief CriFsGroupFileInfo�\���̂̔z��C���f�N�X�̎擾(ID�w��)
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[in]	id				�R���e���c�t�@�C��ID
 * \param[out]	index 			�z��C���f�N�X
 * \return		CriError		�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C���� ::CriFsGroupFileInfo �\���̂̔z��C���f�N�X���擾���܂��B<br>
 * �t�@�C���̓R���e���c�t�@�C��ID�Ŏw�肵�܂��B�w�肳�ꂽ�t�@�C���̌����ɂ̓��j�A�T�[�`���g�p���Ă��܂��B<br>
 * �w�肳�ꂽ�t�@�C����������Ȃ��ꍇ�́A�Ԓl��-1�ƂȂ�܂��B<br>
 * �O���[�v���[�h���ꂽ�X�̃t�@�C�������ۂɃ��[�h���ꂽ�A�h���X�́A
 * ::CriFsGroupFileInfo �\���̂ɋL�q����܂��B<br>
 * �������@�̓s����A���ɃO���[�v���[�h�ς� ::CriFsGroupFileInfo �����擾���Ă���ꍇ�́A
 *  ::CriFsGroupFileInfo ����ID�𒼐ڌ�����������A�{�֐��ŃC���f�N�X���擾����������������������ł��B<br>
 * ���[�h���ꂽ�f�[�^�փA�N�Z�X����ɂ́A::CriFsGroupFileInfo �\���̂��擾����K�v������܂��B<br>
 * ::CriFsGroupFileInfo �\���̂��擾������@�ɂ́A���[�h�����t�@�C���̃t�@�C������������
 * �R���e���c�t�@�C��ID���w�肵�A�Y������\���̗v�f���擾������@�ƁA�{�֐��Ŏ擾�����C���f�N�X�ɂ��
 * �\���̔z��𒼐ڃA�N�Z�X������@�̂Q�ʂ肪����܂��B
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoById()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoIndexById(CriFsGroupLoaderHn grouploaderhn, CriFsFileId id, CriSint32 *index);

/*JP
 * \brief CriFsGroupFileInfo�\���̂̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[in]	fpath 			�t�@�C�����t���p�X
 * \param[out]	gfinfo			CriFsGroupFileInfo�\���̂ւ̃|�C���^�ւ̃|�C���^
 * \return		CriError 		�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C���� ::CriFsGroupFileInfo �\���̂ւ̃|�C���^���擾���܂��B<br>
 * �t�@�C�����̓t���p�X���Ŏw�肵�܂��B<br>
 * �w�肳�ꂽ�t�@�C����������Ȃ��ꍇ�́A�o�͒l�� NULL �ƂȂ�܂��B
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoIndex()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfo(CriFsGroupLoaderHn grouploaderhn, const CriChar8 *fpath, const CriFsGroupFileInfo **gfinfo);

/*JP
 * \brief CriFsGroupFileInfo�\���̂̎擾(ID�w��)
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[in]	id	 			�R���e���c�t�@�C��ID
 * \param[out]	gfinfo			CriFsGroupFileInfo�\���̂ւ̃|�C���^�ւ̃|�C���^
 * \return		CriError 		�G���[�R�[�h
 * \par �����F
 * �w�肳�ꂽ�t�@�C���� ::CriFsGroupFileInfo �\���̂ւ̃|�C���^���擾���܂��B<br>
 * �t�@�C���̓R���e���c�t�@�C��ID�Ŏw�肵�܂��B<br>
 * �w�肳�ꂽ�t�@�C����������Ȃ��ꍇ�́A�o�͒l�� NULL �ƂȂ�܂��B
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoIndexById()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoById(CriFsGroupLoaderHn grouploaderhn, CriFsFileId id, const CriFsGroupFileInfo **gfinfo);

/*JP
 * \brief �O���[�v���̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	groupname 		�O���[�v��
 * \return		CriError 		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_�ň����O���[�v�̃O���[�v�����擾���܂��B
 */
CriError CRIAPI criFsGroupLoader_GetGroupName(CriFsGroupLoaderHn grouploaderhn, const CriChar8 **groupname);

/*JP
 * \brief �O���[�v�����̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in] 	grouploaderhn	�O���[�v���[�_�n���h��
 * \param[out]	attrname 		�O���[�v����
 * \return		CriError 		�G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_�ň����O���[�v�̃O���[�v�������擾���܂��B
 */
CriError CRIAPI criFsGroupLoader_GetAttributeName(CriFsGroupLoaderHn grouploaderhn, const CriChar8 **attrname);

/*JP
 * \brief �v���C�I���e�B�̎擾
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader�n���h��
 * \param[out]	priority	�ǂݍ��݃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �O���[�v���[�_���Ŏg�p���郍�[�_( ::CriFsLoaderHn )�̃v���C�I���e�B���擾���܂��i�����l�� ::CRIFSLOADER_PRIORITY_NORMAL �ł��j�B
 * ���[�_�̃v���C�I���e�B�Ɋւ��ẮA::criFsLoader_GetPriority �� ::criFsLoader_SetPriority �̐������Q�Ƃ��������B
 * \sa criFsGroupLoader_GetLoaderPriority, criFsLoader_GetPriority, criFsLoader_SetPriority
 */
CriError CRIAPI criFsGroupLoader_GetLoaderPriority(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderPriority *prio);

/*JP
 * \brief �v���C�I���e�B�̐ݒ�
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader�n���h��
 * \param[in]	priority	�ǂݍ��݃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �O���[�v���[�_���Ŏg�p���郍�[�_( ::CriFsLoaderHn )�̃v���C�I���e�B��ݒ肵�܂��i�����l�� ::CRIFSLOADER_PRIORITY_NORMAL �ł��j�B
 * ���[�_�̃v���C�I���e�B�Ɋւ��ẮA::criFsLoader_GetPriority �� ::criFsLoader_SetPriority �̐������Q�Ƃ��������B
 * \sa criFsGroupLoader_SetLoaderPriority, criFsLoader_SetPriority
 */
CriError CRIAPI criFsGroupLoader_SetLoaderPriority(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderPriority prio);

/*JP
 * \brief �P�ʓǂݍ��݃T�C�Y�̐ݒ�
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader�n���h��
 * \param[in]	unit_size	�P�ʓǂݍ��݃T�C�Y
 * \return	CriError	�G���[�R�[�h
 * \param err �G���[�R�[�h
 * \par ����:
 * �O���[�v���[�_���Ŏg�p���郍�[�_�̒P�ʓǂݍ��݃T�C�Y��ݒ肵�܂��B
 * CriFsLoader�́A�傫�ȃT�C�Y�̃��[�h�v������������ہA����𕡐��̏����ȒP�ʂ̃��[�h�����ɕ������ĘA�����s���܂��B<br>
 * ���̊֐����g�p���邱�ƂŒP�ʃ��[�h�����T�C�Y��ύX���邱�Ƃ��\�ł��B<br>
 * ���[�h�v���̃L�����Z����A���v���C�I���e�B�̃��[�h�����̊��荞�ݓ��́A�P�ʃ��[�h�T�C�Y���E�ł̂ݏ�������܂��B<br>
 * ���̂��߁A���j�b�g�T�C�Y���������ݒ肷��ƁAI/O�����̃��X�|���X�����サ�܂��B�t�ɁA���j�b�g�T�C�Y��傫���ݒ肷��ƁA�t�@�C���P�ʂ̓ǂݍ��ݑ��x�����サ�܂��B
 */
CriError CRIAPI criFsGroupLoader_SetReadUnitSize(CriFsGroupLoaderHn grouploaderhn, CriSint64 unit_size);

/*JP
 * \brief ���[�h���~�b�^�ԍ��̐ݒ�
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in]	grouploader		CriFsGroupLoader�n���h��
 * \param[in]	limiter_no		���[�h���~�b�^�ԍ�
 * \return	CriError			�G���[�R�[�h
 * \par ����:
 * CriFsGroupLoader�n���h���Ƀ��[�h���~�b�^�ԍ������蓖�Ă܂��B<br>
 * ���ʂ̃��~�b�^�ԍ������蓖�Ă��S�Ẵ��[�_�A�O���[�v���[�_�A�o�b�`���[�_�̍��v�ǂݍ��݃T�C�Y����������܂��B<br>
 * \attention
 * �Q�[���@�����ł̓��[�h���~�b�^�@�\�͔�T�|�[�g�ł��B���̊֐��͌Ăяo���Ȃ��ł��������B<br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFsGroupLoader_SetLoadLimiter(CriFsGroupLoaderHn grouploaderhn, CriFsLoadLimiterNo limiter_no);

/*JP
 * \brief �T�[�o����������̏����t�@�C�����̐���
 * \ingroup FSLIB_GROUPLOADER
 * \param[in] grouploaderhn     �O���[�v���[�_�n���h��
 * \param[in] nfile_per_server  �P�T�[�o������̏��������t�@�C�����A�܂��́A���ʒl
 *                              CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT
 * \return  CriError �G���[�R�[�h
 * \par �����F
 * �O���[�v���[�_�̏��������̏������@��ݒ肵�܂��B<br>
 * ���̊֐����Ăяo���Ȃ��ꍇ�A�܂��́ACRIFS_GROUPLOADER_NO_PREPARATION_LIMIT ���w�肵���ꍇ�́A
 * criFsGroupLoader_LoadBulk �����ŏ������������������܂��B���̏������@�ł́A�O���[�v���t�@�C����������
 * �ꍇ�� criFsGroupLoader_LoadBulk �֐��̏������Ԃ������Ȃ�A�R�}��������������ꍇ������܂��B<br>
 * ���̖�����������i�Ƃ��āA�O���[�v���[�_�̏����������T�[�o�����ɕ��U������@�\��ǉ����܂����B<br>
 * ���ʒl�ȊO�̐��l���w�肵���ꍇ�A���������� criFsGroupLoader_LoadBulk �֐�����T�[�o�����Ɉڊǂ���A
 * 1��̃T�[�o�����ŏ����������s���t�@�C���̐��͎w�肵�����ɐ�������܂��B<br>
 * �O���[�v���[�_�̃T�[�o�����́AcriFsGroupLoader_GetStatus �֐����Ŏ��s����܂��B<br>
 * <br>
 * ��̓I�ȃR�[�h�̗�͈ȉ��̂Ƃ���ł��B
 * \par ��:
 * \code
 * {
 *   // �n���h��a�̏���������LoadBulk�֐����ōs���B
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_a, CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT);
 *   // �n���h��b��c�̏��������̓T�[�o������500�t�@�C���Âs���B�n���h�����Ɍʂɏ����ʂ𐧌�����B
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_b, 500);
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_c, 500);
 * }
 * \endcode
 */
CriError CRIAPI criFsGroupLoader_LimitNumPreparingFiles(CriFsGroupLoaderHn grouploaderhn, CriSint32 nfile_per_server);

/*JP
 * \brief ����A�g���r���[�g��CriFsGroupFileInfo�\���̔z��̊J�n�I�t�Z�b�g�̎擾
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in] group_all   �O���[�v���[�_�n���h��(�O���[�v�S��)
 * \param[in] group_attr  �O���[�v���[�_�n���h��(����A�g���r���[�g)
 * \param[out] offset     �O���[�v�S�̂�CriFsGroupFileInfo�\���̂̔z��ɑ΂���A����A�g���r���[�g���J�n����I�t�Z�b�g
 * \return  CriError   �G���[�R�[�h
 * \par �����F
 * ���L�̏����ŃO���[�v���[�_�𗘗p����ꍇ�ɁA���̊֐��𗘗p����ƌ����������������P���邱�Ƃ��ł��܂��B<br>
 * \par �K�p����:
 * �@�E�O���[�v���ɕ����̃A�g���r���[�g�̃t�@�C�����܂߂�B<br>
 * �@�E�O���[�v���̕����̃A�g���r���[�g�̃t�@�C���𓯎��Ƀ��[�h����B<br>
 * �@�E�A�g���r���[�g���ɓ]�����؂蕪����B<br>
 * �@�E�A�g���r���[�g����肷����͎������ɁA�t�@�C�����܂��̓t�@�C��ID����O���[�v�t�@�C��������������B<br>
 * �@�E�O���[�v�̊K�w�\���i�T�u�O���[�v�j�͗��p���Ă��Ȃ��B<br>
 * �@�ECPK�t�@�C�����ɖ{API�����p����ǉ���񂪋L�^����Ă���B�i�{API�̃T�|�[�g�͊��ˑ��ł��j<br>
 * <br>
 * ���̊֐��𗘗p���Ȃ��ꍇ�́A�X�̃t�@�C�����ǂ̃A�g���r���[�g�ɑ����邩������Ȃ��̂ŁA�S�ẴO���[�v�n���h���𒀎��������Ȃ���΂Ȃ�܂���B<br>
 * ���̊֐��𗘗p����ꍇ�́A�P��̌����ŖړI�̃t�@�C���������邱�Ƃ��ł��܂��B<br>
 * �O���[�v���[�h�����s����n���h���́A�O���[�v���ƃA�g���r���[�g�����w�肵�āA�O���[�v���[�_�n���h�����쐬���Ă��������B<br>
 * ����ɂP�A����������ړI�Ƃ����A�O���[�v�S�̂̃O���[�v���[�_�n���h�����쐬���܂��B���̎��̓O���[�v���������w�肵�A�A�g���r���[�g���ɂ�CRI_NULL���w�肵�Ă��������B<br>
 * CriFsGroupFileInfo�\���̔z��ɂ��ẮA�O���[�v�S�̂̔z���A���������Ƃ��Ċm�ۂ��Ă��������B<br>
 * ���̃O���[�v�S�̂̔z���؂蕪���āA�X�� criFsGroupLoader_LoadBulk �֐��̈����Ɏw�肵�܂��B<br>
 * �X�̃O���[�v���[�_�̓���ƁA�O���[�v�S�̂ɑ΂��錟���������������邽�߂ɂ́A�O���[�v�S�̂̔z���K�؂ɐ؂蕪����K�v������܂��B<br>
 * �{�֐����o�͂���u����A�g���r���[�g�̊J�n�I�t�Z�b�g�v�𗘗p���āA�S�̂̔z���؂蕪���Ă��������B<br>
 * ��̓I�ȃR�[�h�̗���ȉ��Ɏ����܂��B<br>
 * \par ��:
 * \code
 * {
 *   criFsGroupLoader_Create(bindid, "GROUP1", CRI_NULL, &group_all);
 *   criFsGroupLoader_Create(bindid, "GROUP1", "RAM1", &group_ram1);
 *   criFsGroupLoader_Create(bindid, "GROUP1", "RAM2", &group_ram2);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_all, &nfiles_all);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_ram1, &nfiles_ram1);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_ram2, &nfiles_ram2);
 *   criFsGroupLoader_GetGroupFileInfoStartOffset(group_all, group_ram1, &offset_ram1);
 *   criFsGroupLoader_GetGroupFileInfoStartOffset(group_all, group_ram2, &offset_ram2);
 *   gfinf_all = malloc(sizeof(CriFsGroupFileInfo) * nfiles_all);
 *   //memset(gfinf_all, 0, sizeof(CriFsGroupFileInfo) * nfiles_all);���[���N���A���K�v�ȃP�[�X�ɂ��ĉ��L�Q��
 *   criFsGroupLoader_LoadBulk(group_ram1, buffer_ram1, buffer_size_ram1, &gfinf_all[offset_ram1], nfiles_ram1);
 *   criFsGroupLoader_LoadBulk(group_ram2, buffer_ram2, buffer_size_ram2, &gfinf_all[offset_ram2], nfiles_ram2);
 *   for (;;) {
 *     criFsGroupLoader_GetStatus(group_ram1, &status_ram1);
 *     criFsGroupLoader_GetStatus(group_ram2, &status_ram2);
 *     if (status_ram1 == CRIFSLOADER_STATUS_COMPLETE && 
 *         status_ram2 == CRIFSLOADER_STATUS_COMPLETE) {
 *       break;
 *     }
 *   }
 *   criFsGroupLoader_GetGroupFileInfoIndex(group_all, "sample.bmp", &index);
 *   userDrawBitmap(gfinf_all[index].datapointer);
 * }
 * \endcode
 * \attention
 * ��:�O���[�v�Ɋ܂܂��S�ẴA�g���r���[�g�����[�h�����ΏۂƂ��Ȃ��ꍇ�ɂ͒��ӂ��K�v�ł��B
 * ���[�h���Ȃ������t�@�C���ł��������������܂����A�擾�����C���f�b�N�X�ŎQ�Ƃł���
 * CriFsGroupFileInfo�\���̂̓��e�͕s��l�ƂȂ��Ă��܂��B
 * ���[�h���Ȃ������t�@�C������������\��������Ȃ�A���炩���ߔz����[���N���A���Ă����A
 * �\���̂̓��e�������ł��邱�Ƃ����ʂł���悤�ɂ��Ă��������B<br>
 * \attention
 * �{API�̃T�|�[�g�͊��ˑ��ł��B���T�|�[�g�̊��ŌĂяo�����ꍇ�̓G���[�ƂȂ�܂��B<br>
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoStartOffset(CriFsGroupLoaderHn group_all, CriFsGroupLoaderHn group_attr, CriSint32 *offset);

/*JP
 * \brief �P��t�@�C���̃��[�h�m�F�̐ݒ�
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in]	use_flag		CRI_TRUE �܂��� CRI_FALSE
 * \par ����:
 * criFsGroupLoader_IsLoaded�֐����g�p���邩��ݒ肵�܂��B<br>
 * CRI_TRUE���w�肷��Ǝg�p���ACRI_FALSE���w�肷��Ǝg�p���܂���<br>
 * criFsGroupLoader_IsLoaded�֐����g�p���Ȃ��ꍇ�A���[�h�������̏����������Ȃ�܂��A
 * �P��t�@�C���̃��[�h�m�F���s���܂���B
 * criFsGroupLoader_LoadBulk �֐������s����O�ɖ{�֐����Ă�ł��������B
 * \sa criFsGroupLoader_IsLoaded criFsGroupLoader_LoadBulk 
 */
void CRIAPI criFsGroupLoader_SetUseLoadedFlag(CriBool use_flag);

/*==========================================================================
 *      Log Output API
 *=========================================================================*/
/*JP
 * \brief ���O�o�͋@�\�̒ǉ�
 * \ingroup FSLIB_CRIFS
 * \param[in] mode				���O�o�̓��[�h
 * \param[in] param				�g���p�����[�^
 * \return	CriError 			�G���[�R�[�h
 * \par ����:
 * ���O�o�͋@�\��L���ɂ��A�t�@�C���A�N�Z�X���O�̏o�͂��J�n���܂��B<br>
 * �{�֐������s����ƁA�t�@�C���ɃA�N�Z�X����^�C�~���O�ŁA�f�o�b�K���Ƀt�@�C���A�N�Z�X���O���o�͂����悤�ɂȂ�܂��B<br>
 * \attention
 * �{�֐������s��A�K���΂ɂȂ� ::criFs_DetachLogOutput �֐������s���Ă��������B<br>
 * �܂��A ::criFs_DetachLogOutput �֐������s����܂ł́A�{�֐����ēx���s���邱�Ƃ͂ł��܂���B<br>
 * \sa criFs_DetachLogOutput
 */
CriError CRIAPI criFs_AttachLogOutput(CriFsLogOutputMode mode, void *param);

/*JP
 * \brief ���O�o�͋@�\�̍폜
 * \ingroup FSLIB_CRIFS
 * \return	CriError 			�G���[�R�[�h
 * \par ����:
 * ���O�o�͋@�\�𖳌��ɂ��A�t�@�C���A�N�Z�X���O�̏o�͂��~���܂��B<br>
 * �{�֐������s���邱�ƂŁA�f�o�b�K���ւ̃t�@�C���A�N�Z�X���O�̏o�͂��~���邱�Ƃ��\�ł��B<br>
 * \attention
 * ::criFs_DetachLogOutput �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criFs_AttachLogOutput
 */
CriError CRIAPI criFs_DetachLogOutput(void);

/*JP
 * \brief ���[�U��`���O�o�͊֐��̓o�^
 * \ingroup FSLIB_CRIFS
 * \param[in]	func			���O�o�͊֐�
 * \param[in]	obj				���O�o�͊֐��ɓn���I�u�W�F�N�g
 * \return	CriError 			�G���[�R�[�h
 * \par ����:
 * ���O�̏o�͊֐������[�U�w��̊֐��ɒu�������܂��B<br>
 * �{�֐����g�p���邱�ƂŁA�t�@�C���A�N�Z�X���O�̏o�͕��@�����[�U�����R��
 * �J�X�^�}�C�Y���邱�Ƃ��\�ł��B
 * \par ���l:
 * �{�֐����g�p���Ă��Ȃ��ꍇ��A���O�o�͊֐��ifunc�j��NULL���w�肵���ꍇ�A
 * CRI File System���C�u�����̃f�t�H���g���O�o�͊֐����g�p����܂��B
 */
CriError CRIAPI criFs_SetUserLogOutputFunction(CriFsLogOutputFunc func, void *obj);

/*JP
 * \brief ���[�h��Ԃ̊J�n
 * \ingroup FSLIB_CRIFS
 * \param[in] name				���[�h��Ԗ�
 * \return	CriError 			�G���[�R�[�h
 * \par ����:
 * ���[�h��Ԃ̊J�n��錾���܂��B<br>
 * ::criFs_AttachLogOutput �֐��Ńt�@�C���A�N�Z�X���O�̏o�͂�L���ɂ��Ă���ꍇ�A�{�֐��̈����iname�j�Ŏw�肵�����[�h��Ԗ������O�ɏo�͂���܂��B<br>
 * ���[�h��Ԃ́A�t�@�C�����œK�ɔz�u���邽�߂̖ڈ��Ƃ��Ďg�p����܂��B<br>
 * CPK File Builder�Ńt�@�C���A�N�Z�X���O����O���[�v���쐬����ꍇ�A�{�֐��Œ�`�������[�h��Ԃ��O���[�v�ɕϊ�����܂��B<br>
 * �i���ꃍ�[�h��ԓ��Ń��[�h����t�@�C�����m�́A�œK�z�u���ɋ߂��ꏊ�ɔz�u�����\���������Ȃ�܂��B�j<br>
 * \attention
 * �����̃��[�h��Ԃ��d�������邱�Ƃ͂ł��܂���B<br>
 * �{�֐������s��A�K���΂ɂȂ� ::criFs_EndLoadRegion �֐������s���Ă��������B
 * �{�֐��� ::criFs_BeginGroup �֐��𕹗p���邱�Ƃ͂ł��܂���B<br>
 * �iCRI File System Ver.2.02.00���A�{�֐��̋@�\�� ::criFs_BeginGroup �֐��ɓ�������A�֐����̂� ::criFs_BeginGroup �֐����Ăяo���}�N���ɕύX����܂����B�j<br>
 * \sa criFs_EndLoadRegion, criFs_BeginGroup
 */
#define criFs_BeginLoadRegion(name)			criFs_BeginGroup(name, NULL)

/*JP
 * \brief ���[�h��Ԃ̏I��
 * \ingroup FSLIB_CRIFS
 * \return	CriError 			�G���[�R�[�h
 * \par ����:
 * ���[�h��Ԃ̏I����錾���܂��B
 * \attention
 * �{�֐��� ::criFs_EndGroup �֐��𕹗p���邱�Ƃ͂ł��܂���B<br>
 * �iCRI File System Ver.2.02.00���A�{�֐��̋@�\�� ::criFs_EndGroup �֐��ɓ�������A�֐����̂� ::criFs_EndGroup �֐����Ăяo���}�N���ɕύX����܂����B�j<br>
 * \sa criFs_BeginLoadRegion, criFs_EndGroup
 */
#define criFs_EndLoadRegion()				criFs_EndGroup()

/*==========================================================================
 *      CriFsStdio API
 *=========================================================================*/
/*JP
 * \brief ANSI C �ɏ������t�@�C���I�[�v��
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] bndr  �I�[�v���������t�@�C�����o�C���h����Ă���CriFsBinder�̃n���h��
 * \param[in] fname �I�[�v���������t�@�C���p�X
 * \param[in] mode  �I�[�v�����[�h ("r":�ǂݍ��ݐ�p���[�h,"w":�������ݐ�p���[�h)
 * \return	CriFsStdioHn ���������ꍇ�A�L����CriFsStdio�n���h����Ԃ��܂��B<br>
 *                       ���s�����ꍇ��NULL��Ԃ��܂��B
 * \par �����F
 * �w�肳�ꂽ�t�@�C�����I�[�v�����܂��B<br>
 * �������ɂ́A�I�[�v���������t�@�C�����o�C���h����Ă���o�C���_���w�肵�܂��B<br>
 * �v���b�g�t�H�[���W���̃t�@�C���p�X����t�@�C�����I�[�v���������ꍇ�A�������ɂ�NULL���w�肵�܂��B<br>
 * �������ɂ́A�I�[�v���������t�@�C���p�X�𕶎���Ŏw�肵�܂��B<br>
 * ��O�����́A�I�[�v���̃��[�h�ł��B"r"���w�肷��Ɠǂݍ��ݐ�p���[�h�A<br>
 * "w"���w�肷��Ə������ݐ�p���[�h�Ńt�@�C�����I�[�v�����܂��B<br>
 * �������ݐ�p���[�h�́A�t�@�C���������݂��T�|�[�g���Ă���v���b�g�t�H�[���ł̂ݐ���ɓ��삵�A
 * ���T�|�[�g�̃v���b�g�t�H�[���ł̓G���[�R�[���o�b�N���������A�I�[�v���͎��s���܂��B<br>
 * \par ���l�F
 * �t�@�C���̏������݂͈ȉ��̃��[���ōs���܂��B<br>
 * - �w�肵���t�@�C�������݂��Ȃ��ꍇ�A�V�K�Ƀt�@�C�����쐬�B
 * - �w�肵���t�@�C�������ɑ��݂���ꍇ�A�����t�@�C����ҏW���܂��B<br>
 * �i�����t�@�C�����폜����邱�Ƃ͂���܂���B�j
 * <br>
 * �����t�@�C�����폜���ĐV�K�Ƀt�@�C���̏������݂��s�������ꍇ�ɂ́A
 * �{�֐������s����O�� ::criFsStdio_RemoveFile �֐��Ńt�@�C���̍폜���s���Ă��������B
 * \sa criFsStdio_CloseFile, criFsStdio_RemoveFile
 */
CriFsStdioHn CRIAPI criFsStdio_OpenFile(CriFsBinderHn bndr, const char *fname, const char *mode);

/*JP
 * \brief ANSI C �ɏ������t�@�C���N���[�Y
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn �N���[�Y����t�@�C����CriFsStdio�n���h��
 * \return CriError �G���[�R�[�h<br>
 * \par �����F
 * �w�肵���t�@�C�����N���[�Y���܂��B<br>
 * �������ɂ́A�N���[�Y�������t�@�C����CriFsStdio�n���h�����w�肵�܂��B<br>
 * \sa criFsStdio_OpenFile
 */
CriError CRIAPI criFsStdio_CloseFile(CriFsStdioHn stdhn);

/*JP
 * \brief ANSI C �ɏ�����API�Ɋ�Â��t�@�C���T�C�Y�擾
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn �T�C�Y���擾�������t�@�C����CriFsStdio�n���h��
 * \return CriSint64 �w�肵���n���h�����L���ł���΁A�t�@�C���T�C�Y��Ԃ��܂��B
 * \par �����F
 * �w�肵���t�@�C���̃T�C�Y���擾���܂��B<br>
 * �������ɂ́A�T�C�Y���擾�������t�@�C����CriFsStdio�n���h�����w�肵�܂��B<br>
 */
CriSint64 CRIAPI criFsStdio_GetFileSize(CriFsStdioHn stdhn);

/*JP
 * \brief ANSI C �ɏ������t�@�C�����[�h�I�t�Z�b�g�̎擾
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn ���[�h�I�t�Z�b�g���擾�������t�@�C����CriFsStdio�n���h��
 * \return CriSint64 �w�肵���n���h�����L���ł���΁A���[�h�I�t�Z�b�g�ibyte�j��Ԃ��܂��B
 * \par �����F
 * �w�肵���t�@�C���̓Ǎ��ʒu���擾���܂��B<br>
 * �������ɂ́A�Ǎ��ʒu���擾�������t�@�C���́ACriFsStdio�n���h�����w�肵�܂��B<br>
 * \sa criFsStdio_SeekFile
 */
CriSint64 CRIAPI criFsStdio_TellFileOffset(CriFsStdioHn stdhn);

/*JP
 * \brief ANSI C �ɏ����� �t�@�C�����[�h�I�t�Z�b�g�̃V�[�N
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn                ���[�h�I�t�Z�b�g���V�[�N�������t�@�C����CriFsStdio�n���h��
 * \param[in] offset               �V�[�N�̃I�t�Z�b�g�ibyte�j
 * \param[in] CRIFSSTDIO_SEEK_TYPE �V�[�N�J�n�ʒu�̎w��
 * \return CriSint64 ���� 0<br>
 *                   ���s -1<br>
 * \par �����F
 * �w�肵���t�@�C���̃��[�h�I�t�Z�b�g���V�[�N���܂��B<br>
 * �������ɂ́A���[�h�I�t�Z�b�g���V�[�N�������t�@�C���́ACriFsStdio�n���h�����w�肵�܂��B<br>
 * �������ɂ́A�V�[�N�̃I�t�Z�b�g���w�肵�܂��B�P�ʂ�byte�ł��B<br>
 * \attention
 * �t�@�C���擪����O�ɃV�[�N���邱�Ƃ͏o���܂���B�t�@�C�����[�h�I�t�Z�b�g���t�@�C���擪���
 * ��O�ɂȂ�悤�V�[�N�I�t�Z�b�g���w�肵���ꍇ�A�V�[�N���ʂ̃t�@�C�����[�h�I�t�Z�b�g�̓t�@�C���擪�ɂȂ�܂��B<br>
 * ����A�t�@�C���I�[�𒴂����V�[�N�͉\�ł��B<br>
 * �܂��A�w���CriFsStdio�n���h�������ԃo�b�t�@�����ꍇ�A
 * �{�֐��Œ��ԃo�b�t�@�̗L���͈͊O�ɃV�[�N����ƁA���ԃo�b�t�@�̓��e���j������܂��B<br>
 * \sa criFsStdio_TellFileOffset
 * \sa criFsStdio_SetInterstageBuffer
 */
CriSint64 CRIAPI criFsStdio_SeekFile(CriFsStdioHn rdr, CriSint64 offset, CRIFSSTDIO_SEEK_TYPE seek_type);

/*JP
 * \brief ANSI C �ɏ�����API�Ɋ�Â��t�@�C���Ǎ��p���ԃo�b�t�@�̐ݒ�
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn            ���ԃo�b�t�@��ݒ肵����CriFsStdio�n���h��
 * \param[in] temp_buffer      ���ԃo�b�t�@�̐擪�A�h���X
 * \param[in] temp_buffer_size ���ԃo�b�t�@�̃T�C�Y�ibyte�j
 * \return CriSint64 ���ԃo�b�t�@�ݒ��̃t�@�C���Ǎ��ʒu
 * \par �����F
 * �w�肵���t�@�C����ǂݍ��ލۂ̒��ԃo�b�t�@��ݒ肵�܂��B<br>
 * �������ɂ́A���ԃo�b�t�@��ݒ肵����CriFsStdio�n���h�����w�肵�܂��B<br>
 * �������ɂ́A���ԃo�b�t�@�Ƃ��ė��p���郁�����̈�̐擪�A�h���X���w�肵�܂��B
 * NULL���w�肵���ꍇ�A���ԃo�b�t�@���g���܂���B<br>
 * ��O�����ɂ́A���ԃo�b�t�@�̃T�C�Y���w�肵�܂��B�P�ʂ�byte�ł��B
 * 0���w�肵���ꍇ�A�������ɗL���ȃA�h���X���w�肵�Ă��Ă��A���ԃo�b�t�@���g���܂���B<br>
 * \attention
 * criFsStdio_OpenFile()�œ���ꂽ�t�@�C���n���h���́A�f�t�H���g�ł͒��ԃo�b�t�@�������܂���B<br>
 * ���ԃo�b�t�@���K�v�ȏꍇ�A�{�֐��Őݒ肷��K�v������܂��B<br>
 * ���ԃo�b�t�@��ݒ肷��ƁA�ő�� temp_buffer_size ���̃f�[�^���t�@�C������
 * ���ԃo�b�t�@�֓ǂݍ��ނ悤�ɂȂ�܂��B<br>
 * ���ԃo�b�t�@���Ƀf�[�^���������A
 * criFsStdio_ReadFile()�ɂ��t�@�C���Ǎ��̓������R�s�[�ɂȂ邽�߁A
 * �A�����čׂ����t�@�C���Ǎ����s���ꍇ
 * �����I�ȃt�@�C���A�N�Z�X�̔����p�x��}���邱�Ƃ��ł��܂��B<br>
 * �������AcriFsStdio_SeekFile()�Œ��ԃo�b�t�@�̗L���͈͊O�ɃV�[�N����ƁA
 * ���ԃo�b�t�@�̓��e���j������܂��B
 * \sa criFsStdio_TellFileOffset
 * \sa criFsStdio_SeekFile
 * \sa criFsStdio_OpenFile
 * \sa criFsStdio_ReadFile
 */
CriSint64 CRIAPI criFsStdio_SetInterstageBuffer(CriFsStdioHn stdhn, CriUint8 *temp_buffer, CriUint32 temp_buffer_size);

/*JP
 * \brief ANSI C �ɏ�����API�Ɋ�Â��t�@�C������̃f�[�^�Ǎ�
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn �Ǎ�����CriFsStdio�n���h��
 * \param[in] rsize �Ǎ��v���T�C�Y�ibyte�j
 * \param[in] buf   �Ǎ���o�b�t�@
 * \param[in] bsize �Ǎ���o�b�t�@�̃T�C�Y�ibyte�j
 * \return CriSint64 �Ǎ����� �ǂݍ��߂��T�C�Y�ibyte�j<br>
 *                   �Ǎ����s -1
 * \par �����F
 * �t�@�C������f�[�^���w��T�C�Y�ibyte�j���ǂݍ��݂܂��B<br>
 * �������ɂ́A�f�[�^�̓Ǎ����ł���t�@�C����CriFsStdio�n���h�����w�肵�܂��B<br>
 * �������ɂ́A�ǂݍ��ރT�C�Y���w�肵�܂��B<br>
 * ��O�����ɂ́A�ǂݍ��񂾃f�[�^�̏������ݐ�o�b�t�@���w�肵�܂��B<br>
 * ��l�����ɂ́A�ǂݍ��񂾃f�[�^�̏������ݐ�o�b�t�@�T�C�Y���w�肵�܂��B<br>
 * \attention
 * �߂�l�́A���<b>�Ǎ��v���T�C�Y�ȉ��ɂȂ�</b>���Ƃɒ��ӂ��Ă��������B<br>
 * �Ⴆ�΃t�@�C���I�[�ł́A�߂�l���Ǎ��v���T�C�Y��菬�����Ȃ邱�Ƃ�����܂����A
 * �Ǎ��Ɏ��s���Ă���킯�ł͂���܂���B�Ǎ��Ɏ��s�����ꍇ�A-1��Ԃ��܂��B
 */
CriSint64 CRIAPI criFsStdio_ReadFile(CriFsStdioHn stdhn, CriSint64 rsize, void *buf, CriSint64 bsize);

/*JP
 * \brief ANSI C �ɏ�����API�Ɋ�Â��f�[�^�̃t�@�C������
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn �������CriFsStdio�n���h��
 * \param[in] rsize �����v���T�C�Y�ibyte�j
 * \param[in] buf   �������o�b�t�@
 * \param[in] bsize �������o�b�t�@�̃T�C�Y�ibyte�j
 * \return CriSint64 �������� �������߂��T�C�Y�ibyte�j<br>
 *                   �������s -1
 * \par �����F
 * �t�@�C������f�[�^���w��T�C�Y�ibyte�j���ǂݍ��݂܂��B<br>
 * �������ɂ́A�f�[�^�̏�����ł���t�@�C����CriFsStdio�n���h�����w�肵�܂��B<br>
 * �������ɂ́A�������ރT�C�Y���w�肵�܂��B<br>
 * ��O�����ɂ́A�������ƂȂ�f�[�^�̃o�b�t�@���w�肵�܂��B<br>
 * ��l�����ɂ́A�������ƂȂ�f�[�^�̃o�b�t�@�T�C�Y���w�肵�܂��B<br>
 * \attention
 * �߂�l�́A�����ɐ��������T�C�Y�ibyte�j�ł��B<br>
 * �����Ɏ��s�����ꍇ�A-1��Ԃ��܂��B
 * �{�֐��́A�t�@�C���������݂��T�|�[�g���Ă���v���b�g�t�H�[���ɂ����Ă̂ݎg�p���邱�Ƃ��ł��܂��B<br>
 * �t�@�C���������݂��T�|�[�g���Ă��Ȃ��v���b�g�t�H�[���Ŗ{�֐����Ăяo���ƁA<br>
 * �����N���ɃV���{���������炸�A�r���h�G���[�ɂȂ�܂��B
 */
CriSint64 CRIAPI criFsStdio_WriteFile(CriFsStdioHn stdhn, CriSint64 rsize, void *buf, CriSint64 bsize);

/*JP
 * \brief CriFsStdio�n���h���̃t�@�C���ǂݍ��݃v���C�I���e�B��ύX
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn �v���C�I���e�B��ύX������CriFsStdio�n���h��
 * \param[in] prio  �ύX�������v���C�I���e�B�̒l
 * \return CriError CRIERR_OK ����<br>
 *                  ���̑�   ���s
 * \par �����F
 * criFsStdio_ReadFile()���g�����t�@�C���ǂݍ��ݗD��x���ACriFsStdio�n���h�����ɐݒ肵�܂��B<br>
 */
CriError CRIAPI criFsStdio_SetReadPriority(CriFsStdioHn stdhn, CriFsLoaderPriority prio);

/*JP
 * \brief �t�@�C���̍폜
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in]	path		�폜����t�@�C���̃p�X
 * \param[out]	result		�폜����
 * \return		CriError	�G���[�R�[�h
 * \par �����F
 * �w�肵���t�@�C�����폜���܂��B<br>
 * �t�@�C���̍폜�ɐ��������ꍇ�A�o�͒l�i result �j�� CRIFSSTDIO_FILE_REMOVED ���Z�b�g����܂��B<br>
 * �w�肵���t�@�C�������݂��Ȃ��ꍇ��A�ǂݍ��ݐ�p�t�@�C�����폜���悤�Ƃ����ꍇ�A
 * �t�@�C���̍폜�Ɏ��s���A�o�͒l�i result �j�� CRIFSSTDIO_IO_ERROR_OCCURRD ���Z�b�g����܂��B<br>
 * \par ���l�F
 * �w�肵���������s���ȏꍇ��A�t�@�C���폜�p�̃n���h�����m�ۂł��Ȃ��ꍇ�A
 * �o�͒l�i result �j�� CRIFSSTDIO_NOT_EXECUTED ���Z�b�g����A
 * �֐��̖߂�l���G���[�l�i CRIERR_OK �ȊO�̒l�j�ɂȂ�܂��B<br>
 */
CriError CRIAPI criFsStdio_RemoveFile(
	CriFsBinderHn binder, const CriChar8 *path, CriFsStdioRemoveResult *result);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define CriFsConfiguration				CriFsConfig
#define criFs_InitializeConfiguration(config)	criFs_SetDefaultConfig(&config)
#define criFs_CalculateWorkSize(config, nbyte)	criFs_CalculateWorkSizeForLibrary(&config, nbyte)
#define criFs_Initialize(config, buffer, size)	criFs_InitializeLibrary(&config, buffer, size)
#define criFs_Finalize()				criFs_FinalizeLibrary()
#define CriFsBinderUserHeapAllocateCbFunc CriFsMallocFunc
#define CriFsBinderUserHeapFreeCbFunc CriFsFreeFunc
#define CRIFS_PRIMARYCPK_ERROR_NONE	(CRIFS_BINDCPK_ERROR_NONE)
#define CRIFS_PRIMARYCPK_ERROR_CRC  (CRIFS_BINDCPK_ERROR_DATA)
#define CRIFS_PRIMARYCPK_ERROR_CANNOT_READ	(CRIFS_BINDCPK_ERROR_CANNOT_READ)
#define CRIFS_PRIMARYCPK_ERROR_NONEXISTENT	(CRIFS_BINDCPK_ERROR_NONEXISTENT)
typedef CriFsBindCpkError CriFsPrimaryCpkError;
typedef CriFsBindId CriFsBinderId;

#endif	/* CRI_FILE_SYSTEM_H_INCLUDED */

/* --- end of file --- */
