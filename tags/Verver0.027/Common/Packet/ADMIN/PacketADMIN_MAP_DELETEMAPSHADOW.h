/* Copyright(C)URARA-works 2007 */
/* ========================================================================= */
/* �t�@�C����	:PacketADMIN_MAP_DELETEMAPSHADOW.h							 */
/* ���e			:�R�}���h(�Ǘ��Ҍn:�}�b�v�}�b�v�e�폜) ��`�t�@�C��			 */
/* �쐬			:�N����N���t�����(URARA-works)							 */
/* �쐬�J�n��	:2007/06/07													 */
/* ========================================================================= */

#pragma once

#include "PacketBase.h"

/* ========================================================================= */
/* �N���X�錾																 */
/* ========================================================================= */

typedef class CPacketADMIN_MAP_DELETEMAPSHADOW : public CPacketBase
{
public:
			CPacketADMIN_MAP_DELETEMAPSHADOW();				/* �R���X�g���N�^ */
	virtual ~CPacketADMIN_MAP_DELETEMAPSHADOW();			/* �f�X�g���N�^ */

	void	Make	(DWORD dwShadowID);								/* �p�P�b�g���쐬 */
	PBYTE	Set		(PBYTE pPacket);								/* �p�P�b�g��ݒ� */


public:
	DWORD	m_dwShadowID;			/* �}�b�v�eID */
} CPacketADMIN_MAP_DELETEMAPSHADOW, *PCPacketADMIN_MAP_DELETEMAPSHADOW;

/* Copyright(C)URARA-works 2007 */