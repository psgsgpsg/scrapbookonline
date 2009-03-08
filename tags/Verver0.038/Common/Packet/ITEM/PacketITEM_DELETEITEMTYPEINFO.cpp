/* Copyright(C)URARA-works 2007 */
/* ========================================================================= */
/* ファイル名	:PacketITEM_DELETEITEMTYPEINFO.cpp							 */
/* 内容			:コマンド(アイテム系:アイテム種別情報削除) 実装ファイル		 */
/* 作成			:年がら年中春うらら(URARA-works)							 */
/* 作成開始日	:2007/10/03													 */
/* ========================================================================= */

#include "StdAfx.h"
#include "Command.h"
#include "PacketITEM_DELETEITEMTYPEINFO.h"


/* ========================================================================= */
/* 関数名	:CPacketITEM_DELETEITEMTYPEINFO::CPacketITEM_DELETEITEMTYPEINFO	 */
/* 内容		:コンストラクタ													 */
/* 日付		:2007/10/03														 */
/* ========================================================================= */

CPacketITEM_DELETEITEMTYPEINFO::CPacketITEM_DELETEITEMTYPEINFO()
{
	m_dwTypeID = 0;
}


/* ========================================================================= */
/* 関数名	:CPacketITEM_DELETEITEMTYPEINFO::~CPacketITEM_DELETEITEMTYPEINFO */
/* 内容		:デストラクタ													 */
/* 日付		:2007/10/03														 */
/* ========================================================================= */

CPacketITEM_DELETEITEMTYPEINFO::~CPacketITEM_DELETEITEMTYPEINFO()
{
}


/* ========================================================================= */
/* 関数名	:CPacketITEM_DELETEITEMTYPEINFO::Make							 */
/* 内容		:パケットを作成													 */
/* 日付		:2007/10/03														 */
/* ========================================================================= */

void CPacketITEM_DELETEITEMTYPEINFO::Make(
	DWORD dwTypeID)		/* [in] 種別ID */
{
	PBYTE pData, pDataTmp;
	DWORD dwSize;
	PPACKETBASE pPacketBase;

	dwSize = sizeof (PACKETBASE) +
			 sizeof (dwTypeID);

	pData = new BYTE[dwSize];
	ZeroMemory (pData, dwSize);
	pPacketBase = (PPACKETBASE)pData;

	pPacketBase->byCmdMain	= SBOCOMMANDID_MAIN_ITEM;
	pPacketBase->byCmdSub	= SBOCOMMANDID_SUB_ITEM_DELETEITEMTYPEINFO;

	pDataTmp = (PBYTE)(pPacketBase + 1);
	CopyMemoryRenew (pDataTmp, &dwTypeID, sizeof (dwTypeID), pDataTmp);	/* 種別ID */

	RenewPacket (pData, dwSize);
}


/* ========================================================================= */
/* 関数名	:CPacketITEM_DELETEITEMTYPEINFO::Set							 */
/* 内容		:パケットを設定													 */
/* 日付		:2007/10/03														 */
/* ========================================================================= */

PBYTE CPacketITEM_DELETEITEMTYPEINFO::Set(PBYTE pPacket)
{
	PBYTE pRet, pDataTmp;

	pRet		= pPacket;
	pDataTmp	= CPacketBase::Set (pPacket);

	CopyMemoryRenew (&m_dwTypeID,	pDataTmp, sizeof (m_dwTypeID), pDataTmp);	/* 種別ID */

	pRet = pDataTmp;
	return pRet;
}

/* Copyright(C)URARA-works 2007 */
