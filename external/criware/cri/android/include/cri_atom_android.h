/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2015 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for Android
 * File     : cri_atom_android.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_android.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_CRI_ATOM_ANDROID_H
#define	CRI_INCL_CRI_ATOM_ANDROID_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <jni.h>
#include <cri_xpt.h>
#include <cri_error.h>
#include "cri_atom.h"
#include "cri_atom_ex.h"
#include "cri_atom_asr.h"

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/*JP
 * \brief Stream Type ID
 * \ingroup ATOMLIB_Android
 * �����o�͐�̃X�g���[���^�C�v��ݒ肷��l�ł��B<br>
 */
typedef enum {
    CRIATOMANDROID_STREAM_TYPE_MUSIC,
    CRIATOMANDROID_STREAM_TYPE_ALARM,
    CRIATOMANDROID_STREAM_TYPE_DTMF ,
    CRIATOMANDROID_STREAM_TYPE_NOTIFICATION,
    CRIATOMANDROID_STREAM_TYPE_RING,
    CRIATOMANDROID_STREAM_TYPE_SYSTEM,
    CRIATOMANDROID_STREAM_TYPE_VOICE_CALL,
	CRIATOMANDROID_STREAM_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomAndroidStreamType;

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_Android
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtom_Initialize_ANDROID �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomConfig_ANDROID �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \attention
 * �{�}�N���͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�}�N���̑����
 * ::criAtomEx_SetDefaultConfig_ANDROID �}�N���������p���������B
 * \sa CriAtomConfig_ANDROID
 */
