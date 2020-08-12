
// MFCToolView.h : CMFCToolView 클래스의 인터페이스
//

#pragma once

#include "MFCToolDoc.h"

class CPreForm;

BEGIN(Engine)

class CGraphicDev;
class CCubeCol;
class CVIBuffer;
class CCamera;
class CTransform;

END

class CMFCToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// 특성입니다.
public:
	CMFCToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

private:
	Engine::CGraphicDev*	m_pDeviceClass = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;
	Engine::CVIBuffer*		m_pBuffer=nullptr;
	Engine::CVIBuffer*		m_pBufferLand = nullptr;
	Engine::CTransform*		m_pTransformCamera = nullptr;
	Engine::CTransform*		m_pTransformWorld = nullptr;
	Engine::CCamera*		m_pCamera=nullptr;
	CPreForm*				m_pPreform=nullptr;
	bool					m_bWire=false;
	bool					m_bCull=true;
	vector<Engine::VTXCOL>	m_vecVertex;
	list<Engine::INDEX16>	m_listIndex;
	list<Engine::_vec3>		m_listNormal;

public:
	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	void				Reset_Buffer(list<Engine::VTXCOL> _listVertex,list<Engine::INDEX16> _listIndex);
	void				Set_Preform(CPreForm* _preform);
	void				Set_Wire(bool _wire);
	void				Set_Cull(bool _cull);
	void				Begin_Draw();
	void				End_Draw();
	int					Get_VertexNum();
};

#ifndef _DEBUG  // MFCToolView.cpp의 디버그 버전
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

