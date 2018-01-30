/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2011 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header for PC
 * File     : cri_file_system_pc.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system_pc.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_PC_H_INCLUDED
#define	CRI_FILE_SYSTEM_PC_H_INCLUDED

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <windows.h>
#include "cri_xpt.h"
#include "cri_error.h"

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
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * ���� prio �ɂ� Win32 API �̃X���b�h�D�惌�x���i SetThreadPriority �֐��̈����j���w�肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� THREAD_PRIORITY_HIGHEST �ł��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI Atom���C�u�����Ŏg�p���Ă�����̂Ɠ����ł��i���p���Ă��܂��j�B<br>
 * ���ł�CRI Atom���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ�A<br>
 * �{�֐����Ăяo���Ɛݒ���㏑�����Ă��܂��̂ł����ӂ��������B
 */
CriError CRIAPI criFs_SetServerThreadPriority_PC(int prio);

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetServerThreadPriority_PC(int *prio);

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * ���� prio �ɂ� Win32 API �̃X���b�h�D�惌�x���i SetThreadPriority �֐��̈����j���w�肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� THREAD_PRIORITY_HIGHEST �ł��B<BR>
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
CriError CRIAPI criFs_SetFileAccessThreadPriority_PC(int prio);

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_PC
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
CriError CRIAPI criFs_GetFileAccessThreadPriority_PC(int *prio);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * ���� prio �ɂ� Win32 API �̃X���b�h�D�惌�x���i SetThreadPriority �֐��̈����j���w�肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h�����Ⴂ�v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� THREAD_PRIORITY_LOWEST �ł��B<BR>
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
CriError CRIAPI criFs_SetMemoryFileSystemThreadPriority_PC(int prio);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_PC
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
CriError CRIAPI criFs_GetMemoryFileSystemThreadPriority_PC(int *prio);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * ���� prio �ɂ� Win32 API �̃X���b�h�D�惌�x���i SetThreadPriority �֐��̈����j���w�肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h�����Ⴂ�v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� THREAD_PRIORITY_LOWEST �ł��B<BR>
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
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_PC(int prio);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_PC
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
CriError CRIAPI criFs_GetDataDecompressionThreadPriority_PC(int *prio);

/*JP
 * \brief �C���X�g�[���X���b�h�̃v���C�I���e�B�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[���X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<BR>
 * ���� prio �ɂ� Win32 API �̃X���b�h�D�惌�x���i SetThreadPriority �֐��̈����j���w�肵�܂��B<BR>
 * �A�v���P�[�V�����̃��C���X���b�h���������v���C�I���e�B���w�肵�Ă��������B<BR>
 * �v���C�I���e�B�̃f�t�H���g�l�� THREAD_PRIORITY_ABOVE_NORMAL �ł��B<BR>
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
CriError CRIAPI criFs_SetInstallerThreadPriority_PC(int prio);

/*JP
 * \brief �C���X�g�[���X���b�h�̃v���C�I���e�B�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	�X���b�h�̃v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[���X���b�h�̃v���C�I���e�B���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetInstallerThreadPriority_PC(int *prio);

/*JP
 * \brief �T�[�o�����X���b�h�̃A�t�B�j�e�B�}�X�N�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃A�t�B�j�e�B�}�X�N��ݒ肵�܂��B<BR>
 * ���� mask �ɂ� Win32 API �̃X���b�h�A�t�B�j�e�B�}�X�N�i SetThreadAffinityMask �֐��̈����j���w�肵�܂��B<BR>
 * �f�t�H���g��Ԃł̓A�t�B�j�e�B�}�X�N�͐ݒ肳��Ă��܂���B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI Atom���C�u�����Ŏg�p���Ă�����̂Ɠ����ł��i���p���Ă��܂��j�B<br>
 * ���ł�CRI Atom���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ�A<br>
 * �{�֐����Ăяo���Ɛݒ���㏑�����Ă��܂��̂ł����ӂ��������B
 */
CriError CRIAPI criFs_SetServerThreadAffinityMask_PC(DWORD_PTR mask);

/*JP
 * \brief �T�[�o�����X���b�h�̃A�t�B�j�e�B�}�X�N�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetServerThreadAffinityMask_PC(DWORD_PTR *mask);

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃A�t�B�j�e�B�}�X�N�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃A�t�B�j�e�B�}�X�N��ݒ肵�܂��B<BR>
 * ���� mask �ɂ� Win32 API �̃X���b�h�A�t�B�j�e�B�}�X�N�i SetThreadAffinityMask �֐��̈����j���w�肵�܂��B<BR>
 * �f�t�H���g��Ԃł̓A�t�B�j�e�B�}�X�N�͐ݒ肳��Ă��܂���B<BR>
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
CriError CRIAPI criFs_SetFileAccessThreadAffinityMask_PC(DWORD_PTR mask);

/*JP
 * \brief �t�@�C���A�N�Z�X�X���b�h�̃A�t�B�j�e�B�}�X�N�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���A�N�Z�X�X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetFileAccessThreadAffinityMask_PC(DWORD_PTR *mask);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃A�t�B�j�e�B�}�X�N�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������t�@�C���V�X�e���X���b�h�̃A�t�B�j�e�B�}�X�N��ݒ肵�܂��B<BR>
 * ���� mask �ɂ� Win32 API �̃X���b�h�A�t�B�j�e�B�}�X�N�i SetThreadAffinityMask �֐��̈����j���w�肵�܂��B<BR>
 * �f�t�H���g��Ԃł̓A�t�B�j�e�B�}�X�N�͐ݒ肳��Ă��܂���B<BR>
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
CriError CRIAPI criFs_SetMemoryFileSystemThreadAffinityMask_PC(DWORD_PTR mask);

/*JP
 * \brief �������t�@�C���V�X�e���X���b�h�̃A�t�B�j�e�B�}�X�N�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������t�@�C���V�X�e���X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetMemoryFileSystemThreadAffinityMask_PC(DWORD_PTR *mask);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃A�t�B�j�e�B�}�X�N�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃A�t�B�j�e�B�}�X�N��ݒ肵�܂��B<BR>
 * ���� mask �ɂ� Win32 API �̃X���b�h�A�t�B�j�e�B�}�X�N�i SetThreadAffinityMask �֐��̈����j���w�肵�܂��B<BR>
 * �f�t�H���g��Ԃł̓A�t�B�j�e�B�}�X�N�͐ݒ肳��Ă��܂���B<BR>
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
CriError CRIAPI criFs_SetDataDecompressionThreadAffinityMask_PC(DWORD_PTR mask);

/*JP
 * \brief �f�[�^�W�J�X���b�h�̃A�t�B�j�e�B�}�X�N�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �f�[�^�W�J�X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetDataDecompressionThreadAffinityMask_PC(DWORD_PTR *mask);

/*JP
 * \brief �C���X�g�[���X���b�h�̃A�t�B�j�e�B�}�X�N�ݒ�
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[���X���b�h�̃A�t�B�j�e�B�}�X�N��ݒ肵�܂��B<BR>
 * ���� mask �ɂ� Win32 API �̃X���b�h�A�t�B�j�e�B�}�X�N�i SetThreadAffinityMask �֐��̈����j���w�肵�܂��B<BR>
 * �f�t�H���g��Ԃł̓A�t�B�j�e�B�}�X�N�͐ݒ肳��Ă��܂���B<BR>
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
CriError CRIAPI criFs_SetInstallerThreadAffinityMask_PC(DWORD_PTR mask);

/*JP
 * \brief �C���X�g�[���X���b�h�̃A�t�B�j�e�B�}�X�N�擾
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	�A�t�B�j�e�B�}�X�N
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[���X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<BR>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIFS_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[��Ԃ��܂��B<br>
 */
CriError CRIAPI criFs_GetInstallerThreadAffinityMask_PC(DWORD_PTR *mask);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_FILE_SYSTEM_PC_H_INCLUDED */

/* --- end of file --- */
