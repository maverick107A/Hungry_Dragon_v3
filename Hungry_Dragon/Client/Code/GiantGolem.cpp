#include "stdafx.h"
#include "Export_Function.h"
#include "Terrain_Locater.h"
#include "GiantGolem.h"


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
	m_fMonster_HP = 100.f;
	m_fMonster_MaxHP = 100.f;
	m_fScale = 100.f;
	m_fMaxScale = 1000.f;
	m_fDamaged = 2.f;
	m_eState = MONSTER_REBORN;
	m_ePattern = PAT_APEAR;
	return S_OK;
}

int CGiantGolem::Update_Object(const float & fTimeDelta)
{

	if (m_eState == MONSTER_REBORN && m_eState != MONSTER_DEACTIVATE)
	{
		//m_vFirstPos = { 19200.f ,  -1500.f  ,  19200.f };
		//m_pTransform->Set_Trans(&m_vFirstPos);
		//m_pTransform->Set_Scale(m_fMaxScale);
		m_fMonster_HP = 100.f;
		//m_fScale = 15.f;
		m_pParticle = nullptr;
		m_iEvent = OBJ_NOEVENT;
		m_eState = MONSTER_IDLE;
		m_ePattern = PAT_APEAR;
	}


	if (MONSTER_DEAD == Engine::CMonsterMain::Update_Object(fTimeDelta))
	{
		m_eState = MONSTER_REBORN;

		return m_iEvent;
	}

	if (m_ePattern == PAT_CICLE)
	{ 
		m_pTransform->m_vAngle.y += 0.3f;
	}
	else
	{
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

		m_pTransform->m_vAngle.y = m_fAngle;
	}


	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_HEAD);
	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_BODY);
	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_LEFTARM);
	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_LEFTHAND);
	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_RIGHTARM);
	//m_pAnimationController->Set_SpecificFrame(PAT_IDLE, PART_RIGHTHAND);


	if (m_bPatternEnd)
	{
		m_ePattern = PAT_IDLE;
		m_bPatternEnd = false;
	}


	if (m_ePattern == PAT_IDLE)
	{
		m_fPatternTime += fTimeDelta;

		if (m_fPatternTime > m_fPatternDelay)
		{
			switch (m_iPatternNum)
			{
			case 0:
				m_ePattern = PAT_PUNCH;
				++m_iPatternNum;
				break;		
			case 1:
				m_ePattern = PAT_STOMP;
				++m_iPatternNum;
				break;
			
			case 2:
				m_ePattern = PAT_CICLE;
				++m_iPatternNum;
				break;
			
			case 3:
				m_ePattern = PAT_FIREBALL;
				m_iPatternNum = 0;
				break;
			}

			m_fPatternDelay = 0;
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


	return m_iEvent;
}

void CGiantGolem::Render_Object(void)
{
	TCHAR str[64] = L"";
	//wsprintf(str, L"POSITION : (%d,%d,%d)", (int)m_vPos.x, (int)m_vPos.y, (int)m_vPos.z);
	wsprintf(str, L"POSITION : (%d,%d,%d)", (int)m_pPartsTrans[PART_RIGHTHAND]->m_matWorld._41, (int)m_pPartsTrans[PART_RIGHTHAND]->m_matWorld._42, (int)m_pPartsTrans[PART_RIGHTHAND]->m_matWorld._43);
	Engine::Render_Font(L"Font_Light", str, &_vec2(50.f, 10.f), D3DXCOLOR(1.f, 1.f, 0.f, 1.f));

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Animation_Render();
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

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

	//얼굴
	pComponent = m_pPartsTrans[PART_HEAD] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_HeadTransform", pComponent);
	//턱
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);
	//몸통
	pComponent = m_pPartsTrans[PART_LEFTARM] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LeftArmTransform", pComponent);

	pComponent = m_pPartsTrans[PART_LEFTHAND] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LeftHandTransform", pComponent);

	pComponent = m_pPartsTrans[PART_RIGHTARM] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightArmTransform", pComponent);
	//날개
	pComponent = m_pPartsTrans[PART_RIGHTHAND] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_RightHandTransform", pComponent);


	//애니메이션 컨트롤러
	pComponent = m_pAnimationController = Engine::CAnimation_Controller::Create(PARTS_END);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Set_Address(this);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_AnimationController", pComponent);

	//애니메이션 설정
	Preset_Animation();

	return S_OK;
}

