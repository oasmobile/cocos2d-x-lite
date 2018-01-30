/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2008 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header
 * File     : cri_file_system_ver1api.h
 * Date     : 2008-09-17
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system_ver1api.h
 */
 
#ifdef __cplusplus

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_VER1PAI_H_INCLUDED
#define	CRI_FILE_SYSTEM_VER1PAI_H_INCLUDED

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_allocator.h"
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
namespace CriFs {
	/*JP
	 * \brief �t�@�C���I�[�v�����[�h
	 */
	/*EN
	 * \brief File Opening Mode
	 */
	enum FileMode {
		FILE_MODE_APPEND,			/*JP< �����t�@�C���ɒǋL								*/	/*EN< Appends to an existing file						*/
		FILE_MODE_CREATE,			/*JP< �t�@�C���̐V�K�쐬�i�����̃t�@�C���͏㏑���j		*/	/*EN< Creates a new file always							*/
		FILE_MODE_CREATE_NEW,		/*JP< �t�@�C���̐V�K�쐬�i�㏑���s�j					*/	/*EN< Creates a new file (Can not overwrite)			*/
		FILE_MODE_OPEN,				/*JP< �����t�@�C���̃I�[�v��							*/	/*EN< Opens an existing file							*/
		FILE_MODE_OPEN_OR_CREATE,	/*JP< �t�@�C���̃I�[�v���i���݂��Ȃ��ꍇ�͐V�K�쐬�j	*/	/*EN< Opens a file if available (Or creates new file)	*/
		FILE_MODE_TRUNCATE,			/*JP< �����t�@�C����0Byte�ɐ؂�l�߂ăI�[�v��			*/	/*EN< Opens a file and truncates it						*/
		/* enum be 4bytes */
		FILE_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
	};
	
	/*JP
	 * \brief �t�@�C���A�N�Z�X���
	 */
	/*EN
	 * \brief Kind of File Access
	 */
	enum FileAccess {
		FILE_ACCESS_READ,			/*JP< �ǂݍ��݂̂�		*/	/*EN< Read Only			*/
		FILE_ACCESS_WRITE,			/*JP< �������݂̂�		*/	/*EN< Write Only		*/
		FILE_ACCESS_READ_WRITE,		/*JP< �ǂݏ���			*/	/*EN< Read and Write	*/
		/* enum be 4bytes */
		FILE_ACCESS_ENUM_BE_SINT32 = 0x7FFFFFFF
	};
	
	/*JP
	 * \brief �V�[�N�J�n�ʒu
	 */
	/*EN
	 * \brief Seek Origin
	 */
	enum SeekOrigin {
		SEEK_FROM_BEGIN,		/*JP< �擪�ʒu����		*/	/*EN< from Top Position			*/
		SEEK_FROM_CURRENT,		/*JP< ���݈ʒu����		*/	/*EN< from Current Position		*/
		SEEK_FROM_END,			/*JP< �I�[�ʒu����		*/	/*EN< from Terminal position	*/
		/* enum be 4bytes */
		SEEK_FROM_ENUM_BE_SINT32 = 0x7FFFFFFF
	};
	
	/*JP
	 * \brief �񓯊������X�e�[�^�X
	 */
	/*EN
	 * \brief Async Status
	 */
	enum AsyncStatus {
		ASYNC_STATUS_STOP,		/*JP< ��~				*/	/*EN< Stop			*/
		ASYNC_STATUS_BUSY,		/*JP< ������			*/	/*EN< Busy			*/
		ASYNC_STATUS_COMPLETE,	/*JP< ����				*/	/*EN< Complete		*/
		ASYNC_STATUS_CANCELED,	/*JP< �L�����Z�����ꂽ	*/	/*EN< Canceled		*/
		ASYNC_STATUS_ERROR,		/*JP< �G���[			*/	/*EN< Error			*/
		/* enum be 4bytes */
		ASYNC_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
	};
	
	/*JP
	 * \brief �v���C�I���e�B
	 */
	/*EN
	 * \brief Priority
	 */
	enum Priority {
		PRIORITY_HIGHEST 		= 10,	/*JP< �ō�		*/	/*EN< Highest		*/
		PRIORITY_ABOVE_NORMAL 	= 9,	/*JP< ��		*/	/*EN< Above normal	*/
		PRIORITY_NORMAL 		= 8,	/*JP< ����		*/	/*EN< Normal		*/
		PRIORITY_BELOW_NORMAL 	= 7,	/*JP< ��		*/	/*EN< Below normal	*/
		PRIORITY_LOWEST 		= 6,	/*JP< �Œ�		*/	/*EN< Lowest		*/
		/* enum be 4bytes */
		PRIORITY_ENUM_BE_SINT32 = 0x7FFFFFFF
	};
}

/***************************************************************************
 *      �ϐ��錾
 *      Prototype Variables
 ***************************************************************************/
namespace CriFs {
	/* �G���[�ȗ��p */
	extern CriError ErrorContainer;
}

/***************************************************************************
 *      �N���X�錾
 *      Prototype Classes
 ***************************************************************************/

/*-------------------------------------------------------------------------*
 *	CriFsManager
 *-------------------------------------------------------------------------*/
/*JP
 * \brief �t�@�C���V�X�e���}�l�[�W��
 * \ingroup FSLIB_BASIC
 * \par ����:
 * �t�@�C���V�X�e���}�l�[�W���Ƃ́A�_���I�ȃf�o�C�X�̂悤�Ȃ��̂�\�����W���[���ł��B<br>
 * �W���I�ȃt�@�C���������W���t�@�C���V�X�e���}�l�[�W����p�b�L���O���ꂽ�t�@�C�����A�N�Z�X����CPK�t�@�C���V�X�e���}�l�[�W���Ȃǂ�����܂��B
 */
/*EN
 * \brief File System Manager
 * \ingroup FSLIB_BASIC
 * \par
 * The File system manager is a module expressing a thing such as a logical device.<br>
 * It has Standard File Manager and CPK File Manager.
 */
class CriFsManager : public CriAllocator
{
public:
	/*JP
	 * \brief �t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̔j��
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * �t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g��j�����܂��B
	 */
	/*EN
	 * \brief Destroy a File System Manager
	 * \param err A CriError information
	 * \par
	 * This function destroys the File System Manager object.
	 */
	virtual void Destroy(CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �t�@�C���T�C�Y�̎擾
	 * \param path �t�@�C���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���̃T�C�Y��Ԃ��܂��B
	 */
	/*EN
	 * \brief Get File size
	 * \param path filepath
	 * \param err A CriError information
	 * \return File size
	 * \par
	 * This function returns size of an appointed file.
	 */
	virtual CriSint64 GetFileSize(const CriChar8 *path, CriError &err=CriFs::ErrorContainer) = 0;

	
	virtual void* GetBinder(CriError &err=CriFs::ErrorContainer) = 0;

protected:
	CriFsManager() {};
	virtual ~CriFsManager() {};
};

/*-------------------------------------------------------------------------*
 *	CriFsManagerStandard
 *-------------------------------------------------------------------------*/
/*JP
 * \brief �W���t�@�C���V�X�e���}�l�[�W��
 * \ingroup FSLIB_BASIC
 * \par ����:
 * �W���t�@�C���V�X�e���}�l�[�W���Ƃ́A�W���I�ȃt�@�C���𑀍삷�邽�߂̃I�u�W�F�N�g�ł��B
 */
/*EN
 * \brief Standard File System Manager Object
 * \ingroup FSLIB_BASIC
 * \par
 * Standard File System Manager is an object to access a standard file.
 */
class CriFsManagerStandard : public CriFsManager
{
public:
	/*JP
	 * \brief �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̍쐬
	 * \param heap CRI Heap �I�u�W�F�N�g
	 * \param err �G���[�R�[�h<br>
	 * \return	�W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g
	 * \par ����:
	 * �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g���쐬���܂��B<br>�쐬�����I�u�W�F�N�g��j������ɂ́A CriFsManagerStandard::Destroy�֐����g�p���܂��B
	 * \sa CriFsManagerStandard::Destroy
	 */
	/*EN
	 * \brief Create a Standard File System Manager
	 * \param heap A CRI Heap object
	 * \param err A CriError information
	 * \return	A Standard File System Manager object
	 * \par
	 * This function creates a Standard File System Manager object.<br>When you destroy this object, you must call CriFsManagerStandard::Destroy function. 
	 * \sa CriFsManagerStandard::Destroy
	 */
	static CriFsManagerStandard* CRIAPI Create(CriHeap heap, CriError &err = CriFs::ErrorContainer);

