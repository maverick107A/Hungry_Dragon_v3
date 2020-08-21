#ifndef GiantGolem_Right_Hand_h__
#define GiantGolem_Right_Hand_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGiantGolem_Right_Hand : public Engine::CMonsterMain
{
private:
	explicit CGiantGolem_Right_Hand(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGiantGolem_Right_Hand(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
public:
	Engine::CMonsterMain * Get_Parent_Parts() { return m_ArmParts; }
	void				   Set_Parent_Parts(Engine::CMonsterMain* pObject) { m_ArmParts = pObject; }
private:
	HRESULT		Add_Component(void);

public:
	static CGiantGolem_Right_Hand*	Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CMonsterMain* pObject);


private:
	D3DXVECTOR3 m_vHandPos;
	D3DXVECTOR3 m_vArmPos;
	D3DXVECTOR3 m_vAddPos;

	Engine::CMonsterMain * m_ArmParts;
private:
	virtual void Free(void) override;

};


#endif // GiantGolem_Right_Hand_h__
