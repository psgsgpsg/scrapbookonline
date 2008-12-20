/* Copyright(C)URARA-works 2008 */
/* ========================================================================= */
/* �t�@�C����	:WindowOPTION_INPUTSET.cpp									 */
/* ���e			:�I�v�V����-���͐ݒ�E�B���h�E�N���X �����t�@�C��			 */
/* �쐬			:�N����N���t�����(URARA-works)							 */
/* �쐬�J�n��	:2008/07/12													 */
/* ========================================================================= */

#include "stdafx.h"
#include "Img32.h"
#include "MgrData.h"
#include "MgrGrpData.h"
#include "MgrWindow.h"
#include "MgrSound.h"
#include "WindowOPTION_INPUTSET.h"


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::CWindowOPTION_INPUTSET					 */
/* ���e		:�R���X�g���N�^													 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

CWindowOPTION_INPUTSET::CWindowOPTION_INPUTSET()
{
	m_nPosMax		= 0;
	m_bInput		= TRUE;
	m_nID			= WINDOWTYPE_OPTION_INPUTSET;
	m_ptViewPos.x	= 8 * 13;
	m_ptViewPos.y	= 16 * 10;
	m_sizeWindow.cx	= 16 * 2 + 16 * 16 + 8;
	m_sizeWindow.cy	= 16 * 2 + 16 * 1;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::~CWindowOPTION_INPUTSET				 */
/* ���e		:�f�X�g���N�^													 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

CWindowOPTION_INPUTSET::~CWindowOPTION_INPUTSET()
{
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::Create									 */
/* ���e		:�쐬															 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

void CWindowOPTION_INPUTSET::Create(CMgrData *pMgrData)
{
	CWindowBase::Create (pMgrData);

	m_bActive = TRUE;
	m_pDib->Create (m_sizeWindow.cx, m_sizeWindow.cy);
	m_pDib->SetColorKey (0);
	m_nPos = 0;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::Draw									 */
/* ���e		:�`��															 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

void CWindowOPTION_INPUTSET::Draw(PCImg32 pDst)
{
	int nLevel;
	HDC hDC;
	HFONT hFontOld;
	COLORREF clText;

	if (m_dwTimeDrawStart) {
		goto Exit;
	}

	DrawFrame ();

	clText		= RGB (1, 1, 1);
	hDC			= m_pDib->Lock ();
	hFontOld	= (HFONT)SelectObject (hDC, m_hFont);
	SetBkMode (hDC, TRANSPARENT);

	TextOut2 (hDC, 32, 16 + 16 * 0, "�g�p����W���C�p�b�h�̐ݒ�", clText);

	SelectObject (hDC, hFontOld);
	m_pDib->Unlock ();

	DrawCursor (8, 16 + 16 * m_nPos);
	m_dwTimeDrawStart = timeGetTime ();

Exit:
	nLevel = 100;
	if (m_bActive == FALSE) {
		nLevel = 60;
	}
	pDst->BltLevel (m_ptViewPos.x + 32, m_ptViewPos.y + 32, m_sizeWindow.cx, m_sizeWindow.cy, m_pDib, 0, 0, nLevel, TRUE);
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnUp									 */
/* ���e		:�L�[�n���h��(��)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnUp(void)
{
	BOOL bRet;

	bRet = FALSE;

	if (m_nPos <= 0) {
		goto Exit;
	}
	m_nPos --;
	m_nCursorAnime = 0;
	m_dwLastTimeCursor = 0;
	m_pMgrSound->PlaySound (SOUNDID_CURSORMOVE);

	bRet = TRUE;
Exit:
	return bRet;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnDown									 */
/* ���e		:�L�[�n���h��(��)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnDown(void)
{
	BOOL bRet;

	bRet = FALSE;

	if (m_nPos >= m_nPosMax) {
		goto Exit;
	}
	m_nPos ++;
	m_nCursorAnime = 0;
	m_dwLastTimeCursor = 0;
	m_pMgrSound->PlaySound (SOUNDID_CURSORMOVE);

	bRet = TRUE;
Exit:
	return bRet;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnLeft									 */
/* ���e		:�L�[�n���h��(��)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnLeft(void)
{
	m_nPos = 0;
	m_nCursorAnime = 0;
	m_dwLastTimeCursor = 0;
	m_pMgrSound->PlaySound (SOUNDID_CURSORMOVE);

	return TRUE;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnRight								 */
/* ���e		:�L�[�n���h��(��)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnRight(void)
{
	m_nPos = m_nPosMax;
	m_nCursorAnime = 0;
	m_dwLastTimeCursor = 0;
	m_pMgrSound->PlaySound (SOUNDID_CURSORMOVE);

	return TRUE;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnX									 */
/* ���e		:�L�[�n���h��(X)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnX(BOOL bDown)
{
	BOOL bRet;

	bRet = FALSE;
	if (bDown) {
		goto Exit;
	}

	m_pMgrSound->PlaySound (SOUNDID_OK_PI73);
	PostMessage (m_hWndMain, WM_WINDOWMSG, m_nID, m_nPos);

	bRet = TRUE;
Exit:
	return bRet;
}


/* ========================================================================= */
/* �֐���	:CWindowOPTION_INPUTSET::OnZ									 */
/* ���e		:�L�[�n���h��(Z)												 */
/* ���t		:2008/07/12														 */
/* ========================================================================= */

BOOL CWindowOPTION_INPUTSET::OnZ(BOOL bDown)
{
	BOOL bRet;

	bRet = FALSE;
	if (bDown) {
		goto Exit;
	}

	m_bDelete = TRUE;
	m_pMgrSound->PlaySound (SOUNDID_CANCEL);

	bRet = TRUE;
Exit:
	return bRet;
}

/* Copyright(C)URARA-works 2008 */