#ifndef Line_Renderer_h__
#define Line_Renderer_h__

#include "Define.h"
#include "GameObject.h"

class CBill_Line;

USING(Engine)

class CLine_Renderer : public CBase {
	DECLARE_SINGLETON(CLine_Renderer)
private:
	explicit CLine_Renderer();
	virtual ~CLine_Renderer(void);

public:
	HRESULT Ready_Renderer(LPDIRECT3DDEVICE9 pGraphicDev);
	int Update_Renderer(const float& fTimeDelta);
	void Render_Renderer(void);
	void Render_SpriteMode();

public:
	void Draw_Dot(float _fX, float _fY, float _fZ, float _fSpeed = 60.f, float _fScale = 50.f);
	void Draw_DotSprite(LPD3DXSPRITE _pSprite, float _fX, float _fY, float _fSpeed = 60.f, float _fScale = 50.f, DWORD _dwColor = 0xffffffff);
	void Draw_Line(_vec3 _vSrc, _vec3 _vDest, _uint _uLerp = 1, float _fSpeed = 60.f, float _fScale = 50.f);
	int Get_Size() { return m_listLine.size(); }

private:
	HRESULT		Add_Component(void);


private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	list<CBill_Line*>			m_listLine;
	list<CBill_Line*>			m_listSprite;
	IDirect3DTexture9*			m_pTex = nullptr;

private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
