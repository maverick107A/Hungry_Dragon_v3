#include "stdafx.h"
#include "Ingame_Info.h"
#include "Export_Function.h"

USING(Engine)

IMPLEMENT_SINGLETON(CIngame_Info)



CIngame_Info::CIngame_Info(void)
{
}


CIngame_Info::CIngame_Info(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
}

CIngame_Info::~CIngame_Info(void)
{
}

void CIngame_Info::Init_Info(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;

	m_pPlayerStatus->fHp			= 100;
	m_pPlayerStatus->fMax_Hp		= 100;

	m_pPlayerStatus->fEvo			= 0;
	m_pPlayerStatus->fMax_Evo		= 100;

	m_pPlayerStatus->fSp			= 100;
	m_pPlayerStatus->fMax_Mp		= 100;

	m_pPlayerStatus->fMp			= 100;
	m_pPlayerStatus->fMax_Sp		= 100;

}