void CGiantGolem::Preset_Animation()
{

	float fQater = D3DX_PI * 0.5f;
	float fFull = D3DX_PI * 2.f;
	m_pAnimationController->Add_Animator(-1);


	// Idle

	// Body
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_BODY, 0, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_BODY, 0, _vec3(0.f, 1500.f, 0.f));
	// Head
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_HEAD, 0, _vec3(200.f, 200.f, 200.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_HEAD, 0, _vec3(100.f, 700.f, 100.f));
	// Left
	// Arm
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_LEFTARM, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_IDLE, PART_LEFTARM, 0, _vec3(0.f, D3DX_PI, 0.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_LEFTARM, 0, _vec3(-1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_LEFTHAND, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_IDLE, PART_LEFTHAND, 0, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_LEFTHAND, 0, _vec3(0.f, -1200.f, 0.f));
	// Right
	// Arm
	m_pAnimationController->Insert_Scale(PAT_IDLE, PART_RIGHTARM, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_IDLE, PART_RIGHTARM, 0, _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE, PART_RIGHTARM, 0, _vec3(1700, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_IDLE,  PART_RIGHTHAND, 0, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_IDLE, PART_RIGHTHAND, 0, _vec3(0.f,  2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_IDLE,  PART_RIGHTHAND, 0, _vec3(0.f, -1200.f, 0.f));




	// 두등 등장
	m_pAnimationController->Add_Animator(PAT_IDLE);

	// 팔 크로스!
	// Left
	// Arm
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_LEFTARM,	10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_LEFTARM,	10, _vec3(0.7f, 4.14, 0.f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_LEFTARM,	10, _vec3(-1000.f, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_LEFTHAND,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_LEFTHAND, 10, _vec3(-1.5f, 2.76f, 0.6f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_LEFTHAND,  10, _vec3(300.f, -1000.f, 0.f));
	// Right
	// Arm
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_RIGHTARM,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_RIGHTARM, 10, _vec3(-1.0f, -1.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_RIGHTARM,  10, _vec3(1200.f, 800.f, 0.f));
	//// Hand
	m_pAnimationController->Insert_Scale(PAT_APEAR, PART_RIGHTHAND,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_APEAR, PART_RIGHTHAND, 10, _vec3(1.0f, 2.8f, -0.5f));
	m_pAnimationController->Insert_Trans(PAT_APEAR, PART_RIGHTHAND,  10, _vec3(300.f, -1000.f, 0.f));





	// Punch
	m_pAnimationController->Add_Animator(PAT_IDLE);

	// 팔 수직 상승
	//m_pPartsTrans[PART_RIGHTARM]->m_fDamping =  0.08f;
	//m_pPartsTrans[PART_RIGHTHAND]->m_fDamping = 0.08f;
	//m_pPartsTrans[PART_BODY]->m_fDamping =      0.08f;

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,   10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM,  10, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,   10, _vec3(1700, 800.f, 0.f));
	

	// 바디 회전 당기기
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  20, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 20, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  20, _vec3(1700, 800.f, -300.f));
	
	m_pAnimationController->Insert_Scale(PAT_PUNCH,  PART_BODY,     20, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_BODY,     20, _vec3( 0.f , 0.5f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH,  PART_BODY,     20, _vec3(0.f, 1800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,   20, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND,	 20, _vec3(0.f, 2.8f, 0.4f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,	 20, _vec3(0.f, -1200.f, 0.f));



	// 지르기
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 30, _vec3(-fQater, 0.5f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  30, _vec3(1700, 500.f, 150.f));
	 
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_BODY,  30, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_BODY, 30, _vec3(0.f, -0.5f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_BODY,  30, _vec3(0.f, 1800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,  30, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND, 30, _vec3(0.f, 120.2f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,  30, _vec3(0.f, -1800.f, 0.f));


	// 바디 원래위치로!
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_BODY, 50, _vec3(1000.f, 1300.f, 1000.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_BODY, 50, _vec3(0.f, 1800.f, 0.f));
	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_HEAD, 50, _vec3(200.f, 200.f, 200.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_HEAD, 50, _vec3(100.f, 700.f, 100.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTARM,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTARM, 50, _vec3(-fQater, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTARM,  50, _vec3(1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_PUNCH, PART_RIGHTHAND,  50, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_PUNCH, PART_RIGHTHAND, 50, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_PUNCH, PART_RIGHTHAND,  50, _vec3(0.f, -1200.f, 0.f));


	//양손 모아 찍기
	m_pAnimationController->Add_Animator(PAT_IDLE);
	
	// 양팔 크로스
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
	

	// 팔크기 증가!
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_RIGHTHAND,  30, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_RIGHTHAND, 30, _vec3(0.f, 2.8f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_RIGHTHAND,  30, _vec3(0.f, -1800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_STOMP, PART_LEFTHAND, 30, _vec3(800.f, 1000.f, 800.f));
	m_pAnimationController->Insert_Rotate(PAT_STOMP, PART_LEFTHAND, 30, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_STOMP, PART_LEFTHAND, 30, _vec3(0.f, -1800.f, 0.f));

	// 내려찍기
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


	// 회전 회오리
	m_pAnimationController->Add_Animator(PAT_IDLE);
	//
	//// 양팔 수직 상승
	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_RIGHTARM,  10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_RIGHTARM, 10, _vec3(0.f, 0.f, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_RIGHTARM,  10, _vec3(1700, 800.f, 0.f));
	
	m_pAnimationController->Insert_Scale(PAT_CICLE,  PART_LEFTARM, 10, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_LEFTARM, 10, _vec3(0.f, D3DX_PI, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE,  PART_LEFTARM, 10, _vec3(-1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_RIGHTARM, 1000, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_RIGHTARM, 1000, _vec3(0.f, 0.f, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_RIGHTARM, 1000, _vec3(1700, 800.f, 0.f));

	m_pAnimationController->Insert_Scale(PAT_CICLE, PART_LEFTARM,  1000, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_CICLE, PART_LEFTARM, 1000, _vec3(0.f, D3DX_PI, fQater));
	m_pAnimationController->Insert_Trans(PAT_CICLE, PART_LEFTARM,  1000, _vec3(-1700, 800.f, 0.f));
	
	
	
	
	
	// 회전 회오리
	m_pAnimationController->Add_Animator(PAT_IDLE);

	// 왼팔 조준
	// 왼 어깨
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTARM,  5, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTARM, 5, _vec3(fQater, D3DX_PI, -0.3f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTARM,  5, _vec3(-1200, 500.f, 0.f));
	// 왼 손															
	m_pAnimationController->Insert_Scale(PAT_FIREBALL, PART_LEFTHAND, 5, _vec3(500.f, 500.f, 500.f));
	m_pAnimationController->Insert_Rotate(PAT_FIREBALL, PART_LEFTHAND,5, _vec3(0.f, 2.76f, 0.f));
	m_pAnimationController->Insert_Trans(PAT_FIREBALL, PART_LEFTHAND, 5, _vec3(0.f, -1800.f, 0.f));


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
