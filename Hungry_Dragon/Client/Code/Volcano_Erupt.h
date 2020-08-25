#ifndef Volcano_Erupt_h__
#define Volcano_Erupt_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTransform;
class CTexture;

END

USING(Engine)

class CVolcano_Erupt : public Engine::CGameObject
{
private:
	explicit CVolcano_Erupt(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CVolcano_Erupt(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Trans(_vec3& _vPos);
	void Set_Scale(_uint _uTimes);


private:
	HRESULT		Add_Component(void);

private:
	CTexture_Square*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	_uint					m_uTexFrame = 0;

public:
	static CVolcano_Erupt*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
