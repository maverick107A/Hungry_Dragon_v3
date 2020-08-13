#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxcolorbutton.h"

#include "MFCToolView.h"

// CPreForm 폼 뷰입니다.

class CPreForm : public CFormView
{
	DECLARE_DYNCREATE(CPreForm)

protected:
	CPreForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVertexAdd();
	afx_msg void OnLbnSelchangeVertexList();
	afx_msg void OnBnClickedVertexSave();
	afx_msg void OnBnClickedIndexAdd();
	afx_msg void OnLbnSelchangeIndexList();
	afx_msg void OnBnClickedIndexSave();
	afx_msg void OnBnClickedIndexDel();
	afx_msg void OnBnClickedVertexDel();
	afx_msg void OnBnClickedMeshSave();
	afx_msg void OnBnClickedMeshLoad();
	afx_msg void OnBnClickedSetPreview();
	afx_msg void OnBnClickedBtnWire();
	afx_msg void OnBnClickedBtnCul();

	void Erase_Index(int _delIndex);
	void Add_VertexToListBox();
	void Add_IndexToListBox();
	void Set_ToolView(CMFCToolView* _toolView);
	bool Check_Index16(Engine::INDEX16 _index,int _vertexNum);
	void Change_ColorMFCToDirect(DWORD* _mfc, DWORD* _direct);
	void Change_ColorDirectToMFC(DWORD* _direct, DWORD* _mfc);
	void GiveBack_Color(int _index);

	list<Engine::VTXCOL> Get_Vertex();

	CListBox				m_vertexListBox;
	Engine::_int			m_vertexCount=0;
	list<Engine::VTXCOL>	m_listVertex;
	CEdit					m_VertexPosX;
	CEdit					m_VertexPosY;
	CEdit					m_VertexPosZ;
	CMFCColorButton			m_colorButton;

	CListBox				m_indexListBox;
	Engine::_int			m_indexCount=0;
	list<Engine::INDEX16>	m_listIndex;
	CEdit					m_Index0;
	CEdit					m_Index1;
	CEdit					m_Index2;
	CMFCToolView*			m_pToolView;

	CButton					m_bWire;
	CButton					m_bCul;

	int						m_pickIndex = -1;
	Engine::_ulong			m_pickColor;
};


