#ifndef BillCloud_Object_h__
#define BillCloud_Object_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END

USING(Engine)

class CBillCloud_Object : public Engine::CGameObject {
private:
	explicit CBillCloud_Object(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBillCloud_Object(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Pos(_vec3 _vPos) { m_vPosOrigin = _vPos; }
	void Set_Scale(_vec3 _vScale) { m_vScaleOrigin = _vScale; }
	void Set_Cloud(_uint _uNum) { m_uTexFrame = _uNum; }

private:
	HRESULT		Add_Component(void);


private:
	CTexture_Square*			m_pBufferCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;
	CTransform*		m_pTransform = nullptr;
	CRenderer*		m_pRendererCom = nullptr;

	_uint m_uTexFrame = 0;
	_vec3 m_vPosOrigin;
	_vec3 m_vScaleOrigin;


public:
	static CBillCloud_Object*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
