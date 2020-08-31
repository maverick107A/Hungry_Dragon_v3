#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem.h"
#include "Boss_Flow.h"
#include "Ingame_Info.h"

CGiantGolem::CGiantGolem(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CMonsterMain(pGraphicDev)
{
}

CGiantGolem::~CGiantGolem(void)
{
}

HRESULT CGiantGolem::Ready_Object(void)
{
	Engine::CMonsterMain::Ready_Object();
	Add_Component();
	m_fSpeed = 50.f;
	m_fMonster_HP = 20000.f;
	m_fMonster_MaxHP = 20000.f;
	m_fScale = 3.f;
	m_fMaxScale = 3.f;
	// m_fMaxScale = 0.01f;
	m_fDamaged = 5.f;
	m_eState = MONSTER_REBORN;
	m_ePattern = PAT_APEAR;
	m_fDead_Range = 999999.f;
	return S_OK;
}

int CGiantGolem::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		m_vFirstPos = { 19200.f ,  -2500.f  ,  19200.f };
		m_pTransform->Set_Trans(&m_vFirstPos);
		m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = m_fMonster_MaxHP;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
		m_ePattern = PAT_APEAR;
		m_pAnimationController->Set_Pattern(m_ePattern);
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	if (m_ePattern == PAT_CICLE)
	{ 
		m_pTransform->m_vAngle.y += 0.3f;
		if (m_pTransform->m_vAngle.y >= D3DXToRadian(360.f))
		{
			m_pTransform->m_vAngle.y -= D3DXToRadian(360.f);
		}
	}
	else 
	{

		Get_FMOD()->StopLoop(L"LavaBurn");
		D3DXVECTOR3 vPos;
		m_vPlayerPos = { m_vPlayerPos.x , 0 , m_vPlayerPos.z };

		m_pTransform->Get_Info(Engine::INFO_POS, &m_vBodyPos);

		m_vBodyPos = { m_vBodyPos.x , 0 , m_vBodyPos.z };

		m_vPos = m_vPlayerPos - m_vBodyPos;
		vPos = m_vPlayerPos - m_vBodyPos;
		D3DXVec3Normalize(&vPos, &vPos);
		m_vLookPos = { 0.f, 0.f ,1.f };

		m_fAngle = acosf(D3DXVec3Dot(&vPos, &m_vLookPos));

		if (vPos.x < 0)
			m_fAngle *= -1;

		if (m_ePattern == PAT_IDLE) {
			m_pTransform->m_vAngle.y += (m_fAngle - m_pTransform->m_vAngle.y)*fTimeDelta;
		}
		else {
			m_pTransform->m_vAngle.y += (m_fAngle - m_pTransform->m_vAngle.y)*fTimeDelta*0.3f;
		}
	}

	if (m_ePattern == PAT_FIREBALL)
	{
		m_fShotingLate += fTimeDelta;

		if (m_fShotingLate > m_fShotingDelay)
		{
			Get_FMOD()->PlayEffect(L"Takeon");
			Shooting();
			m_fShotingLate = 0;
		}

	}
	else
		m_fShotingLate = 0;


	if (m_ePattern == PAT_PUNCH)
	{
		if (m_fPunchLate == 0)
			Get_FMOD()->PlayEffect(L"LavaBurn");    // ÁØºñ

		m_fPunchLate += fTimeDelta;
		if (m_fPunchLate > m_fPunchDelay)
		{
			if(m_fPunchLate < 10.f)
			Get_FMOD()->PlayEffect(L"Kick");	    // ÆÝÄ¡

			m_fPunchLate = 10;

		}
	}
	else
		m_fPunchLate = 0;




	if (m_ePattern == PAT_STOMP)
	{
		if (m_fStompLate == 0)
			Get_FMOD()->PlayEffect(L"LavaBurn");    // ÁØºñ


		m_fStompLate += fTimeDelta;
		
		
		if (m_fStompLate > m_fStompDelay)
		{
			if (m_fStompLate < 15.f)
			Get_FMOD()->PlayEffect(L"Bound");		// ³»·ÁÂï±â

			m_fStompLate = 15;

		}
	}
	else
		m_fStompLate = 0;
	






	if (m_ePattern == PAT_CICLE)
	{
		if (m_fCicleLate == 0)
			Get_FMOD()->PlayEffect(L"LavaBurnLong");

		m_fCicleLate += 5;
	}
	else
		m_fCicleLate = 0;









	if (m_ePattern == PAT_APEAR && m_pTransform->m_vInfo[Engine::INFO_POS].y < 2500.f )
	{
		D3DXVECTOR3 _vPos = { 0.f, 10.f, 0.f };
		m_pTransform->Add_Trans(&_vPos);
	}
	else if (m_ePattern == PAT_APEAR && m_pTransform->m_vInfo[Engine::INFO_POS].y >= 2500.f)
	{
		CBoss_Flow::GetInstance()->Set_Phase(CBoss_Flow::PHASE_2);
	}

	if (m_bPatternEnd)
	{
		if (PAT_IDLE != m_ePattern)
		{
			m_ePattern = PAT_IDLE;
			m_pPartsTrans[PART_BODY]->m_fDamping = 0.01f;
			m_bPatternEnd = false;
			m_fPatternTime = 0;
		}
	}


	for (int i = 0; i < PARTS_END; ++i)
	{
		MOVEMENT nextFrameMovement = m_pAnimationController->Get_Movement(m_ePattern, i);
		m_pPartsTrans[i]->m_vAfterAngle = nextFrameMovement.vecRot;
		m_pPartsTrans[i]->m_vAfterPos = nextFrameMovement.vecTrans;
		m_pPartsTrans[i]->m_vAfterRevAngle = nextFrameMovement.vecRevolution;
		m_pPartsTrans[i]->m_vScale = nextFrameMovement.vecScale;
	}

	if (GetAsyncKeyState('O') & 0x0001)
	{
		TCHAR s[256];
		wsprintf(s, L"Frame : %d", m_pAnimationController->Get_Movement(m_ePattern, 2).tFrame);
		MessageBox(nullptr, s, L"", 0);
	}


	if (m_bHit)
	{
		// Á¡¼ö ³Ö¾î¿µ
		CIngame_Info::GetInstance()->Push_OnePolygon();

	}
	m_bHit = false;

	return m_iEvent;
}

