// PreForm.cpp : 구현 파일입니다.
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


// CPreForm 진단입니다.

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


// CPreForm 메시지 처리기입니다.

void CPreForm::Set_ToolView(CMFCToolView * _toolView)
{
	m_pToolView = _toolView;
}


void CPreForm::OnInitialUpdate() {
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_Tab.InsertItem(0, L"Object");
	
	//m_Tab.SetCurSel(0);

	//CRect rect;
	//m_Tab.GetWindowRect(&rect);

	//m_pObjTab = new CObjectTab;
	//m_pObjTab->Create(IDD_DIALOG)
}
