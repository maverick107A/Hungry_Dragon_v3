#ifndef Select_Scroller_h__
#define Select_Scroller_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture_Square;

END

class CSelect_Map;

class CSelect_Scroller : public Engine::CGameObject {
private:
	explicit CSelect_Scroller(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSelect_Scroller(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Focus(int _iFocus);

private:
	HRESULT		Add_Component(void);

private:
	CSelect_Map* m_arrSelect[10];

public:
	static CSelect_Scroller*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
