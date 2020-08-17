
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
	Engine::Safe_Release(m_pBufferLand);
	Engine::Safe_Release(m_pGraphicDev);
	Engine::Safe_Release(m_pDeviceClass);
	Engine::Safe_Release(m_pTransformCamera);
	Engine::Safe_Release(m_pTransformWorld);
	Engine::Safe_Release(m_pCamera);

	Engine::Release_Utility();
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
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	Engine::_vec3 posForLand = Engine::_vec3(-50.f, 0.f, -50.f);
	m_pTransformWorld->Add_Trans(&posForLand);
	m_pTransformWorld->Update_Component(0.f);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pTransformWorld->Set_Transform(m_pGraphicDev);
	
	m_pBufferLand->Render_Buffer();

	posForLand *= -1.f;
	m_pTransformWorld->Add_Trans(&posForLand);
	m_pTransformWorld->Update_Component(0.f);
	m_pTransformWorld->Set_Transform(m_pGraphicDev);

	Begin_Draw();
	if(m_pBuffer!=nullptr)
		m_pBuffer->Render_Buffer();
	End_Draw();

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
	Engine::Ready_Buffer(m_pGraphicDev, RESOURCE_STATIC, L"Test_Map", Engine::BUFFER_KOREA,101,101,1);

	m_pBufferLand = static_cast<Engine::CVIBuffer*>(Engine::Clone(RESOURCE_STATIC, L"Test_Map"));
	m_pBuffer = static_cast<Engine::CVIBuffer*>(Engine::Create_Preview(m_pGraphicDev, L"../Asset/VIMesh/Test.dat"));
	m_pTransformCamera = Engine::CTransform::Create();
	m_pTransformWorld = Engine::CTransform::Create();

	Engine::Load_ParticleMFC(m_pGraphicDev);

	_matrix  matProj;

	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(45.f),
		_float(1600) / 900,
		1.f,
		1000.f);

	RECT clientScreen;
	GetClientRect(&clientScreen);
	ClientToScreen(&clientScreen);

	m_pCamera = Engine::CCamera::Create();

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);

	SetTimer(0, 1, nullptr);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	_vec3 posVec;
	_vec3 lookVec;
	_vec3 rightVec;
	_vec3 upVec;

	m_pTransformCamera->Update_Component(0.f);
	m_pTransformCamera->Get_Info(Engine::INFO_POS, &posVec);

	m_pCamera->Update_CameraMFC(m_pGraphicDev, posVec, &lookVec, &upVec);
	D3DXVec3Cross(&rightVec,&_vec3(0.f, 1.f, 0.f), &lookVec);
	D3DXVec3Normalize(&rightVec, &rightVec);

	lookVec *= 0.2f;
	rightVec *= 0.2f;
	upVec *= 0.2f;

	/*if (Engine::Get_DIMouseState(DIM_RB) & 0x80)
	{
		if (Engine::Get_DIKeyState(DIK_W) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&lookVec);
		}

		if (Engine::Get_DIKeyState(DIK_S) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&(-1*lookVec));
		}

		if (Engine::Get_DIKeyState(DIK_D) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&rightVec);
		}

		if (Engine::Get_DIKeyState(DIK_A) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&(-1 * rightVec));
		}

		if (Engine::Get_DIKeyState(DIK_Q) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&upVec);
		}

		if (Engine::Get_DIKeyState(DIK_E) & 0x80)
		{
			m_pTransformCamera->Add_Trans(&(-1 * upVec));
		}

	}*/



	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&lookVec);
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&(-1 * lookVec));
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&rightVec);
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&(-1 * rightVec));
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&upVec);
		}

		if (GetAsyncKeyState('E') & 0x8000)
		{
			m_pTransformCamera->Add_Trans(&(-1 * upVec));
		}

	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		m_pTransformCamera->Set_Trans(&_vec3(0.f, 0.f, -5.f));
		m_pCamera->Set_Angle(0, 0.f);
		m_pCamera->Set_Angle(1, 0.f);
		m_pCamera->Set_Angle(2, 0.f);
	}

	Invalidate(FALSE);


	CView::OnTimer(nIDEvent);
}

void CMFCToolView::Reset_Buffer(list<Engine::VTXCOL> _listVertex, list<Engine::INDEX16> _listIndex)
{
	Engine::Safe_Release(m_pBuffer);

	m_pBuffer = static_cast<CVIBuffer*>(Engine::Create_Preview(m_pGraphicDev, _listVertex, _listIndex));
}

void CMFCToolView::Set_Wire(bool _wire)
{
	m_bWire = _wire;
}

void CMFCToolView::Set_Cull(bool _cull)
{
	m_bCull = _cull;
}

void CMFCToolView::Begin_Draw()
{
	if (m_bWire)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	else
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (m_bCull)
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	else
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

}

void CMFCToolView::End_Draw()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}
