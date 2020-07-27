#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "Texture.h"
#include "VIBuffer.h"
#include "Terrain.h"
#include "CubeDra.h"
#include "CubeCol.h"
#include "TerrainTex.h"
#include "CubeTex.h"

BEGIN(Engine)

class ENGINE_DLL CResourcesMgr : public CBase
{
	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit CResourcesMgr(void);
	virtual ~CResourcesMgr(void);

public:
	HRESULT	Reserve_ContainerSize(const _ushort& wSize);
	
	HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
						const _ushort& wContainerIdx,
						const _tchar* pBufferTag,
						BUFFERID eID,
						const _ulong& dwCntX = 1,
						const _ulong& dwCntZ = 1,
						const _ulong& dwVtxItv = 1);

	HRESULT	Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pTextureTag,
							TEXTURETYPE eType, 
							const _tchar* pPath, 
							const _uint& iCnt = 1);

	
	void	Render_Buffer(const _ushort& wContainerIdx,
							const _tchar* pBufferTag);

	CResources*		Clone(const _ushort& wContainerIdx, 
							const _tchar* pResourceTag);

private:
	CResources*		Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag);

private:
	map<const _tchar*, CResources*>*		m_pmapResource = nullptr;
	_ushort									m_sMaxContainer;

public:
	virtual void Free(void);
};

END
#endif // ResourcesMgr_h__
