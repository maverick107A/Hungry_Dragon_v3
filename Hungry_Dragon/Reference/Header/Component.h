#ifndef Component_h__
#define Component_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent(void);
	virtual ~CComponent(void);

public:
	virtual _int	Update_Component(const _float& fTimeDelta) { return 0; }

protected:
	virtual CComponent*		Clone(void)PURE;
	virtual void			Free(void)PURE;
};

END
#endif // Component_h__
