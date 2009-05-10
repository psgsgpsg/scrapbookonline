/* Copyright(C)URARA-works 2004 */
/* ========================================================================= */
/* ファイル名	:mySection.cpp												 */
/* 内容			:クリティカルセクションクラス 実装ファイル					 */
/* 作成			:年がら年中春うらら(URARA-works)							 */
/* 作成開始日	:2004/09/01													 */
/* ========================================================================= */

#include "StdAfx.h"
#include "mySection.h"


/* ========================================================================= */
/* 関数名	:CmySection::CmySection											 */
/* 内容		:コンストラクタ													 */
/* 日付		:2004/09/01														 */
/* ========================================================================= */

CmySection::CmySection()
{
	InitializeCriticalSection (&m_Crit);
}


/* ========================================================================= */
/* 関数名	:CmySection::~CmySection										 */
/* 内容		:デストラクタ													 */
/* 日付		:2004/09/01														 */
/* ========================================================================= */

CmySection::~CmySection()
{
	DeleteCriticalSection (&m_Crit);
}


/* ========================================================================= */
/* 関数名	:CmySection::Enter												 */
/* 内容		:ロック															 */
/* 日付		:2004/09/01														 */
/* ========================================================================= */

void CmySection::Enter(void)
{
	EnterCriticalSection (&m_Crit);
}


/* ========================================================================= */
/* 関数名	:CmySection::Leave												 */
/* 内容		:ロック解除														 */
/* 日付		:2004/09/01														 */
/* ========================================================================= */

void CmySection::Leave(void)
{
	LeaveCriticalSection (&m_Crit);
}

/* Copyright(C)URARA-works 2004 */
