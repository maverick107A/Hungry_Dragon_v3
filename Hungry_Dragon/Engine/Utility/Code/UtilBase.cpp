#include "UtilBase.h"

USING(Engine)

Engine::CUtilBase::CUtilBase(void)
	:CBase()
{
}

Engine::CUtilBase::~CUtilBase(void) {
}

void* CUtilBase::Get_Parent() {
	if (nullptr != m_AddressTag.ComponentAddress)
		return m_AddressTag.ObjAddress;
	else if (nullptr != m_AddressTag.ObjAddress)
		return m_AddressTag.LayerAddress;
	else
		return nullptr;
}
