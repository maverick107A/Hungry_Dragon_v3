#ifndef EngineEventMgr_h__
#define EngineEventMgr_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CEngineEventMgr :public CBase {
	DECLARE_SINGLETON(CEngineEventMgr)

private:
	explicit CEngineEventMgr(void);
	virtual ~CEngineEventMgr(void);

	// Ŭ�󿡼� �����Ѿ��� �̺�Ʈ�� �����Ϳ� �Բ� �ɾ��ֱ� (��Ƽ� �����ϴ� �뵵)
public:
	void Set_Event(ENGINE_EVENT _tEvent) { m_listEvents.emplace_back(_tEvent); }
	void Set_Event(_uint _uEventNum, _uint _uDataNum) { m_listEvents.emplace_back(ENGINE_EVENT(_uEventNum, _uDataNum)); }
	void Set_Event(_uint _uEventNum, _uint _uDataNum, _uint _uTypeNum) { m_listEvents.emplace_back(ENGINE_EVENT(_uEventNum, _uDataNum, _uTypeNum)); }
	Engine::_uint Get_EventCount() { return m_listEvents.size(); }
	ENGINE_EVENT Pop_Event() 
	{
		ENGINE_EVENT tEvent = m_listEvents.front(); 
		m_listEvents.pop_front(); 
		return tEvent;
	};

private:
	list<ENGINE_EVENT> m_listEvents;

	
	// CBase��(��) ���� ��ӵ�
	virtual void Free(void) override;
};

END

#endif