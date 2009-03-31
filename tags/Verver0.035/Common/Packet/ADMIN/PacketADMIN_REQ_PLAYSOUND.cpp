/* Copyright(C)URARA-works 2008 */
/* ========================================================================= */
/* �t�@�C����	:PacketADMIN_REQ_PLAYSOUND.cpp								 */
/* ���e			:�R�}���h(�Ǘ��Ҍn:���ʉ��̍Đ��v��) �����t�@�C��			 */
/* �쐬			:�N����N���t�����(URARA-works)							 */
/* �쐬�J�n��	:2008/06/02													 */
/* ========================================================================= */

#include "StdAfx.h"
#include "Command.h"
#include "PacketADMIN_REQ_PLAYSOUND.h"

/* ========================================================================= */
/* �֐���	:CPacketADMIN_REQ_PLAYSOUND::CPacketADMIN_REQ_PLAYSOUND			 */
/* ���e		:�R���X�g���N�^													 */
/* ���t		:2008/06/02														 */
/* ========================================================================= */

CPacketADMIN_REQ_PLAYSOUND::CPacketADMIN_REQ_PLAYSOUND()
{
	m_dwSoundID = 0;
}


/* ========================================================================= */
/* �֐���	:CPacketADMIN_REQ_PLAYSOUND::~CPacketADMIN_REQ_PLAYSOUND		 */
/* ���e		:�f�X�g���N�^													 */
/* ���t		:2008/06/02														 */
/* ========================================================================= */

CPacketADMIN_REQ_PLAYSOUND::~CPacketADMIN_REQ_PLAYSOUND()
{
}


/* ========================================================================= */
/* �֐���	:CPacketADMIN_REQ_PLAYSOUND::Make								 */
/* ���e		:�p�P�b�g���쐬													 */
/* ���t		:2008/06/02														 */
/* ========================================================================= */

void CPacketADMIN_REQ_PLAYSOUND::Make(
	DWORD dwSoundID)		/* [in] ���ʉ�ID */
{
	PBYTE pData, pDataTmp;
	DWORD dwSize;
	PPACKETBASE pPacketBase;

	dwSize = sizeof (PACKETBASE) +
			 sizeof (dwSoundID);

	pData = new BYTE[dwSize];
	ZeroMemory (pData, dwSize);
	pPacketBase = (PPACKETBASE)pData;

	pPacketBase->byCmdMain	= SBOCOMMANDID_MAIN_ADMIN;
	pPacketBase->byCmdSub	= SBOCOMMANDID_SUB_ADMIN_REQ_PLAYSOUND;

	pDataTmp = (PBYTE)(pPacketBase + 1);
	CopyMemoryRenew (pDataTmp, &dwSoundID, sizeof (dwSoundID), pDataTmp);	/* ���ʉ�ID */

	RenewPacket (pData, dwSize);
}


/* ========================================================================= */
/* �֐���	:CPacketADMIN_REQ_PLAYSOUND::Set								 */
/* ���e		:�p�P�b�g��ݒ�													 */
/* ���t		:2008/06/02														 */
/* ========================================================================= */

PBYTE CPacketADMIN_REQ_PLAYSOUND::Set(PBYTE pPacket)
{
	PBYTE pRet, pDataTmp;

	pRet		= pPacket;
	pDataTmp	= CPacketBase::Set (pPacket);

	CopyMemoryRenew (&m_dwSoundID, pDataTmp, sizeof (m_dwSoundID), pDataTmp);	/* ���ʉ�ID */

	pRet = pDataTmp;
	return pRet;
}

/* Copyright(C)URARA-works 2008 */