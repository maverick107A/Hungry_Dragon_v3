
// MFCToolView.h : CMFCToolView 클래스의 인터페이스
//

#pragma once

BEGIN(Engine)

class CGraphicDev;
class CCubeCol;
class CVIBuffer;

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
	Engine::CVIBuffer*		m_pBuffer;
	bool					m_bCam = false;

private:
	POINT			m_tCenter = {};
	float			m_fAngleY = 0.f;
	float			m_fAngleX = 0.f;
	float			m_fAngleZ = 0.f;
	D3DXVECTOR3			m_vDir = { 0.f,0.f,0.f };
	D3DXVECTOR3			m_vDirCam = {0.f,0.f,0.f};
	D3DXVECTOR3			m_vUpOrigin = { 0.f, 1.f, 0.f };
	D3DXVECTOR3			m_vUp = { 0.f, 1.f, 0.f };
	D3DXVECTOR3			m_vUpCam = { 0.f, 1.f, 0.f };
	D3DXVECTOR3			m_vLook = { 0.f,0.f,1.f };
	D3DXVECTOR3			m_vPos = { 0.f,50.f,0.f };
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCToolView.cpp의 디버그 버전
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

