/* Copyright(C)URARA-works 2007 */
/* ========================================================================= */
/* ファイル名	:PacketMAP_SETPARTS.cpp										 */
/* 内容			:コマンド(マップ系:マップパーツ配置) 実装ファイル			 */
/* 作成			:年がら年中春うらら(URARA-works)							 */
/* 作成開始日	:2007/04/30													 */
/* ========================================================================= */

#include "StdAfx.h"
#include "InfoMapParts.h"
#include "Command.h"
#include "PacketMAP_SETPARTS.h"

/* ========================================================================= */
/* 関数名	:CPacketMAP_SETPARTS::CPacketMAP_SETPARTS						 */
/* 内容		:コンストラクタ													 */
/* 日付		:2007/04/30														 */
/* ========================================================================= */

CPacketMAP_SETPARTS::CPacketMAP_SETPARTS()
{
	m_ptPos.x	= 0;
	m_ptPos.y	= 0;
	m_dwMapID	= 0;
	m_dwPartsID	= 0;
}


/* ========================================================================= */
/* 関数名	:CPacketMAP_SETPARTS::~CPacketMAP_SETPARTS						 */
/* 内容		:デストラクタ													 */
/* 日付		:2007/04/30														 */
/* ========================================================================= */

CPacketMAP_SETPARTS::~CPacketMAP_SETPARTS()
{
}


/* ========================================================================= */
/* 関数名	:CPacketMAP_SETPARTS::Make										 */
/* 内容		:パケットを作成													 */
/* 日付		:2007/04/30														 */
/* ========================================================================= */

void CPacketMAP_SETPARTS::Make(
	DWORD dwMapID,			/* [in] マップID */
	int x,					/* [in] X座標 */
	int y,					/* [in] Y座標 */
	DWORD dwPartsID)		/* [in] パーツID */
{
	PBYTE pData, pDataTmp;
	DWORD dwSize;
	POINT ptPos;
	PPACKETBASE pPacketBase;

	ptPos.x = x;
	ptPos.y = y;

	dwSize = sizeof (PACKETBASE)	+
			 sizeof (ptPos)			+
			 sizeof (dwMapID)		+
			 sizeof (dwPartsID);

	pData = new BYTE[dwSize];
	ZeroMemory (pData, dwSize);
	pPacketBase = (PPACKETBASE)pData;

	pPacketBase->byCmdMain	= SBOCOMMANDID_MAIN_MAP;
	pPacketBase->byCmdSub	= SBOCOMMANDID_SUB_MAP_SETPARTS;

	pDataTmp = (PBYTE)(pPacketBase + 1);
	CopyMemoryRenew (pDataTmp, &dwMapID,	sizeof (dwMapID),	pDataTmp);	/* マップID */
	CopyMemoryRenew (pDataTmp, &ptPos,		sizeof (ptPos),		pDataTmp);	/* 座標 */
	CopyMemoryRenew (pDataTmp, &dwPartsID,	sizeof (dwPartsID),	pDataTmp);	/* パーツID */

	RenewPacket (pData, dwSize);
}


/* ========================================================================= */
/* 関数名	:CPacketMAP_SETPARTS::Set										 */
/* 内容		:パケットを設定													 */
/* 日付		:2007/04/30														 */
/* ========================================================================= */

PBYTE CPacketMAP_SETPARTS::Set(PBYTE pPacket)
{
	PBYTE pRet, pDataTmp;

	pRet		= pPacket;
	pDataTmp	= CPacketBase::Set (pPacket);

	CopyMemoryRenew (&m_dwMapID,	pDataTmp, sizeof (m_dwMapID),	pDataTmp);	/* マップID */
	CopyMemoryRenew (&m_ptPos,		pDataTmp, sizeof (m_ptPos),		pDataTmp);	/* 座標 */
	CopyMemoryRenew (&m_dwPartsID,	pDataTmp, sizeof (m_dwPartsID),	pDataTmp);	/* パーツID */

	pRet = pDataTmp;
	return pRet;
}

/* Copyright(C)URARA-works 2007 */
