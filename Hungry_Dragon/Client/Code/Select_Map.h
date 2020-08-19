#ifndef Select_Map_h__
#define Select_Map_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;
class CTexture;
class CTransform;
class CRenderer;

END



class CSelect_Map : public Engine::CGameObject {
private:
	explicit CSelect_Map(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSelect_Map(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Focus(Engine::_bool _bFocused) { m_bFocused = _bFocused; }
	void Set_MapNum(Engine::_uint _uMapNum) { m_uMapNum = _uMapNum; }
	void Set_LerpX(Engine::_float _fX) { m_fLerpX = _fX; }
	void Set_PosX(Engine::_float _fX);

private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture_Square*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;

	Engine::_uint m_uMapNum = 0;
	Engine::_bool m_bFocused = false;
	Engine::_float m_fLerpX = 0.f;

public:
	static CSelect_Map*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
