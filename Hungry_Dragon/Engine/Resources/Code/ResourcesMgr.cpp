#include "ResourcesMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResourcesMgr)

#include "Engine_Define.h"

Engine::CResourcesMgr::CResourcesMgr(void)
	: m_pmapResource(nullptr)
{

}

Engine::CResourcesMgr::~CResourcesMgr(void)
{
	Free();
}

HRESULT Engine::CResourcesMgr::Reserve_ContainerSize(const _ushort& wSize)
{
	if (nullptr != m_pmapResource)
		return E_FAIL;

	m_pmapResource = new map<const _tchar*, CResources*>[wSize];
	m_vecParticle.reserve(PART_END);

	m_sMaxContainer = wSize;

	return S_OK;
}

HRESULT Engine::CResourcesMgr::Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
											const _ushort& wContainerIdx,
											const _tchar* pBufferTag,
											BUFFERID eID,
											const _ulong& dwCntX,
											const _ulong& dwCntZ,
											const _ulong& dwVtxItv)
{
	NULL_CHECK_RETURN(m_pmapResource, E_FAIL);

	CResources*	pResources = Find_Resources(wContainerIdx, pBufferTag);

	if (nullptr != pResources)
		return E_FAIL;

	switch (eID)
	{
	case BUFFER_TERRAIN:
		pResources = CTerrain::Create(pGraphicDev);
		break;
	case BUFFER_RCCOL:
		pResources = CCubeCol::Create(pGraphicDev);
		break;
		//여기부터 플레이어꺼
	case  BUFFER_FACE:
		pResources = CDragonFace::Create(pGraphicDev);
		break;
	case  BUFFER_JAW:
		pResources = CDragonJaw::Create(pGraphicDev);
		break;
	case  BUFFER_BODY:
		pResources = CDragonBody::Create(pGraphicDev);
		break;
	case  BUFFER_WING:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/RightWing.dat");
		break;
	case  BUFFER_LWING:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/LeftWing.dat");
		break;
	case BUFFER_TEXCUBE:
		pResources = CTexture_Cube::Create(pGraphicDev);
		break;
	case BUFFER_TERRAINTEX:
		pResources = CTerrainTex::Create(pGraphicDev, dwCntX, dwCntZ, dwVtxItv);
		break;
	case BUFFER_TEXSQUARE:
		pResources = CTexture_Square::Create(pGraphicDev);
		break;
	case BUFFER_LANDTEX:
		pResources = CTexture_Plane::Create(pGraphicDev, dwCntX, dwCntZ, dwVtxItv);
		break;
	case BUFFER_FOREST:
		pResources = CForestLand::Create(pGraphicDev);
		break;
	case BUFFER_KOREA:	// 맵툴 대신에 일케 자동화 구조를 짜서 깔아봄 Forest 대용 Forest 버퍼는 프로토타입용으로 쓰였음
		pResources = CHeightCol::Create(pGraphicDev, dwCntX, dwCntZ, dwVtxItv);
		break;
	case BUFFER_RIFT:
		pResources = CCliffCylinder::Create(pGraphicDev);
		break;

	case BUFFER_VOLCANO:
		//pResources = CRcCol::Create(pGraphicDev);
		break;

	case BUFFER_ICEAGE:
		//pResources = CRcTex::Create(pGraphicDev);
		break;
	case BUFFER_SKYSPHERE:
		pResources = CSkyCube::Create(pGraphicDev);
		break;

	case SPRITE_ANIM :
		pResources = CMonsterBoard::Create(pGraphicDev, (_float)dwCntX, (_float)dwCntZ);
		break;

	case BUFFER_CAVECYLINDER:
		pResources = CCaveCylinder::Create(pGraphicDev);

		break;
	case BUFFER_VENTCUBE:
		pResources = CVentCube::Create(pGraphicDev);
		break;
	case BUFFER_CUSTOMMESH:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Test.dat");
		break;
	case BUFFER_OBSTACLECUBE:
		pResources = CObstacleCube::Create(pGraphicDev);
		break;
	case BUFFER_DIAMESH:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Diamond.dat");
		break;
	case BUFFER_ROCKMESH:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Rock12.dat");
		break;
	case BUFFER_TREEMESH:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/PolyTree.dat");
		break;
	case BUFFER_STUMPMESH:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/PolyStump.dat");
		break;
	case BUFFER_CHRYSTAL:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Chrystal.dat");
		break;
	case BUFFER_DIAMOB_UPPER:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Mob_Dia_Upper.dat");
		break;
	case BUFFER_DIAMOB_UNDER:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/Mob_Dia_Under.dat");
		break;
	
	case BUFFER_GOLEMBODY:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/GiantBody4.dat");
		break;
	case BUFFER_LEFTHAND:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/LeftHand2.dat");
		break;
	case BUFFER_RIGHTHAND:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/RightHand2.dat");
		break;
	case BUFFER_TWINFACE:
		pResources = CVICustom::Create(pGraphicDev, L"../../Asset/VIMesh/TwinDragon_Head.dat");
		break;

	}

	m_pmapResource[wContainerIdx].emplace(pBufferTag, pResources);

	return S_OK;
}

