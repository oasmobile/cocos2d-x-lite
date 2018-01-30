/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2012 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Installer
 * File     : crifs_installer.h
 *
 ****************************************************************************/

/*!
 *	\file		crifs_installer.h
 */

/*JP
 * \addtogroup FSLIB_CRIFS_INSTALLER
 * HDD�C���X�g�[���@�\���g�p���邽�߂�API�ł��B<br>
 * HDD�C���X�g�[���@�\�́AHDD���̏������݉\�ȃf�o�C�X�ɑ΂��āA�ȒP�Ƀt�@�C���̃R�s�[���s�����Ƃ��ł���@�\�ł��B<br>
 * �ڍׂɂ��Ă� \ref crifs_installer ���Q�Ƃ��Ă��������B
 * @{
 */
/*EN
 * \addtogroup FSLIB_CRIFS_INSTALLER
 * @{
 */

/* ���d��`�h�~ */
/* Prevention of redefinition */
#ifndef	CRIFS_INSTALLER_H_INCLUDED
#define	CRIFS_INSTALLER_H_INCLUDED

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
/* �C���X�g�[���I�u�W�F�N�g�̑O���錾 */
struct _CriFsInstallerObj;

/*JP
 * \brief CriFsInstaller�n���h��
 * \par ����:
 * �C���X�g�[���ɃA�N�Z�X���邽�߂̃n���h���ł��B<br>
 * ::criFsInstaller_Create�֐��ɂ��쐬���܂��B
 * \sa criFsInstaller_Create
 */
typedef struct _CriFsInstallerObj *CriFsInstallerHn;


/*JP
 * \brief �C���X�g�[���X�e�[�^�X
 * \par ����:
 * �C���X�g�[���n���h���̏�Ԃ�\���܂��B<br>
 * ::criFsInstaller_GetStatus�֐��ɂ��擾�ł��܂��B
 * \sa criFsInstaller_GetStatus
 */
/*EN
 * \brief Installer Status
 */
typedef enum CriFsInstallerStatusTag {
	CRIFSINSTALLER_STATUS_STOP,		/*JP< ��~��		*/	/*EN< Stopping			*/
	CRIFSINSTALLER_STATUS_BUSY,		/*JP< ������		*/	/*EN< Busy				*/
	CRIFSINSTALLER_STATUS_COMPLETE,	/*JP< ����			*/	/*EN< Complete			*/
	CRIFSINSTALLER_STATUS_ERROR		/*JP< �G���[		*/	/*EN< Error				*/
} CriFsInstallerStatus;

/*JP
 * \brief �C���X�g�[���v���C�I���e�B
 * \par ����:
 * �ǂݍ��݂܂��͏������݂̗D��x�ł��B<br>
 * \sa criFsInstaller_SetLoadPriority
 * \sa criFsInstaller_SetWritePriority
 */
/*EN
 * \brief Priority
 */
typedef enum CriFsInstallerPriorityTag {
	CRIFSINSTALLER_PRIORITY_HIGHEST 		= 2,	/*JP< �ō�		*/	/*EN< Highest		*/
	CRIFSINSTALLER_PRIORITY_ABOVE_NORMAL 	= 1,	/*JP< ��		*/	/*EN< Above normal	*/
	CRIFSINSTALLER_PRIORITY_NORMAL 			= 0,	/*JP< ����		*/	/*EN< Normal		*/
	CRIFSINSTALLER_PRIORITY_BELOW_NORMAL 	= -1,	/*JP< ��		*/	/*EN< Below normal	*/
	CRIFSINSTALLER_PRIORITY_LOWEST 			= -2	/*JP< �Œ�		*/	/*EN< Lowest		*/
} CriFsInstallerPriority;

/*JP
 * \brief �R�s�[�|���V�[
 * \par ����:
 * �t�@�C�����R�s�[���邩�ۂ��𔻒肷��������w�肵�܂��B
 * �C���X�g�[���쐬���i::criFsInstaller_Create�֐��j�ɁA::CriFsInstallerOption�\���̂ɂĎw�肵�܂��B
 * \sa CriFsInstallerOption
 * \sa criFsInstaller_Create
 */
typedef enum CriFsInstallerCopyPolicyTag {
	CRIFSINSTALLER_COPY_POLICY_ALWAYS 			= 0		/*JP< ��ɃR�s�[����					*/
							 							/*EN< Copy Always						*/
} CriFsInstallerCopyPolicy;

/*JP
 * \brief �C���X�g�[���I�v�V����
 * \par ����:
 * �C���X�g�[���̊e��ݒ�ł��B<br>
 * �C���X�g�[���쐬���i::criFsInstaller_Create�֐��j�Ɏw�肵�܂��B<br>
 * �����I�Ƀ����o��������\���ɔ����A�ݒ�O��0�N���A���Ă���g�p���Ă��������B
 * \sa criFsInstaller_Create
 */
