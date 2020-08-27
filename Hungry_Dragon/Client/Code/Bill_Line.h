#ifndef Bill_Line_h__
#define Bill_Line_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTransform;
class CRenderer;

END

USING(Engine)

class CBill_Line : public Engine::CGameObject {
private:
	explicit CBill_Line(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBill_Line(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	void Render_Sprite(LPDIRECT3DTEXTURE9 _pTex);

public:
	void Set_Sprite(LPD3DXSPRITE _pSprite, DWORD _dwColor) { m_pSprite = _pSprite; m_dwColor = _dwColor; }
	void Set_Pos(_vec3 _vPos) { m_vPosOrigin = _vPos; }
	void Set_Scale(_float _fScale) { m_fScale = _fScale; }
	void Set_Speed(_float _fSpeed) { m_fShrinkSpeed = _fSpeed; }
	void Set_Color(_uint _uNum) { m_uTexColor = _uNum; }

private:
	HRESULT		Add_Component(void);


private:
	// 스프라이트용
	LPD3DXSPRITE				m_pSprite = nullptr;
	DWORD						m_dwColor = 0;


	// 공용
	CTexture_Square*			m_pBufferCom = nullptr;
	CTransform*		m_pTransform = nullptr;
	CRenderer*		m_pRendererCom = nullptr;

	_uint m_uTexColor = 0;
	_vec3 m_vPosOrigin;
	//_vec3 m_vScaleOrigin;

	float m_fScale = 1.f;
	float m_fShrinkSpeed = 1.f;

public:
	static CBill_Line*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