CResources* Engine::CResourcesMgr::Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag)
{
	auto	iter = find_if(m_pmapResource[wContainerIdx].begin(), m_pmapResource[wContainerIdx].end(), CTag_Finder(pResourceTag));

	if (iter == m_pmapResource[wContainerIdx].end())
		return nullptr;

	return iter->second;
}

void Engine::CResourcesMgr::Free(void)
{
	for (_ushort i = 0; i < m_sMaxContainer; ++i)
	{
		for_each(m_pmapResource[i].begin(), m_pmapResource[i].end(), CDeleteMap());
		m_pmapResource[i].clear();
	}

	for (size_t i = 0; i < PART_END; ++i) {
		Safe_Release(m_vecParticle[i]);
	}
	m_vecParticle.clear();
	
	Safe_Delete_Array(m_pmapResource);
}

CResources* CResourcesMgr::Get_Particle(LPDIRECT3DDEVICE9 pGraphicDev, PARTICLEID _ePartID, BoundingBox _boundingBox, _vec3 _vOrigin) 
{
	if ((size_t)_ePartID >= m_vecParticle.size())
	{
		return nullptr;
	}

	return m_vecParticle[_ePartID]->Clone(_vOrigin, _boundingBox);
}

void Engine::CResourcesMgr::Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag)
{
	CResources*	pResources = Find_Resources(wContainerIdx, pBufferTag);
	NULL_CHECK(pResources);

	static_cast<CResources*>(pResources)->Render_Buffer();
}

CResources* Engine::CResourcesMgr::Clone(const _ushort& wContainerIdx, const _tchar* pResourceTag)
{
	if (nullptr == m_pmapResource)
		return nullptr;

	CResources*	pPrototype = Find_Resources(wContainerIdx, pResourceTag);

	return static_cast<CResources*>(pPrototype->Clone());
}

HRESULT Engine::CResourcesMgr::Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
	const _ushort& wContainerIdx,
	const _tchar* pTextureTag, 
	TEXTURETYPE eType, const _tchar* pPath, const _uint& iCnt /*= 1*/)
{
	NULL_CHECK_RETURN(m_pmapResource, E_FAIL);

	CResources*	pResources = Find_Resources(wContainerIdx, pTextureTag);

	if (nullptr != pResources)
		return E_FAIL;
	
	pResources = CTexture::Create(pGraphicDev, pPath, eType, iCnt);
	NULL_CHECK_RETURN(pResources, E_FAIL);
	

	m_pmapResource[wContainerIdx].emplace(pTextureTag, pResources);

	return S_OK;
}

void CResourcesMgr::Load_Particle(LPDIRECT3DDEVICE9 pGraphicDev) {

	//파티클 전용 타이머 추가
	CTimerMgr::GetInstance()->Ready_Timer(L"Paticle_Timer");

	CParticle* pParticle;

	for (int i = 0; i < PART_END; ++i) {
		switch (i) {
		case PART_ATK:
			pParticle = CPart_Atk::Create(pGraphicDev, 500);
			static_cast<Engine::CPart_Atk*>(pParticle)->Set_Texture(L"../../Asset/snowflake.dds");
			break;
		case PART_WIND:
			pParticle = CPart_Wind::Create(pGraphicDev, 70, 100.f);
			break;
		case PART_FRAGILE:
			pParticle = CPart_Fragile::Create(pGraphicDev, 500);
			static_cast<Engine::CPart_Fragile*>(pParticle)->Set_TexArray();
			break;
		case PART_LEAF:
			pParticle = CPart_Leaf::Create(pGraphicDev, 500);
			static_cast<Engine::CPart_Leaf*>(pParticle)->Set_Texture(L"../../Asset/Particle/leaf.png");
			break;
		default:
			pParticle = nullptr;
			break;
		}

		m_vecParticle.emplace_back(pParticle);
	}
}

void CResourcesMgr::Load_ParticleMFC(LPDIRECT3DDEVICE9 pGraphicDev) {
	//파티클 전용 타이머 추가
	CTimerMgr::GetInstance()->Ready_Timer(L"Paticle_Timer");

	CParticle* pParticle;

	for (int i = 0; i < PART_END; ++i) {
		switch (i) {
		case PART_ATK:
			pParticle = CPart_Atk::Create(pGraphicDev, 500);
			static_cast<Engine::CPart_Atk*>(pParticle)->Set_Texture(L"../Asset/snowflake.dds");
			break;
		case PART_WIND:
			pParticle = CPart_Wind::Create(pGraphicDev, 70, 100.f);
			break;
		case PART_FRAGILE:
			pParticle = CPart_Fragile::Create(pGraphicDev, 500);
			static_cast<Engine::CPart_Fragile*>(pParticle)->Set_TexArrayMFC();
			break;
		default:
			pParticle = nullptr;
			break;
		}

		m_vecParticle.emplace_back(pParticle);
	}
}
