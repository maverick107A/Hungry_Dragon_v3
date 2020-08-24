#include "PHit.h"
#include "Transform.h"
#include "PlayerMain.h"

USING(Engine)

Engine::CPHit::CPHit(void)
{
	
}

Engine::CPHit::CPHit(const CPHit& rhs)
{

}

Engine::CPHit::~CPHit(void)
{

}

void CPHit::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_pPlayer->Set_Animation(ANI_HIT);
	m_fAngle = m_pPlayer->Get_Transform()->m_vAngle.x;
}

void CPHit::Update_State(const float& fTimeDelta)
{
	float fDeltaAngle = -D3DX_PI*0.5f - m_fAngle;
	m_fAngle += fDeltaAngle*0.1f;
	m_pPlayer->Get_Transform()->m_vAngle.x = m_fAngle;
	m_fTime -= fTimeDelta;


	_vec3 vDir;

	memcpy(&vDir, &m_pPlayer->Get_Transform()->m_matWorld._31, sizeof(_vec3));
	m_pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS] += vDir*m_fDis;
	
	m_fDis *= 0.95f;

	if (m_fTime < 0)
		m_pPlayer->Set_Sate(CPlayerMain::STATE_FLYIDLE);
}

void CPHit::LateUpdate_State()
{

}

void CPHit::Out_State()
{
}

CPHit* Engine::CPHit::Create(void)
{
	return new CPHit;
}

void Engine::CPHit::Free(void)
{

}

CComponent* Engine::CPHit::Clone(void)
{
	return new CPHit(*this);
}