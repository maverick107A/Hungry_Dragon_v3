#ifndef Ingame_Flow_h__
#define Ingame_Flow_h__

#include "Define.h"
#include "Engine_Define.h"

class CTerrain_Parts;
class CTree_Object;

class CColor_Mask;

class CIngame_Flow
{
	DECLARE_SINGLETON(CIngame_Flow)
public:
	enum EVENTID{EVENT_SCENECHANGE, EVENT_END};
	enum STAGEID { STAGE_FOREST , STAGE_CAVE_ONE, STAGE_CAVE_TWO, STAGE_CAVE_FINAL, STAGE_SKY , STAGE_LAVA , STAGE_END };

private:
	explicit CIngame_Flow(void);
	explicit CIngame_Flow(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIngame_Flow(void);

public:			// �� ���� �޼ҵ� (�� �������� ȥ�ڼ� ������)
	void Init_Flow(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXSPRITE pSprite);
	void Update_BeforeScene(const Engine::_float& _fTimeDelta);
	void Update_AfterScene(const Engine::_float& _fTimeDelta);
	void LateUpdate_BeforeScene(const Engine::_float& _fTimeDelta);
	void LateUpdate_AfterScene(const Engine::_float& _fTimeDelta);
	void Render_BeforeScene();
	void Render_AfterScene();
	void Update_Event();

public:			// ����/����
	void Init_Mask();
	void Change_SceneTo(SCENENUM::ID _eID) { m_eReservedScene = _eID; Set_Event(EVENT_SCENECHANGE); }
	void Set_Event(int _iEvent) { m_listEvent.emplace_back(_iEvent); }
	void Occur_Event(int _iEvent);
	void Set_MaskColor(int _iIdx);
	void Set_DefaultTex();
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }

	void Set_StageID(STAGEID eStageID) { m_eStageID = eStageID; }
	STAGEID Get_StageID() { return m_eStageID; }
	


public:			// �� �帧 ���� �޼ҵ� + �Ŵ�����Ʈ�� ����ȯ ��û
	void Load_ForestTerrain();		// ������Ʈ �ͷ��� 50������ �ε���ѳ��� (����׿� �͸����� �ϴ� ���δµ� ���߿� �׶��׶� �Ҹ�)
	void Release_ForestTerrain();	// �Ҹ� �Լ�
	CTerrain_Parts** GetEntry_ForestTerrain() { return m_pParts; }

	void Load_TreeList();	// �÷��α� �� ũ���ѵ�..
	void Release_TreeList();
	list<CTree_Object*>* GetEntry_TreeList(int _iIdx) { return &m_arrRenderGroupIdx[_iIdx]; }
	void Release_AllResources();


private:		// �� ���� Ȥ�� �ӽ� �ΰ��ӿ� ������
	list<int> m_listEvent;
	SCENENUM::ID m_eReservedScene;
	STAGEID		 m_eStageID;
	CTerrain_Parts*	m_pParts[50] = { 0 };
	list<CTree_Object*> m_arrRenderGroupIdx[50];

private:
	CColor_Mask*	m_pMaskTexObj[8];

private:
	// ����� �۵��.
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	LPD3DXSPRITE					m_pSprite;
};


#endif // GameMgr_h__
