#include "Export_Resources.h"
// ResourcesMgr
// Get
// Set
// General
HRESULT	Reserve_ContainerSize(const _ushort& wSize)
{
	return CResourcesMgr::GetInstance()->Reserve_ContainerSize(wSize);
}

HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
	const _ushort& wContainerIdx,
	const _tchar* pBufferTag,
	BUFFERID eID,
	const _ulong& dwCntX,
	const _ulong& dwCntZ,
	const _ulong& dwVtxItv)
{
	return CResourcesMgr::GetInstance()->Ready_Buffer(pGraphicDev, wContainerIdx, pBufferTag, eID, dwCntX, dwCntZ, dwVtxItv);
}
HRESULT	Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
						const _ushort& wContainerIdx,
						const _tchar* pTextureTag,
						TEXTURETYPE eType,
						const _tchar* pPath,
						const _uint& iCnt)
{
	return CResourcesMgr::GetInstance()->Ready_Texture(pGraphicDev, wContainerIdx, pTextureTag, eType, pPath, iCnt);
}

inline void Load_Particle(LPDIRECT3DDEVICE9 pGraphicDev) {
	CResourcesMgr::GetInstance()->Load_Particle(pGraphicDev);
}


void	Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag)
{
	CResourcesMgr::GetInstance()->Render_Buffer(wContainerIdx, pBufferTag);
}

CResources*		Clone(const _ushort& wContainerIdx, const _tchar* pResourceTag)
{
	return CResourcesMgr::GetInstance()->Clone(wContainerIdx, pResourceTag);
}

inline CResources * Get_Particle(LPDIRECT3DDEVICE9 pGraphicDev, PARTICLEID _ePartID, BoundingBox _boundingBox, _vec3 _vOrigin) {
	return CResourcesMgr::GetInstance()->Get_Particle(pGraphicDev, _ePartID, _boundingBox, _vOrigin);
}

inline CResources * Create_Preview(LPDIRECT3DDEVICE9 pGraphicDev, LPCTSTR _address)
{
	return CVICustom::Create(pGraphicDev, _address);
}

inline CResources * Create_Preview(LPDIRECT3DDEVICE9 pGraphicDev, list<VTXCOL> _listVertex, list<INDEX16> _listIndex)
{
	return CVICustom::Create(pGraphicDev, _listVertex, _listIndex);
}

// Release
void		Release_Resources(void)
{
	CResourcesMgr::GetInstance()->DestroyInstance();
}