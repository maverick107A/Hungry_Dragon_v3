// PreForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "PreForm.h"

using namespace std;

// CPreForm

IMPLEMENT_DYNCREATE(CPreForm, CFormView)

CPreForm::CPreForm()
	: CFormView(IDD_PREFORM)
{
}

CPreForm::~CPreForm()
{
}

void CPreForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CPreForm, CFormView)
END_MESSAGE_MAP()


// CPreForm �����Դϴ�.

#ifdef _DEBUG
void CPreForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreForm �޽��� ó�����Դϴ�.

void CPreForm::Set_ToolView(CMFCToolView * _toolView)
{
	m_pToolView = _toolView;
}


void CPreForm::OnInitialUpdate() {
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_Tab.InsertItem(0, L"Object");
	
	//m_Tab.SetCurSel(0);

	//CRect rect;
	//m_Tab.GetWindowRect(&rect);

	//m_pObjTab = new CObjectTab;
	//m_pObjTab->Create(IDD_DIALOG)
}
