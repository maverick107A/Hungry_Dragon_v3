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
		//pResources = CRcCol::Create(pGraphicDev);

		//임시로 큐브 오브젝트 띄움
		pResources = CCubeCol::Create(pGraphicDev);
		break;

	case BUFFER_RCTEX:
		//pResources = CRcTex::Create(pGraphicDev);
		break;
	case BUFFER_TERRINTEX:
		//pResources = CHeightMap::Create(pGraphicDev);
		break;
	case  BUFFER_CUBEDRA:
		pResources = CCubeDra::Create(pGraphicDev);
		break;
	case BUFFER_CUBETEX:
		pResources = CCubeTex::Create(pGraphicDev);
		break;
	case BUFFER_TERRAINTEX:
		pResources = CTerrainTex::Create(pGraphicDev, dwCntX, dwCntZ, dwVtxItv);
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
	
	Safe_Delete_Array(m_pmapResource);
}

void CResourcesMgr::Ready_Particle(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort & wContainerIdx, const _tchar * pTextureTag, PARTICLEID _ePartID, float _fSize, BoundingBox _boundingBox, _vec3 m_vOrigin) {
}

void Engine::CResourcesMgr::Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag)
{
	CResources*	pResources = Find_Resources(wContainerIdx, pBufferTag);
	NULL_CHECK(pResources);

	static_cast<CVIBuffer*>(pResources)->Render_Buffer();
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

void CResourcesMgr::Load_Particle() {
	//CParticle* pParticle;
}