#define criAtom_SetDefaultConfig_ANDROID(p_config)			\
{															\
	(p_config)->initialize_hca_mx = CRI_TRUE;				\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_Android
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomEx_Initialize_ANDROID �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExConfig_ANDROID �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomExConfig_ANDROID
 */
#define criAtomEx_SetDefaultConfig_ANDROID(p_config)		\
{															\
	(p_config)->initialize_hca_mx = CRI_TRUE;				\
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
 * \ingroup ATOMLIB_Android
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtom_Initialize_ANDROID �֐��̈����Ɏw�肵�܂��B<br>
 * \attention
 * �{�\���͉̂��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�\���̂̑����
 * ::CriAtomExConfig_ANDROID �\���̂������p���������B
 * \sa criAtom_Initialize_ANDROID, criAtom_SetDefaultConfig_ANDROID
 */
typedef struct {
	CriBool					initialize_hca_mx;	/*JP< HCA-MX�����������邩�ǂ���		*/
	CriAtomConfig			atom;				/*JP< Atom�������p�R���t�B�O�\����		*/
	CriAtomAsrConfig		asr;				/*JP< ASR�������p�R���t�B�O				*/
	CriAtomHcaMxConfig		hca_mx;				/*JP< HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomConfig_ANDROID;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_Android
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtomEx_Initialize_ANDROID �֐��̈����Ɏw�肵�܂��B<br>
 * \sa criAtomEx_Initialize_ANDROID, criAtomEx_SetDefaultConfig_ANDROID
 */
typedef struct {
	CriBool					initialize_hca_mx;	/*JP< HCA-MX�����������邩�ǂ���		*/
	CriAtomExConfig			atom_ex;			/*JP< AtomEx�������p�R���t�B�O�\����	*/
	CriAtomExAsrConfig		asr;				/*JP< ASR�������p�R���t�B�O				*/
	CriAtomExHcaMxConfig	hca_mx;				/*JP< HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomExConfig_ANDROID;

/*JP
 * \brief �x�������� ��ԗ񋓌^
 * \ingroup ATOMLIB_Android
 * �x��������̏�Ԃ�\���񋓌^�ł��B <br>
 */
typedef enum CriAtomExLatencyEstimatorStatus_Tag {
	CRIATOM_LATENCYESTIMATOR_STATUS_STOP,			/* �������/��~���	(���s���X���b�h�Ȃ�) */
	CRIATOM_LATENCYESTIMATOR_STATUS_PROCESSING,		/* �x�����Ԃ𐄑���		(���s���X���b�h����) */
	CRIATOM_LATENCYESTIMATOR_STATUS_DONE,			/* �x�����Ԃ̐�������	(���s���X���b�h�Ȃ�) */
	CRIATOM_LATENCYESTIMATOR_STATUS_ERROR,			/* �G���[				(���s���X���b�h�Ȃ�) */
	CRIATOM_LATENCYESTIMATOR_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomLatencyEstimatorStatus;

/*JP
 * \brief �x�������� ���\����
 * \ingroup ATOMLIB_Android
 * �x��������̏���\���\���̂ł��B<br>
 * �x��������̏�ԂƁA�����x������(�~���b)�������܂��B
 */
typedef struct CriAtomExLatencyEstimatorInfo_Tag {
	CriAtomLatencyEstimatorStatus	status;
	CriUint32						latency_msec; // �ُ�l��0
} CriAtomLatencyEstimatorInfo;

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
 * \ingroup ATOMLIB_Android
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomConfig_ANDROID �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑����
 * ::criAtomEx_CalculateWorkSize_ANDROID �֐��������p���������B
 * \sa CriAtomConfig_ANDROID, criAtom_Initialize_ANDROID
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_ANDROID(const CriAtomConfig_ANDROID *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_Android
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtom_Finalize_ANDROID �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtom_CalculateWorkSize_ANDROID
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtom_Finalize_ANDROID �֐������s���Ă��������B<br>
 * �܂��A ::criAtom_Finalize_ANDROID �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑����
 * ::criAtomEx_Initialize_ANDROID �֐��������p���������B
 * \sa CriAtomConfig_ANDROID, criAtom_Finalize_ANDROID,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_ANDROID
 */
void CRIAPI criAtom_Initialize_ANDROID(
	const CriAtomConfig_ANDROID *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_Android
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
 * ::criAtom_Initialize_ANDROID �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * <br>
 * �{�֐��͉��ʃ��C��������API�ł��B<br>
 * AtomEx���C���̋@�\�𗘗p����ۂɂ́A�{�֐��̑����
 * ::criAtomEx_Finalize_ANDROID �֐��������p���������B
 * \sa criAtom_Initialize_ANDROID
 */
void CRIAPI criAtom_Finalize_ANDROID(void);

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�ύX
 * \ingroup ATOMLIB_Android
 * \param[in]	prio	�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B��ύX���܂��B<br>
 * �f�t�H���g��ԁi�{�֐������s���Ȃ��ꍇ�j�ł́A�T�[�o�����X���b�h�̃v���C�I���e�B��
 * -19(�i�C�X�l) �ɐݒ肳��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 * \sa criAtom_Initialize_ANDROID, criAtom_GetThreadPriority_ANDROID
 */
void CRIAPI criAtom_SetThreadPriority_ANDROID(int prio);

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�擾
 * \ingroup ATOMLIB_Android
 * \return	int		�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B���擾���܂��B<br>
 * �擾�ɐ�������ƁA�{�֐��̓T�[�o�������s���X���b�h�̃v���C�I���e�B(�i�C�X�l)��Ԃ��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * \sa criAtom_Initialize_ANDROID, criAtom_SetThreadPriority_ANDROID
 */
int CRIAPI criAtom_GetThreadPriority_ANDROID(void);

/*JP
 * \brief JavaVM�I�u�W�F�N�g�̐ݒ�
 * \ingroup ATOMLIB_Android
 * \return	JavaVM*		JavaVM�I�u�W�F�N�g
 * \par ����:
 * JavaVM�I�u�W�F�N�g��Atom���C�u�����ɓo�^���܂��B<br>
 * Android OS 2.3���O��OS���T�|�[�g����ꍇ�́A�{�֐���K���g�p���AJavaVM�I�u�W�F�N�g��o�^���Ă��������B<br>
 * Android OS 2.3�ȍ~��OS�݂̂�ΏۂƂ���ꍇ�́A�{�֐����Ăяo���Ȃ��Ă����삵�܂��B<br>
 * \attention:
 * JavaVM�I�u�W�F�N�g��o�^�����ꍇ�A���C�u���������ō쐬�����X���b�h��JavaVM�ɃA�^�b�`���܂��B<br>
 *
 * <br>
 * �{�֐��̓��C�u�����������O�Ɏ��s����K�v������܂��B<br>
 * \sa criAtom_Initialize_ANDROID
 */
void CRIAPI criAtom_SetJavaVM_ANDROID(JavaVM* vm);

/*JP
 * \brief �����o�͐�X�g���[���^�C�v�̐ݒ�
 * \ingroup ATOMLIB_Android
 * \return
 * \par ����:
 * �����o�͐�X�g���[���^�C�v��ݒ肵�܂��B<br>
 * <br>
 * �{�֐��̓��C�u�����������O�Ɏ��s����K�v������܂��B<br>
 * \sa criAtomEx_Initialize_ANDROID
 */
void CRIAPI criAtom_SetOutputStreamType(CriAtomAndroidStreamType type);

/*JP
 * \brief �Đ��J�n�o�b�t�@�����O���Ԃ̐ݒ�
 * \ingroup ATOMLIB_Android
 * \param[in]	time	�Đ��J�n�o�b�t�@�����O���ԁi�~���b�P�ʁj
 * \par ����:
 * Atom���C�u�������ŉ����Đ��J�n���Ƀo�b�t�@�����O���鎞�ԁi�~���b�P�ʁj���w�肵�܂��B<br>
 * 0 ���w�肵���ꍇ�A�f�t�H���g�T�C�Y�Ńo�b�t�@�����O���܂��B<br>
 * �{�֐��̐ݒ�l��NSR�i�l�C�e�B�u�T�E���h�����_���j���[�h�ł̍Đ��J�n���C�e���V�ɉe�����܂��B<br>
 * �i�傫���l��ݒ肵�Ă��܂��Ƃ��̕��A�Đ��J�n���C�e���V���傫���Ȃ邱�ƂɂȂ�܂��j<br>
 * \par ���l:
 * �f�t�H���g�ł�3V�����̍Đ��J�n�o�b�t�@�����O���Ԃ�ݒ肵�Ă��܂��B
 * �i�T�[�o���g���̐ݒ肪60[fps]�F16.6[ms]�̏ꍇ�A3V�͖�50[ms]�̍Đ��J�n�o�b�t�@�����O���ԂɂȂ�܂��j<br>
 * <br>
 * Android�[���ɂ���Ă͍Đ��J�n�o�b�t�@�����O���Ԃ����Ȃ��ƃm�C�Y�ɂȂ��Ă��܂��ꍇ������܂��B
 * ���̏ꍇ�͖{�֐��Œ������邱�Ƃŉ��P���鎖������܂��B
 * \sa criAtom_SetSoundBufferingTime_ANDROID
 */
void CRIAPI criAtom_SetSoundStartBufferingTime_ANDROID(CriSint32 time);

/*JP
 * \brief �T�E���h�f�R�[�h�o�b�t�@�ʂ̐ݒ�i�~���b�P�ʁj
 * \ingroup ATOMLIB_Android
 * \param[in]	time	�T�E���h�f�R�[�h�o�b�t�@�ʁi�~���b�P�ʁj
 * \par ����:
 * Atom���C�u�������ŉ����Đ��Ŏg�p����f�R�[�h�o�b�t�@�ʁi�~���b�P�ʁj���w�肵�܂��B<br>
 * 0 ���w�肵���ꍇ�A�f�t�H���g�T�C�Y�̃T�E���h�f�R�[�h�o�b�t�@�ʂ�ݒ肵�܂��B<br>
 * �{�֐��̐ݒ�l��ASR�iAtom�T�E���h�����_���j���[�h�ł̍Đ��J�n���C�e���V�ɉe�����܂��B<br>
 * �i�傫���l��ݒ肵�Ă��܂��Ƃ��̕��A�Đ��J�n���C�e���V���傫���Ȃ邱�ƂɂȂ�܂��j<br>
 * \par ���l:
 * �f�t�H���g�ł�4V�����̃f�R�[�h�o�b�t�@�ʂ�ݒ肵�܂��B
 * �i�T�[�o���g���̐ݒ肪60[fps]�F16.6[ms]�̏ꍇ�A4V�͖�66[ms]�̃T�E���h�f�R�[�h�o�b�t�@�ʂɂȂ�܂��j<br>
 * <br>
 * Android�[���ɂ���Ă̓T�E���h�f�R�[�h�o�b�t�@�ʂ����Ȃ��ƃm�C�Y�ɂȂ��Ă��܂��ꍇ������܂��B
 * ���̏ꍇ�͖{�֐��Œ������邱�Ƃŉ��P���鎖������܂��B
 * \attention
 * �{�֐��͏����������O�Ɏ��s���Ă����K�v������܂��B<br>
 * \sa criAtom_SetSoundStartBufferingTime_ANDROID
 */
void CRIAPI criAtom_SetSoundBufferingTime_ANDROID(CriSint32 time);

/*JP
 * \brief �T�E���h�o�b�t�@�T�C�Y�̐ݒ�
 * \ingroup ATOMLIB_Android
 * \param[in]	num_samples	�T�E���h�o�b�t�@�T�C�Y�i�T���v�����P�ʁj
 * \par ����:
 * �{�֐��͌݊����̂��߂Ɏc���Ă���܂��B
 * CRI Atom Ver.1.30.02�ȍ~��criAtom_SetSoundBufferingTime_ANDROID�֐���
 * �g�p���ăT�E���h�o�b�t�@�T�C�Y�𒲐����ĉ������B
 * ����͌݊����̂��߂ɋ��֐��Ƃ��Ďc���Ă���܂��B
 * <br>
 * Atom���C�u�������Ń{�C�X�ɃL���[�C���O����T���v�����̍ő�l���w�肵�܂��B<br>
 * �T�E���h�o�b�t�@�̃T�C�Y�̓T���v�����P�ʂŎw�肵�܂��B<br>
 * <br>
 * �T�E���h�o�b�t�@�T�C�Y�� 0 ���w�肵���ꍇ�A
 * �f�t�H���g�T�C�Y�ŃT�E���h�o�b�t�@���쐬����܂��B<br>
 * \sa criAtom_SetSoundBufferingTime_ANDROID
 */
void CRIAPI criAtom_SetSoundBufferSize_ANDROID(CriSint32 num_samples);

/*JP
 * \brief �[���ŗL�v���p�e�B�̓K�p
 * \ingroup ATOMLIB_Android
 * \param[in]	vm		JavaVM�I�u�W�F�N�g�̎Q��
 * \param[in]	context		android.content.Context �I�u�W�F�N�g
 * \return		CriBool	�v���p�e�B�̓K�p�ɐ���������
 * \par ����:
 * �o�̓T���v�����O���[�g�ȂǁA�[���ŗL�̃v���p�e�B�����C�u�����̓���ɓK�p���܂��B<br>
 * CRI_TRUE ��Ԃ����ꍇ�A�K�p�ɐ������Ă��܂��B<br>
 * CRI_FALSE ��Ԃ����ꍇ�AAPI Level���Ⴂ�Ȃǂ̗��R�ɂ�莸�s���Ă���A�f�t�H���g�̐ݒ��
 * ���삵�܂��B<br>
 * \par ���l:
 * NSR�i�l�C�e�B�u�T�E���h�����_���j���[�h�𗘗p���ĉ����o�͂��s���ꍇ�A�[����Android OS��
 * �o�[�W�����ɂ��A�����Đ��̕��ׂ����傷�邱�Ƃ�����܂��B<br>
 * �{�֐��̌Ăяo���ɂ��AOpenSL ES�̃��C���Œ[���̃T���v�����O���[�g�ɉ�����������s��
 * �悤�ɂȂ�A�Đ����ׂ�ጸ���邱�Ƃ��\�ł��B>
 * \attention
 * �{�֐��͏����������O�Ɏ��s���Ă����K�v������܂��B<br>
 * \sa criAtomEx_Initialize_ANDROID
 */
CriBool CRIAPI criAtom_ApplyHardwareProperties_ANDROID(JavaVM* vm, jobject context);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_Android
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomExConfig_ANDROID �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa CriAtomExConfig_ANDROID, criAtomEx_Initialize_ANDROID
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_ANDROID(const CriAtomExConfig_ANDROID *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_Android
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtomEx_Finalize_ANDROID �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�ɂ́A ::criAtomEx_CalculateWorkSize_ANDROID
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
 * �{�֐������s��A�K���΂ɂȂ� ::criAtomEx_Finalize_ANDROID �֐������s���Ă��������B<br>
 * �܂��A ::criAtomEx_Finalize_ANDROID �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * \sa CriAtomExConfig_ANDROID, criAtomEx_Finalize_ANDROID,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_ANDROID
 */
void CRIAPI criAtomEx_Initialize_ANDROID(
	const CriAtomExConfig_ANDROID *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_Android
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
 * ::criAtomEx_Initialize_ANDROID �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_Initialize_ANDROID
 */
void CRIAPI criAtomEx_Finalize_ANDROID(void);

/*JP
 * \brief �T�E���h�����̍ĊJ
 * \ingroup ATOMLIB_Android
 * \par ����:
 * �{�֐����ł�Atom�T�[�o�X���b�h�̃��b�N��Ԃ���������܂��B<br>
 * �܂��AASR�̒�~���������܂��B<br>
 * �{�֐��̓���ۏ؂̂��߁A�Ăяo���̑O�ɂ͕K��criAtom_StopSound_ANDROID�֐���<br>
 * �Ă΂�邱�Ƃ��m�F���Ă��������B
 * \sa criAtomEx_StartSound_ANDROID
 */
void CRIAPI criAtomEx_StartSound_ANDROID(void);

/*JP
 * \brief �T�E���h�����̒�~
 * \ingroup ATOMLIB_Android
 * \par ����:
 * �{�֐����ł�Atom�T�[�o�X���b�h�����b�N��Ԃɂ��܂��B<br>
 * �܂��AASR�̏������~���܂��B<br>
 * �{�֐��̓���ۏ؂̂��߁A�Ăяo���̌�ɂ͕K��criAtom_StartSound_ANDROID�֐���<br>
 * �Ă΂�邱�Ƃ��m�F���Ă��������B
 * \sa criAtomEx_StopSound_ANDROID
 */
void CRIAPI criAtomEx_StopSound_ANDROID(void);

/*JP
 * \brief �����x�����Ԑ����@�\�̗L�����E������
 * \ingroup ATOMLIB_Android
 * \attention
 * �{�֐��̓x�[�^�@�\�ł��B���i�ɂ͎g�p���Ȃ��ł��������B<br/>
 * \par ����:
 * Android�[���̉����x�����Ԑ����@�\�̗L�����E��������؂�ւ��܂��B<br/>
 * ������CRI_TRUE��^���鎖�ŗL�����ACRI_FALSE��^���鎖�Ŗ��������܂��B
 * �L��������ƁAAtom���C�u�����̓����Œx�����菈���������悤�ɂȂ�܂��B<br/>
 * <br/>
 * �����@�\��L���ɂ�����ԂŁA criAtom_GetSlBufferConsumptionLatency_ANDROID �֐����Ăяo����
 * ���s����Android�[���̉����Đ��x�����Ԃ̐����l���擾�ł��܂��B<br/>
 * <br/>
 * �{�֐���Atom ���C�u�����̏������O�ɌĂ�ŉ������B
 * �܂��A���ʂ��擾������́A�{�֐����g�p���Čv�������𖳌������Ă��������B
 * \sa criAtom_GetSlBufferConsumptionLatency_ANDROID
 */
void criAtom_EnableSlLatencyCheck_ANDROID(CriBool sw);

/*JP
 * \brief �����Đ��x�����Ԃ̎擾
 * \ingroup ATOMLIB_Android
 * \attention
 * �{�֐��̓x�[�^�@�\�ł��B���i�ɂ͎g�p���Ȃ��ł��������B<br/>
 * \par ����:
 * ���s����Android�[����ł̉����Đ��x�����Ԃ��擾�ł��܂��B<br/>
 * <br/>
 * �v�����ʂ͂����܂Ō��ς���ɉ߂����A���ۂ̒x�����ԂƈقȂ�ꍇ������܂��B<br/>
 * �{�֐��œ���ꂽ���ʂ͊J�����̃p�����^�����̂��߂̖ڈ��Ƃ��A���ۂ̃A�v���P�[�V������Ŏg�p���Ȃ��ł��������B<br>
 * \par ����:
 * �{�֐������s����ꍇ�A���O�� criAtom_EnableSlLatencyCheck_ANDROID �֐���p���āA�x���v��������L�������Ă����K�v������܂��B
 * \sa criAtom_EnableSlLatencyCheck_ANDROID
 */
CriSint32 criAtom_GetSlBufferConsumptionLatency_ANDROID();	// �x����m�肽���Ƃ��ɌĂ�

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�ύX
 * \ingroup ATOMLIB_Android
 * \param[in]	prio	�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B��ύX���܂��B<br>
 * �f�t�H���g��ԁi�{�֐������s���Ȃ��ꍇ�j�ł́A�T�[�o�����X���b�h�̃v���C�I���e�B��
 * -19(�i�C�X�l) �ɐݒ肳��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 * \sa criAtomEx_Initialize_ANDROID, criAtomEx_GetThreadPriority_ANDROID
 */
#define criAtomEx_SetThreadPriority_ANDROID(prio)	\
	criAtom_SetThreadPriority_ANDROID(prio)

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�擾
 * \ingroup ATOMLIB_Android
 * \return	int		�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B���擾���܂��B<br>
 * �擾�ɐ�������ƁA�{�֐��̓T�[�o�������s���X���b�h�̃v���C�I���e�B(�i�C�X�l)��Ԃ��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * \sa criAtomEx_Initialize_ANDROID, criAtomEx_SetThreadPriority_ANDROID
 */
#define criAtomEx_GetThreadPriority_ANDROID()	\
	criAtom_GetThreadPriority_ANDROID()

/*JP
 * \brief JavaVM�I�u�W�F�N�g�̐ݒ�
 * \ingroup ATOMLIB_Android
 * \return	JavaVM*		JavaVM�I�u�W�F�N�g
 * \par ����:
 * JavaVM�I�u�W�F�N�g��Atom���C�u�����ɓo�^���܂��B<br>
 * Android OS 2.3���O��OS���T�|�[�g����ꍇ�́A�{�֐���K���g�p���AJavaVM�I�u�W�F�N�g��o�^���Ă��������B<br>
 * Android OS 2.3�ȍ~��OS�݂̂�ΏۂƂ���ꍇ�́A�{�֐����Ăяo���Ȃ��Ă����삵�܂��B<br>
 * \attention:
 * JavaVM�I�u�W�F�N�g��o�^�����ꍇ�A���C�u���������ō쐬�����X���b�h��JavaVM�ɃA�^�b�`���܂��B<br>
 *
 * <br>
 * �{�֐��̓��C�u�����������O�Ɏ��s����K�v������܂��B<br>
 * \sa criAtomEx_Initialize_ANDROID
 */
#define criAtomEx_SetJavaVM_ANDROID(vm)		\
	criAtom_SetJavaVM_ANDROID(vm)

/*JP
 * \brief �����o�͐�X�g���[���^�C�v�̐ݒ�
 * \ingroup ATOMLIB_Android
 * \return	JavaVM*		JavaVM�I�u�W�F�N�g
 * \par ����:
 * �����o�͐�X�g���[���^�C�v��ݒ肵�܂��B<br>
 * <br>
 * �{�֐��̓��C�u�����������O�Ɏ��s����K�v������܂��B<br>
 * \sa criAtomEx_Initialize_ANDROID
 */
#define criAtomEx_SetOutputStreamType(type)		\
	criAtom_SetOutputStreamType(type)

/*JP
 * \brief �x��������̏�����
 * \ingroup ATOMLIB_Android
 * \par ����:
 * �x������������������܂��B<br>
 * <br>
 * �x����������g�p����ہA�{�֐��̌Ăяo���͕K�{�ł��B
 * <br>
 * �{�֐����Ăяo���ƁAAtom���C�u���������Œx�������킪�����A�N�����܂��B
 * �N�����ꂽ�x��������̃X���b�h�́A���X���b�h�̗v������҂����x�������������J�n���܂��B
 * �x���������I������ɂ́A::criAtomLatencyEstimator_Finalize �֐����ĂԕK�v������܂��B
 * <br>
 * �܂��A�{�֐��͊������A�ł��B���d�Ăяo�������e���܂����AAtom���C�u�������ł�
 * �{�֐��̌Ăяo���񐔂��J�E���g���Ă��܂��B
 * ���ۂ̏��������������s�����̂́A�ŏ��̌Ăяo���̎������ɂȂ�܂��B
 * �Ȃ��A���̌Ăяo���񐔃J�E���^�́A::criAtomLatencyEstimator_Finalize �֐����Ăяo���x��
 * �f�N�������g����܂��B
 * \attention
 * ::criAtom_Initialize_ANDROID �֐����s�O�ɖ{�֐������s���Ȃ��ł��������B<br>
 * \sa criAtomLatencyEstimator_Finalize
 */
void CRIAPI criAtomLatencyEstimator_Initialize_ANDROID();

/*JP
 * \brief �x��������̏I��
 * \ingroup ATOMLIB_Android
 * \par ����:
 * �x����������I�����܂��B<br>
 * <br>
 * �x����������I������ہA�{�֐����Ăяo���Ă��������B
 * <br>
 * �N�����̒x��������X���b�h�́A�{�֐��̌Ăяo���ɂ���Đ����������I�����܂��B
 * �����������I�����X���b�h�́A�����I�ɔj������܂��B
 * <br>
 * �܂��A�{�֐��͊������A�ł��B���d�Ăяo�������e���܂��B
 * �{�֐����Ăяo���ƁA::criAtomLatencyEstimator_Initialize �֐��̌Ăяo���J�E���^��
 * �f�N�������g����܂��B�{�֐���::criAtomLatencyEstimator_Initialize �֐��̌Ăяo���񐔂�
 * �����ɂȂ�悤���ӂ��Ă��������B
 * \attention
 * ::criAtom_Initialize_ANDROID �֐����s�O�ɖ{�֐������s���Ȃ��ł��������B<br>
 * \sa criAtomLatencyEstimator_Initialize
 */
void CRIAPI criAtomLatencyEstimator_Finalize_ANDROID();

/*JP
 * \brief �x��������̏��擾
 * \ingroup ATOMLIB_Android
 * \return	CriAtomLatencyEstimatorInfo		�x��������̏��
 * \par ����:
 * �x��������̌��݂̏����擾���܂��B<br>
 * �擾�ł�����́u�x��������̏�ԁv�u�����x������(�~���b)�v�̂Q�ł��B<br>
 * <br>
 * ::criAtomLatencyEstimator_Initialize �֐����Ăяo������A�{�֐����ĂԂ��Ƃ�
 * ���݂̒x��������̏��(��ԁA�����x������)���擾���邱�Ƃ��ł��܂��B
 * ��Ԃ� ::CRIATOM_LATENCYESTIMATOR_STATUS_DONE �ł��鎞�A�����x�����Ԃ�0�łȂ����l�ɂȂ�܂��B
 * ����ȊO�̏�Ԃł́A�����x�����Ԃ�0��Ԃ��܂��B
 * <br>
 * \attention
 * ::criAtomLatencyEstimator_Initialize �֐����s�O�ɖ{�֐������s���Ȃ��ł��������B<br>
 * ::criAtomLatencyEstimator_Finalize �֐����s��ɖ{�֐������s���Ȃ��ł��������B<br>
 * \sa criAtomLatencyEstimator_Initialize criAtomLatencyEstimator_Finalize
 */
CriAtomLatencyEstimatorInfo CRIAPI criAtomLatencyEstimator_GetCurrentInfo_ANDROID();

/*JP
 * \brief ���C�u������������Ԃ̎擾
 * \ingroup ATOMLIB_Android
 * \return	CriBool		�������ς݂��ǂ���
 * \retval	CRI_FALSE	�����������
 * \retval	CRI_TRUE	�������ς�
 * \par ����:
 * �x�������킪���ɏ���������Ă��邩�ǂ������`�F�b�N���܂��B<br>
 * \sa criAtomLatencyEstimator_Initialize criAtomLatencyEstimator_Finalize
 */
CriBool CRIAPI criAtomLatencyEstimator_IsInitialized_ANDROID();

#ifdef __cplusplus
}
#endif

#endif	/* CRI_INCL_CRI_ATOM_ANDROID_H */


/***************************************************************************
 *      ���o�[�W�����Ƃ̌݊��p
 *      For compatibility with old version
 ***************************************************************************/
#define CriAtomConfig_Android \
		CriAtomConfig_ANDROID

#define criAtom_SetDefaultConfig_Android(p_config) \
		criAtom_SetDefaultConfig_ANDROID(p_config)

#define criAtom_CalculateWorkSize_Android(config) \
		criAtom_CalculateWorkSize_ANDROID(config)

#define criAtom_Initialize_Android(config, work, work_size) \
		criAtom_Initialize_ANDROID((config), (work), (work_size))

#define criAtom_Finalize_Android() \
		criAtom_Finalize_ANDROID()

#define criAtom_SetThreadPriority_Android(prio) \
		criAtom_SetThreadPriority_ANDROID(prio)

#define criAtom_GetThreadPriority_Android() \
		criAtom_GetThreadPriority_ANDROID()

#define criAtom_SetSoundBufferSize_Android(num_samples) \
		criAtom_SetSoundBufferSize_ANDROID(num_samples)

#define criAtom_SetJavaVM(vm) \
		criAtom_SetJavaVM_ANDROID(vm)

#define CriAtomExConfig_Android \
		CriAtomExConfig_ANDROID

#define criAtomEx_SetDefaultConfig_Android(p_config) \
		criAtomEx_SetDefaultConfig_ANDROID(p_config)

#define criAtomEx_CalculateWorkSize_Android(config) \
		criAtomEx_CalculateWorkSize_ANDROID(config)

#define criAtomEx_Initialize_Android(config, work, work_size) \
		criAtomEx_Initialize_ANDROID((config), (work), (work_size))

#define criAtomEx_Finalize_Android() \
		criAtomEx_Finalize_ANDROID()

#define criAtomEx_SetThreadPriority_Android(prio) \
		criAtomEx_SetThreadPriority_ANDROID(prio)

#define criAtomEx_GetThreadPriority_Android() \
		criAtomEx_GetThreadPriority_ANDROID()

#define criAtomEx_SetJavaVM(vm)	\
		criAtomEx_SetJavaVM_ANDROID(vm)

#define criAtomEx_StartSound_Android() \
		criAtomEx_StartSound_ANDROID()

#define criAtomEx_StopSound_Android() \
		criAtomEx_StopSound_ANDROID()

/* --- end of file --- */
