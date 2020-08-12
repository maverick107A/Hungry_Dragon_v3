#ifndef Export_Resources_h__
#define Export_Resources_h__

#include "Engine_Define.h"
#include "ResourcesMgr.h"

BEGIN(Engine)

// ResourcesMgr
// Get
// Set
// General
inline HRESULT	Reserve_ContainerSize(const _ushort& wSize);

inline HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pBufferTag,
	BUFFERID eID,
	const _ulong& dwCntX = 1,
	const _ulong& dwCntZ = 1,
	const _ulong& dwVtxItv = 1);

inline HRESULT	Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pTextureTag,
							TEXTURETYPE eType,
							const _tchar* pPath,
							const _uint& iCnt = 1);

inline void	Load_Particle(LPDIRECT3DDEVICE9 pGraphicDev);

inline void	Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag);
inline CResources*		Clone(const _ushort& wContainerIdx, const _tchar* pResourceTag);

inline CResources*	Get_Particle(LPDIRECT3DDEVICE9 pGraphicDev,
	PARTICLEID _ePartID,
	BoundingBox _boundingBox,
	_vec3 _vOrigin);

inline CResources* Create_Preview(LPDIRECT3DDEVICE9 pGraphicDev, LPCTSTR _address);
inline CResources* Create_Preview(LPDIRECT3DDEVICE9 pGraphicDev, list<VTXCOL> _listVertex, list<INDEX16> _listIndex);
// Release
inline void		Release_Resources(void);

#include "Export_Resources.inl"

END
#endif // Export_Resources_h__
