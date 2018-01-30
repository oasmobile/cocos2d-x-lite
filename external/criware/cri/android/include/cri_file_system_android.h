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

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_ANDROID_H_INCLUDED
#define	CRI_FILE_SYSTEM_ANDROID_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"
#include <jni.h>

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
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * ファイルアクセススレッドのプライオリティを設定します。<BR>
 * criFs_Initialize() の呼出し後に設定してください。<BR>
 * プライオリティはナイス値で指定してください。範囲は-20(最高)から19(最低)です。
 * アプリケーションのメインスレッドよりも高いプライオリティを指定してください。<BR>
 * プライオリティのデフォルト値は -7 です。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数は何も処理を行いません。<br>
 * （エラーコールバックが発生します。）<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行しても、効果はありません。<br>
 * （エラーコールバックが発生します。）<br>
 */
CriError CRIAPI criFs_SetFileAccessThreadPriority_ANDROID(int prio);

/*JP
 * \brief ファイルアクセススレッドのプライオリティ取得
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * ファイルアクセススレッドのプライオリティを取得します。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数はエラーを返します。<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行した場合、本関数はエラーを返します。<br>
 */
CriError CRIAPI criFs_GetFileAccessThreadPriority_ANDROID(int *prio);

/*JP
 * \brief メモリファイルシステムスレッドのプライオリティ設定
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * メモリファイルシステムスレッドのプライオリティを設定します。<BR>
 * プライオリティはナイス値で指定してください。範囲は-20(最高)から19(最低)です。
 * アプリケーションのメインスレッドよりも高いプライオリティを指定してください。<BR>
 * プライオリティのデフォルト値は 7 です。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数は何も処理を行いません。<br>
 * （エラーコールバックが発生します。）<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行しても、効果はありません。<br>
 * （エラーコールバックが発生します。）<br>
 */
CriError CRIAPI criFs_SetMemoryFileSystemThreadPriority_ANDROID(int prio);

/*JP
 * \brief メモリファイルシステムスレッドのプライオリティ取得
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * メモリファイルシステムスレッドのプライオリティを取得します。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数はエラーを返します。<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行した場合、本関数はエラーを返します。<br>
 */
CriError CRIAPI criFs_GetMemoryFileSystemThreadPriority_ANDROID(int *prio);

/*JP
 * \brief データ展開スレッドのプライオリティ設定
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * データ展開スレッドのプライオリティを設定します。<BR>
 * プライオリティはナイス値で指定してください。範囲は-20(最高)から19(最低)です。
 * アプリケーションのメインスレッドよりも高いプライオリティを指定してください。<BR>
 * プライオリティのデフォルト値は 9 です。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数は何も処理を行いません。<br>
 * （エラーコールバックが発生します。）<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行しても、効果はありません。<br>
 * （エラーコールバックが発生します。）<br>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_ANDROID(int prio);

/*JP
 * \brief データ展開スレッドのプライオリティ取得
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	prio	スレッドのプライオリティ
 * \return	CriError	エラーコード
 * \par 説明:
 * データ展開スレッドのプライオリティを取得します。<BR>
 * \attention:
 * 本関数は、ライブラリ初期化時にスレッドモデルをマルチスレッドモデル
 * （ ::CRIFS_THREAD_MODEL_MULTI ）に設定した場合にのみ効果を発揮します。<br>
 * 他のスレッドモデルを選択した場合、本関数はエラーを返します。<br>
 * <br>
 * 本関数は初期化後～終了処理前の間に実行する必要があります。<br>
 * 初期化前や終了処理後に本関数を実行した場合、本関数はエラーを返します。<br>
 */
CriError CRIAPI criFs_GetDataDecompressionThreadPriority_ANDROID(int *prio);

/*JP
 * \brief JavaVMオブジェクトの登録
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[out]	vm	JavaVMオブジェクトへの参照
 * \par 説明:
 * JavaVMオブジェクトへの参照をCriFileSystemライブラリに登録します。<br>
 * \attention:
 * JavaVMオブジェクトへの参照を登録した場合、ライブラリ内部で作成されたスレッドはJavaVMにアタッチされます。<br>
 */
void CRIAPI criFs_SetJavaVM_ANDROID(JavaVM* vm);

/* 
 * 本関数は旧仕様の関数で、互換性のため残してあります。
 * criFs_EnableAssetsAccess_ANDROIDの方をお使い下さい。
 */
CriError CRIAPI criFs_SetContext_ANDROID(jobject jobj);

/*JP
 * \brief Androidプロジェクト内のassetsフォルダに対するアクセスの有効化
 * \ingroup FSLIB_CRIFS_ANDROID
 * \param[in]	vm		JavaVMオブジェクトへの参照
 * \param[in]	jobj	android.content.Contextオブジェクト
 * \return	CriError	エラーコード
 * \par 説明:
 * assetフォルダへのアクセスを有効化します。<br>
 * <br>
 * 本関数は、assetsフォルダへのアクセスを有効化します。<br>
 * 本関数の引数として渡されたJavaVMオブジェクトへの参照(vm)と、android.content.Contextオブジェクト(jobj)は<br>
 * CriFileSystemライブラリに登録されます。<br>
 * \attention:
 * 本関数の誤使用は、期待しない動作につながります。以下の点に注意して下さい。<br>
 * (1) 本関数を呼び出す前に、CRI File Systemライブラリの初期化が完了済みである事を確認して下さい。<br>
 * (2) assetsフォルダへのアクセス前に、本関数を呼び出して下さい。<br>
 * (3) 登録したContextオブジェクトは、Java VMのガベージコレクション対象から外れます。<br>
 *     登録を解除するには、::criFs_DisableAssetsAccess_ANDROID関数を呼び出してください。<br>
 *     または、新たなContextオブジェクトを登録し直すことでも、古いContextの登録解除が可能です。<br>
 * (4) 本関数を呼び出したスレッドは、予めJavaVMにアタッチされていなかった場合に限り、JavaVMにアタッチされます。<br>
 * (5) 本関数を呼び出したスレッドは、終了前に必ず::criFs_DisableAssetsAccess_ANDROID関数を呼ぶ必要があります。<br>
 */
CriError CRIAPI criFs_EnableAssetsAccess_ANDROID(JavaVM* vm, jobject jobj);

/*JP
 * \brief Androidプロジェクト内のassetsフォルダに対するアクセスの無効化
 * \ingroup FSLIB_CRIFS_ANDROID
 * \return	CriError	エラーコード
 * \par 説明:
 * assetフォルダへのアクセスを無効化します。<br>
 * ::criFs_EnableAssetsAccess_ANDROID関数によってCriFileSystemライブラリに登録されたandroid.content.Contextオブジェクトは<br>
 * 本関数呼び出しにより登録解除されます。
 * \attention:
 * 本関数の誤使用は、期待しない動作につながります。以下の点に注意して下さい。<br>
 * (1) 本関数を呼び出したスレッドは、予めJavaVMにアタッチされていなかった場合に限り、JavaVMからデタッチされます。<br>
 * (2) ::criFs_EnableAssetsAccess_ANDROID関数を呼び出したスレッドは、終了前に必ず本関数を呼ぶ必要があります。<br>
 */
CriError CRIAPI criFs_DisableAssetsAccess_ANDROID();


#ifdef __cplusplus
}
#endif

#endif	/* CRI_FILE_SYSTEM_ANDROID_H_INCLUDED */

/***************************************************************************
 *      旧バージョンとの互換用
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
