/* Copyright(C)URARA-works 2008 */
/* ========================================================================= */
/* ファイル名	:LibInfoSystem.cpp											 */
/* 内容			:システム情報クラス 実装ファイル							 */
/* 作成			:年がら年中春うらら(URARA-works)							 */
/* 作成開始日	:2008/09/28													 */
/* ========================================================================= */

#include "stdafx.h"
#include "LibInfoSystem.h"


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::CLibInfoSystem									 */
/* 内容		:コンストラクタ													 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

CLibInfoSystem::CLibInfoSystem()
{
	m_pInfo = NULL;
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::~CLibInfoSystem								 */
/* 内容		:デストラクタ													 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

CLibInfoSystem::~CLibInfoSystem()
{
	Destroy ();
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::Create											 */
/* 内容		:作成															 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

void CLibInfoSystem::Create(void)
{
	m_pInfo = new CInfoSystem;
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::Destroy										 */
/* 内容		:破棄															 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

void CLibInfoSystem::Destroy(void)
{
	SAFE_DELETE (m_pInfo);
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::GetCount										 */
/* 内容		:データ数を取得													 */
/* 日付		:2007/04/30														 */
/* ========================================================================= */

int  CLibInfoSystem::GetCount(void)
{
	return 1;
}

/* ========================================================================= */
/* 関数名	:CLibInfoSystem::GetNew											 */
/* 内容		:新規データを取得												 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

PCInfoBase CLibInfoSystem::GetNew(void)
{
	return (PCInfoSystem)new CInfoSystem;
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::Add											 */
/* 内容		:追加															 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

void CLibInfoSystem::Add(PCInfoBase pInfo)
{
	SAFE_DELETE (m_pInfo);
	m_pInfo = (PCInfoSystem)pInfo;
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::Delete											 */
/* 内容		:削除															 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

void CLibInfoSystem::Delete(int nNo)
{
	SAFE_DELETE (m_pInfo);
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::DeleteAll										 */
/* 内容		:全て削除														 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

void CLibInfoSystem::DeleteAll(void)
{
	SAFE_DELETE (m_pInfo);
}


/* ========================================================================= */
/* 関数名	:CLibInfoSystem::GetPtr											 */
/* 内容		:情報を取得														 */
/* 日付		:2008/09/28														 */
/* ========================================================================= */

PCInfoBase CLibInfoSystem::GetPtr(int nNo/*0*/)
{
	return m_pInfo;
}

/* Copyright(C)URARA-works 2008 */