void CGiantGolem::Render_Object(void)
{
	
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Animation_Render();
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

}

void CGiantGolem::Set_Phase_One_Pattern(float  _fTimeDelta)
{
	if (m_ePattern == PAT_IDLE)
	{
		m_fPatternTime += _fTimeDelta;
	
		if (m_fPatternTime > m_fPatternDelay)
		{
			switch (m_iPatternNum)
			{
			case 0:
				m_ePattern = PAT_PUNCH;
				m_pPartsTrans[PART_BODY]->m_fDamping = 0.3f;
				m_pAnimationController->Set_Pattern(m_ePattern);
				++m_iPatternNum;
				break;
			case 1:
				m_ePattern = PAT_STOMP;
				m_pPartsTrans[PART_BODY]->m_fDamping = 0.3f;
				m_pAnimationController->Set_Pattern(m_ePattern);
				++m_iPatternNum;
				break;
	
			case 2:
				m_ePattern = PAT_CICLE;
				m_pPartsTrans[PART_BODY]->m_fDamping = 0.3f;
				m_pAnimationController->Set_Pattern(m_ePattern);
				++m_iPatternNum;
				break;
			case 3:
				m_ePattern = PAT_FIREBALL;
				m_pPartsTrans[PART_BODY]->m_fDamping = 0.3f;
				m_pAnimationController->Set_Pattern(m_ePattern);
				m_iPatternNum = 0;
				break;
			}
			for (int i = 0; i < BOSSPARTS::PARTS_END; ++i)
			{
				m_pAnimationController->Set_SpecificFrame(m_ePattern, i);
			}
			m_bPatternEnd = false;
		}
	}
}

