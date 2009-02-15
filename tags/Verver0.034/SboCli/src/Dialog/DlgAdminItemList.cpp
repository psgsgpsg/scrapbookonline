/* Copyright(C)URARA-works 2007 */
/* ========================================================================= */
/* �t�@�C����	:DlgAdminItemList.cpp										 */
/* ���e			:�A�C�e���ꗗ�_�C�A���O�N���X �����t�@�C��					 */
/* �쐬			:�N����N���t�����(URARA-works)							 */
/* �쐬�J�n��	:2007/08/14													 */
/* ========================================================================= */

#include "stdafx.h"
#include "resource.h"
#include "PacketADMIN_ITEM_ADD.h"
#include "PacketADMIN_ITEM_COPY.h"
#include "PacketADMIN_ITEM_DELETE.h"
#include "PacketITEM_REQ_ITEMINFO.h"
#include "PacketITEM_RENEWITEMINFO.h"
#include "UraraSockTCPSBO.h"
#include "LibInfoItemType.h"
#include "LibInfoItem.h"
#include "LayoutHelper.h"
#include "InfoCharCli.h"
#include "LibInfoCharCli.h"
#include "MgrData.h"
#include "DlgAdminItemNew.h"
#include "DlgAdminItemList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMERID_RENEW	(100)		/* �ꗗ�X�V�^�C�}�[ */
#define TIMER_RENEW		(100)		/* �ꗗ�X�V�^�C�}�[���� */

/* ========================================================================= */
/* �N���X�̐ݒ�																 */
/* ========================================================================= */

void CDlgAdminItemList::DoDataExchange(CDataExchange* pDX)
{
	CDlgAdminBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAdminItemList)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_DROP, m_bDrop);
	DDX_Check(pDX, IDC_MAP, m_bMap);
}

BEGIN_MESSAGE_MAP(CDlgAdminItemList, CDlgAdminBase)
	//{{AFX_MSG_MAP(CDlgAdminItemList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_RENEW, OnRenew)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DROP, &CDlgAdminItemList::OnBnClickedDrop)
	ON_BN_CLICKED(IDC_MAP, &CDlgAdminItemList::OnBnClickedMap)
	ON_WM_TIMER()
END_MESSAGE_MAP()


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::CDlgAdminItemList							 */
/* ���e		:�R���X�g���N�^													 */
/* ���t		:2007/08/14														 */
/* ========================================================================= */

