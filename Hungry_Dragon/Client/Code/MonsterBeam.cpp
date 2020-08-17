#include "stdafx.h"
#include "MonsterBeam.h"
#include "Export_Function.h"
#include "Export_Function.h"
#include "BulletMain.h"


CMonsterBeam::CMonsterBeam(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CBulletMain(pGraphicDev)
{
}

CMonsterBeam::~CMonsterBeam(void)
{
}

HRESULT CMonsterBeam::Ready_Object(void)
{

	Engine::CBulletMain::Ready_Object();
	Add_Component();
	m_eState = IDLE_BULLET;
	m_preState = IDLE_BULLET;



	return S_OK;
}

int CMonsterBeam::Update_Object(const float & fTimeDelta)
{
	//Engine::CBulletMain::Update_Object(fTimeDelta);


	if (m_bFirst)
	{
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransformX->Set_Trans(&m_vFirstPos);

	//	m_pTransform->Add_Trans(&D3DXVECTOR3(1.f, 0.f, 0.f));
		m_pTransform->m_vScale.y = 100.f;

		CGameObject* pPlayer = ((Engine::CLayer*)(Get_Parent()))->Get_Object(L"TestPlayer", Engine::Find_First, nullptr);
		Engine::CTransform* pPlayerTransformCom = static_cast<Engine::CTransform*>(pPlayer->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));
		pPlayerTransformCom->Get_Info(Engine::INFO_POS, &m_vPlayerPos);

		m_pTransform->Chase_RotaionTarget(&m_vPlayerPos);
		m_bFirst = false;
		m_iEvent = 0;
		m_eState = IDLE_BULLET;
	
	}

	// X 트랜스폼은 X 축 빌보드 회전을 통해 회전을 여기서 다 잡아주고




	//if (m_eState == IDLE_BULLET)
	//{
	//	// 빔의 라이프 타임을 떨구고
	//	// 떨군 라이프 타임 만큼 빔의 Y 룰 줄여줘라
	//	// m_pTransform->Dir_Fly(&m_FirstPos, (fTimeDelta * 100.f));
	//}
	//else if (m_eState == DEAD_BULLET)
	//{
	//	//m_bFirst = true;
	//	Dead_Bullet();
	//}

	D3DXMATRIX		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pTransform->m_matWorld._11 = matView._11;
	m_pTransform->m_matWorld._13 = matView._13;
	m_pTransform->m_matWorld._31 = matView._31;
	m_pTransform->m_matWorld._33 = matView._33;
	//State_Change();

	return m_iEvent;
}

void CMonsterBeam::Render_Object(void)
{

	//m_pTransform->Set_Scale(5);
	//m_vRightArmPos = { m_vRightArmPos.x - (sinf(m_fAngle) * 10)  ,m_vRightArmPos.y - 5.f , m_vRightArmPos.z - (cosf(m_fAngle) * 10) };
	//m_pTransform->Set_Trans(&m_vRightArmPos);






	//m_pTransformX->Update_Component(0.01f);
	//m_pTransformX->Set_Transform(m_pGraphicDev);
	//m_pTextureCom->Set_Texture(0);
	//m_pBufferBoradCom->Render_Buffer();




	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);



	



	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pTextureCom->Set_Texture(1);
	m_pBufferBoradCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//m_pTransformX->Add_Trans(&D3DXVECTOR3(101.f, 0.f , 0.f));
	//m_pTransform->Update_Component(0.01f);
	//m_pTransform->Set_Transform(m_pGraphicDev);
	//m_pTextureCom->Set_Texture(2);
	//m_pBufferBoradCom->Render_Buffer();
	//m_pTransformX->Add_Trans(&D3DXVECTOR3(-101.f, 0.f , 0.f));

}

HRESULT CMonsterBeam::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"Sprite_Bat"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Buffer", pComponent);

	// Texture

	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"Texture_MonsterBeam"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);



	return S_OK;
}

void CMonsterBeam::State_Change()
{
	if (m_preState != m_eState && m_preState != DEAD_BULLET)
	{
		m_preState = m_eState;
	}

}

CMonsterBeam * CMonsterBeam::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterBeam*		pInstance = new CMonsterBeam(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CMonsterBeam::Free(void)
{
	Engine::CBulletMain::Free();
}
