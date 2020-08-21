#ifndef Terrain_Parts_h__
#define Terrain_Parts_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CHeightCol;
class CTransform;
class CRenderer;

END

USING(Engine)

class CTerrain_Parts : public Engine::CGameObject
{
private:
	explicit CTerrain_Parts(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTerrain_Parts(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_HeightMap(const _tchar* _pPath);
	void Set_A();
	void Set_Trans(_vec3& _vPos);
	CHeightCol*	Get_BufferCom() { return m_pBufferCom; }
	vector<int> Get_HeightVector();

public:
	void Weld_Edge(CTerrain_Parts* _Dst, bool _bHorizontal);


private:
	HRESULT		Add_Component(void);

private:
	Engine::CHeightCol*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

public:
	static CTerrain_Parts*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
