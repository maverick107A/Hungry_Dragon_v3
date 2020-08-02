#include "Component.h"

USING(Engine)

Engine::CComponent::CComponent(void)
{
	
}

Engine::CComponent::~CComponent(void)
{

}

void CComponent::Set_Address(CGameObject * _pObject) {
	m_AddressTag.StateFlag &= (char)0;
	m_AddressTag.StateFlag |= (char)32;
	m_AddressTag.LayerAddress = _pObject->Get_Parent();
	m_AddressTag.ObjAddress = _pObject;
	m_AddressTag.ComponentAddress = this;
}
