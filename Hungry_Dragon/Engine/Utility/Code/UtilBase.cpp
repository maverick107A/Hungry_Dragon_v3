#include "UtilBase.h"

USING(Engine)

Engine::CUtilBase::CUtilBase(void)
	:CBase()
{
}

Engine::CUtilBase::~CUtilBase(void) {
}

void * CUtilBase::Get_Parent() {
	return nullptr;
}
