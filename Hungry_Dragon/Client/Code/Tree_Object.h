#ifndef Tree_Object_h__
#define Tree_Object_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CVICustom;
class CTransform;

END

USING(Engine)

class CTree_Object : public Engine::CGameObject
{
private:
	explicit CTree_Object(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTree_Object(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Trans(_vec3& _vPos);
	void Set_Scale(_uint _uTimes);
	CVICustom*	Get_BufferCom() { return m_pBufferCom; }


private:
	HRESULT		Add_Component(void);

private:
	Engine::CVICustom*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

public:
	static CTree_Object*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
