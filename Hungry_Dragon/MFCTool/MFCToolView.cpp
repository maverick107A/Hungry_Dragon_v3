
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"

//-------------------------------------------------------
//�Ŵ��� ���********************************************
//-------------------------------------------------------
//���⿡ �Ŵ��� ��� �߰�

#include "Export_Function.h"


//-------------------------------------------------------
//��Ÿ ���**********************************************
//-------------------------------------------------------
//���⿡ ��Ÿ ��� �߰�


//-------------------------------------------------------

USING(Engine)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CView)

BEGIN_MESSAGE_MAP(CMFCToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFCToolView::~CMFCToolView()
{
	Engine::Safe_Release(m_pBuffer);
	Engine::Safe_Release(m_pGraphicDev);
	Engine::Safe_Release(m_pDeviceClass);

	Engine::Release_Resources();
	Engine::Release_System();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	m_pBuffer->Render_Buffer();

	Engine::Render_End();
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnInitialUpdate() {
	CView::OnInitialUpdate();
	//g_hWnd = m_hWnd;
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SetTimer(0, 1, nullptr);
	
	Engine::Ready_GraphicDev(m_hWnd,
		Engine::MODE_WIN,
		WINCX,
		WINCY,
		&m_pDeviceClass);

	m_pDeviceClass->AddRef();

	m_pGraphicDev = m_pDeviceClass->GetDevice();
	m_pGraphicDev->AddRef();

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	Engine::Reserve_ContainerSize(RESOURCE_END);
	Engine::Ready_Buffer(m_pGraphicDev, RESOURCE_STATIC, L"Test_Buffer", Engine::BUFFER_RCCOL);

	m_pBuffer = static_cast<Engine::CVIBuffer*>(Engine::Clone(RESOURCE_STATIC, L"Test_Buffer"));

	_matrix  matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(1600) / 900,
		1.f,
		1000.f);

	RECT clientScreen;
	GetClientRect(&clientScreen);
	ClientToScreen(&clientScreen);
	m_tCenter = { (LONG)((clientScreen.left+clientScreen.right)*0.5f),  (LONG)((clientScreen.top + clientScreen.bottom)*0.5f) };

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//PŰ�� ī�޶� ���
	if (GetAsyncKeyState('P')&0x8000) {
		m_bCam = true;
	}

	if (GetAsyncKeyState('O') & 0x8000) {
		m_bCam = false;
	}

	if (m_bCam) {
		POINT tPos = {};
		GetCursorPos(&tPos);
		/*m_fAngleY += (tPos.x - m_tCenter.x)*0.01f*cosf(m_fAngleZ) + (tPos.y - m_tCenter.y)*0.01f*sinf(m_fAngleZ);
		m_fAngleX += (tPos.y - m_tCenter.y)*0.01f*cosf(m_fAngleZ) + -(tPos.x - m_tCenter.x)*0.01f*sinf(m_fAngleZ);*/
		m_fAngleY += (tPos.x - m_tCenter.x)*0.005f + (tPos.y - m_tCenter.y)*0.005f;
		m_fAngleX += (tPos.y - m_tCenter.y)*0.005f + -(tPos.x - m_tCenter.x)*0.005f;

		D3DXMATRIX vRotZ;
		D3DXMatrixRotationZ(&vRotZ, m_fAngleZ);
		D3DXVec3TransformNormal(&m_vUp, &m_vUpOrigin, &vRotZ);



		D3DXMATRIX vRotX, vRotY, vRotTotal;
		D3DXMatrixRotationX(&vRotX, m_fAngleX);
		//D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRot);


		D3DXMatrixRotationY(&vRotY, m_fAngleY);

		vRotTotal = vRotX*vRotY;
		D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRotTotal);
		//������
		D3DXVec3TransformNormal(&m_vUpCam, &m_vUp, &vRotTotal);

		SetCursorPos(m_tCenter.x, m_tCenter.y);

		m_vDirCam = m_vDir;
		m_vDirCam = m_vPos + m_vDir;

		_matrix		matView, matProj;



		if (GetAsyncKeyState(VK_SHIFT))
			m_vDir *= 2.f;

		if (GetAsyncKeyState('W'))
			m_vPos += 0.1f*m_vDir;
		if (GetAsyncKeyState('S'))
			m_vPos -= 0.1f*m_vDir;

		D3DXVECTOR3 rightVec;
		D3DXVec3Cross(&rightVec, &m_vUpCam, &m_vDir);

		if (GetAsyncKeyState('A'))
			m_vPos -= 0.1f*rightVec;
		if (GetAsyncKeyState('D'))
			m_vPos += 0.1f*rightVec;

		if (GetAsyncKeyState(VK_SPACE))
			m_vPos.y += 0.1f;

		if (GetAsyncKeyState(VK_CONTROL))
			m_vPos.y -= 0.1f;

		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDirCam, &m_vUpCam);
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);
	}

	InvalidateRect(nullptr,FALSE);

	CView::OnTimer(nIDEvent);
}
