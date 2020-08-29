#include "stdafx.h"
#include "Boss_Flow.h"
#include "Export_Function.h"

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

	switch (m_uPhaseNum)
	{
	case CBoss_Flow::PHASE_1:		// �����
		

		break;
	case CBoss_Flow::PHASE_2:		// �� �ֵθ��� 1������
		m_pBoss->Set_Phase_One_Pattern(_fTimeDelta);
		break;
	case CBoss_Flow::PHASE_3:		// ���׿� ������ ��� 2������


		break;
	case CBoss_Flow::PHASE_4:		// ���� �� �ִ� ũ�� ���� ���� ������ (��� �� ������ �ʿ��ϸ� �߰�)


		break;
	default:
		abort();
		break;
	}
}

void CBoss_Flow::Render_Sfx()
{

}



