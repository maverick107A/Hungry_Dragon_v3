#ifndef Jump_Monster_h__
#define Jump_Monster_h__


#include "Define.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeTex;
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
	static CJump_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;
	void	Jump(const float& fTimeDelta);
private:
	bool					m_bJump_check = false;
	float					m_fJumpPower;
	float					m_fJumpSpeed = 0.1f;
	float					m_fAccel = 0.1f;
	float					m_fFirstY;
};





#endif // Jump_Monster_h__
