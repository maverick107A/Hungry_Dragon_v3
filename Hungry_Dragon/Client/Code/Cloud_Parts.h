#ifndef Cloud_Parts_h__
#define Cloud_Parts_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CBaseLand;
class CHeightCol;

END


USING(Engine)

class CCloud_Parts : public Engine::CGameObject
{
private:
	explicit CCloud_Parts(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCloud_Parts(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Trans(_vec3& _vPos);
	void Set_RotationReverse();
	void Set_Height(_float _fHeight, _uint _uContrast);
	CHeightCol*	Get_BufferCom() { return m_pBufferCom; }

public:
	void Weld_Edge(CCloud_Parts * _Dst, bool _bHorizontal);

private:
	HRESULT		Add_Component(void);
	
	

private:
	Engine::CTransform*		m_pTransform;
	_uint					m_uLength;
	_uint					m_uVerCntX;
	_uint					m_uVerCntZ;
	Engine::CHeightCol*		m_pBufferCom = nullptr;

public:
	static CCloud_Parts*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