	/*JP
	 * \brief �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̍쐬
	 * \param heap CRI Heap �I�u�W�F�N�g
	 * \param path �f�B���N�g���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return	�W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g
	 * \par ����:
	 * �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g���쐬���܂��B<br>�쐬�����I�u�W�F�N�g��j������ɂ́A CriFsManagerStandard::Destroy�֐����g�p���܂��B<br>
	 * �w�肳�ꂽ�f�B���N�g�����J�����g�f�B���N�g���ɐݒ肵�܂��B
	 * \sa CriFsManagerStandard::Destroy
	 */
	/*EN
	 * \brief Create a Standard File System Manager
	 * \param heap A CRI Heap object
	 * \param path A Directory path
	 * \param err A CriError information
	 * \return	A Standard File System Manager object
	 * \par
	 * This function creates a Standard File System Manager object.<br>When you destroy this object, you must call CriFsManagerStandard::Destroy function. <br>
	 * This function sets the current directory.
	 * \sa CriFsManagerStandard::Destroy
	 */
	static CriFsManagerStandard* CRIAPI Create(CriHeap heap, const CriChar8 *path, CriError &err = CriFs::ErrorContainer);
	
	/*JP
	 * \brief �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̔j��
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �W���t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g��j�����܂��B
	 */
	/*EN
	 * \brief Destroy a Standard File System Manager object
	 * \param err A CriError information
	 * \par
	 * This function deletes a Standard File System Manager object.
	 */
	virtual void Destroy(CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �J�����g�f�B���N�g���p�X�̐ݒ�
	 * \param path �f�B���N�g���p�X
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * �w�肳�ꂽ�f�B���N�g�����J�����g�f�B���N�g���ɐݒ肵�܂��B<br>
	 * \sa CriFsManagerStandard::GetDirectory
	 */
	/*EN
	 * \brief Set Current Directory
	 * \param path A Directory path
	 * \param err A CriError information
	 * \par
	 * This function sets the current directory.<br>
	 * \sa CriFsManagerStandard::GetDirectory
	 */
	virtual void SetDirectory(const CriChar8 *path, CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �J�����g�f�B���N�g���̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	�J�����g�f�B���N�g���̃p�X
	 * \par ����:
	 * �J�����g�f�B���N�g���̃p�X��Ԃ��܂��B<br>
	 * \sa CriFsManagerStandard::SetDirectory
	 */
	/*EN
	 * \brief Get Current Directory
	 * \param err A CriError information
	 * \return	Path of the current directory
	 * \par
	 * This function returns path of the current directory.<br>
	 * \sa CriFsManagerStandard::SetDirectory
	 */
	virtual const CriChar8 *GetDirectory(CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �t�@�C���T�C�Y�̎擾
	 * \param path �t�@�C���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���̃T�C�Y��Ԃ��܂��B<br>
	 * �{�֐��͊������A�֐��ł��B���A�܂ł�100�~���b���x�̎��Ԃ��|����ꍇ������܂��B
	 */
	/*EN
	 * \brief Get File size
	 * \param path A File path
	 * \param err A CriError information
	 * \return File size
	 * \par
	 * This function returns size of an appointed file.<br>
	 * This function is a completion return function. It may have waiting time of around 100 miliseconds.
	 */
	virtual CriSint64 GetFileSize(const CriChar8 *path, CriError &err=CriFs::ErrorContainer) = 0;

protected:
	CriFsManagerStandard() {};
	virtual ~CriFsManagerStandard() {};
};


/*-------------------------------------------------------------------------*
 *	CriFsManagerCpk
 *-------------------------------------------------------------------------*/
class CriFsGroupLoader;
/*JP
 * \brief CPK�t�@�C���V�X�e���}�l�[�W��
 * \ingroup FSLIB_BASIC
 * \par ����:
 * CPK�t�@�C���V�X�e���}�l�[�W���A�p�b�L���O���ꂽCPK�t�@�C�����������߂̃I�u�W�F�N�g�ł��B
 */
/*EN
 * \brief CPK File System Manager
 * \ingroup FSLIB_BASIC
 * \par
 * CPK File System Manager is an object to access a CPK file.
 */
class CriFsManagerCpk : public CriFsManager
{
public:
	/*JP
	 * \brief �}�E���g�X�e�[�^�X
	 * \par ����:
	 * CPK�t�@�C�����}�E���g����ۂɁA CriFsManagerCpk::GetMountStatus�֐�����Ԃ�X�e�[�^�X�ł��B
	 */
	/*EN
	 * \brief Mount Status
	 * \par
	 * This is status returning from CriFsManagerCpk::GetMountStatus function.
	 */
	enum MountStatus {
		MOUNT_STATUS_STOP	= (0),	/*JP< ��~		*/	/*EN< Stop			*/
		MOUNT_STATUS_BUSY,			/*JP< ������	*/	/*EN< Busy			*/
		MOUNT_STATUS_COMPLETE,		/*JP< ����		*/	/*EN< Complete		*/
		MOUNT_STATUS_ERROR,			/*JP< �G���[	*/	/*EN< Error			*/
		/* enum be 4bytes */
		MOUNT_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
	};

	/*JP
	 * \brief �R���e���c�t�@�C�����\����
	 */
	/*EN
	 * \brief Structure of the content file information
	 */
	struct ContentsFileInfo {
		CriUint32		filesize;		/*JP< �R���e���c�t�@�C���̃t�@�C���T�C�Y	*/	/*EN< File size	of content file			*/
		CriUint64		offset;			/*JP< �R���e���c�t�@�C���̃I�t�Z�b�g�ʒu	*/	/*EN< Offset position of content file	*/
	};

	/*JP
	 * \brief �R���e���c�t�@�C���ڍ׏��\����
	 */
	/*EN
	 * \brief Structure of the content detail file information
	 */
	struct ContentsFileInfoDetail {
		CriChar8		*directory;     /*JP< �R���e���c�t�@�C���̃f�B���N�g����    */	/*EN< Directory name of content file	*/
		CriChar8		*filename;		/*JP< �R���e���c�t�@�C���̃t�@�C�����O      */	/*EN< Filename of content file			*/
		CriUint32		filesize;		/*JP< �R���e���c�t�@�C���̃t�@�C���T�C�Y	*/	/*EN< File size	of content file			*/
		CriUint64		offset;			/*JP< �R���e���c�t�@�C���̃I�t�Z�b�g�ʒu	*/	/*EN< Offset position of content file	*/
	};
		

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�t�@�C�����\����
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Structure of the file information for group
	 * \endif
	 */
	struct GroupFileInfo {
		CriChar8		*directory;     /*JP< �R���e���c�t�@�C���̃f�B���N�g����    */	/*EN< Directory name of content file	*/
		CriChar8		*filename;		/*JP< �R���e���c�t�@�C���̃t�@�C�����O      */	/*EN< Filename of content file			*/
		CriUint32		filesize;		/*JP< �R���e���c�t�@�C���̃t�@�C���T�C�Y	*/	/*EN< File size	of content file			*/
		void		*datapointer;	/*JP< �R���e���c�t�@�C���̃f�[�^�|�C���^	*/	/*EN< Data pointer of content file		*/
		CriUint32		gfinfotag;		/*JP< �R���e���c�t�@�C���̔ėp�^�O          */  /*EN< Tag for content file              */
	};
		
	/*JP
	 * \brief CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̍쐬
	 * \param heap CRI Heap �I�u�W�F�N�g
	 * \param err �G���[�R�[�h<br>
	 * \return	CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g
	 * \par ����:
	 * CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g���쐬���܂��B<br>�쐬�����I�u�W�F�N�g��j������ɂ́A CriFsManagerCpk::Destroy�֐����g�p���܂��B
	 * \sa CriFsManagerCpk::Destroy
	 */
	/*EN
	 * \brief Create a CPK File System Manager object
	 * \param heap A CRI Heap object
	 * \param err A CriError information
	 * \return	A CPK File System Manager object
	 * \par
	 * This function creates a CPK File System Manager object.<br>When you destroy this object, you must call CriFsManagerCpk::Destroy function. 
	 * \sa CriFsManagerCpk::Destroy
	 */
	static CriFsManagerCpk* CRIAPI Create(CriHeap heap, CriError &err = CriFs::ErrorContainer);

	/*JP
	 * \brief CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̍쐬
	 * \param heap CRI Heap �I�u�W�F�N�g
	 * \param path �f�B���N�g���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return	CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g
	 * \par ����:
	 * CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g���쐬���܂��B<br>�쐬�����I�u�W�F�N�g��j������ɂ́A CriFsManagerCpk::Destroy�֐����g�p���܂��B<br>
	 * �w�肳�ꂽ�f�B���N�g�����J�����g�f�B���N�g���ɐݒ肵�܂��B<br>
	 * \sa CriFsManagerCpk::Destroy
	 */
	/*EN
	 * \brief Create a CPK File System Manager object
	 * \param heap A CRI Heap object
	 * \param path A Directory path
	 * \param err A CriError information
	 * \return	A CPK File System Manager object
	 * \par
	 * This function creates a CPK File System Manager object.<br>When you destroy this object, you must call CriFsManagerCpk::Destroy function. <br>
	 * This function sets the current directory.
	 * \sa CriFsManagerCpk::Destroy
	 */
	static CriFsManagerCpk* CRIAPI Create(CriHeap heap, const CriChar8 *path, CriError &err = CriFs::ErrorContainer);

	/*JP
	 * \brief CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g�̔j��
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * CPK�t�@�C���V�X�e���}�l�[�W���I�u�W�F�N�g��j�����܂��B
	 * \sa CriFsManagerCpk::Create
	 */
	/*EN
	 * \brief Destroy a CPK File System Manager
	 * \param err A CriError information
	 * \par
	 * This function destroys a CPK File System Manager object.
	 * \sa CriFsManagerCpk::Create
	 */
	virtual void Destroy(CriError &err=CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �J�����g�f�B���N�g���p�X�̐ݒ�
	 * \param path �f�B���N�g���p�X
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * �w�肳�ꂽ�f�B���N�g�����J�����g�f�B���N�g���ɐݒ肵�܂��B<br>
	 * \sa CriFsManagerCpk::GetDirectory
	 */
	/*EN
	 * \brief Set Current Directory
	 * \param path A Directory path
	 * \param err A CriError information
	 * \par
	 * This function sets the current directory.<br>
	 * \sa CriFsManagerCpk::GetDirectory
	 */
	virtual void SetDirectory(const CriChar8 *path, CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �J�����g�f�B���N�g���̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	�J�����g�f�B���N�g���̃p�X
	 * \par ����:
	 * �J�����g�f�B���N�g���̃p�X��Ԃ��܂��B<br>
	 * \sa CriFsManagerCpk::SetDirectory
	 */
	/*EN
	 * \brief Get Current Directory
	 * \param err A CriError information
	 * \return	Path of the current directory
	 * \par
	 * This function returns path of the current directory.<br>
	 * \sa CriFsManagerCpk::SetDirectory
	 */
	virtual const CriChar8 *GetDirectory(CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �t�@�C���T�C�Y�̎擾
	 * \param path �t�@�C���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���̃T�C�Y��Ԃ��܂��B<br>
	 * ���k����Ă���ꍇ�́A�W�J��̃T�C�Y��Ԃ��܂��B<br>
	 * �{�֐��͊������A�֐��ł��B�������A�҂����Ԃ͂قƂ�ǂ���܂���B
	 */
	/*EN
	 * \brief Get File size
	 * \param path filepath
	 * \param err A CriError information
	 * \return File size
	 * \par
	 * This function returns size of an appointed file.<br>
	 * When file is compressed, this function returns decompressed file size.
	 * This function is completion return. There is not waiting time.
	 */
	virtual CriSint64 GetFileSize(const CriChar8 *path, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �t�@�C���T�C�Y�̎擾
	 * \param id �t�@�C��ID
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C��ID�����ɃT�C�Y��Ԃ��܂��B<br>
	 * ���k����Ă���ꍇ�́A�W�J��̃T�C�Y��Ԃ��܂��B<br>
	 * �{�֐��͊������A�֐��ł��B�������A�҂����Ԃ͂قƂ�ǂ���܂���B
	 */
	/*EN
	 * \brief Get File size
	 * \param id file ID
	 * \param err A CriError information
	 * \return File size
	 * \par
	 * This function returns size of an appointed file ID.<br>
	 * When file is compressed, this function returns decompressed file size.
	 * This function is completion return. There is not waiting time.
	 */
	virtual CriSint64 GetFileSize(CriUint16 id, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �p�b�N�t�@�C���T�C�Y�̎擾
	 * \param path �t�@�C���p�X
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���̃p�b�N���ꂽ�t�@�C���T�C�Y��Ԃ��܂��B<br>
	 * �t�@�C�������k����Ă���΁A���k���ꂽ�t�@�C����Ԃ��܂��B
	 * �{�֐��͊������A�֐��ł��B�������A�҂����Ԃ͂قƂ�ǂ���܂���B
	 */
	/*EN
	 * \brief Get Packed File size
	 * \param path filepath
	 * \param err A CriError information
	 * \return Packed file size
	 * \par
	 * This function returns size of an appointed file.<br>
	 * When file is compressed, this function returns compressed file size.
	 * This function is completion return. There is not waiting time.
	 */
	virtual CriSint64 GetPackedFileSize(const CriChar8 *path, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �p�b�N�t�@�C���T�C�Y�̎擾
	 * \param id �t�@�C��ID
	 * \param err �G���[�R�[�h<br>
	 * \return�@�t�@�C���T�C�Y
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C��ID�����Ƀp�b�N���ꂽ�t�@�C���T�C�Y��Ԃ��܂��B<br>
	 * �t�@�C�������k����Ă���΁A���k���ꂽ�t�@�C����Ԃ��܂��B
	 * �{�֐��͊������A�֐��ł��B�������A�҂����Ԃ͂قƂ�ǂ���܂���B
	 */
	/*EN
	 * \brief Get Packed File size
	 * \param id file ID
	 * \param err A CriError information
	 * \return Packed file size
	 * \par
	 * This function returns size of an appointed file ID.<br>
	 * When file is compressed, this function returns compressed file size.
	 * This function is completion return. There is not waiting time.
	 */
	virtual CriSint64 GetPackedFileSize(CriUint16 id, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief CPK�t�@�C���̃}�E���g
	 * \param	manager �t�@�C���V�X�e���}�l�[�W��
	 * \param	path �t�@�C���p�X
	 * \param	offset �t�@�C���I�t�Z�b�g
	 * \param	size �t�@�C���T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CPK�t�@�C���̃}�E���g���s���܂��B<br>�{�֐��͊������A�ł��B�}�E���g�����̏�Ԃ𒲂ׂ邽�߂ɂ́A CriFsManagerCpk::MountStatus�֐����g�p���Ă��������B
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	/*EN
	 * \brief Mount the CPK File
	 * \param	manager A File System Manager
	 * \param	path A CPK File path
	 * \param	offset A File offset
	 * \param	size A Size of file
	 * \param 	err A CriError information
	 * \par
	 * This function mounts the CPK File.<br>
	 * This function is return immediately. You use CriFsManagerCpk::GetMountStatus function to examine mounting completion.<br>
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	virtual void MountCpkFile(CriFsManager *manager, const CriChar8 *path, CriSint64 offset, CriSint64 size, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief CPK�t�@�C���̃}�E���g(�t�@�C���I�t�Z�b�g�A�T�C�Y�̏ȗ�)
	 * \param	manager �t�@�C���V�X�e���}�l�[�W��
	 * \param	path �t�@�C���p�X
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CPK�t�@�C���̃}�E���g���s���܂��B<br>�{�֐��͊������A�ł��B�}�E���g�����̏�Ԃ𒲂ׂ邽�߂ɂ́A CriFsManagerCpk::MountStatus�֐����g�p���Ă��������B
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	/*EN
	 * \brief Mount the CPK File (abbreviation File offset and size)
	 * \param	manager A File System Manager
	 * \param	path A CPK File path
	 * \param 	err A CriError information
	 * \par
	 * This function mounts the CPK File.<br>
	 * This function is return immediately. You use CriFsManagerCpk::GetMountStatus function to examine mounting completion.<br>
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	virtual void MountCpkFile(CriFsManager *manager, const CriChar8 *path, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief CPK�t�@�C���̃}�E���g(�t�@�C���V�X�e���}�l�[�W���̏ȗ�)
	 * \param	path �t�@�C���p�X
	 * \param	offset �t�@�C���I�t�Z�b�g
	 * \param	size �t�@�C���T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CPK�t�@�C���̃}�E���g���s���܂��B<br>�{�֐��͊������A�ł��B�}�E���g�����̏�Ԃ𒲂ׂ邽�߂ɂ́A CriFsManagerCpk::MountStatus�֐����g�p���Ă��������B
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	/*EN
	 * \brief Mount the CPK File (abbreviation of File System Manager)
	 * \param	path A CPK File path
	 * \param	offset A File offset
	 * \param	size A Size of file
	 * \param 	err A CriError information
	 * \par
	 * This function mounts the CPK File.<br>
	 * This function is return immediately. You use CriFsManagerCpk::GetMountStatus function to examine mounting completion.<br>
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	virtual void MountCpkFile(const CriChar8 *path, CriSint64 offset, CriSint64 size, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief CPK�t�@�C���̃}�E���g(�t�@�C���I�t�Z�b�g�A�T�C�Y�A�t�@�C���V�X�e���}�l�[�W���̏ȗ�)
	 * \param	path �t�@�C���p�X
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CPK�t�@�C���̃}�E���g���s���܂��B<br>�{�֐��͊������A�ł��B�}�E���g�����̏�Ԃ𒲂ׂ邽�߂ɂ́A CriFsManagerCpk::MountStatus�֐����g�p���Ă��������B
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	/*EN
	 * \brief Mount the CPK File (abbreviation of File System Manager and File offset, File size)
	 * \param	path A CPK File path
	 * \param 	err A CriError information
	 * \par
	 * This function mounts the CPK File.<br>
	 * This function is return immediately. You use CriFsManagerCpk::GetMountStatus function to examine mounting completion.<br>
	 * \sa CriFsManagerCpk::GetMountStatus
	 */
	virtual void MountCpkFile(const CriChar8 *path, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �}�E���g�X�e�[�^�X�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	MountStatus �}�E���g�X�e�[�^�X
	 * \par ����:
	 * CPK�t�@�C���̃}�E���g�X�e�[�^�X���擾���܂��B
	 * \sa CriFsManagerCpk::MountCpkFile
	 */
	/*EN
	 * \brief Get Mount status
	 * \param err A CriError information
	 * \return	MountStatus Mounting status
	 * \par
	 * This function returns Mounting status.
	 * \sa CriFsManagerCpk::MountCpkFile
	 */
	virtual MountStatus GetMountStatus(CriError &err = CriFs::ErrorContainer) = 0;

	/* �R���e���c�t�@�C�����̎擾 */	
	/*JP
	 * \brief �R���e���c�t�@�C�����̎擾
	 * \param cfinf ContentsFileInfo* �R���e���c�t�@�C�����\����
	 * \param path �R���e���c�t�@�C����
	 * \param err �G���[�R�[�h
	 * \return	CriBool �擾�ɐ����������ۂ�
	 * \par ����:
	 * �R���e���c�t�@�C�������w�肵�ď����擾���܂��B
	 */
	/*EN
	 * \brief Get Information of a contents file
	 * \param cfinf ContentsFileInfo* Structure of content file information
	 * \param path A Content file name
	 * \param err A CriError information
	 * \return	CriBool Result.
	 * \par
	 * This function gets a content file information.
	 */
	virtual CriBool GetContentsFileInfo(ContentsFileInfo *cfinf, const CriChar8 *path, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �R���e���c�t�@�C�����̎擾
	 * \param cfinf ContentsFileInfo* �R���e���c�t�@�C�����\����
	 * \param id ID
	 * \param err �G���[�R�[�h
	 * \return	CriBool �擾�ɐ����������ۂ�
	 * \par ����:
	 * �R���e���c�t�@�C�������w�肵�ď����擾���܂��B
	 */
	/*EN
	 * \brief Get the Information of a contents file
	 * \param cfinf ContentsFileInfo* Structure of content file information
	 * \param id ID
	 * \param err A CriError information
	 * \return	CriBool Result.
	 * \par
	 * This function gets a content file information.
	 */
	virtual CriBool GetContentsFileInfo(ContentsFileInfo *cfinf, CriUint16 id, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �R���e���c�t�@�C���ڍ׏��̎擾
	 * \param cfdinf ContentsFileInfoDetail* �R���e���c�t�@�C�����\����
	 * \param index �C���f�b�N�X�ԍ�
	 * \param err �G���[�R�[�h
	 * \return	CriBool �擾�ɐ����������ۂ�
	 * \par ����:
	 * �C���f�b�N�X�ԍ����w�肵�ăR���e���c�����擾���܂��B
	 */
	/*EN
	 * \brief Get the Detail information of a contents file
	 * \param cfdinf ContentsFileInfoDetail* Structure of content file information
	 * \param index A number of index
	 * \param err A CriError information
	 * \return	CriBool Result.
	 * \par
	 * This function gets a content file information by number of index.
	 */
	virtual CriBool GetContentsFileInfoDetails(ContentsFileInfoDetail *cfdinf, CriSint32 index, CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief CPK�t�@�C���p�X���̎擾
	 * \param err �G���[�R�[�h
	 * \return	CriChar8 * CPK�t�@�C���p�X��
	 * \par ����:
	 * CPK�t�@�C���p�X�����擾���܂�
	 */
	/*EN
	 * \brief Get the CPK file path
	 * \param err A CriError information
	 * \return	CriChar8 * CPK filename path
	 * \par
	 * This function gets a CPK file path string.
	 */
	virtual	const CriChar8 *GetCpkFilePath(CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �R���e���c�t�@�C�����̎擾
	 * \param err �G���[�R�[�h
	 * \return	�R���e���c�t�@�C����
	 * \par ����:
	 * �R���e���c�t�@�C���̐����擾���܂��B
	 */
	/*EN
	 * \brief Get the number of content
	 * \param err A CriError information
	 * \return	The number of content.
	 * \par
	 * This function gets number of content.
	 */
	virtual CriSint32 GetNumberOfContents(CriError &err = CriFs::ErrorContainer) = 0;
	
	// �݊����ێ��̂���
	CriSint32 GetNumContents(CriError &err = CriFs::ErrorContainer) { return GetNumberOfContents(err); }

	/*JP
	 * \if fsgroup
	 * \brief CriFsGroupLoader�I�u�W�F�N�g�̍쐬
	 * \param	groupname �O���[�v��
	 * \param	attrname ������
	 * \param	err �G���[�R�[�h
	 * \return	�O���[�v���[�_�I�u�W�F�N�g
	 * \par ����:
	 * CriFsGroupLoader�I�u�W�F�N�g���쐬���܂��B
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Create a CriFsGroupLoader object
	 * \param	groupname A Name of group
	 * \param	attrname A Name of attribute
	 * \param err A CriError information
	 * \return	A CriFsGroupLoader object
	 * \par
	 * This function creates a CriFsGroupLoader object.
	 * \endif
	 */
	 virtual CriFsGroupLoader *CreateGroupLoader(const CriChar8 *groupname, const CriChar8 *attrname, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief CriFsGroupLoader�I�u�W�F�N�g�̔j��
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CriFsLoader�I�u�W�F�N�g��j�����܂��B
	 * \sa CriFsManagerCpk::CreateGroupLoader
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Destroy CriFsGroupLoader object
	 * \param err A CriError information
	 * \par
	 * This function deletes the CriFsGroupLoader object.
	 * \sa CriFsManagerCpk::CreateGroupLoader
	 * \endif
	 */
	 virtual void DestroyGroupLoader(CriFsGroupLoader *grouploader, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�t�@�C�����̎擾
	 * \param	groupname �O���[�v��
	 * \param	attrname ������
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �O���[�v�ɑ�����t�@�C�������擾���܂��B
	 * \sa CriFsManagerCpk::GetTotalGroupDataSize
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get the number of files in group
	 * \param	groupname A Name of group
	 * \param	attrname A Name of attribute
	 * \param err A CriError information
	 * \par
	 * This function gets number of files in group.
	 * \sa CriFsManagerCpk::GetTotalGroupDataSize
	 * \endif
	 */
	 virtual CriSint32 GetNumberOfGroupFiles(const CriChar8 *groupname, const CriChar8 *attrname, CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�f�[�^�T�C�Y�̎擾
	 * \param	groupname �O���[�v��
	 * \param	attrname ������
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �O���[�v���[�h�ɕK�v�ȃf�[�^�T�C�Y���擾���܂��B<br>
	 * �A���C�����g�Ȃǂ��������ꂽ�f�[�^�T�C�Y�ƂȂ�܂��B
	 * \sa CriFsManagerCpk::GetNumberOfGroupFiles
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get the size of data in group
	 * \param	groupname A Name of group
	 * \param	attrname A Name of attribute
	 * \param err A CriError information
	 * \par
	 * This function gets size of data in group. Alignment is included in data size.
	 * \sa CriFsManagerCpk::GetNumberOfGroupFiles
	 * \endif
	 */
	 virtual CriSint64 GetTotalGroupDataSize(const CriChar8 *groupname, const CriChar8 *attrname, CriError &err = CriFs::ErrorContainer) = 0;

protected:
	CriFsManagerCpk() {};
	virtual ~CriFsManagerCpk() {};
};

/*-------------------------------------------------------------------------*
 *	CriFsGroupLoader
 *-------------------------------------------------------------------------*/
/*JP
 * \if fsgroup
 * \brief �O���[�v���[�_
 * \ingroup FSLIB_BASIC
 * \par ����:
 * CriFsGroupLoader��CPK�t�@�C���̃O���[�v���[�h���s�����߂̃I�u�W�F�N�g�ł��B
 * \endif
 */
/*EN
 * \if fsgroup
 * \brief Group Loader
 * \ingroup FSLIB_BASIC
 * \par
 * CriFsGroupLoader is an object for performing the group load of a CPK file.
 * \endif
 */
class CriFsGroupLoader
{
public:
	enum Status {
		LOAD_STATUS_STOP=(0),	/*JP< ��~��		*/	/*EN< Stopping			*/
		LOAD_STATUS_LOADING,	/*JP< ���[�h��		*/	/*EN< Loading			*/
		LOAD_STATUS_COMPLETE,	/*JP< ����			*/	/*EN< Complete			*/
		LOAD_STATUS_ERROR,		/*JP< �G���[		*/	/*EN< Error				*/
		/* enum be 4bytes */
		LOAD_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
	};

	/*JP
	 * \if fsgroup
	 * \brief �f�[�^�̃��[�h
	 * \param	buffer �o�b�t�@�ւ̃|�C���^
	 * \param	buffer_size �o�b�t�@�̃T�C�Y
	 * \param	gfinf[] CriFsManagerCpk::GroupFileInfo�\���̂̔z��
	 * \param	numgfinf �z��̐�
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �O���[�v�����ꂽ�����t�@�C���f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
	 * �t�@�C��������CriFsManagerCpk::GroupFileInfo�\���̂̔z����w�肷��K�v������܂��B<br>
	 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� CriFsGroupLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * \sa CriFsGroupLoader::GetStatus
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Loading File Data
	 * \param	buffer		A Reading buffer
	 * \param	buffer_size A Size of Reading buffer
	 * \param	gfinf[]		A CriFsManagerCpk::GroupFileInfo array of structures
	 * \param	numgfinf	A Number of structures
	 * \param 	err 		A CriError information
	 * \par
	 * This function starts loading of the group of files.<br>
	 * This function is return immediately.
	 * You use an CriFsGroupLoader::GetStatus function to examine reading completion.<br>
	 * \sa CriFsGroupLoader::GetStatus
	 * \endif
	 */
	virtual CriSint32 LoadBulk(void *buffer, CriSint64 buffer_size, CriFsManagerCpk::GroupFileInfo gfinf[], CriSint32 numgfinf, CriError &err=CriFs::ErrorContainer) = 0;

	 /*JP
	 * \if fsgroup
	 * \brief ���[�h�X�e�[�^�X�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	CriFsGroupLoader::Status ���[�h�X�e�[�^�X
	 * \par ����:
	 * ���[�h�X�e�[�^�X���擾���܂��B
	 * \image html fs_state_transition.png �O���[�v���[�_�̏�ԑJ�ڐ}
	 */
	/*EN
	 * \brief Get Loading status
	 * \param err A CriError information
	 * \return	CriFsGroupLoader::Status Loading Status
	 * \par
	 * This function returns Loading status.
	 * \image html fs_state_transition.png Transition of Group Loader Status
	 * \endif
	 */
	virtual CriFsGroupLoader::Status GetStatus(CriError &err=CriFs::ErrorContainer) = 0;

	 /*JP
	 * \if fsgroup
	 * \brief ���[�h���ꂽ�t�@�C�����̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	���[�h���ꂽ�t�@�C����
	 * \par ����:
	 * CriFsGroupLoader::LoadBulk �֐��Ŋ��ɓǂݍ��܂ꂽ�t�@�C������Ԃ��܂�
	 */
	/*EN
	 * \brief Get Loaded files
	 * \param err A CriError information
	 * \return	The loaded files
	 * \par
	 * This function returns Loaded number of files.
	 * \endif
	 */
	virtual CriSint32 GetLoadedFiles(CriError &err=CriFs::ErrorContainer) = 0;


	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�t�@�C�����̎擾
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �O���[�v�ɑ�����t�@�C�������擾���܂��B
	 * \sa CriFsGroupLoader::GetTotalGroupDataSize
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get the number of files in group
	 * \param err A CriError information
	 * \par
	 * This function gets number of files in group.
	 * \sa CriFsGroupLoader::GetTotalGroupDataSize
	 * \endif
	 */
	 virtual CriSint32 GetNumberOfGroupFiles(CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�f�[�^�T�C�Y�̎擾
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �O���[�v���[�h�ɕK�v�ȃf�[�^�T�C�Y���擾���܂��B<br>
	 * �A���C�����g�Ȃǂ��������ꂽ�f�[�^�T�C�Y�ƂȂ�܂��B
	 * \sa CriFsGroupLoader::GetNumberOfGroupFiles
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get the size of data in group
	 * \param err A CriError information
	 * \par
	 * This function gets size of data in group. Alignment is included in data size.
	 * \sa CriFsGroupLoader::GetNumberOfGroupFiles
	 * \endif
	 */
	 virtual CriSint64 GetTotalGroupDataSize(CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief CriFsManagerCpk::GroupFileInfo�\���̂̔z��C���f�N�X�̎擾
	 * \param	gfinf[] CriFsManagerCpk::GroupFileInfo�\���̂̔z��
	 * \param	numgfinf �z��̐�
	 * \param	fpath �t�@�C�����t���p�X
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C����CriFsManagerCpk::GroupFileInfo�\���̂̔z��C���f�N�X���擾���܂��B<br>
	 * �t�@�C�����̓t���p�X���Ŏw�肵�܂��B<br>
	 * �w�肳�ꂽ�t�@�C����������Ȃ��ꍇ�́A�Ԓl��-1�ƂȂ�܂��B
	 * \sa CriFsGroupLoader::GetNumberOfGroupFiles
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get the index of file in CriFsManagerCpk::GroupFileInfo array of structures.
	 * \param err A CriError information
	 * \param	gfinf[]		A CriFsManagerCpk::GroupFileInfo array of structures
	 * \param	numgfinf	A Number of structures
	 * \param	fpath    	A Filename path
	 * \param 	err 		A CriError information
	 * \par
	 * This function gets index of file in CriFsManagerCpk::GroupFileInfo array of structure.
	 * \sa CriFsManagerCpk::GroupFileInfo
	 * \endif
	 */
	 virtual CriSint32 GetGroupFileInfoIndex(const CriFsManagerCpk::GroupFileInfo gfinf[], CriSint32 numgfinf, const CriChar8 *fpath, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v���̎擾
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * ���[�_�[�ň����O���[�v�̃O���[�v�����擾���܂��B
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get a name of group.
	 * \param err A CriError information.
	 * \par
	 * This function gets a name of group.
	 * \endif
	 */
 	 virtual CriChar8 *GetGroupName(CriError &err = CriFs::ErrorContainer) = 0;

	/*JP
	 * \if fsgroup
	 * \brief �O���[�v�����̎擾
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * ���[�_�[�ň����O���[�v�̃O���[�v�������擾���܂��B
	 * \endif
	 */
	/*EN
	 * \if fsgroup
	 * \brief Get a attribute of group.
	 * \param err A CriError information.
	 * \par
	 * This function gets a attribute of groupp.
	 * \endif
	 */
 	 virtual CriChar8 *GetAttributeName(CriError &err = CriFs::ErrorContainer) = 0;

protected:
	CriFsGroupLoader() {};
	virtual ~CriFsGroupLoader() {};
};

/*-------------------------------------------------------------------------*
 *	CriFsLoader
 *-------------------------------------------------------------------------*/
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
 * CriFsLoader is reading module.It is very simple and easy.
 */
class CriFsLoader : public CriAllocator
{
public:
	/*JP
	 * \brief ���[�h�X�e�[�^�X
	 */
	/*EN
	 * \brief Loading Status
	 */
	 enum Status {
		LOAD_STATUS_STOP=(0),	/*JP< ��~��		*/	/*EN< Stopping			*/
		LOAD_STATUS_LOADING,	/*JP< ���[�h��		*/	/*EN< Loading			*/
		LOAD_STATUS_COMPLETE,	/*JP< ����			*/	/*EN< Complete			*/
		LOAD_STATUS_ERROR,		/*JP< �G���[		*/	/*EN< Error				*/
		/* enum be 4bytes */
		LOAD_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
	};

	/*JP
	 * \brief �G���[�R�[�h
	 */
	/*EN
	 * \brief Error Code
	 */
	enum ErrorCode {
		ERROR_CODE_OK=(0),		/*JP< ����							*/	/*EN< No Error					*/
		ERROR_CODE_CANT_OPEN,	/*JP< �t�@�C���I�[�v���ł��Ȃ�		*/	/*EN< Can't Open a file			*/
		ERROR_CODE_READ_ERROR,	/*JP< �ǂݍ��݃G���[				*/	/*EN< Reading error				*/
		/* enum be 4bytes */
		ERROR_CODE_ENUM_BE_SINT32 = 0x7FFFFFFF
	};

	/*JP
	 * \brief CriFsLoader�I�u�W�F�N�g�̍쐬
	 * \param heap CRI Heap �I�u�W�F�N�g
	 * \param err �G���[�R�[�h
	 * \return	CriFsLoader �I�u�W�F�N�g
	 * \par ����:
	 * CriFsLoader�I�u�W�F�N�g���쐬���܂��B
	 */
	/*EN
	 * \brief Create a CriFsLoader
	 * \param heap A CRI Heap object
	 * \param err A CriError information
	 * \return	A CriFsLoader object
	 * \par
	 * This function creates a CriFsLoader object.
	 */
	static CriFsLoader *Create(CriHeap heap, CriError &err=CriFs::ErrorContainer);
	
	/*JP
	 * \brief CriFsLoader�I�u�W�F�N�g�̔j��
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * CriFsLoader�I�u�W�F�N�g��j�����܂��B
	 * \sa CriFsLoader::Create
	 */
	/*EN
	 * \brief Destroy CriFsLoader object
	 * \param err A CriError information
	 * \par
	 * This function deletes the CriFsLoader object.
	 * \sa CriFsLoader::Create
	 */
	virtual void Destroy(CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �v���C�I���e�B�̎擾
	 * \param	err �G���[�R�[�h
	 * \return	CriFs::Priority �ǂݍ��݃v���C�I���e�B
	 * \par ����:
	 * �f�[�^���[�h�̃v���C�I���e�B���擾���܂��B
	 * \sa CriFsLoader::SetPriority
	 */
	/*EN
	 * \brief Get a Priority
	 * \param err A CriError information
	 * \return CriFs::Priority Reading Priority
	 * \par
	 * This function gets Loading Priority.
	 * \sa CriFsLoader::SetPriority
	 */
	virtual CriFs::Priority GetPriority(CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �v���C�I���e�B�̐ݒ�
	 * \param	priority �ǂݍ��݃v���C�I���e�B
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �f�[�^���[�h�̃v���C�I���e�B��ݒ肵�܂��B
	 * \sa CriFsLoader::GetPriority
	 */
	/*EN
	 * \brief Set a Priority
	 * \param priority Priority of the loader
	 * \param err A CriError information
	 * \par
	 * This function sets Loading Priority.
	 * \sa CriFsLoader::GetPriority
	 */
	virtual void SetPriority(CriFs::Priority priority, CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �P�ʓǂݍ��݃T�C�Y�̐ݒ�
	 * \param size �P�ʓǂݍ��݃T�C�Y
	 * \param err �G���[�R�[�h
	 * \par ����:
	 * �P�ʓǂݍ��݃T�C�Y��ݒ肵�܂��B
	 * CriFsLoader�́A�傫�ȃT�C�Y�̃��[�h�v������������ہA����𕡐��̏����ȒP�ʂ̃��[�h�����ɕ������ĘA�����s���܂��B<br>
	 * ���̊֐����g�p���邱�ƂŒP�ʃ��[�h�����T�C�Y��ύX���邱�Ƃ��\�ł��B<br>
	 * ���[�h�v���̃L�����Z����A���v���C�I���e�B�̃��[�h�����̊��荞�ݓ��́A�P�ʃ��[�h�T�C�Y���E�ł̂ݏ�������܂��B<br>
	 * ���̂��߁A���j�b�g�T�C�Y���������ݒ肷��ƁAI/O�����̃��X�|���X�����サ�܂��B�t�ɁA���j�b�g�T�C�Y��傫���ݒ肷��ƁA�t�@�C���P�ʂ̓ǂݍ��ݑ��x�����サ�܂��B
	 * \sa CriFsLoader::GetReadUnitSize
	 */
	/*EN
	 * \brief Get Read Unit Size
	 * \param err The size of read unit
	 * \param err A CriError information
	 * \par
	 * When reading large data, CriFsLoader divides it into multiple small unit, and reads them.<br>
	 * This function sets the size of read units.<br>
	 * Interrupt request, such as cancel of current read process, can be applied only at unit boundary.<br>
	 * Therefore, if the unit size is smaller, the response of I/O process becomes better. If the unit size is larger, the speed of single reading becomes better.
	 * \sa CriFsLoader::GetReadUnitSize
	 */
	virtual void SetReadUnitSize(CriSint64 size, CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �P�ʓǂݍ��݃T�C�Y�̎擾
	 * \param err �G���[�R�[�h
	 * \return �P�ʓǂݍ��݃T�C�Y
	 * \par ����:
	 * �P�ʓǂݍ��݃T�C�Y���擾���܂��B
	 * \sa CriFsReader::SetReadUnitSize
	 */
	/*EN
	 * \brief Get Read Unit Size
	 * \param err A CriError information
	 * \return read unit size
	 * \par
	 * This function gets the size of read units.
	 * \sa CriFsReader::SetReadUnitSize
	 */
	virtual CriSint64 GetReadUnitSize(CriError &err = CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief �f�[�^�̃��[�h
	 * \param	manager �t�@�C���V�X�e���}�l�[�W��
	 * \param	path �t�@�C���p�X��
	 * \param	offset �t�@�C���̐擪����̃I�t�Z�b�g�ʒu
	 * \param	read_size ���[�h�T�C�Y
	 * \param	buffer �o�b�t�@�ւ̃|�C���^
	 * \param	buffer_size �o�b�t�@�̃T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���V�X�e���}�l�[�W���ƃt�@�C�����ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
	 * �t�@�C������ offset �o�C�g�ڂ���Aread_size �o�C�g���ǂݍ��݂܂��B<br>
	 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� CriFsLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * \sa CriFsLoader::GetStatus
	 */
	/*EN
	 * \brief Loading File Data
	 * \param	manager		A File System Manager
	 * \param	path 		A File path
	 * \param	offset		A Seek position from top of file
	 * \param	read_size	A Reading size
	 * \param	buffer		A Reading buffer
	 * \param	buffer_size A Size of Reading buffer
	 * \param 	err 		A CriError information
	 * \par
	 * This function starts loading of data by appointed File path and the File System Manager.<br>
	 * This function is return immediately.
	 * You use an CriFsLoader::GetStatus function to examine reading completion.<br>
	 * \sa CriFsLoader::GetStatus
	 */
	virtual void Load(CriFsManager *manager, const CriChar8 *path,
		CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size,
		CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �f�[�^�̃��[�h(�V�[�N�ʒu�ƃT�C�Y�̏ȗ�)
	 * \param	manager �t�@�C���V�X�e���}�l�[�W��
	 * \param	path �t�@�C���p�X��
	 * \param	buffer �o�b�t�@�ւ̃|�C���^
	 * \param	buffer_size �o�b�t�@�̃T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽ�t�@�C���V�X�e���}�l�[�W���ƃt�@�C���ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
	 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� CriFsLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * - �t�@�C���̐擪����ǂݍ��݂��J�n���܂��B<br>
	 * \sa CriFsLoader::GetStatus
	 */
	/*EN
	 * \brief Loading File Data(Abbreviation of Seek Position)
	 * \param	manager		A File System Manager
	 * \param	path 		A File path
	 * \param	buffer		A Reading buffer
	 * \param	buffer_size A Size of Reading buffer
	 * \param 	err 		A CriError information
	 * \par
	 * This function starts loading of data by appointed File path and the File System Manager.<br>
	 * This function is return immediately. You use an CriFsLoader::GetStatus function to examine reading completion.<br>
	 * - This function starts reading from the top of file.<br>
	 * \sa CriFsLoader::GetStatus
	 */
	virtual void Load(CriFsManager *manager, const CriChar8 *path,
		void *buffer, CriSint64 buffer_size, CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �f�[�^�̃��[�h (CPK�t�@�C�����̃t�@�C�����ʎq���w��)
	 * \param	manager CPK�t�@�C���V�X�e���}�l�[�W��
	 * \param	fid �t�@�C�����ʎq
	 * \param	offset �t�@�C���̐擪����̃I�t�Z�b�g�ʒu
	 * \param	read_size ���[�h�T�C�Y
	 * \param	buffer �o�b�t�@�ւ̃|�C���^
	 * \param	buffer_size �o�b�t�@�̃T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽCPK�t�@�C���V�X�e���}�l�[�W���ƃt�@�C�����ʎq�ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
	 * �t�@�C������ offset �o�C�g�ڂ���Aread_size �o�C�g���ǂݍ��݂܂��B<br>
	 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� CriFsLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * \sa CriFsLoader::GetStatus
	 */
	/*EN
	 * \brief Loading File Data (Using File ID in CPK File)
	 * \param	manager		A File System Manager
	 * \param	file 		A File ID
	 * \param	offset		A Seek position from top of file
	 * \param	read_size	A Reading size
	 * \param	buffer		A Reading buffer
	 * \param	buffer_size A Size of Reading buffer
	 * \param 	err 		A CriError information
	 * \par
	 * This function starts loading of data by appointed File ID and the File System Manager of CPK.<br>
	 * This function is return immediately.
	 * You use an CriFsLoader::GetStatus function to examine reading completion.<br>
	 * \sa CriFsLoader::GetStatus
	 */
	virtual void Load(CriFsManagerCpk *manager, CriUint32 fid,
		CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size,
		CriError &err=CriFs::ErrorContainer) = 0;

	/*JP
	 * \brief �f�[�^�̃��[�h(�V�[�N�ʒu�ƃT�C�Y�̏ȗ��ACPK�t�@�C�����̃t�@�C�����ʎq���w��)
	 * \param	manager CPK�t�@�C���V�X�e���}�l�[�W��
	 * \param	path �t�@�C���p�X��
	 * \param	buffer �o�b�t�@�ւ̃|�C���^
	 * \param	buffer_size �o�b�t�@�̃T�C�Y
	 * \param	err �G���[�R�[�h
	 * \par ����:
	 * �w�肳�ꂽCPK�t�@�C���V�X�e���}�l�[�W���ƃt�@�C�����ʎq�ŁA�f�[�^�̓ǂݍ��݂��J�n���܂��B<br>
	 * �{�֐��͑������A�֐��ł��B<br>���[�h�̊�����Ԃ��擾����ɂ� CriFsLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * - �t�@�C���̐擪����ǂݍ��݂��J�n���܂��B<br>
	 * \sa CriFsLoader::GetStatus
	 */
	/*EN
	 * \brief Loading File Data(Abbreviation of Seek Position, Using File ID in CPK File)
	 * \param	manager		A File System Manager
	 * \param	path 		A File path
	 * \param	buffer		A Reading buffer
	 * \param	buffer_size A Size of Reading buffer
	 * \param 	err 		A CriError information
	 * \par
	 * This function starts loading of data by appointed File ID in CPK File and the File System Manager CPK.<br>
	 * This function is return immediately. You use an CriFsLoader::GetStatus function to examine reading completion.<br>
	 * - This function starts reading from the top of file.<br>
	 * \sa CriFsLoader::GetStatus
	 */
	virtual void Load(CriFsManagerCpk *manager, CriUint32 fid,
		void *buffer, CriSint64 buffer_size, CriError &err=CriFs::ErrorContainer) = 0;

	 /*JP
	 * \brief ���[�h�X�e�[�^�X�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	CriFsLoader::Status ���[�h�X�e�[�^�X
	 * \par ����:
	 * ���[�h�X�e�[�^�X���擾���܂��B
	 * \image html fs_state_transition.png �t�@�C���V�X�e�����[�_�̏�ԑJ�ڐ}
	 * \sa CriFsLoader::GetErrorCode
	 */
	/*EN
	 * \brief Get Loading status
	 * \param err A CriError information
	 * \return	CriFsLoader::Status Loading Status
	 * \par
	 * This function returns Loading status.
	 * \image html fs_state_transition.png Transition of File System Loader Status
	 * \sa CriFsLoader::GetErrorCode
	 */
	virtual CriFsLoader::Status GetStatus(CriError &err=CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief ���[�_�G���[�R�[�h�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	CriFsLoader::ErrorCode ���[�_�G���[�R�[�h
	 * \par ����:
	 * ���[�_�G���[�R�[�h���擾���܂��B<br>
	 * ���[�_�X�e�[�^�X���G���[�̍ہA�G���[�̏ڍׂ𒲂ׂ鎖���o���܂��B
	 */
	/*EN
	 * \brief Get Error Code of Loading
	 * \param err A CriError information
	 * \return	CriFsLoader::ErrorCode Error Code of Loading
	 * \par
	 * This function returns Error Code of Loading.<br>
	 * You can examine the details of error.
	 */
	virtual CriFsLoader::ErrorCode GetErrorCode(CriError &err=CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief ���[�h�̒�~
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * ���[�h���~���܂��B<br>�{�֐��͑������A�֐��ł��B��~��Ԃ��擾����ɂ� CriFsLoader::GetStatus�֐����g�p���Ă��������B<br>
	 * \sa CriFsLoader::GetStatus
	 */
	/*EN
	 * \brief Stop Loading
	 * \param err A CriError information
	 * \par
	 * This function stops the loading.
	 * \sa CriFsLoader::GetStatus
	 */
	virtual void Stop(CriError &err=CriFs::ErrorContainer) = 0;
	
	/*JP
	 * \brief ���[�h�T�C�Y�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return	���[�h�T�C�Y
	 * \par ����:
	 * ���[�h���ꂽ�T�C�Y���擾���܂��B<br>
	 */
	/*EN
	 * \brief Get Loading size
	 * \param err A CriError information
	 * \return	Loading size
	 * \par
	 * This function returns Loading size.
	 */
	virtual CriSint64 GetLoadSize(CriError &err=CriFs::ErrorContainer) = 0;

protected:
	/* �R���X�g���N�^���f�X�g���N�^ */
	CriFsLoader(void) {};
	virtual ~CriFsLoader(void) {};
};


/*-------------------------------------------------------------------------*
 *	CriFsIo
 *-------------------------------------------------------------------------*/
class CriFsIo
{
public:
	/* �f�o�C�X��� */
	typedef struct DeviceInfoTag {
		CriChar8 path[32];
		CriSint32 bus;
		CriBool can_read;
		CriBool can_write;
		CriBool can_seek;
		CriSint32 minimum_read_size;
		CriSint32 minimum_write_size;
		CriSint32 minimum_seek_size;
		CriSint32 read_buffer_alignment;
		CriSint32 write_buffer_alignment;
	} DeviceInfo;
	
	static const CriSint64 INVALID_SIZE = -1;
	
	/* �f�o�C�X���̎擾 */
	virtual CriBool GetDeviceInfo(const CriChar8 *path, DeviceInfo *devinfo) = 0;
	
	/* I/O���� */
	virtual void *Open(CriHeap heap, const CriChar8 *path, CriFs::FileMode mode, CriFs::FileAccess access) = 0;
	virtual CriBool Close(CriHeap heap, void *fp) = 0;
	virtual CriSint64 GetFileSize(void *fp) = 0;
	virtual CriSint64 Read(void *fp, CriSint64 offset, void *buffer, CriSint64 size) = 0;
	virtual CriSint64 Write(void *fp, CriSint64 offset, void *buffer, CriSint64 size) = 0;
	virtual CriBool Flush(void *fp) = 0;
	virtual CriBool Resize(void *fp, CriSint64 size) = 0;
	
	/* �R���X�g���N�^���f�X�g���N�^ */	
	CriFsIo(void) {};
	virtual ~CriFsIo(void) {};
};



/***************************************************************************
 *      �֐��錾
 *      Prototype Functions
 ***************************************************************************/
/*-------------------------------------------------------------------------*
 *	CriFs
 *-------------------------------------------------------------------------*/
/*JP
 * \brief CRI File System �I�u�W�F�N�g
 * \ingroup FSLIB_BASIC
 * \par ����:
 * CRI File System�̊�{�ƂȂ�I�u�W�F�N�g�N���X�ł��B
 */
/*EN
 * \brief CRI File System Object
 * \ingroup FSLIB_BASIC
 * \par
 * Basic object class for CRI File System.
 */
namespace CriFs 
{
	/*JP
	 * \brief CRI File System�̏�����
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * CRI File System�����������܂��B<br>
	 * CRI File System���g�p���邽�߂ɂ́A���̊֐����R�[�����ď��������s���Ă��������B<br>
	 * \sa CriFs::Finalize
	 */
	/*EN
	 * \brief Initialize the CRI File System
	 * \param err A CriError information
	 * \par
	 * Initialize the CRI File System<br>
	 * \sa CriFs::Finalize
	 */
	void CRIAPI Initialize(CriError &err = CriFs::ErrorContainer);
	
	/*JP
	 * \brief CRI File System�̏I��
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * CRI File System���I�����܂��B<br>
	 * \sa CriFs::Initialize
	 */
	/*EN
	 * \brief Finalize the CRI File System
	 * \param err A CriError information
	 * \par
	 * Finalize the CRI File System<br>
	 * \sa CriFs::Initialize
	 */
	 void CRIAPI Finalize(CriError &err = CriFs::ErrorContainer);
	
	/*JP
	 * \brief �O��I/O�C���^�t�F�[�X�̓o�^
	 * \param io CriFsIo I/O�C���^�t�F�[�X
	 * \param err �G���[�R�[�h<br>
	 * \par ����:
	 * �O��I/O�C���^�t�F�[�X��o�^���܂��B<br>
	 * �Ǝ���I/O���W���[�����g�p���邱�Ƃ��\�ɂȂ�܂��B
	 */
	/*EN
	 * \brief Set External I/O Interface
	 * \param io CriFsIo I/O Interface
	 * \param err A CriError information
	 * \par
	 * This function sets the I/O Interface<br>
	 */
	void CRIAPI SetIoInterface(CriFsIo *io, CriError &err = CriFs::ErrorContainer);
	
	/*JP
	 * \brief I/O�C���^�t�F�[�X�̎擾
	 * \param err �G���[�R�[�h<br>
	 * \return CriFsIo I/O�C���^�t�F�[�X
	 * \par ����:
	 * I/O�C���^�t�F�[�X���擾���܂��B<br>
	 */
	/*EN
	 * \brief Set External I/O Interface
	 * \param err A CriError information
	 * \return CriFsIo I/O Interface
	 * \par
	 * This function gets the I/O Interface<br>
	 */
	CriFsIo * CRIAPI GetIoInterface(CriError &err = CriFs::ErrorContainer);
	
//	void CRIAPI AllocateStreamingBuffer(CriHeap heap, CriUint32 size, CriError &err = CriFs::ErrorContainer);
//	void CRIAPI ReleaseStreamingBuffer(CriError &err = CriFs::ErrorContainer);
}

#endif	/* CRI_FILE_SYSTEM_VER1PAI_H_INCLUDED */

#endif /* __cplusplus */

/* --- end of file --- */
