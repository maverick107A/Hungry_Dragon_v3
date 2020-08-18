#ifndef Texture_h__
#define Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CResources
{
protected:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture(void);

public:
	HRESULT		Ready_Texture(const _tchar* pPath, 
								TEXTURETYPE eType, 
								const _uint& iCnt);

	void		Set_Texture(const _uint& iIndex = 0);
	PDIRECT3DTEXTURE9 Get_Texture() {return m_pTexture;}

private:
	vector<IDirect3DBaseTexture9*>			m_vecTexture;
	PDIRECT3DTEXTURE9						m_pTexture;

public:
	static CTexture*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _tchar* pPath, 
									TEXTURETYPE eType, 
									const _uint& iCnt = 1);

	virtual CResources*		Clone(void);
	virtual void			Free(void);


	// CResources을(를) 통해 상속됨
	virtual void Render_Buffer(void) override;

};

END
#endif // Texture_h__
