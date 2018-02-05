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

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_XAUDIO2_H
#define CRI_INCL_CRI_ATOM_XAUDIO2_H

/***************************************************************************
 *      インクルードファイル
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
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ライブラリ初期化用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMLIB_XAUDIO2
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtom_Initialize_XAUDIO2 関数に設定するコンフィグ構造体
 * （ ::CriAtomConfig_XAUDIO2 ）に、デフォルトの値をセットします。<br>
 * \attention
 * 本マクロは下位レイヤ向けのAPIです。<br>
 * AtomExレイヤの機能を利用する際には、本マクロの代わりに 
 * ::criAtomEx_SetDefaultConfig_XAUDIO2 マクロをご利用ください。
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
 * \brief ライブラリ初期化用コンフィグ構造体にデフォルト値をセット
 * \ingroup ATOMLIB_XAUDIO2
 * \param[out]	p_config	初期化用コンフィグ構造体へのポインタ
 * \par 説明:
 * ::criAtomEx_Initialize_XAUDIO2 関数に設定するコンフィグ構造体
 * （ ::CriAtomExConfig_XAUDIO2 ）に、デフォルトの値をセットします。<br>
 * \sa CriAtomExConfig_XAUDIO2
 */
#define criAtomEx_SetDefaultConfig_XAUDIO2(p_config)		\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief Atomライブラリ初期化用コンフィグ構造体
 * \ingroup ATOMLIB_XAUDIO2
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtom_Initialize_XAUDIO2 関数の引数に指定します。<br>
 * \attention
 * 本構造体は下位レイヤ向けのAPIです。<br>
 * AtomExレイヤの機能を利用する際には、本構造体の代わりに 
 * ::CriAtomExConfig_XAUDIO2 構造体をご利用ください。
 * \sa criAtom_Initialize_XAUDIO2, criAtom_SetDefaultConfig_XAUDIO2
 */
typedef struct CriAtomConfigTag_XAUDIO2 {
	CriAtomConfig			atom;		/*JP< Atom初期化用コンフィグ構造体		*/
	CriAtomAsrConfig		asr;		/*JP< ASR初期化用コンフィグ			*/
	CriAtomHcaMxConfig		hca_mx;		/*JP< HCA-MX初期化用コンフィグ構造体	*/
} CriAtomConfig_XAUDIO2;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atomライブラリ初期化用コンフィグ構造体
 * \ingroup ATOMLIB_XAUDIO2
 * CRI Atomライブラリの動作仕様を指定するための構造体です。<br>
 * ::criAtomEx_Initialize_XAUDIO2 関数の引数に指定します。<br>
 * \sa criAtomEx_Initialize_XAUDIO2, criAtomEx_SetDefaultConfig_XAUDIO2
 */
typedef struct CriAtomExConfigTag_XAUDIO2 {
	CriAtomExConfig			atom_ex;	/*JP< AtomEx初期化用コンフィグ構造体	*/
	CriAtomExAsrConfig		asr;		/*JP< ASR初期化用コンフィグ			*/
	CriAtomExHcaMxConfig	hca_mx;		/*JP< HCA-MX初期化用コンフィグ構造体	*/
} CriAtomExConfig_XAUDIO2;

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

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ライブラリ初期化用ワーク領域サイズの計算
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		初期化用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \par 説明:
 * ライブラリを使用するために必要な、ワーク領域のサイズを取得します。<br>
 * \par 備考:
 * ライブラリが必要とするワーク領域のサイズは、ライブラリ初期化用コンフィグ
 * 構造体（ ::CriAtomConfig_XAUDIO2 ）の内容によって変化します。<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * 本関数は下位レイヤ向けのAPIです。<br>
 * AtomExレイヤの機能を利用する際には、本関数の代わりに 
 * ::criAtomEx_CalculateWorkSize_XAUDIO2 関数をご利用ください。
 * \sa CriAtomConfig_XAUDIO2, criAtom_Initialize_XAUDIO2
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_XAUDIO2(const CriAtomConfig_XAUDIO2 *config);

