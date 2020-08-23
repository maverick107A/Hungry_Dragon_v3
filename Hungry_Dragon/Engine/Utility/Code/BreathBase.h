#ifndef BreathBase_h__
#define BreathBase_h__

#include "Component.h"

BEGIN(Engine)
class CPlayerMain;
class CParticle;
class ENGINE_DLL CBreathBase : public CComponent
{
private:
	explicit CBreathBase(void);
	explicit CBreathBase(const CBreathBase& rhs);
	virtual ~CBreathBase(void);

public:
	HRESULT Ready_BreathBase(LPDIRECT3DDEVICE9& _pGraphicDev);
	virtual void	Initialize_Component(void);
	virtual _int	Update_Component(CPlayerMain* _pPlayer);
	virtual void	LateUpdate_Component(const _float& fTimeDelta);
	void Render_Breath(CPlayerMain* _pPlayer);

public:
	static CBreathBase*		Create(LPDIRECT3DDEVICE9& _pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);

private:
	ID3DXMesh*				m_pCylinder = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev;
};
END
#endif // BreathBase_h__
