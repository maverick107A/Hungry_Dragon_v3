#ifndef GiantGolem_Left_Arm_h__
#define GiantGolem_Left_Arm_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGiantGolem_Left_Arm : public Engine::CMonsterMain
{
private:
	explicit CGiantGolem_Left_Arm(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGiantGolem_Left_Arm(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
public:
	Engine::CMonsterMain * Get_Parent_Parts() { return m_BodyParts; }
	void				   Set_Parent_Parts(Engine::CMonsterMain* pObject) { m_BodyParts = pObject; }
private:
	HRESULT		Add_Component(void);

public:
public:
	static CGiantGolem_Left_Arm*	Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CMonsterMain* pObject);
private:
	D3DXVECTOR3 m_vArmPos;
	D3DXVECTOR3 m_vBodyPos;
	D3DXVECTOR3 m_vAddPos;

	Engine::CMonsterMain * m_BodyParts;
private:
	virtual void Free(void) override;

};


#endif // GiantGolem_Left_Hand_h__
