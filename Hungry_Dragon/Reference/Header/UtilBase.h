#ifndef UtilBase_h__
#define UtilBase_h__

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
	
class ENGINE_DLL CUtilBase :public CBase {
protected:
	explicit CUtilBase(void);
	virtual ~CUtilBase(void);
};

END
#endif
