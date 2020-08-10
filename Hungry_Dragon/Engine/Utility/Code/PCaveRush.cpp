#include "PCaveRush.h"
#include "Transform.h"
#include "PlayerMain.h"

#include "Export_System.h""

USING(Engine)

Engine::CPCaveRush::CPCaveRush(void)
{
	
}

Engine::CPCaveRush::CPCaveRush(const CPCaveRush& rhs)
{

}

Engine::CPCaveRush::~CPCaveRush(void)
{

}

void CPCaveRush::Enter_State(CPlayerMain* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CPCaveRush::Update_State(const float& fTimeDelta)
{
	Engine::Get_DIKeyState(Engine::DIMS_X);
}

void CPCaveRush::Out_State()
{
}

CPCaveRush* Engine::CPCaveRush::Create(void)
{
	return new CPCaveRush;
}

void Engine::CPCaveRush::Free(void)
{

}

CComponent* Engine::CPCaveRush::Clone(void)
{
	return new CPCaveRush(*this);
}