HRESULT CGiantGolem::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_GOLEMBODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);


	// buffer
	pComponent = m_pBufferChrystalMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_RIGHTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"RIGHTHAND_Buffer", pComponent);
	

	pComponent = m_pBufferBodyMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_LEFTHAND"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"LEFTHAND_Buffer", pComponent);


	// buffer
	pComponent = m_pBufferHeadMeshCom = dynamic_cast<Engine::CVICustom*>
		(Engine::Clone(RESOURCE_STAGE, L"BUFFER_ROCKMESH"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Head_Buffer", pComponent);



	//Transform

	//¾ó±¼
	pComponent = m_pPartsTrans[PART_HEAD] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_HeadTransform", pComponent);
	//ÅÎ
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);
	//¸öÅë
	pComponent = m_pPartsTrans[PART_LEFTARM] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LeftArmTransform", pComponent);

	pComponent = m_pPartsTrans[PART_LEFTHAND] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LeftHandTransform", pComponent);

	pComponent = m_pPartsTrans[PART_RIGHTARM] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightArmTransform", pComponent);
	//³¯°³
	pComponent = m_pPartsTrans[PART_RIGHTHAND] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightHandTransform", pComponent);


	//¾Ö´Ï¸ÞÀÌ¼Ç ÄÁÆ®·Ñ·¯
	pComponent = m_pAnimationController = Engine::CAnimation_Controller::Create(PARTS_END);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Set_Address(this);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_AnimationController", pComponent);
	pComponent->Set_Address(this);
	//¾Ö´Ï¸ÞÀÌ¼Ç ¼³Á¤
	Preset_Animation();

	return S_OK;
}

