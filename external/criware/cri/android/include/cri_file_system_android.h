/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header for Android
 * File     : cri_file_system_android.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system_android.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_ANDROID_H_INCLUDED
#define	CRI_FILE_SYSTEM_ANDROID_H_INCLUDED

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"
#include <jni.h>

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
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * criFs_Initialize() �̌ďo����ɐݒ肵�Ă��������B<BR>
 * �v���C�I���e�B�̓i�C�X�l�Ŏw�肵�Ă��������B�͈͂�-20(�ō�)����19(�Œ�)�ł��B
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� -7 �ł��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 */
CriError CRIAPI criFs_SetFileAccessThreadPriority_ANDROID(int prio);

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetFileAccessThreadPriority_ANDROID(int *prio);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * �v���C�I���e�B�̓i�C�X�l�Ŏw�肵�Ă��������B�͈͂�-20(�ō�)����19(�Œ�)�ł��B
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� 7 �ł��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 */
CriError CRIAPI criFs_SetMemoryFileSystemThreadPriority_ANDROID(int prio);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetMemoryFileSystemThreadPriority_ANDROID(int *prio);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * �v���C�I���e�B�̓i�C�X�l�Ŏw�肵�Ă��������B�͈͂�-20(�ō�)����19(�Œ�)�ł��B
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� 9 �ł��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_ANDROID(int prio);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃v���C�I���e�B���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetDataDecompressionThreadPriority_ANDROID(int *prio);

/*JP
 * \brief JavaVM�I�u�W�F�N�g�̓o�^
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	vm	JavaVM�I�u�W�F�N�g�ւ̎Q��
 * \par ����:
 * JavaVM�I�u�W�F�N�g�ւ̎Q�Ƃ�CriFileSystem���C�u�����ɓo�^���܂��B<br>
 * \attention:
 * JavaVM�I�u�W�F�N�g�ւ̎Q�Ƃ�o�^�����ꍇ�A���C�u���������ō쐬���ꂽ�X���b�h��JavaVM�ɃA�^�b�`����܂��B<br>
 */
void CRIAPI criFs_SetJavaVM_ANDROID(JavaVM* vm);

/* 
 * �{�֐��͋��d�l�̊֐��ŁA�݊����̂��ߎc���Ă���܂��B
 * criFs_EnableAssetsAccess_ANDROID�̕������g���������B
 */
CriError CRIAPI criFs_SetContext_ANDROID(jobject jobj);

/*JP
 * \brief Android�v���W�F�N�g����assets�t�H���_�ɑ΂���A�N�Z�X�̗L����
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	vm		JavaVM�I�u�W�F�N�g�ւ̎Q��
 * \param[in]	jobj	android.content.Context�I�u�W�F�N�g
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * asset�t�H���_�ւ̃A�N�Z�X��L�������܂��B<br>
 * <br>
 * �{�֐��́Aassets�t�H���_�ւ̃A�N�Z�X��L�������܂��B<br>
 * �{�֐��̈����Ƃ��ēn���ꂽJavaVM�I�u�W�F�N�g�ւ̎Q��(vm)�ƁAandroid.content.Context�I�u�W�F�N�g(jobj)��<br>
 * CriFileSystem���C�u�����ɓo�^����܂��B<br>
 * \attention:
 * �{�֐��̌�g�p�́A���҂��Ȃ�����ɂȂ���܂��B�ȉ��̓_�ɒ��ӂ��ĉ������B<br>
 * (1) �{�֐����Ăяo���O�ɁACRI File System���C�u�����̏������������ς݂ł��鎖���m�F���ĉ������B<br>
 * (2) assets�t�H���_�ւ̃A�N�Z�X�O�ɁA�{�֐����Ăяo���ĉ������B<br>
 * (3) �o�^����Context�I�u�W�F�N�g�́AJava VM�̃K�x�[�W�R���N�V�����Ώۂ���O��܂��B<br>
 *     �o�^����������ɂ́A::criFs_DisableAssetsAccess_ANDROID�֐����Ăяo���Ă��������B<br>
 *     �܂��́A�V����Context�I�u�W�F�N�g��o�^���������Ƃł��A�Â�Context�̓o�^�������\�ł��B<br>
 * (4) �{�֐����Ăяo�����X���b�h�́A�\��JavaVM�ɃA�^�b�`����Ă��Ȃ������ꍇ�Ɍ���AJavaVM�ɃA�^�b�`����܂��B<br>
 * (5) �{�֐����Ăяo�����X���b�h�́A�I���O�ɕK��::criFs_DisableAssetsAccess_ANDROID�֐����ĂԕK�v������܂��B<br>
 */
CriError CRIAPI criFs_EnableAssetsAccess_ANDROID(JavaVM* vm, jobject jobj);

/*JP
 * \brief Android�v���W�F�N�g����assets�t�H���_�ɑ΂���A�N�Z�X�̖�����
 * \ingroup FSLIB_CRIFS_ANDROID
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * asset�t�H���_�ւ̃A�N�Z�X�𖳌������܂��B<br>
 * ::criFs_EnableAssetsAccess_ANDROID�֐��ɂ����CriFileSystem���C�u�����ɓo�^���ꂽandroid.content.Context�I�u�W�F�N�g��<br>
 * �{�֐��Ăяo���ɂ��o�^��������܂��B
 * \attention:
 * �{�֐��̌�g�p�́A���҂��Ȃ�����ɂȂ���܂��B�ȉ��̓_�ɒ��ӂ��ĉ������B<br>
 * (1) �{�֐����Ăяo�����X���b�h�́A�\��JavaVM�ɃA�^�b�`����Ă��Ȃ������ꍇ�Ɍ���AJavaVM����f�^�b�`����܂��B<br>
 * (2) ::criFs_EnableAssetsAccess_ANDROID�֐����Ăяo�����X���b�h�́A�I���O�ɕK���{�֐����ĂԕK�v������܂��B<br>
 */
CriError CRIAPI criFs_DisableAssetsAccess_ANDROID();


#ifdef __cplusplus
}
#endif

#endif	/* CRI_FILE_SYSTEM_ANDROID_H_INCLUDED */

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define criFs_SetFileAccessThreadPriority_Android(prio) \
		criFs_SetFileAccessThreadPriority_ANDROID(prio)

#define criFs_GetFileAccessThreadPriority_Android(prio) \
		criFs_GetFileAccessThreadPriority_ANDROID(prio)

#define criFs_SetMemoryFileSystemThreadPriority_Android(prio) \
		criFs_SetMemoryFileSystemThreadPriority_ANDROID(prio)

#define criFs_GetMemoryFileSystemThreadPriority_Android(prio) \
		criFs_GetMemoryFileSystemThreadPriority_ANDROID(prio)

#define criFs_SetDataDecompressionThreadPriority_Android(prio) \
		criFs_SetDataDecompressionThreadPriority_ANDROID(prio)

#define criFs_GetDataDecompressionThreadPriority_Android(prio) \
		criFs_GetDataDecompressionThreadPriority_ANDROID(prio)

#define criFs_SetActivity_ANDROID(jobj)	\
		criFs_SetContext_ANDROID(jobj)


/* --- end of file --- */
