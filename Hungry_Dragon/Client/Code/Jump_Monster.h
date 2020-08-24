#ifndef Jump_Monster_h__
#define Jump_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;

END

class  CJump_Monster : public Engine::CMonsterMain
{
private:
	explicit CJump_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CJump_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);
	void LateUpdate_Object(const float & fTimeDelta);
public:
	static CJump_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;
	void	Jump(const float& fTimeDelta);
private:
	bool					m_bJump_check = false;
	float					m_fJumpPower = 0.8f;
	float					m_fJumpSpeed = 0.1f;
	float					m_fAccel = 0.01f;
	float					m_fFirstY;
	D3DXVECTOR3				m_vChasePos;


	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vLookPos;
	D3DXVECTOR3 m_vBodyPos;

	float		m_fAngle = 0;
};





#endif // Jump_Monster_h__
