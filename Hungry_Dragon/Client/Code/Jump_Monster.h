#ifndef Jump_Monster_h__
#define Jump_Monster_h__


#include "Define.h"
#include "Monster.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;

END

class  CJump_Monster : public CMonster
{
private:
	explicit CJump_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CJump_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	static CJump_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev , D3DXVECTOR3 _pos);
private:
	virtual void Free(void) override;
	void	Jump(const float& fTimeDelta);
private:
	bool					m_bJump_check = false;
	float					m_fJumpPower = 0.5;
	float					m_fJumpSpeed = 0.1f;
	float					m_fAccel = 0.01f;
	float					m_fFirstY;
	D3DXVECTOR3				m_vChasePos;
};





#endif // Jump_Monster_h__
