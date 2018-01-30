/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for Mac OS X
 * File     : cri_atom_macosx.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_macosx.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_CRI_ATOM_MACOSX_H
#define	CRI_INCL_CRI_ATOM_MACOSX_H

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
 * \ingroup ATOMLIB_MACOSX
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtom_Initialize_MACOSX �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomConfig_MACOSX �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \attention
 * �{�}�N���͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�}�N���̑���� 
 * ::criAtomEx_SetDefaultConfig_MACOSX �}�N���������p���������B
 * \sa CriAtomConfig_MACOSX
 */
#define criAtom_SetDefaultConfig_MACOSX(p_config)				\
{															\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_MACOSX
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomEx_Initialize_MACOSX �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExConfig_MACOSX �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomExConfig_MACOSX
 */
#define criAtomEx_SetDefaultConfig_MACOSX(p_config)			\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
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
 * \ingroup ATOMLIB_MACOSX
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtom_Initialize_MACOSX �֐��̈����Ɏw�肵�܂��B<br>
 * \attention
 * �{�\���͉̂��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�\���̂̑���� 
 * ::CriAtomExConfig_MACOSX �\���̂������p���������B
 * \sa criAtom_Initialize_MACOSX, criAtom_SetDefaultConfig_MACOSX
 */
typedef struct {
	CriAtomConfig			atom;		/* Atom�������p�R���t�B�O�\����		*/
	CriAtomAsrConfig		asr;		/* ASR�������p�R���t�B�O			*/
	CriAtomHcaMxConfig		hca_mx;		/* HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomConfig_MACOSX;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_MACOSX
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtomEx_Initialize_MACOSX �֐��̈����Ɏw�肵�܂��B<br>
 * \sa criAtomEx_Initialize_MACOSX, criAtomEx_SetDefaultConfig_MACOSX
 */
typedef struct {
	CriAtomExConfig			atom_ex;	/* AtomEx�������p�R���t�B�O�\����	*/
	CriAtomExAsrConfig		asr;		/* ASR�������p�R���t�B�O			*/
	CriAtomExHcaMxConfig	hca_mx;		/* HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomExConfig_MACOSX;

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
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomConfig_MACOSX �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_CalculateWorkSize_MACOSX �֐��������p���������B
 * \sa CriAtomConfig_MACOSX, criAtom_Initialize_MACOSX
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_MACOSX(const CriAtomConfig_MACOSX *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtom_Finalize_MACOSX �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtom_CalculateWorkSize_MACOSX 
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtom_Finalize_MACOSX �֐������s���Ă��������B<br>
 * �܂��A ::criAtom_Finalize_MACOSX �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Initialize_MACOSX �֐��������p���������B
 * \sa CriAtomConfig_MACOSX, criAtom_Finalize_MACOSX,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_MACOSX
 */
void CRIAPI criAtom_Initialize_MACOSX(
	const CriAtomConfig_MACOSX *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_MACOSX
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
 * ::criAtom_Initialize_MACOSX �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑���� 
 * ::criAtomEx_Finalize_MACOSX �֐��������p���������B
 * \sa criAtom_Initialize_MACOSX
 */
void CRIAPI criAtom_Finalize_MACOSX(void);

/*JP
 * \brief �T�[�o�X���b�h�v���C�I���e�B�̐ݒ�
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \par ����:
 * CRI�T�[�o�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<br>
 * ���� prio �� pthread �̃v���C�I���e�B�ݒ�l�Ƃ��Ďg�p���܂��B<br>
 * �w��ł���l�͈̔͂͒ʏ� -16�`99�ŁA�������傫�������D��x�������Ȃ�܂��B<br>
 * �A�v���P�[�V�����̃��C���X���b�h(0)���������v���C�I���e�B���w�肵�Ă��������B<br>
 * �v���C�I���e�B�̃f�t�H���g�l��10�ł��B<br>
 * \attention
 * ::criAtom_Initialize_MACOSX �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 */
void CRIAPI criAtom_SetServerThreadPriority_MACOSX(int prio);


/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomExConfig_MACOSX �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa CriAtomExConfig_MACOSX, criAtomEx_Initialize_MACOSX
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_MACOSX(const CriAtomExConfig_MACOSX *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtomEx_Finalize_MACOSX �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtom_CalculateWorkSize_MACOSX 
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtomEx_Finalize_MACOSX �֐������s���Ă��������B<br>
 * �܂��A ::criAtomEx_Finalize_MACOSX �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * \sa CriAtomExConfig_MACOSX, criAtomEx_Finalize_MACOSX,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_MACOSX
 */
void CRIAPI criAtomEx_Initialize_MACOSX(
	const CriAtomExConfig_MACOSX *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_MACOSX
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
 * ::criAtomEx_Initialize_MACOSX �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_Initialize_MACOSX
 */
void CRIAPI criAtomEx_Finalize_MACOSX(void);

/*JP
 * \brief �T�[�o�X���b�h�v���C�I���e�B�̐ݒ�
 * \ingroup ATOMLIB_MACOSX
 * \param[in]	prio	�X���b�h�̃v���C�I���e�B
 * \par ����:
 * CRI�T�[�o�X���b�h�̃v���C�I���e�B��ݒ肵�܂��B<br>
 * ���� prio �� pthread �̃v���C�I���e�B�ݒ�l�Ƃ��Ďg�p���܂��B<br>
 * �w��ł���l�͈̔͂͒ʏ� -16�`99�ŁA�������傫�������D��x�������Ȃ�܂��B<br>
 * �A�v���P�[�V�����̃��C���X���b�h(0)���������v���C�I���e�B���w�肵�Ă��������B<br>
 * �v���C�I���e�B�̃f�t�H���g�l��10�ł��B<br>
 * \attention
 * ::criAtomEx_Initialize_MACOSX �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 */
void CRIAPI criAtomEx_SetServerThreadPriority_MACOSX(int prio);


#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define criAtom_SetDefaultConfig_MacOSX(p_config)		criAtom_SetDefaultConfig_MacOSX
#define criAtomEx_SetDefaultConfig_MacOSX(p_config)		criAtomEx_SetDefaultConfig_MACOSX(p_config)
#define CriAtomConfig_MacOSX							CriAtomConfig_MACOSX
#define CriAtomExConfig_MacOSX							CriAtomExConfig_MACOSX
#define criAtom_CalculateWorkSize_MacOSX				criAtom_CalculateWorkSize_MACOSX
#define criAtom_Initialize_MacOSX						criAtom_Initialize_MACOSX
#define criAtom_Finalize_MacOSX							criAtom_Finalize_MACOSX
#define criAtom_SetServerThreadPriority_MacOSX			criAtom_SetServerThreadPriority_MACOSX
#define criAtomEx_CalculateWorkSize_MacOSX				criAtomEx_CalculateWorkSize_MACOSX
#define criAtomEx_Initialize_MacOSX						criAtomEx_Initialize_MACOSX
#define criAtomEx_Finalize_MacOSX						criAtomEx_Finalize_MACOSX
#define criAtomEx_SetServerThreadPriority_MacOSX		criAtomEx_SetServerThreadPriority_MACOSX

#endif	/* CRI_INCL_CRI_ATOM_MACOSX_H */

/* --- end of file --- */
