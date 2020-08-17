#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxcolorbutton.h"

#include "MFCToolView.h"

#include "ObjectTab.h"
#include "afxcmn.h"

// CPreForm �� ���Դϴ�.

class CPreForm : public CFormView
{
	DECLARE_DYNCREATE(CPreForm)

protected:
	CPreForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPreForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PREFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Set_ToolView(CMFCToolView* _toolView);

	CMFCToolView*			m_pToolView;
	virtual void OnInitialUpdate();
	CTabCtrl m_Tab;
	CObjectTab* m_pObjTab;
};


