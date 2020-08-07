#include "ResourcesMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResourcesMgr)

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
	case  BUFFER_CUBEDRA:
		pResources = CCubeDra::Create(pGraphicDev);
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
	case BUFFER_RIFT:
		//pResources = CTriCol::Create(pGraphicDev);
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

CResources* CResourcesMgr::Get_Particle(LPDIRECT3DDEVICE9 pGraphicDev, PARTICLEID _ePartID, BoundingBox _boundingBox, _vec3 _vOrigin) {
	if ((size_t)_ePartID >= m_vecParticle.size()) {
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
			pParticle = CPart_Atk::Create(pGraphicDev, 50);
			break;
		case PART_WIND:
			pParticle = CPart_Wind::Create(pGraphicDev, 70,100.f);
			break;
		default:
			pParticle = nullptr;
			break;
		}

		m_vecParticle.emplace_back(pParticle);
	}

}