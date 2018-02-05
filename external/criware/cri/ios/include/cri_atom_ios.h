/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2015 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for iOS
 * File     : cri_atom_ios.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_ios.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_CRI_ATOM_IOS_H
#define	CRI_INCL_CRI_ATOM_IOS_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>
#include <cri_error.h>
#include "cri_atom.h"
#include "cri_atom_ex.h"
#include "cri_atom_asr.h"

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_IOS
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtom_Initialize_IOS �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomConfig_IOS �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \attention
 * �{�}�N���͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�}�N���̑���� 
 * ::criAtomEx_SetDefaultConfig_IOS �}�N���������p���������B
 * \sa CriAtomConfig_IOS
 */
#define criAtom_SetDefaultConfig_IOS(p_config)				\
{															\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
    criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
    (p_config)->buffering_time = 50;						\
    (p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE; \
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_IOS
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomEx_Initialize_IOS �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExConfig_IOS �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomExConfig_IOS
 */
#define criAtomEx_SetDefaultConfig_IOS(p_config)			\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
    criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
    (p_config)->buffering_time = 50;						\
    (p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE; \
}

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_IOS
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtom_Initialize_IOS �֐��̈����Ɏw�肵�܂��B<br>
 * \attention
 * �{�\���͉̂��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�\���̂̑���� 
 * ::CriAtomExConfig_IOS �\���̂������p���������B
 * \sa criAtom_Initialize_IOS, criAtom_SetDefaultConfig_IOS
 */
typedef struct {
	CriAtomConfig			atom;		/* Atom�������p�R���t�B�O�\����		*/
	CriAtomAsrConfig		asr;		/* ASR�������p�R���t�B�O			*/
	CriAtomHcaMxConfig		hca_mx;		/* HCA-MX�������p�R���t�B�O�\����		*/
	CriUint32				buffering_time;	/* �o�̓o�b�t�@�����O����(�P��:msec)	*/
	CriSint32				output_sampling_rate;	/* �o�̓T���v�����O���g��	*/
} CriAtomConfig_IOS;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_IOS
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtomEx_Initialize_IOS �֐��̈����Ɏw�肵�܂��B<br>
 * \sa criAtomEx_Initialize_IOS, criAtomEx_SetDefaultConfig_IOS
 */
typedef struct {
	CriAtomExConfig			atom_ex;	/* AtomEx�������p�R���t�B�O�\����	*/
	CriAtomExAsrConfig		asr;		/* ASR�������p�R���t�B�O		*/
	CriAtomExHcaMxConfig	hca_mx;		/* HCA-MX�������p�R���t�B�O�\����	*/
	CriUint32				buffering_time;	/* �o�̓o�b�t�@�����O����(�P��:msec)	*/
	CriSint32				output_sampling_rate;	/* �o�̓T���v�����O���g��	*/
} CriAtomExConfig_IOS;

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
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_IOS
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomConfig_IOS �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_CalculateWorkSize_IOS �֐��������p���������B
 * \sa CriAtomConfig_IOS, criAtom_Initialize_IOS
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_IOS(const CriAtomConfig_IOS *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_IOS
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtom_Finalize_IOS �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtom_CalculateWorkSize_IOS 
 * �֐����g�p���Ă��������B<br>
 * \par ���l:
 * ::criAtom_SetUserAllocator �}�N�����g�p���ăA���P�[�^��o�^�ς݂̏ꍇ�A
 * �{�֐��Ƀ��[�N�̈���w�肷��K�v�͂���܂���B<br>
 * �i work �� NULL �A work_size �� 0 ���w�肷�邱�ƂŁA�o�^�ς݂̃A���P�[�^
 * ����K�v�ȃ��[�N�̈�T�C�Y���̃����������I�Ɋm�ۂ���܂��B�j
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͓����I�Ɉȉ��̊֐������s���܂��B<br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	.
 * �{�֐������s����ꍇ�A��L�֐������s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐������s��A�K���΂ɂȂ� ::criAtom_Finalize_IOS �֐������s���Ă��������B<br>
 * �܂��A ::criAtom_Finalize_IOS �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Initialize_IOS �֐��������p���������B
 * \sa CriAtomConfig_IOS, criAtom_Finalize_IOS,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_IOS
 */
void CRIAPI criAtom_Initialize_IOS(
	const CriAtomConfig_IOS *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * ���C�u�������I�����܂��B<br>
 * \attention
 * �{�֐��͓����I�Ɉȉ��̊֐������s���܂��B<br>
 * 	- ::criAtom_Finalize
 * 	- ::criAtomAsr_Finalize
 * 	- ::criAtomHcaMx_Finalize
 * 	.
 * �{�֐������s����ꍇ�A��L�֐������s���Ȃ��ł��������B<br>
 * <br>
 * ::criAtom_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Finalize_IOS �֐��������p���������B
 * \sa criAtom_Initialize_IOS
 */
void CRIAPI criAtom_Finalize_IOS(void);

/*JP
 * \brief �T�[�o�X���b�h�v���C�I���e�B�̐ݒ�
 * \ingroup ATOMLIB_IOS
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \par ����:
 * CRI�T�[�o�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<br>
 * ���� prio �� pthread �̃v���C�I���e�B�ݒ�l�Ƃ��Ďg�p���܂��B<br>
 * �v���C�I���e�B�ݒ�l�̓��C���X���b�h����̑��Βl�ɂȂ�܂��B<br>
 * �A�v���P�[�V�����̃��C���X���b�h(0)���������v���C�I���e�B���w�肵�Ă��������B<br>
 * �v���C�I���e�B�̃f�t�H���g�l��16�ł��B<br>
 * \attention
 * ::criAtom_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 */
void CRIAPI criAtom_SetServerThreadPriority_IOS(int prio);

/*JP
 * \brief �T�E���h�����̍ĊJ
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSession��Interruption Callbak�֐�����Ăяo�����߂̊֐��ł��B<br>
 * �T�E���h�������ĊJ���܂��B<br>
 * �{�֐����Ăяo���O�ɁAAudioSession�̃p�����[�^�ݒ�ƃA�N�e�B�x�C�g���s���Ă��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_StartSound_IOS �֐��������p���������B
 * \attention
 * ::criAtom_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtom_StopSound_IOS
 */
void CRIAPI criAtom_StartSound_IOS(void);

/*JP
 * \brief �T�E���h�����̒�~
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSession��Interruption Callbak�֐�����Ăяo�����߂̊֐��ł��B<br>
 * �T�E���h�������~���܂��B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_StopSound_IOS �֐��������p���������B
 * \attention
 * ::criAtom_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtom_StartSound_IOS
 */
void CRIAPI criAtom_StopSound_IOS(void);

/*JP
 * \brief �T�E���h�̕���
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSessionAddPropertyListener Callback�֐�����Ăяo�����߂̊֐��ł��B<br>
 * ���C�u���������̃{�C�X�𕜋����܂��B<br>
 * iOS�̃f�[�����ł���mediaserverd�����S�����ۂɂ́A���C�u�������̃{�C�X�������ȃ{�C�X�ɂȂ�A
 * �Đ������K�v�ɂȂ�܂��B<br>
 * ���̂悤�ɁA�{�C�X�̕������K�v�ȍۂɌĂяo���Ă��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_RecoverSound_IOS �֐��������p���������B
 */
void CRIAPI criAtom_RecoverSound_IOS(void);

 /*JP
  * \brief �T�E���h�̏������ɐ����������ۂ�
  * \ingroup ATOMLIB_IOS
  * \par ����:
  * �T�E���h���C�u�����̏������ɐ����������ۂ���Ԃ��֐��ł��B<br>
  * iOS�ł́A�A�v�����o�b�N�O���E���h�ɂ����ԂŃT�E���h���C�u�����̏��������s�����ꍇ��
  * �����I��AudioSession�̏��������Ɏ��s���Ă���ꍇ������܂��B<br>
  * �{�֐��ŏ����������s���Ă��邱�Ƃ��m�F�����ꍇ�́A�A�v�����t�H�A�O���E���h�ɂ����Ԃ�
  * �ēx���C�u�����̏��������s�����A ::criAtom_RecoverSound_IOS ��p����
  * �T�E���h�̕������s���K�v������܂��B<br>
  * <br>
  * �{�֐��͉��ʃ��C��������API�ł��B<br>
  * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑����
  * ::criAtomEx_IsInitializationSucceeded_IOS �֐��������p���������B
  */
CriBool CRIAPI criAtom_IsInitializationSucceeded_IOS(void);


/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_IOS
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomExConfig_IOS �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa CriAtomExConfig_IOS, criAtomEx_Initialize_IOS
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_IOS(const CriAtomExConfig_IOS *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_IOS
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtomEx_Finalize_IOS �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtomEx_CalculateWorkSize_IOS 
 * �֐����g�p���Ă��������B<br>
 * \par ���l:
 * ::criAtomEx_SetUserAllocator �}�N�����g�p���ăA���P�[�^��o�^�ς݂̏ꍇ�A
 * �{�֐��Ƀ��[�N�̈���w�肷��K�v�͂���܂���B<br>
 * �i work �� NULL �A work_size �� 0 ���w�肷�邱�ƂŁA�o�^�ς݂̃A���P�[�^
 * ����K�v�ȃ��[�N�̈�T�C�Y���̃����������I�Ɋm�ۂ���܂��B�j
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͓����I�Ɉȉ��̊֐������s���܂��B<br>
 * 	- ::criAtomEx_Initialize
 * 	- ::criAtomExAsr_Initialize
 * 	- ::criAtomExHcaMx_Initialize
 * 	.
 * �{�֐������s����ꍇ�A��L�֐������s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐������s��A�K���΂ɂȂ� ::criAtomEx_Finalize_IOS �֐������s���Ă��������B<br>
 * �܂��A ::criAtomEx_Finalize_IOS �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * \sa CriAtomExConfig_IOS, criAtomEx_Finalize_IOS,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_IOS
 */
void CRIAPI criAtomEx_Initialize_IOS(
	const CriAtomExConfig_IOS *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * ���C�u�������I�����܂��B<br>
 * \attention
 * �{�֐��͓����I�Ɉȉ��̊֐������s���܂��B<br>
 * 	- ::criAtomEx_Finalize
 * 	- ::criAtomExAsr_Finalize
 * 	- ::criAtomExHcaMx_Finalize
 * 	.
 * �{�֐������s����ꍇ�A��L�֐������s���Ȃ��ł��������B<br>
 * <br>
 * ::criAtomEx_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_Initialize_IOS
 */
void CRIAPI criAtomEx_Finalize_IOS(void);

/*JP
 * \brief �T�[�o�X���b�h�v���C�I���e�B�̐ݒ�
 * \ingroup ATOMLIB_IOS
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \par ����:
 * CRI�T�[�o�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<br>
 * ���� prio �� pthread �̃v���C�I���e�B�ݒ�l�Ƃ��Ďg�p���܂��B<br>
 * �v���C�I���e�B�ݒ�l�̓��C���X���b�h����̑��Βl�ɂȂ�܂��B<br>
 * �A�v���P�[�V�����̃��C���X���b�h(0)���������v���C�I���e�B���w�肵�Ă��������B<br>
 * �v���C�I���e�B�̃f�t�H���g�l��16�ł��B<br>
 * \attention
 * ::criAtomEx_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 */
void CRIAPI criAtomEx_SetServerThreadPriority_IOS(int prio);

/*JP
 * \brief �T�E���h�����̍ĊJ
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSession��Interruption Callbak�֐�����Ăяo�����߂̊֐��ł��B<br>
 * �T�E���h�������ĊJ���܂��B<br>
 * �{�֐����Ăяo���O�ɁAAudioSession�̃p�����[�^�ݒ�ƃA�N�e�B�x�C�g���s���Ă��������B<br>
 * \par ��:
 * \code
 * // AudioSession Interruption Callbak
 * static void interruptionListenerCallback(void *inUserData, UInt32 interruptionState)
 * {
 * 	if (interruptionState == kAudioSessionBeginInterruption) {
 * 		// �I�[�f�B�I�����̒�~
 * 		criAtomEx_StopSound_IOS();
 * 	}
 * 	if (interruptionState == kAudioSessionEndInterruption) {
 * 		// AudioSession�̃v���p�e�B�ݒ�ƃA�N�e�B�x�C�g
 * 		setupAudioSession();
 * 		// �I�[�f�B�I�����̊J�n
 * 		criAtomEx_StartSound_IOS();
 * 	}
 * }
 * // AudioSession�̃v���p�e�B�ݒ�ƃA�N�e�B�x�C�g
 * static void setupAudioSession(void)
 * {
 * 		:
 * }
 * \endcode
 * \attention
 * ::criAtomEx_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_StopSound_IOS
 */
void CRIAPI criAtomEx_StartSound_IOS(void);

/*JP
 * \brief �T�E���h�����̒�~
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSession��Interruption Callbak�֐�����Ăяo�����߂̊֐��ł��B<br>
 * �T�E���h�������~���܂��B<br>
 * \attention
 * ::criAtomEx_Initialize_IOS �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_StartSound_IOS
 */
void CRIAPI criAtomEx_StopSound_IOS(void);

/*JP
 * \brief �T�E���h�̕���
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * AudioSessionAddPropertyListener Callback�֐�����Ăяo�����߂̊֐��ł��B<br>
 * ���C�u���������̃{�C�X�𕜋����܂��B<br>
 * iOS�̃f�[�����ł���mediaserverd�����S�����ۂɂ́A���C�u�������̃{�C�X�������ȃ{�C�X�ɂȂ�A
 * �Đ������K�v�ɂȂ�܂��B<br>
 * ���̂悤�ɁA�{�C�X�̕������K�v�ȍۂɌĂяo���Ă��������B<br>
 */
void CRIAPI criAtomEx_RecoverSound_IOS(void);

/*JP
 * \brief �T�E���h�̏������ɐ����������ۂ�
 * \ingroup ATOMLIB_IOS
 * \par ����:
 * �T�E���h���C�u�����̏������ɐ����������ۂ���Ԃ��֐��ł��B<br>
 * iOS�ł́A�A�v�����o�b�N�O���E���h�ɂ����ԂŃT�E���h���C�u�����̏��������s�����ꍇ��
 * �����I��AudioSession�̏��������Ɏ��s���Ă���ꍇ������܂��B<br>
 * �{�֐��ŏ����������s���Ă��邱�Ƃ��m�F�����ꍇ�́A�A�v�����t�H�A�O���E���h�ɂ����Ԃ�
 * �ēx���C�u�����̏��������s�����A ::criAtomEx_RecoverSound_IOS ��p����
 * �T�E���h�̕������s���K�v������܂��B<br>
 */
CriBool CRIAPI criAtomEx_IsInitializationSucceeded_IOS(void);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define criAtom_SetDefaultConfig_iOS(p_config)		criAtom_SetDefaultConfig_IOS(p_config)
#define criAtomEx_SetDefaultConfig_iOS(p_config)	criAtomEx_SetDefaultConfig_IOS(p_config)
#define CriAtomConfig_iOS							CriAtomConfig_IOS
#define CriAtomExConfig_iOS							CriAtomExConfig_IOS
#define criAtom_CalculateWorkSize_iOS				criAtom_CalculateWorkSize_IOS
#define criAtom_Initialize_iOS						criAtom_Initialize_IOS
#define criAtom_Finalize_iOS						criAtom_Finalize_IOS
#define criAtom_SetServerThreadPriority_iOS			criAtom_SetServerThreadPriority_IOS
#define criAtom_StartSound_iOS						criAtom_StartSound_IOS
#define criAtom_StopSound_iOS						criAtom_StopSound_IOS
#define criAtomEx_CalculateWorkSize_iOS				criAtomEx_CalculateWorkSize_IOS
#define criAtomEx_Initialize_iOS					criAtomEx_Initialize_IOS
#define criAtomEx_Finalize_iOS						criAtomEx_Finalize_IOS
#define criAtomEx_SetServerThreadPriority_iOS		criAtomEx_SetServerThreadPriority_IOS
#define criAtomEx_StartSound_iOS					criAtomEx_StartSound_IOS
#define criAtomEx_StopSound_iOS						criAtomEx_StopSound_IOS


#endif	/* CRI_INCL_CRI_ATOM_IOS_H */

/* --- end of file --- */