typedef struct CriFsInstallerOptionTag {
	/*JP
	 * \brief �R�s�[�|���V�[
	 * \par ����:
	 * �R�s�[�|���V�[���w�肵�܂��B
	 * \sa CriFsInstallerCopyPolicy
	 */
	CriFsInstallerCopyPolicy copy_policy;
} CriFsInstallerOption;

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
 * \brief �T�[�o�����̎��s
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �T�[�o���������s���܂��B���̊֐��͒���I�i��F1V��1��j�ɌĂяo���Ă��������B<br>
 * �}���`�X���b�h���f���̏ꍇ�́A�C���X�g�[���X���b�h�𖾎��I�Ɏ��s��Ԃɂ��܂��B<br>
 * ���[�U�}���`�X���b�h���f���A�V���O���X���b�h���f���̏ꍇ�́A���[�h���N�G�X�g�^���C�g���N�G�X�g���̏��������̊֐����ōs���܂��B
 * \par ��:
 * \code
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \sa CriFsThreadModel
 */
CriError CRIAPI criFsInstaller_ExecuteMain(void);


/*JP
 * \brief �C���X�g�[���̍쐬
 * \param[out]	installer	�C���X�g�[���n���h��
 * \param[in]	option	�C���X�g�[���I�v�V����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[�����쐬���A�C���X�g�[���n���h����Ԃ��܂��B<br>
 * \par ��:
 * \code
 * CriFsInstallerHn installer;
 * CriFsInstallerOption installer_option;
 * memset(&installer_option, 0, sizeof(installer_option));
 * installer_option.copy_policy = CRIFSINSTALLER_COPY_POLICY_ALWAYS;
 * criFsInstaller_Create(&installer, option);
 *
 * 		:
 * 		:
 * 		:
 *
 * criFsInstaller_Destroy(installer);
 * \endcode
 * \sa CriFsInstallerOption
 * \sa criFsInstaller_Destroy
 */
CriError CRIAPI criFsInstaller_Create(CriFsInstallerHn *installer, CriFsInstallerOption option);

/*JP
 * \brief �C���X�g�[���̔j��
 * \param[in]	installer	�C���X�g�[���n���h��
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �C���X�g�[����j�����܂��B<br>
 * \par ��:
 * \code
 * CriFsInstallerHn installer;
 * CriFsInstallerOption installer_option;
 * memset(&installer_option, 0, sizeof(installer_option));
 * installer_option.copy_policy = CRIFSINSTALLER_COPY_POLICY_ALWAYS;
 * criFsInstaller_Create(&installer, option);
 *
 * 		:
 * 		:
 * 		:
 *
 * criFsInstaller_Destroy(installer);
 * \endcode
 * \sa criFsInstaller_Create
 */
CriError CRIAPI criFsInstaller_Destroy(CriFsInstallerHn installer);

/*JP
 * \brief �t�@�C���̃R�s�[
 * \param[in]	installer	�C���X�g�[���n���h��
 * \param[in]	binder	CriFsBinder�n���h��
 * \param[in]	src_path	�R�s�[���t�@�C���p�X��
 * \param[in]	dst_path	�R�s�[��t�@�C���p�X��
 * \param[in]	buffer	�o�b�t�@�ւ̃|�C���^
 * \param[in]	buffer_size	�o�b�t�@�̃T�C�Y�i2�̔{���j
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �t�@�C���̃R�s�[���J�n���܂��B<br>
 * buffer�����Ŏw�肷��o�b�t�@�́A�ǂݍ��݁^�������݂̒��ԃo�b�t�@�Ƃ��Ďg�p����܂��B
 * �܂��A���̃o�b�t�@�͓����I�ɓ񕪊�����A�ǂݍ��݁^�������݂����ɍs���܂��B���̂��߁A�o�b�t�@�T�C�Y��2�̔{���Ŏw�肷��K�v������܂��B<br>
 * ::criFs_SetUserMallocFunction �֐��܂���::criFs_SetUserAllocator �}�N���Ń������m�ۊ֐����o�^����Ă���ꍇ�A
 * buffer��NULL�Abuffer_size��0���w�肷�邱�ƂŁA�o�^�ς݂̃������m�ۊ֐����g�p���ăo�b�t�@�������I�Ɋm�ۂ��܂��B
 * ���̂Ƃ��m�ۂ����������́A::criFsInstaller_Destroy �֐��Ăяo�����A�܂��̓o�b�t�@���w�肵�Ė{�֐����Ăяo�����ۂɉ������܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * �R�s�[�̊�����Ԃ��擾����ɂ� ::criFsInstaller_GetStatus�֐����g�p���Ă��������B
 * \par ��:
 * \code
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \attention
 * �R�s�[�悪���݂��Ȃ��ꍇ�G���[�ɂȂ邽�߁A���O�Ƀt�H���_�쐬���Ė{API���Ăяo���Ă��������B<br>
 * \sa criFsInstaller_GetStatus
 */
CriError CRIAPI criFsInstaller_Copy(CriFsInstallerHn installer,
	CriFsBinderHn binder, const CriChar8 *src_path, const CriChar8 *dst_path,
	void *buffer, CriSint64 buffer_size);

/*JP
 * \brief �����̒�~
 * \param[in]	installer	�C���X�g�[���n���h��
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �������~���܂��B<br>
 * <br>
 * �{�֐��͑������A�֐��ł��B<br>
 * ��~�̊�����Ԃ��擾����ɂ� ::criFsInstaller_GetStatus�֐����g�p���Ă��������B
 * \par ��:
 * \code
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_STOP) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 	if (user_stop_flag == CRI_TRUE) {
 * 		criFsInstaller_Stop(installer);
 * 	}
 *
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \sa criFsInstaller_GetStatus
 */
CriError CRIAPI criFsInstaller_Stop(CriFsInstallerHn installer);

/*JP
 * \brief �X�e�[�^�X�̎擾
 * \param[in]	installer	�C���X�g�[���n���h��
 * \param[out]	status	�X�e�[�^�X
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �X�e�[�^�X���擾���܂��B<br>
 * \par ��:
 * \code
 * CriFsInstallerStatus status;
 * criFsInstaller_GetStatus(installer, &status);
 * switch(status) {
 * case CRIFSINSTALLER_STATUS_STOP:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_BUSY:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_COMPLETE:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_ERROR:
 * 	  :
 * 	break;
 * default:
 * 	  :
 * 	break;
 * }
 * \endcode
 */
CriError CRIAPI criFsInstaller_GetStatus(CriFsInstallerHn installer, CriFsInstallerStatus *status);

/*JP
 * \brief �i���󋵂̎擾
 * \param[in]	installer	�C���X�g�[���n���h��
 * \param[out]	progress	�i����
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * �����̐i���󋵂��擾���܂��B�i���󋵂�0.0�`1.0��32�r�b�g���������_���ł��B<br>
 * �t�@�C���R�s�[�����̏ꍇ�A�l�̐��x�̓R�s�[�o�b�t�@�̃T�C�Y�Ɉˑ����܂��B
 * \par ��:
 * \code
 * CriFloat32 progress;
 * CriFloat32 progress_old = 0.0f;
 *
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetProgress(installer, &progress);
 * 	if (progress != progress_old) {
 * 		printf("progress:%5.2f\n", progress*100.0f);
 * 		progress_old = progress;
 * 	}
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 */
CriError CRIAPI criFsInstaller_GetProgress(CriFsInstallerHn installer, CriFloat32 *progress);


/*JP
 * \brief ���[�h�v���C�I���e�B�̐ݒ�
 * \param[in]	installer	�C���X�g�[���n���h��
 * \param[out]	prio	���[�h�v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���[�h�v���C�I���e�B��ݒ肵�܂��B<br>
 * �����Őݒ肵���v���C�I���e�B�́A����::CriFsInstallerHn�A�y��::CriFsLoaderHn�ł̃��[�h�����̏����t���Ɏg�p����܂��B
 * \par ��:
 * \code
 * criFsInstaller_SetLoadPriority(installer, CRIFSINSTALLER_PRIORITY_LOWEST);
 * \endcode
 * \sa CriFsInstallerPriority
 */
CriError CRIAPI criFsInstaller_SetLoadPriority(CriFsInstallerHn installer, CriFsInstallerPriority prio);
/*JP
 * \brief ���C�g�v���C�I���e�B�̐ݒ�
 * \param[in]	installer	�C���X�g�[���n���h��
 * \param[out]	prio	���C�g�v���C�I���e�B
 * \return	CriError	�G���[�R�[�h
 * \par ����:
 * ���C�g�v���C�I���e�B��ݒ肵�܂��B<br>
 * �����Őݒ肵���v���C�I���e�B�́A����::CriFsInstallerHn�ł̃��C�g�����̏����t���Ɏg�p����܂��B
 * \par ��:
 * \code
 * criFsInstaller_SetWritePriority(installer, CRIFSINSTALLER_PRIORITY_HIGHEST);
 * \endcode
 * \sa CriFsInstallerPriority
 */
CriError CRIAPI criFsInstaller_SetWritePriority(CriFsInstallerHn installer, CriFsInstallerPriority prio);

#ifdef __cplusplus
}
#endif

#endif	/* CRIFS_INSTALLER_H_INCLUDED */

/*JP
 * @}
 */
/*EN
 * @}
 */


/* --- end of file --- */