CDlgAdminItemList::CDlgAdminItemList(CWnd* pParent /*=NULL*/)
	: CDlgAdminBase(CDlgAdminItemList::IDD, pParent)
	, m_bDrop(TRUE)
	, m_bMap(TRUE)
{
	//{{AFX_DATA_INIT(CDlgAdminItemList)
	//}}AFX_DATA_INIT

	m_pWndNotify		= NULL;
	m_pLibInfoItemType	= NULL;
	m_pLibInfoItem		= NULL;
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::~CDlgAdminItemList							 */
/* ���e		:�f�X�g���N�^													 */
/* ���t		:2007/08/14														 */
/* ========================================================================= */

CDlgAdminItemList::~CDlgAdminItemList()
{
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::Init										 */
/* ���e		:������															 */
/* ���t		:2007/08/14														 */
/* ========================================================================= */

void CDlgAdminItemList::Init(CMgrData *pMgrData)
{
	CDlgAdminBase::Init (pMgrData);

	m_pLibInfoItemType	= m_pMgrData->GetLibInfoItemType ();
	m_pLibInfoItem		= m_pMgrData->GetLibInfoItem ();

	/* �E�B���h�E�쐬 */
	Create (CDlgAdminItemList::IDD, m_pWndParent);
	ShowWindow (SW_SHOW);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::Renew										 */
/* ���e		:�ꗗ���X�V														 */
/* ���t		:2007/08/14														 */
/* ========================================================================= */

void CDlgAdminItemList::Renew(void)
{
	DWORD dwMapID;
	int i, nCount, nSelect, nIndex;
	PCInfoItem pInfoItem;
	PCInfoCharCli pInfoChar;
	PCLibInfoCharCli pLibInfoChar;
	CString strTmp;

	m_pLibInfoItem->Enter ();

	dwMapID = m_pMgrData->GetMapID ();
	pLibInfoChar = m_pMgrData->GetLibInfoChar ();

	nSelect = m_List.GetNextItem (-1, LVNI_SELECTED);
	m_List.SetRedraw (FALSE);
	m_List.DeleteAllItems ();

	nCount = m_pLibInfoItem->GetCount ();
	m_List.SetItemCount (nCount);

	nIndex = 0;
	for (i = 0; i < nCount; i ++) {
		pInfoItem = (PCInfoItem)m_pLibInfoItem->GetPtr (i);
		if (pInfoItem == NULL) {
			continue;
		}
		if (m_bDrop) {
			if (pInfoItem->m_dwMapID == 0) {
				continue;
			}
		}
		if (m_bMap) {
			if (pInfoItem->m_dwMapID != dwMapID) {
				continue;
			}
		}

		strTmp.Format ("%d", pInfoItem->m_dwItemID);
		m_List.InsertItem (nIndex, strTmp);
		m_List.SetItemData (nIndex, pInfoItem->m_dwItemID);		/* ID */
		m_List.SetItemText (nIndex, 1, pInfoItem->m_strName);	/* �A�C�e���� */

		strTmp = m_pLibInfoItemType->GetTypeNameTypeID (pInfoItem->m_dwItemTypeID);
		m_List.SetItemText (nIndex, 2, strTmp);					/* ��� */

		strTmp.Empty ();
		pInfoChar = (PCInfoCharCli)pLibInfoChar->GetPtr (pInfoItem->m_dwCharID);
		if (pInfoChar) {
			strTmp.Format ("[%u]%s", pInfoChar->m_dwCharID, (LPCSTR)pInfoChar->m_strCharName);
		} else {
			if (pInfoItem->m_dwCharID != 0) {
				strTmp.Format ("[%u]", pInfoItem->m_dwCharID);
			}
		}
		m_List.SetItemText (nIndex, 3, strTmp);					/* �����L���� */

		strTmp.Empty ();
		if (pInfoItem->m_dwMapID) {
			strTmp.Format ("MAPID:%u (%d, %d)", pInfoItem->m_dwMapID, pInfoItem->m_ptPos.x, pInfoItem->m_ptPos.y);
		}
		m_List.SetItemText (nIndex, 4, strTmp);					/* �z�u���W */
		nIndex ++;
	}

	if (nSelect >= 0) {
		m_List.SetItemState (nSelect, LVNI_SELECTED, LVNI_SELECTED);
		m_List.EnsureVisible (nSelect, FALSE);
	}
	m_List.SetRedraw ();

	m_pLibInfoItem->Leave ();
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnAdminMsg									 */
/* ���e		:���b�Z�[�W�n���h��(WM_ADMINMSG)								 */
/* ���t		:2007/08/23														 */
/* ========================================================================= */

void CDlgAdminItemList::OnAdminMsg(int nType, DWORD dwPara)
{
	int i, nCount, nResult;
	UINT unState;

	switch (nType) {
	case ADMINMSG_RENEWMAPINFO:	/* �}�b�v���X�V */
		SetTimer (TIMERID_RENEW, TIMER_RENEW, NULL);
		break;
	case ADMINMSG_NOTIFYTYPE_LBUTTONDOWN:	/* ���N���b�N�ʒm */
		switch (m_pMgrData->GetAdminNotifyTypeL ()) {
		case ADMINNOTIFYTYPE_ITEMID:			/* �A�C�e��ID */
			nResult = GetIndex (dwPara);
			if (nResult < 0) {
				break;
			}
			/* �N���b�N���ꂽ�A�C�e��������I�� */
			nCount = m_List.GetItemCount ();
			for (i = 0; i < nCount; i ++) {
				unState = 0;
				if (i == nResult) {
					unState = LVIS_SELECTED | LVIS_FOCUSED;
				}
				m_List.SetItemState (i, unState, LVIS_SELECTED | LVIS_FOCUSED);
			}
			m_List.EnsureVisible (nResult, FALSE);
			break;

		case ADMINNOTIFYTYPE_CHARPOS:			/* �L�������W */
			{
				PCInfoCharCli pInfoChar;
				PCDlgAdminItemNew pDlg;

				if (m_pWndNotify == NULL) {
					break;
				}
				pDlg = (PCDlgAdminItemNew)m_pWndNotify;
				pInfoChar = m_pMgrData->GetPlayerChar ();

				pDlg->m_nMapID	= pInfoChar->m_dwMapID;
				pDlg->m_nPosX	= HIWORD (dwPara);
				pDlg->m_nPosY	= LOWORD (dwPara);
				pDlg->UpdateData (FALSE);
			}
			break;
		}
	}
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnInitDialog								 */
/* ���e		:���b�Z�[�W�n���h��(WM_INITDIALOG)								 */
/* ���t		:2007/08/14														 */
/* ========================================================================= */

BOOL CDlgAdminItemList::OnInitDialog()
{
	CDlgAdminBase::OnInitDialog();

	m_List.SetExtendedStyle (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn (0, "ID",			LVCFMT_LEFT, 40);
	m_List.InsertColumn (1, "�A�C�e����",	LVCFMT_LEFT, 120);
	m_List.InsertColumn (2, "���",			LVCFMT_LEFT, 120);
	m_List.InsertColumn (3, "�����L����",	LVCFMT_LEFT, 120);
	m_List.InsertColumn (4, "�z�u���W",		LVCFMT_LEFT, 120);

	RegisterControl (IDC_RENEW,	LH_CTRL_X);
	RegisterControl (IDC_LIST,	LH_CTRL_WIDTH | LH_CTRL_HEIGHT);

	/* �S�A�C�e������v�� */
	OnRenew ();

	return TRUE;
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnTimer										 */
/* ���e		:���b�Z�[�W�n���h��(WM_TIMER)									 */
/* ���t		:2008/11/29														 */
/* ========================================================================= */

void CDlgAdminItemList::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case TIMERID_RENEW:
		KillTimer (TIMERID_RENEW);
		Renew ();
		break;
	}

	CDlgAdminBase::OnTimer(nIDEvent);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnMainFrame									 */
/* ���e		:���b�Z�[�W�n���h��(WM_MAINFRAME)								 */
/* ���t		:2007/08/16														 */
/* ========================================================================= */

void CDlgAdminItemList::OnMainFrame(DWORD dwCommand, DWORD dwParam)
{
	switch (dwCommand) {
	case MAINFRAMEMSG_RENEWITEMINFO:		/* �A�C�e�����X�V */
		SetTimer (TIMERID_RENEW, TIMER_RENEW, NULL);
		break;
	}
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnAdd										 */
/* ���e		:�{�^���n���h��(�V�K�ǉ�)										 */
/* ���t		:2007/08/15														 */
/* ========================================================================= */

void CDlgAdminItemList::OnAdd()
{
	int nResult;
	PCInfoItem pInfoItem;
	CPacketADMIN_ITEM_ADD Packet;
	CDlgAdminItemNew Dlg(this);

	nResult = m_pLibInfoItemType->GetCount ();
	if (nResult <= 0) {
		MessageBox ("�A�C�e����ʂ������̂Œǉ��ł��܂���", "�G���[", MB_OK | MB_ICONINFORMATION);
		return;
	}

	pInfoItem = NULL;
	m_pMgrData->SetAdminNotifyTypeL (ADMINNOTIFYTYPE_CHARPOS);

	Dlg.Init (m_pMgrData, &m_pWndNotify);
	nResult = Dlg.DoModal ();
	if (nResult != IDOK) {
		goto Exit;
	}

	pInfoItem = (PCInfoItem)m_pLibInfoItem->GetNew ();
	Dlg.Get (pInfoItem);

	Packet.Make (pInfoItem);
	m_pSock->Send (&Packet);

Exit:
	m_pMgrData->SetAdminNotifyTypeL (ADMINNOTIFYTYPE_ITEMID);
	m_pWndNotify = NULL;
	SAFE_DELETE (pInfoItem);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnModify									 */
/* ���e		:�{�^���n���h��(�ҏW)											 */
/* ���t		:2007/08/16														 */
/* ========================================================================= */

void CDlgAdminItemList::OnModify()
{
	int nResult;
	DWORD dwItemID;
	CDlgAdminItemNew Dlg(this);
	PCInfoItem pInfoItem;
	CPacketITEM_RENEWITEMINFO Packet;

	m_pMgrData->SetAdminNotifyTypeL (ADMINNOTIFYTYPE_CHARPOS);

	nResult = m_List.GetNextItem (-1, LVNI_SELECTED);
	if (nResult < 0) {
		goto Exit;
	}
	dwItemID	= m_List.GetItemData (nResult);
	pInfoItem	= (PCInfoItem)m_pLibInfoItem->GetPtr (dwItemID);
	if (pInfoItem == NULL) {
		goto Exit;
	}

	Dlg.Init (m_pMgrData, &m_pWndNotify);
	Dlg.SetModify (pInfoItem);

	nResult = Dlg.DoModal ();
	if (nResult != IDOK) {
		goto Exit;
	}

	Dlg.Get (pInfoItem);

	Packet.Make (pInfoItem);
	m_pSock->Send (&Packet);

Exit:
	m_pMgrData->SetAdminNotifyTypeL (ADMINNOTIFYTYPE_ITEMID);
	m_pWndNotify = NULL;
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnCopy										 */
/* ���e		:�{�^���n���h��(�R�s�[)											 */
/* ���t		:2007/09/22														 */
/* ========================================================================= */

void CDlgAdminItemList::OnCopy()
{
	int nNo, nResult;
	DWORD dwItemID;
	PCInfoItem pInfoItem;
	CPacketADMIN_ITEM_COPY Packet;

	nNo = m_List.GetNextItem (-1, LVNI_SELECTED);
	if (nNo < 0) {
		return;
	}
	dwItemID	= m_List.GetItemData (nNo);
	pInfoItem	= (PCInfoItem)m_pLibInfoItem->GetPtr (dwItemID);
	if (pInfoItem == NULL) {
		return;
	}

	nResult = MessageBox ("�I������Ă���A�C�e�����R�s�[���܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION);
	if (nResult != IDYES) {
		return;
	}

	Packet.Make (dwItemID);
	m_pSock->Send (&Packet);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnDelete									 */
/* ���e		:�{�^���n���h��(�폜)											 */
/* ���t		:2007/08/19														 */
/* ========================================================================= */

void CDlgAdminItemList::OnDelete()
{
	int nCount, nResult;
	DWORD dwItemID;
	PCInfoItem pInfoItem;
	CString strTmp;
	CPacketADMIN_ITEM_DELETE Packet;
	ARRAYDWORD adwItemID;

	nResult = -1;
	nCount  = 0;
	while (1) {
		nResult = m_List.GetNextItem (nResult, LVNI_SELECTED);
		if (nResult < 0) {
			break;
		}
		dwItemID	= m_List.GetItemData (nResult);
		pInfoItem	= (PCInfoItem)m_pLibInfoItem->GetPtr (dwItemID);
		if (pInfoItem == NULL) {
			continue;
		}
		adwItemID.Add (dwItemID);
		nCount ++;
	}
	if (nCount <= 0) {
		return;
	}
	if (nCount == 1) {
		pInfoItem = (PCInfoItem)m_pLibInfoItem->GetPtr (adwItemID[0]);
		strTmp.Format ("[%s]���폜���܂����H", (LPCSTR)pInfoItem->m_strName);
	} else {
		strTmp.Format ("�I������Ă���A�C�e�����폜���܂����H");
	}
	nResult = MessageBox (strTmp, "�m�F", MB_YESNO | MB_ICONQUESTION);
	if (nResult != IDYES) {
		return;
	}

	Packet.Make (&adwItemID);
	m_pSock->Send (&Packet);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnRenew										 */
/* ���e		:�{�^���n���h��(�X�V)											 */
/* ���t		:2007/09/08														 */
/* ========================================================================= */

void CDlgAdminItemList::OnRenew()
{
	CPacketITEM_REQ_ITEMINFO Packet;

	/* �S�A�C�e������v�� */
	Packet.Make (0);
	m_pSock->Send (&Packet);
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnBnClickedDrop								 */
/* ���e		:�`�F�b�N�{�^���n���h��(�����Ă�����̂����\��)					 */
/* ���t		:2008/11/29														 */
/* ========================================================================= */

void CDlgAdminItemList::OnBnClickedDrop()
{
	UpdateData ();
	Renew ();
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::OnBnClickedDrop								 */
/* ���e		:�`�F�b�N�{�^���n���h��(���݂̃}�b�v�̂�)						 */
/* ���t		:2008/11/29														 */
/* ========================================================================= */

void CDlgAdminItemList::OnBnClickedMap()
{
	UpdateData ();
	Renew ();
}


/* ========================================================================= */
/* �֐���	:CDlgAdminItemList::GetIndex									 */
/* ���e		:�A�C�e��ID����C���f�b�N�X���擾								 */
/* ���t		:2007/08/23														 */
/* ========================================================================= */

int CDlgAdminItemList::GetIndex(DWORD dwItemID)
{
	int nRet, i, nCount;
	DWORD dwItemData;

	nRet = -1;

	nCount = m_List.GetItemCount ();
	for (i = 0; i < nCount; i ++) {
		dwItemData = m_List.GetItemData (i);
		if (dwItemData == dwItemID) {
			nRet = i;
			break;
		}
	}

	return nRet;
}

/* Copyright(C)URARA-works 2007 */