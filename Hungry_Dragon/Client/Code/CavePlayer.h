#ifndef CavePlayer_h__
#define CavePlayer_h__

#include "Define.h"
#include "PlayerMain.h"

BEGIN(Engine)

class CVIBuffer;
class CTexture;
class CTransform;
class CCamera;
class CTerrain;
class CPart_Atk;
class CResources;

END
class CCavePlayer : public Engine::CPlayerMain
{
private:
	explicit CCavePlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCavePlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object(void);
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	
private:
	virtual void	State_Change() override;
	virtual HRESULT	Add_Component(void) override;

public:
	void	Switch_Phase(int _iPhase);

public:
	static CCavePlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

public:
	list<Engine::CResources*>  m_arrParticle;

};

#endif // CavePlayer_h__
