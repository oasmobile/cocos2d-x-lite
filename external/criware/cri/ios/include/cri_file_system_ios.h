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

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_IOS_H_INCLUDED
#define	CRI_FILE_SYSTEM_IOS_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*JP
 * \brief ファイルアクセススレッドのプライオリティ設定
 * \ingroup FSLIB_CRIFS_IOS
 * \param[in]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * ファイルアクセススレッドのプライオリティを設定します。<BR>
 * アプリケーションのメインスレッドよりも高いプライオリティを指定してください。<BR>
 * プライオリティのデフォルト値は 8 です。<BR>
 */
CriError CRIAPI criFs_SetFileAccessThreadPriority_IOS(int prio);

/*JP
 * \brief データ展開スレッドのプライオリティ設定
 * \ingroup FSLIB_CRIFS_IOS
 * \param[in]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * データ展開スレッドのプライオリティを設定します。<BR>
 * アプリケーションのメインスレッドよりも低いプライオリティを指定してください。<BR>
 * プライオリティのデフォルト値は -13 です。<BR>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_IOS(int prio);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      旧バージョンとの互換用
 *      For compatibility with old version
 ***************************************************************************/
#define criFs_SetFileAccessThreadPriority_iOS criFs_SetFileAccessThreadPriority_IOS
#define criFs_SetDataDecompressionThreadPriority_iOS criFs_SetDataDecompressionThreadPriority_IOS

#endif	/* CRI_FILE_SYSTEM_IOS_H_INCLUDED */

/* --- end of file --- */
