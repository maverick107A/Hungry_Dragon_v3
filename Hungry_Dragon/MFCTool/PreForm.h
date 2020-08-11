#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"



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

	void Erase_Index(int _delIndex);
	void Add_VertexToListBox();
	void Add_IndexToListBox();
	bool Check_Index16(Engine::INDEX16 _index,int _vertexNum);

	CListBox				m_vertexListBox;
	Engine::_int			m_vertexCount=0;
	list<Engine::VTXCOL>	m_listVertex;
	CEdit					m_VertexPosX;
	CEdit					m_VertexPosY;
	CEdit					m_VertexPosZ;

	CListBox				m_indexListBox;
	Engine::_int			m_indexCount=0;
	list<Engine::INDEX16>	m_listIndex;
	CEdit					m_Index0;
	CEdit					m_Index1;
	CEdit					m_Index2;
	
};