/*JP
 * \brief ライブラリの初期化
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		初期化用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \par 説明:
 * ライブラリを初期化します。<br>
 * ライブラリの機能を利用するには、必ずこの関数を実行する必要があります。<br>
 * （ライブラリの機能は、本関数を実行後、 ::criAtom_Finalize_XAUDIO2 関数を実行するまでの間、
 * 利用可能です。）<br>
 * <br>
 * ライブラリを初期化する際には、ライブラリが内部で利用するためのメモリ領域（ワーク領域）
 * を確保する必要があります。<br>
 * ライブラリが必要とするワーク領域のサイズは、初期化用コンフィグ構造体の内容に応じて
 * 変化します。<br>
 * ワーク領域サイズの計算には、 ::criAtom_CalculateWorkSize_XAUDIO2 
 * 関数を使用してください。<br>
 * \par 備考:
 * ::criAtom_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。<br>
 * （ work に NULL 、 work_size に 0 を指定することで、登録済みのアロケータ
 * から必要なワーク領域サイズ分のメモリが動的に確保されます。）
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * 本関数は内部的に以下の関数を実行します。<br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	.
 * 本関数を実行する場合、上記関数を実行しないでください。<br>
 * <br>
 * 本関数を実行後、必ず対になる ::criAtom_Finalize_XAUDIO2 関数を実行してください。<br>
 * また、 ::criAtom_Finalize_XAUDIO2 関数を実行するまでは、本関数を再度実行しないでください。<br>
 * <br>
 * 本関数は下位レイヤ向けのAPIです。<br>
 * AtomExレイヤの機能を利用する際には、本関数の代わりに 
 * ::criAtomEx_Initialize_XAUDIO2 関数をご利用ください。
 * \sa CriAtomConfig_XAUDIO2, criAtom_Finalize_XAUDIO2,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_XAUDIO2
 */
void CRIAPI criAtom_Initialize_XAUDIO2(
	const CriAtomConfig_XAUDIO2 *config, void *work, CriSint32 work_size);

/*JP
 * \brief ライブラリの終了
 * \ingroup ATOMLIB_XAUDIO2
 * \par 説明:
 * ライブラリを終了します。<br>
 * \attention
 * 本関数は内部的に以下の関数を実行します。<br>
 * 	- ::criAtom_Finalize
 * 	- ::criAtomAsr_Finalize
 * 	- ::criAtomHcaMx_Finalize
 * 	.
 * 本関数を実行する場合、上記関数を実行しないでください。<br>
 * <br>
 * ::criAtom_Initialize_XAUDIO2 関数実行前に本関数を実行することはできません。<br>
 * <br>
 * 本関数は下位レイヤ向けのAPIです。<br>
 * AtomExレイヤの機能を利用する際には、本関数の代わりに 
 * ::criAtomEx_Finalize_XAUDIO2 関数をご利用ください。
 * \sa criAtom_Initialize_XAUDIO2
 */
void CRIAPI criAtom_Finalize_XAUDIO2(void);

/* 以降はXAudio2.hに依存したAPI */
#if !defined(CRI_ATOM_WITOUT_XAUDIO2_H)

/*JP
 * \brief XAudio2オブジェクトのセット
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	xa2		XAudio2オブジェクト
 * \par 説明:
 * AtomライブラリにXAudio2オブジェクトをセットします。<br>
 * <br>
 * Atomライブラリは、初期化処理時にライブラリ内でXAudio2の初期化を行います。<br>
 * そのため、XAudio2オブジェクトはライブラリ内に隠蔽され、アプリケーション
 * から参照することはできません。<br>
 * <br>
 * アプリケーション内でXAudio2オブジェクトを使用したい場合には、
 * Atomライブラリ初期化前にXAudio2の初期化処理を行い、作成されたXAudio2
 * オブジェクトを本関数を使用してAtomライブラリにセットしてください。<br>
 * 本関数でXAudio2オブジェクトをセットしてからAtomライブラリの初期化を行うと、
 * Atomライブラリは初期化時にXAudio2を初期化せず、本関数でセットされた
 * XAudio2オブジェクトを使用します。<br>
 */
