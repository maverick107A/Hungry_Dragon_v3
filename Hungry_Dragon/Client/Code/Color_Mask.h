#ifndef Color_Mask_h__
#define Color_Mask_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END
class CColor_Mask : public Engine::CGameObject
{
private:
	explicit CColor_Mask(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CColor_Mask(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
public:
	HRESULT Init_MaskTex(int _iNum);
	void Set_ColorMask();

private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture*		m_pTexture = nullptr;

public:
	static CColor_Mask*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
