/* Copyright(C)URARA-works 2006 */
/* ========================================================================= */
/* ファイル名	:stdafx.h													 */
/* 内容			:プリコンパイルヘッダ 定義ファイル							 */
/* 作成			:年がら年中春うらら(URARA-works)							 */
/* 作成開始日	:2006/09/24													 */
/* ========================================================================= */

#pragma once

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。
#define WINVER 0x0500
#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxtempl.h>

//#pragma warning(disable:4192)
//#pragma warning(disable:4146)
//#pragma warning(disable:4049)

#define DIRECTINPUT_VERSION	DIRECTINPUT_HEADER_VERSION

#include <winsock2.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <imm.h>
#include <time.h>
#include <tchar.h>
#include <shlwapi.h>
#include <map>
using namespace std;

#include "GlobalDefine.h"
#include "myArray.h"
#include "myString.h"
#include "mySection.h"
#include "SBOGlobal.h"
#include "SboCli_priv.h"

//{{AFX_INSERT_LOCATION}}

/* Copyright(C)URARA-works 2006 */