void CRIAPI criAtom_SetXAudio2Object_XAUDIO2(IXAudio2 *xa2);

/*JP
 * \brief 出力ボイスのセット
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	ov		XAudio2ボイス
 * \par 説明:
 * Atomライブラリに出力ボイスをセットします。<br>
 * <br>
 * Atomライブラリは、初期化処理時にライブラリ内でマスタリングボイスを作成し、
 * 全ての音声をマスタリングボイスに出力します。<br>
 * <br>
 * Atomライブラリの出力音声を他のボイス（サブミックスボイス等）に
 * 出力したい場合には、Atomライブラリ初期化前に出力ボイスの作成し、
 * 本関数を使用してAtomライブラリにセットしてください。<br>
 * 本関数で出力ボイスをセットしてからAtomライブラリの初期化を行うと、
 * Atomライブラリは初期化時にマスタリングボイスを作成せず、
 * 本関数でセットされた出力ボイスに音声を出力します。<br>
 */
void CRIAPI criAtom_SetOutputVoice_XAUDIO2(IXAudio2Voice *ov);

/*JP
 * \brief 出力ボイスの取得
 * \ingroup ATOMLIB_XAUDIO2
 * \return	IXAudio2Voice*	XAudio2ボイス
 * \par 説明:
 * Atomライブラリが使用する出力ボイスを返します。<br>
 * <br>
 * ::criAtom_SetXAudio2Object_XAUDIO2 関数を使用している場合、
 * 本関数は ::criAtom_SetXAudio2Object_XAUDIO2 関数でセットされたボイスを返します。<br>
 * ::criAtom_SetXAudio2Object_XAUDIO2 関数を使用していない場合、
 * 本関数は初期化処理時にライブラリ内で作成したマスタリングボイスを返します。<br>
 * \par
 * XAudio2の初期化に失敗した場合（サウンドデバイスが使用できない場合等）には、
 * 本関数はNULLを返します。<br>
 * \sa criAtom_SetOutputVoice_XAUDIO2
 */
IXAudio2Voice *criAtom_GetOutputVoice_XAUDIO2(void);

/*JP
 * \brief 出力デバイスインデックスのセット
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	index	デバイスインデックス
 * \par 説明:
 * Atomライブラリに出力デバイスのインデックスをセットします。<br>
 * <br>
 * Atomライブラリは、初期化処理時にライブラリ内でXAudio2の初期化を行い、
 * 0番のデバイスを使用して音声を出力します。<br>
 * <br>
 * 音声出力先のデバイスを変更したい場合には、
 * Atomライブラリ初期化前に本関数を使用して出力デバイスのインデックスを
 * 指定してください。
 * 本関数で出力デバイスのインデックスを指定してからAtomライブラリの
 * 初期化を行うと、Atomライブラリは指定されたデバイスに音声を出力します。<br>
 * \par 備考:
 * index に 0xFFFFFFFF を指定した場合、Atomライブラリはライブラリ内で XAudio2 
 * の初期化を行わないよう、動作を変更します。<br>
 * <br>
 * 本関数への設定値は、Atomライブラリ内でマスタリングボイスを作成する際に使用されます。<br>
 * ::criAtom_SetOutputVoice_XAUDIO2 関数を使用してライブラリ外で作成済みの
 * 出力ボイスを指定する場合、本関数に設定した値は参照されません。<br>
 * \sa criAtom_SetXAudio2Object_XAUDIO2
 */
void CRIAPI criAtom_SetOutputDeviceIndex_XAUDIO2(UINT32 index);

