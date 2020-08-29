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
	case CBoss_Flow::PHASE_1:		// 등장씬
		

		break;
	case CBoss_Flow::PHASE_2:		// 팔 휘두르는 1페이즈
		m_pBoss->Set_Phase_One_Pattern(_fTimeDelta);
		break;
	case CBoss_Flow::PHASE_3:		// 메테오 오지게 쏘는 2페이즈


		break;
	case CBoss_Flow::PHASE_4:		// 먹을 수 있는 크기 됬을 때의 페이즈 (사망 시 페이즈 필요하면 추가)


		break;
	default:
		abort();
		break;
	}
}

void CBoss_Flow::Render_Sfx()
{

}



