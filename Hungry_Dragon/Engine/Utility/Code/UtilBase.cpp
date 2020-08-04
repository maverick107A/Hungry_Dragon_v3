#include "UtilBase.h"

USING(Engine)

Engine::CUtilBase::CUtilBase(void)
	:CBase()
{
}

Engine::CUtilBase::~CUtilBase(void) {
}

CUtilBase* CUtilBase::Get_Parent() {
	if (nullptr != m_AddressTag.ComponentAddress)
		return (CUtilBase*)m_AddressTag.ObjAddress;
	else if (nullptr != m_AddressTag.ObjAddress)
		return (CUtilBase*)m_AddressTag.LayerAddress;
	else
		return nullptr;
}