/*JP
 * \brief サウンドバッファサイズの指定
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	num_samples	サウンドバッファサイズ（サンプル数単位）
 * \par 説明:
 * Atomライブラリ内でボイスにキューイングするサンプル数の最大値を指定します。<br>
 * サウンドバッファのサイズはサンプル数単位で指定します。<br>
 * <br>
 * サウンドバッファサイズに 0 を指定した場合、
 * デフォルトサイズでサウンドバッファが作成されます。<br>
 * （Xbox360では2V分、PCでは4V分のサイズに設定されます。）<br>
 * \par 備考:
 * AtomライブラリはXAudio2SourceVoiceボイスを作成する際、
 * 合わせてサウンドデータをキューイングするためのバッファ（サウンドバッファ）を作成します。<br>
 * デフォルト状態では、バッファサイズはライブラリ初期化時のパラメータに応じて自動的に決定されますが、
 * 本関数を実行することで、サウンドバッファのサイズを任意のサイズに変更することが可能です。<br>
 * <br>
 * ASRを使用する場合、再生処理後、実際に音が鳴るまでに、
 * サウンドバッファサイズ分の遅延が生じることになります。<br>
 * そのため、サウンドバッファのサイズを小さな値に変更すれば、
 * 音声再生開始処理から実際に音が鳴るまでの間隔を、ある程度短くすることができます。<br>
 * \attention
 * ASRが内部的に作成するボイスのサウンドバッファのサイズを変更したい場合、
 * 本関数をASRの初期化よりも前に実行しておく必要があります。<br>
 * （ASR作成に必要なワーク領域のサイズも変わるため、
 * 厳密にはASR初期化用ワーク領域サイズを計算する前に実行する必要があります。）<br>
 * <br>
 * 指定したサイズが小さすぎる場合、音途切れ等の問題が発生する可能性があります。<br>
 * （最低でも「再生サンプリングレート÷サーバ処理周波数」以上の値を指定する必要があります。）<br>
 * <br>
 * PC環境では、サウンドバッファサイズを小さくした場合に再生が正しく行えるかどうかが、
 * サウンドデバイスの性能にも左右されます。<br>
 * 多くの環境で音途切れなく再生を行いたい場合には、
 * サウンドバッファサイズにある程度大きめの値を設定してください。<br>
 */
void CRIAPI criAtom_SetSoundBufferSize_XAUDIO2(CriSint32 num_samples);

/*JP
 * \brief XAudio2で致命的なエラーが発生したかどうかのチェック
 * \ingroup ATOMLIB_XAUDIO2
 * \return	CriBool	エラーの有無（CRI_TRUE = エラーが発生、CRI_FALSE = 正常に動作中）
 * \par 説明:
 * XAudio2でアプリケーションの再起動が必要な致命的エラーが発生したかどうかを返します。<br>
 * <br>
 * PC環境でサウンドデバイスの抜き差しを行った場合、本関数がCRI_TRUEを返します。<br>
 * アプリケーションでデバイス抜き差しをケアしたい場合には、
 * 本関数の戻り値に応じてユーザへの通知等を行ってください。<br>
 * \par 備考:
 * 本関数は、XAudio2内で以下のコールバックが呼び出されたかどうかを判定しています。<br>
 * 	- IXAudio2EngineCallback::OnCriticalError
 * 	- IXAudio2VoiceCallback::OnVoiceError
 * 	.
 * <br>
 * 本関数がCRI_TRUEを返した場合、音声の再生を復旧するには以下の処理を行う必要があります。<br>
 * 	-# サウンドデバイスの再接続する。
 * 	-# ライブラリの終了処理を行う。
 * 	-# ライブラリを再度初期化する。
 * 	.
 */
CriBool CRIAPI criAtom_IsCriticalErrorOccurred_XAUDIO2(void);

