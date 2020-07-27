
// MFCToolView.h : CMFCToolView Ŭ������ �������̽�
//

#pragma once

BEGIN(Engine)

class CGraphicDev;
class CCubeCol;
class CVIBuffer;

END

class CMFCToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// Ư���Դϴ�.
public:
	CMFCToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // MFCToolView.cpp�� ����� ����
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

