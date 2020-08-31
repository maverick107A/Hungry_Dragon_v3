#include "stdafx.h"
#include "Boss_Flow.h"
#include "Export_Function.h"
#include "Ingame_Info.h"

USING(Engine)

IMPLEMENT_SINGLETON(CBoss_Flow)

CBoss_Flow::CBoss_Flow(void)
{

}


void CBoss_Flow::Ready_Boss_Flow(LPDIRECT3DDEVICE9 pGraphicDev, CGiantGolem* _pBoss)	
{
	m_pGraphicDev = pGraphicDev;
	m_pBoss = _pBoss;
}

CBoss_Flow::~CBoss_Flow(void)
{

}

void CBoss_Flow::Update_BossFlow(float _fTimeDelta)
{
	float fRatio = (20000.f - m_pBoss->Get_HP())*0.05f;

	switch (m_uPhaseNum)
	{
	case CBoss_Flow::PHASE_1:		// �����
		m_pBoss->Set_Pattern(m_pBoss->PAT_APEAR);
		break;
	case CBoss_Flow::PHASE_2:		// �� �ֵθ��� 1������
		m_pBoss->Set_Phase_One_Pattern(_fTimeDelta);
		//if (50.f < fRatio)
		//{
			m_uPhaseNum = PHASE_3;
			m_pSpawner->Spawn_Meteor();
		//}
		break;
	case CBoss_Flow::PHASE_3:		// ���׿� ������ ��� 2������
		m_pBoss->Set_Phase_One_Pattern(_fTimeDelta);
		m_pSpawner->Fire_Meteor();
		if (95.f < fRatio)
		{
			m_uPhaseNum = PHASE_4;
		}
		break;
	case CBoss_Flow::PHASE_4:		// ���� �� �ִ� ũ�� ���� ���� ������ (��� �� ������ �ʿ��ϸ� �߰�)
		

		break;
	default:
		abort();
		break;
	}

	if (fRatio < 0)
	{
		fRatio = 999;
	}

	CIngame_Info::GetInstance()->Get_PlayerInfo()->fStage = fRatio;
}

void CBoss_Flow::Render_Sfx()
{

}