#endif

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ライブラリ初期化用ワーク領域サイズの計算
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		初期化用コンフィグ構造体
 * \return		CriSint32	ワーク領域サイズ
 * \par 説明:
 * ライブラリを使用するために必要な、ワーク領域のサイズを取得します。<br>
 * \par 備考:
 * ライブラリが必要とするワーク領域のサイズは、ライブラリ初期化用コンフィグ
 * 構造体（ ::CriAtomExConfig_XAUDIO2 ）の内容によって変化します。<br>
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \sa CriAtomExConfig_XAUDIO2, criAtomEx_Initialize_XAUDIO2
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_XAUDIO2(const CriAtomExConfig_XAUDIO2 *config);

/*JP
 * \brief ライブラリの初期化
 * \ingroup ATOMLIB_XAUDIO2
 * \param[in]	config		初期化用コンフィグ構造体
 * \param[in]	work		ワーク領域
 * \param[in]	work_size	ワーク領域サイズ
 * \par 説明:
 * ライブラリを初期化します。<br>
 * ライブラリの機能を利用するには、必ずこの関数を実行する必要があります。<br>
 * （ライブラリの機能は、本関数を実行後、 ::criAtomEx_Finalize_XAUDIO2 関数を実行するまでの間、
 * 利用可能です。）<br>
 * <br>
 * ライブラリを初期化する際には、ライブラリが内部で利用するためのメモリ領域（ワーク領域）
 * を確保する必要があります。<br>
 * ライブラリが必要とするワーク領域のサイズは、初期化用コンフィグ構造体の内容に応じて
 * 変化します。<br>
 * ワーク領域サイズの計算には、 ::criAtomEx_CalculateWorkSize_XAUDIO2 
 * 関数を使用してください。<br>
 * \par 備考:
 * ::criAtomEx_SetUserAllocator マクロを使用してアロケータを登録済みの場合、
 * 本関数にワーク領域を指定する必要はありません。<br>
 * （ work に NULL 、 work_size に 0 を指定することで、登録済みのアロケータ
 * から必要なワーク領域サイズ分のメモリが動的に確保されます。）
 * <br>
 * 引数 config の情報は、関数内でのみ参照されます。<br>
 * 関数を抜けた後は参照されませんので、関数実行後に config の領域を解放しても
 * 問題ありません。
 * \attention
 * 本関数は内部的に以下の関数を実行します。<br>
 * 	- ::criAtomEx_Initialize
 * 	- ::criAtomExAsr_Initialize
 * 	- ::criAtomExHcaMx_Initialize
 * 	.
 * 本関数を実行する場合、上記関数を実行しないでください。<br>
 * <br>
 * 本関数を実行後、必ず対になる ::criAtomEx_Finalize_XAUDIO2 関数を実行してください。<br>
 * また、 ::criAtomEx_Finalize_XAUDIO2 関数を実行するまでは、本関数を再度実行しないでください。<br>
 * \sa CriAtomExConfig_XAUDIO2, criAtomEx_Finalize_XAUDIO2,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_XAUDIO2
 */
void CRIAPI criAtomEx_Initialize_XAUDIO2(
	const CriAtomExConfig_XAUDIO2 *config, void *work, CriSint32 work_size);

/*JP
 * \brief ライブラリの終了
 * \ingroup ATOMLIB_XAUDIO2
 * \par 説明:
 * ライブラリを終了します。<br>
 * \attention
 * 本関数は内部的に以下の関数を実行します。<br>
 * 	- ::criAtomEx_Finalize
 * 	- ::criAtomExAsr_Finalize
 * 	- ::criAtomExHcaMx_Finalize
 * 	.
 * 本関数を実行する場合、上記関数を実行しないでください。<br>
 * <br>
 * ::criAtomEx_Initialize_XAUDIO2 関数実行前に本関数を実行することはできません。<br>
 * \sa criAtomEx_Initialize_XAUDIO2
 */
void CRIAPI criAtomEx_Finalize_XAUDIO2(void);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      旧バージョンとの互換用
 *      For compatibility with old version
 ***************************************************************************/
#define criAtom_ControlComInitialization_XAUDIO2(sw)

#endif	/* CRI_INCL_CRI_ATOM_XAUDIO2_H */

/* --- end of file --- */