void CGiantGolem::Preset_Animation()
{

	float fQater = D3DX_PI * 0.5f;
	float fFull = D3DX_PI * 2.f;
	m_pAnimationController->Add_Animator(-1);

	float fRatio = 100.f;
	/*float fRatio = m_fMonster_HP / m_fMonster_MaxHP;
	fRatio = 100.f / fRatio;
	*/
	// BASE

	// Body
	m_pAnimationController->Insert_Scale(PAT_BASE, PART_BODY, 0, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_BASE, PART_BODY, 0, _vec3(0.f, 0.f, 0.f));
	// Head
	m_pAnimationController->Insert_Scale(PAT_BASE, PART_HEAD, 0, _vec3(200.f, 200.f, 200.f));
	m_pAnimationController->Insert_Trans(PAT_BASE, PART_HEAD, 0, _vec3(100.f, 700.f, 100.f));
	// Left
	// Arm
	m_pAnimationController->Insert_Scale(PAT_BASE, PART_LEFTARM, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_BASE, PART_LEFTARM, 0, _vec3(0.f, D3DX_PI, 0.f));
	m_pAnimationController->Insert_Trans(PAT_BASE, PART_LEFTARM, 0, _vec3(-1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_BASE, PART_LEFTHAND, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_BASE, PART_LEFTHAND, 0, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_BASE, PART_LEFTHAND, 0, _vec3(0.f, -1200.f, 0.f));
	// Right
	// Arm
	m_pAnimationController->Insert_Scale(PAT_BASE, PART_RIGHTARM, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_BASE, PART_RIGHTARM, 0, _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_BASE, PART_RIGHTARM, 0, _vec3(1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_BASE,  PART_RIGHTHAND, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_BASE, PART_RIGHTHAND, 0, _vec3(0.f,  2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_BASE,  PART_RIGHTHAND, 0, _vec3(0.f, -1200.f, 0.f));

	//IDLE
	m_pAnimationController->Add_Animator(PAT_BASE);
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_BODY, 5, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_BODY, 5, _vec3(0.f, 200.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_BODY, 10, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_BODY, 10, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_BODY, 15, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_BODY, 15, _vec3(0.f, 200.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_BODY, 20, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_BODY, 20, _vec3(0.f, 0.f, 0.f));

	// µÎµî µîÀå
	m_pAnimationController->Add_Animator(PAT_BASE);

	// ÆÈ Å©·Î½º!
	// Left
	// Arm
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_LEFTARM,	 50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_LEFTARM,	 50, _vec3(0.7f, 4.14f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_LEFTARM,	 50, _vec3(-1000.f, 800.f, 0.f));
	//// Hand														 5
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_LEFTHAND,   50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_LEFTHAND,  50, _vec3(-1.5f, 2.76f, 0.6f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_LEFTHAND,   50, _vec3(300.f, -1000.f, 0.f));
	// Right														 5
	// Arm															 5
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_RIGHTARM,   50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_RIGHTARM,  50, _vec3(-1.0f, -1.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_RIGHTARM,   50, _vec3(1200.f, 800.f, 0.f));
	//// Hand														 5
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_RIGHTHAND,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_RIGHTHAND, 50, _vec3(1.0f, 2.8f, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_RIGHTHAND,  50, _vec3(300.f, -1000.f, 0.f));

	// Punch
	m_pAnimationController->Add_Animator(PAT_BASE);

	// ÆÈ ¼öÁ÷ »ó½Â
	//m_pPartsTrans[PART_RIGHTARM]->m_fDamping =  0.08f;
	//m_pPartsTrans[PART_RIGHTHAND]->m_fDamping = 0.08f;
	//m_pPartsTrans[PART_BODY]->m_fDamping =      0.08f;

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,   10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM,  10, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,   10, _vec3(1700, 800.f, 0.f));
	

	// ¹Ùµð È¸Àü ´ç±â±â
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  20, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 20, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  20, _vec3(1700, 800.f, -300.f));
	
	m_pAnimationController->Insert_Scale(PAT_PUNCH,  PART_BODY,     20, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_BODY,     20, _vec3( 0.f , 0.5f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH,  PART_BODY,     20, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,   20, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND,	 20, _vec3(0.f, 2.8f, 0.4f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,	 20, _vec3(0.f, -1200.f, 0.f));



	// Áö¸£±â
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 30, _vec3(-fQater, -0.3f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  30, _vec3(1700, 500.f, 150.f));
	 
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_BODY,  30, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_BODY, 30, _vec3(0.f, -0.5f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_BODY,  30, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,  30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND, 30, _vec3(0.f, 120.2f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,  30, _vec3(0.f, -1800.f, 0.f));


	// ¹Ùµð ¿ø·¡À§Ä¡·Î!
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_BODY, 50, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_BODY, 50, _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_HEAD, 50, _vec3(200.f, 200.f, 200.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_HEAD, 50, _vec3(100.f, 700.f, 100.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 50, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  50, _vec3(1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND, 50, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,  50, _vec3(0.f, -1200.f, 0.f));


	//¾ç¼Õ ¸ð¾Æ Âï±â
	m_pAnimationController->Add_Animator(PAT_BASE);
	
	// ¾çÆÈ Å©·Î½º
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTARM, 10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTARM, 10, _vec3(-D3DX_PI, 0.f, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTARM, 10, _vec3(1700, 800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTARM, 10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTARM, 10, _vec3(D3DX_PI, D3DX_PI, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTARM, 10, _vec3(-1700, 800.f, 0.f));
	
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTHAND, 10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTHAND, 10, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTHAND, 10, _vec3(0.f, -1200.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTHAND,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTHAND, 10, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTHAND, 10, _vec3(0.f, -1200.f, 0.f));
	

	// ÆÈÅ©±â Áõ°¡!
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTARM, 30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTARM, 30, _vec3(-D3DX_PI, 0.f, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTARM, 30, _vec3(1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTARM, 30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTARM, 30, _vec3(D3DX_PI, D3DX_PI, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTARM, 30, _vec3(-1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTHAND,  30, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTHAND, 30, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTHAND,  30, _vec3(0.f, -1800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTHAND, 30, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTHAND, 30, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTHAND, 30, _vec3(0.f, -1800.f, 0.f));

	// ³»·ÁÂï±â
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTARM,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTARM, 50, _vec3(-fQater + 0.4f, 0.f, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTARM,  50, _vec3(1700, 800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTARM,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTARM, 50, _vec3(fQater - 0.4f, D3DX_PI, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTARM,  50, _vec3(-1700, 800.f, 0.f));
	
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTHAND,  50, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTHAND, 50, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTHAND, 50, _vec3(0.f, -1800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTHAND, 50, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTHAND, 50, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTHAND, 50, _vec3(0.f, -1800.f, 0.f));

	// Body
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_BODY, 70, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_BODY, 70, _vec3(0.f, 0.f, 0.f));
	// Head
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_HEAD, 70, _vec3(200.f, 200.f, 200.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_HEAD, 70, _vec3(100.f, 700.f, 100.f));
	// Left
	// Arm
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTARM, 70, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTARM, 70, _vec3(0.f, D3DX_PI, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTARM, 70, _vec3(-1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTHAND, 70, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTHAND, 70, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTHAND, 70, _vec3(0.f, -1200.f, 0.f));
	// Right
	// Arm
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTARM, 70, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTARM, 70, _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTARM, 70, _vec3(1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTHAND, 70, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTHAND, 70, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTHAND, 70, _vec3(0.f, -1200.f, 0.f));







	// È¸Àü È¸¿À¸®
	m_pAnimationController->Add_Animator(PAT_BASE);
	//
	//// ¾çÆÈ ¼öÁ÷ »ó½Â
	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_RIGHTARM,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_RIGHTARM, 10, _vec3(0.f, 0.f, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_RIGHTARM,  10, _vec3(1700, 800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_CICLE,  PART_LEFTARM, 10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_LEFTARM, 10, _vec3(0.f, D3DX_PI, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE,  PART_LEFTARM, 10, _vec3(-1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_RIGHTARM, 30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_RIGHTARM, 30, _vec3(0.f, 0.f, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_RIGHTARM, 30, _vec3(1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_LEFTARM,  30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_LEFTARM, 30, _vec3(0.f, D3DX_PI, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_LEFTARM,  30, _vec3(-1700, 800.f, 0.f));
	
	
	
	
	
	//  »§¾ß¤À»§¾ß
	m_pAnimationController->Add_Animator(PAT_BASE);

	// ¿ÞÆÈ Á¶ÁØ
	// ¿Þ ¾î±ú
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTARM,  5, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTARM, 5, _vec3(fQater, D3DX_PI, -0.3f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTARM,  5, _vec3(-1200, 500.f, 0.f));
	// ¿Þ ¼Õ															
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTHAND, 5, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTHAND,5, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTHAND, 5, _vec3(0.f, -1800.f, 0.f));

	// ¿ÞÆÈ Á¶ÁØ
	// ¿Þ ¾î±ú
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTARM,  15, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTARM, 15, _vec3(fQater, D3DX_PI, -0.3f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTARM,  15, _vec3(-1200, 500.f, 0.f));
	// ¿Þ ¼Õ															
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTHAND,  15, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTHAND, 15, _vec3(0.f, 8.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTHAND,  15, _vec3(0.f, -1800.f, 0.f));
}

void CGiantGolem::Animation_Render()
{
	D3DXMATRIX _matWorld;
	//= Body
	m_pPartsTrans[PART_BODY]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pBufferMeshCom->Render_Buffer();

	//= Head
	m_pPartsTrans[PART_HEAD]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_BODY]->Get_WorldWithoutScale());
	m_pBufferHeadMeshCom->Render_Buffer();
	
	
	//= Left	
	// Arm
	m_pPartsTrans[PART_LEFTARM]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_BODY]->Get_WorldWithoutScale());
	m_pBufferBodyMeshCom->Render_Buffer();
	
	// Hand
	m_pPartsTrans[PART_LEFTHAND]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_LEFTARM]->Get_WorldWithoutScale());
	m_pBufferChrystalMeshCom->Render_Buffer();
	m_vShootPos = { m_pPartsTrans[PART_LEFTHAND]->Get_WorldWithoutScale()._41 ,  m_pPartsTrans[PART_LEFTHAND]->Get_WorldWithoutScale()._42 ,  m_pPartsTrans[PART_LEFTHAND]->Get_WorldWithoutScale()._43 };
	//= Right
	// Arm
	m_pPartsTrans[PART_RIGHTARM]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_BODY]->Get_WorldWithoutScale());
	m_pBufferBodyMeshCom->Render_Buffer();

	// Hand
	m_pPartsTrans[PART_RIGHTHAND]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_RIGHTARM]->Get_WorldWithoutScale());
	m_pBufferChrystalMeshCom->Render_Buffer();

}


void CGiantGolem::LateUpdate_Object(const float & fTimeDelta)
{
	Engine::CMonsterMain::LateUpdate_Object(fTimeDelta);
}



void CGiantGolem::Shooting(void)
{

		
	_matrix _World;
	_World = m_pPartsTrans[PART_LEFTHAND]->Get_WorldWithoutScale();
	_World *= m_pPartsTrans[PART_LEFTARM]->Get_WorldWithoutScale();
	_World *= m_pPartsTrans[PART_BODY]->Get_WorldWithoutScale();



	_vec3 vPos = { _World._41  ,	_World._42 , _World._43 };

	Engine::Set_Bullet_LayerMap(Engine::OBJID::NORMAL_BULLET, 1, m_vShootPos);

}

void CGiantGolem::Set_Pattern(BOSSPATTERN _pattern)
{
	if (m_ePattern == PAT_IDLE)
	{
		m_ePattern = _pattern;
	}
}




CGiantGolem * CGiantGolem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGiantGolem*		pInstance = new CGiantGolem(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CGiantGolem::Free(void)
{

	Engine::CMonsterMain::Free();
}
