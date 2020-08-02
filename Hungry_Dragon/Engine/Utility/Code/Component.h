#ifndef Component_h__
#define Component_h__

#include "Engine_Define.h"
#include "UtilBase.h"

BEGIN(Engine)
class CGameObject;

class ENGINE_DLL CComponent : public CUtilBase
{
protected:
	explicit CComponent(void);
	virtual ~CComponent(void);

public:
	void Set_Address(CGameObject* _pObject);

public:
	virtual _int	Update_Component(const _float& fTimeDelta) { return 0; }
	virtual void	LateUpdate_Component(const _float& fTimeDelta) { return; }

protected:
	virtual CComponent*		Clone(void)PURE;
	virtual void			Free(void)PURE;
};

END
#endif // Component_h__
