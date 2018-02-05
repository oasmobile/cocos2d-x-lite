/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2009-2010 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for XAudio2
 * File     : cri_atom_xaudio2.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_xaudio2.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_XAUDIO2_H
#define CRI_INCL_CRI_ATOM_XAUDIO2_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#if !defined(CRI_ATOM_WITOUT_XAUDIO2_H)
#include <xaudio2.h>
#endif

#include <cri_xpt.h>
#include <cri_atom.h>
#include <cri_atom_ex.h>
#include <cri_atom_asr.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_XAUDIO2
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtom_Initialize_XAUDIO2 �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomConfig_XAUDIO2 �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \attention
 * �{�}�N���͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�}�N���̑���� 
 * ::criAtomEx_SetDefaultConfig_XAUDIO2 �}�N���������p���������B
 * \sa CriAtomConfig_XAUDIO2
 */
#define criAtom_SetDefaultConfig_XAUDIO2(p_config)			\
{															\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomAsr_SetDefaultConfig(&(p_config)->asr);			\
	criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_XAUDIO2
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomEx_Initialize_XAUDIO2 �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExConfig_XAUDIO2 �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomExConfig_XAUDIO2
 */
#define criAtomEx_SetDefaultConfig_XAUDIO2(p_config)		\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_XAUDIO2
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtom_Initialize_XAUDIO2 �֐��̈����Ɏw�肵�܂��B<br>
 * \attention
 * �{�\���͉̂��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�\���̂̑���� 
 * ::CriAtomExConfig_XAUDIO2 �\���̂������p���������B
 * \sa criAtom_Initialize_XAUDIO2, criAtom_SetDefaultConfig_XAUDIO2
 */
typedef struct CriAtomConfigTag_XAUDIO2 {
	CriAtomConfig			atom;		/*JP< Atom�������p�R���t�B�O�\����		*/
	CriAtomAsrConfig		asr;		/*JP< ASR�������p�R���t�B�O			*/
	CriAtomHcaMxConfig		hca_mx;		/*JP< HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomConfig_XAUDIO2;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_XAUDIO2
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtomEx_Initialize_XAUDIO2 �֐��̈����Ɏw�肵�܂��B<br>
 * \sa criAtomEx_Initialize_XAUDIO2, criAtomEx_SetDefaultConfig_XAUDIO2
 */
typedef struct CriAtomExConfigTag_XAUDIO2 {
	CriAtomExConfig			atom_ex;	/*JP< AtomEx�������p�R���t�B�O�\����	*/
	CriAtomExAsrConfig		asr;		/*JP< ASR�������p�R���t�B�O			*/
	CriAtomExHcaMxConfig	hca_mx;		/*JP< HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomExConfig_XAUDIO2;

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
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomConfig_XAUDIO2 �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_CalculateWorkSize_XAUDIO2 �֐��������p���������B
 * \sa CriAtomConfig_XAUDIO2, criAtom_Initialize_XAUDIO2
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_XAUDIO2(const CriAtomConfig_XAUDIO2 *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtom_Finalize_XAUDIO2 �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtom_CalculateWorkSize_XAUDIO2 
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtom_Finalize_XAUDIO2 �֐������s���Ă��������B<br>
 * �܂��A ::criAtom_Finalize_XAUDIO2 �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Initialize_XAUDIO2 �֐��������p���������B
 * \sa CriAtomConfig_XAUDIO2, criAtom_Finalize_XAUDIO2,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_XAUDIO2
 */
void CRIAPI criAtom_Initialize_XAUDIO2(
	const CriAtomConfig_XAUDIO2 *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_XAUDIO2
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
 * ::criAtom_Initialize_XAUDIO2 �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Finalize_XAUDIO2 �֐��������p���������B
 * \sa criAtom_Initialize_XAUDIO2
 */
void CRIAPI criAtom_Finalize_XAUDIO2(void);

/* �ȍ~��XAudio2.h�Ɉˑ�����API */
#if !defined(CRI_ATOM_WITOUT_XAUDIO2_H)

/*JP
 * \brief XAudio2�I�u�W�F�N�g�̃Z�b�g
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	xa2		XAudio2�I�u�W�F�N�g
 * \par ����:
 * Atom���C�u������XAudio2�I�u�W�F�N�g���Z�b�g���܂��B<br>
 * <br>
 * Atom���C�u�����́A�������������Ƀ��C�u��������XAudio2�̏��������s���܂��B<br>
 * ���̂��߁AXAudio2�I�u�W�F�N�g�̓��C�u�������ɉB������A�A�v���P�[�V����
 * ����Q�Ƃ��邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �A�v���P�[�V��������XAudio2�I�u�W�F�N�g���g�p�������ꍇ�ɂ́A
 * Atom���C�u�����������O��XAudio2�̏������������s���A�쐬���ꂽXAudio2
 * �I�u�W�F�N�g��{�֐����g�p����Atom���C�u�����ɃZ�b�g���Ă��������B<br>
 * �{�֐���XAudio2�I�u�W�F�N�g���Z�b�g���Ă���Atom���C�u�����̏��������s���ƁA
 * Atom���C�u�����͏���������XAudio2�������������A�{�֐��ŃZ�b�g���ꂽ
 * XAudio2�I�u�W�F�N�g���g�p���܂��B<br>
 */
void CRIAPI criAtom_SetXAudio2Object_XAUDIO2(IXAudio2 *xa2);

/*JP
 * \brief �o�̓{�C�X�̃Z�b�g
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	ov		XAudio2�{�C�X
 * \par ����:
 * Atom���C�u�����ɏo�̓{�C�X���Z�b�g���܂��B<br>
 * <br>
 * Atom���C�u�����́A�������������Ƀ��C�u�������Ń}�X�^�����O�{�C�X���쐬���A
 * �S�Ẳ������}�X�^�����O�{�C�X�ɏo�͂��܂��B<br>
 * <br>
 * Atom���C�u�����̏o�͉����𑼂̃{�C�X�i�T�u�~�b�N�X�{�C�X���j��
 * �o�͂������ꍇ�ɂ́AAtom���C�u�����������O�ɏo�̓{�C�X�̍쐬���A
 * �{�֐����g�p����Atom���C�u�����ɃZ�b�g���Ă��������B<br>
 * �{�֐��ŏo�̓{�C�X���Z�b�g���Ă���Atom���C�u�����̏��������s���ƁA
 * Atom���C�u�����͏��������Ƀ}�X�^�����O�{�C�X���쐬�����A
 * �{�֐��ŃZ�b�g���ꂽ�o�̓{�C�X�ɉ������o�͂��܂��B<br>
 */
void CRIAPI criAtom_SetOutputVoice_XAUDIO2(IXAudio2Voice *ov);

/*JP
 * \brief �o�̓{�C�X�̎擾
 * \ingroup ATOMLIB_XAUDIO2
 * \return	IXAudio2Voice*	XAudio2�{�C�X
 * \par ����:
 * Atom���C�u�������g�p����o�̓{�C�X��Ԃ��܂��B<br>
 * <br>
 * ::criAtom_SetXAudio2Object_XAUDIO2 �֐����g�p���Ă���ꍇ�A
 * �{�֐��� ::criAtom_SetXAudio2Object_XAUDIO2 �֐��ŃZ�b�g���ꂽ�{�C�X��Ԃ��܂��B<br>
 * ::criAtom_SetXAudio2Object_XAUDIO2 �֐����g�p���Ă��Ȃ��ꍇ�A
 * �{�֐��͏������������Ƀ��C�u�������ō쐬�����}�X�^�����O�{�C�X��Ԃ��܂��B<br>
 * \par
 * XAudio2�̏������Ɏ��s�����ꍇ�i�T�E���h�f�o�C�X���g�p�ł��Ȃ��ꍇ���j�ɂ́A
 * �{�֐���NULL��Ԃ��܂��B<br>
 * \sa criAtom_SetOutputVoice_XAUDIO2
 */
IXAudio2Voice *criAtom_GetOutputVoice_XAUDIO2(void);

/*JP
 * \brief �o�̓f�o�C�X�C���f�b�N�X�̃Z�b�g
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	index	�f�o�C�X�C���f�b�N�X
 * \par ����:
 * Atom���C�u�����ɏo�̓f�o�C�X�̃C���f�b�N�X���Z�b�g���܂��B<br>
 * <br>
 * Atom���C�u�����́A�������������Ƀ��C�u��������XAudio2�̏��������s���A
 * 0�Ԃ̃f�o�C�X���g�p���ĉ������o�͂��܂��B<br>
 * <br>
 * �����o�͐�̃f�o�C�X��ύX�������ꍇ�ɂ́A
 * Atom���C�u�����������O�ɖ{�֐����g�p���ďo�̓f�o�C�X�̃C���f�b�N�X��
 * �w�肵�Ă��������B
 * �{�֐��ŏo�̓f�o�C�X�̃C���f�b�N�X���w�肵�Ă���Atom���C�u������
 * ���������s���ƁAAtom���C�u�����͎w�肳�ꂽ�f�o�C�X�ɉ������o�͂��܂��B<br>
 * \par ���l:
 * index �� 0xFFFFFFFF ���w�肵���ꍇ�AAtom���C�u�����̓��C�u�������� XAudio2 
 * �̏��������s��Ȃ��悤�A�����ύX���܂��B<br>
 * <br>
 * �{�֐��ւ̐ݒ�l�́AAtom���C�u�������Ń}�X�^�����O�{�C�X���쐬����ۂɎg�p����܂��B<br>
 * ::criAtom_SetOutputVoice_XAUDIO2 �֐����g�p���ă��C�u�����O�ō쐬�ς݂�
 * �o�̓{�C�X���w�肷��ꍇ�A�{�֐��ɐݒ肵���l�͎Q�Ƃ���܂���B<br>
 * \sa criAtom_SetXAudio2Object_XAUDIO2
 */
void CRIAPI criAtom_SetOutputDeviceIndex_XAUDIO2(UINT32 index);

/*JP
 * \brief �T�E���h�o�b�t�@�T�C�Y�̎w��
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	num_samples	�T�E���h�o�b�t�@�T�C�Y�i�T���v�����P�ʁj
 * \par ����:
 * Atom���C�u�������Ń{�C�X�ɃL���[�C���O����T���v�����̍ő�l���w�肵�܂��B<br>
 * �T�E���h�o�b�t�@�̃T�C�Y�̓T���v�����P�ʂŎw�肵�܂��B<br>
 * <br>
 * �T�E���h�o�b�t�@�T�C�Y�� 0 ���w�肵���ꍇ�A
 * �f�t�H���g�T�C�Y�ŃT�E���h�o�b�t�@���쐬����܂��B<br>
 * �iXbox360�ł�2V���APC�ł�4V���̃T�C�Y�ɐݒ肳��܂��B�j<br>
 * \par ���l:
 * Atom���C�u������XAudio2SourceVoice�{�C�X���쐬����ہA
 * ���킹�ăT�E���h�f�[�^���L���[�C���O���邽�߂̃o�b�t�@�i�T�E���h�o�b�t�@�j���쐬���܂��B<br>
 * �f�t�H���g��Ԃł́A�o�b�t�@�T�C�Y�̓��C�u�������������̃p�����[�^�ɉ����Ď����I�Ɍ��肳��܂����A
 * �{�֐������s���邱�ƂŁA�T�E���h�o�b�t�@�̃T�C�Y��C�ӂ̃T�C�Y�ɕύX���邱�Ƃ��\�ł��B<br>
 * <br>
 * ASR���g�p����ꍇ�A�Đ�������A���ۂɉ�����܂łɁA
 * �T�E���h�o�b�t�@�T�C�Y���̒x���������邱�ƂɂȂ�܂��B<br>
 * ���̂��߁A�T�E���h�o�b�t�@�̃T�C�Y�������Ȓl�ɕύX����΁A
 * �����Đ��J�n����������ۂɉ�����܂ł̊Ԋu���A������x�Z�����邱�Ƃ��ł��܂��B<br>
 * \attention
 * ASR�������I�ɍ쐬����{�C�X�̃T�E���h�o�b�t�@�̃T�C�Y��ύX�������ꍇ�A
 * �{�֐���ASR�̏����������O�Ɏ��s���Ă����K�v������܂��B<br>
 * �iASR�쐬�ɕK�v�ȃ��[�N�̈�̃T�C�Y���ς�邽�߁A
 * �����ɂ�ASR�������p���[�N�̈�T�C�Y���v�Z����O�Ɏ��s����K�v������܂��B�j<br>
 * <br>
 * �w�肵���T�C�Y������������ꍇ�A���r�؂ꓙ�̖�肪��������\��������܂��B<br>
 * �i�Œ�ł��u�Đ��T���v�����O���[�g���T�[�o�������g���v�ȏ�̒l���w�肷��K�v������܂��B�j<br>
 * <br>
 * PC���ł́A�T�E���h�o�b�t�@�T�C�Y�������������ꍇ�ɍĐ����������s���邩�ǂ������A
 * �T�E���h�f�o�C�X�̐��\�ɂ����E����܂��B<br>
 * �����̊��ŉ��r�؂�Ȃ��Đ����s�������ꍇ�ɂ́A
 * �T�E���h�o�b�t�@�T�C�Y�ɂ�����x�傫�߂̒l��ݒ肵�Ă��������B<br>
 */
void CRIAPI criAtom_SetSoundBufferSize_XAUDIO2(CriSint32 num_samples);

/*JP
 * \brief XAudio2�Œv���I�ȃG���[�������������ǂ����̃`�F�b�N
 * \ingroup ATOMLIB_XAUDIO2
 * \return	CriBool	�G���[�̗L���iCRI_TRUE = �G���[�������ACRI_FALSE = ����ɓ��쒆�j
 * \par ����:
 * XAudio2�ŃA�v���P�[�V�����̍ċN�����K�v�Ȓv���I�G���[�������������ǂ�����Ԃ��܂��B<br>
 * <br>
 * PC���ŃT�E���h�f�o�C�X�̔����������s�����ꍇ�A�{�֐���CRI_TRUE��Ԃ��܂��B<br>
 * �A�v���P�[�V�����Ńf�o�C�X�����������P�A�������ꍇ�ɂ́A
 * �{�֐��̖߂�l�ɉ����ă��[�U�ւ̒ʒm�����s���Ă��������B<br>
 * \par ���l:
 * �{�֐��́AXAudio2���ňȉ��̃R�[���o�b�N���Ăяo���ꂽ���ǂ����𔻒肵�Ă��܂��B<br>
 * 	- IXAudio2EngineCallback::OnCriticalError
 * 	- IXAudio2VoiceCallback::OnVoiceError
 * 	.
 * <br>
 * �{�֐���CRI_TRUE��Ԃ����ꍇ�A�����̍Đ��𕜋�����ɂ͈ȉ��̏������s���K�v������܂��B<br>
 * 	-# �T�E���h�f�o�C�X�̍Đڑ�����B
 * 	-# ���C�u�����̏I���������s���B
 * 	-# ���C�u�������ēx����������B
 * 	.
 */
CriBool CRIAPI criAtom_IsCriticalErrorOccurred_XAUDIO2(void);

#endif

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomExConfig_XAUDIO2 �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa CriAtomExConfig_XAUDIO2, criAtomEx_Initialize_XAUDIO2
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_XAUDIO2(const CriAtomExConfig_XAUDIO2 *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtomEx_Finalize_XAUDIO2 �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtomEx_CalculateWorkSize_XAUDIO2 
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtomEx_Finalize_XAUDIO2 �֐������s���Ă��������B<br>
 * �܂��A ::criAtomEx_Finalize_XAUDIO2 �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * \sa CriAtomExConfig_XAUDIO2, criAtomEx_Finalize_XAUDIO2,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_XAUDIO2
 */
void CRIAPI criAtomEx_Initialize_XAUDIO2(
	const CriAtomExConfig_XAUDIO2 *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_XAUDIO2
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
 * ::criAtomEx_Initialize_XAUDIO2 �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_Initialize_XAUDIO2
 */
void CRIAPI criAtomEx_Finalize_XAUDIO2(void);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define criAtom_ControlComInitialization_XAUDIO2(sw)

#endif	/* CRI_INCL_CRI_ATOM_XAUDIO2_H */

/* --- end of file --- */
