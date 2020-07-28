#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

//-------------------------------------------------------
//�Ŵ��� ���********************************************
//-------------------------------------------------------
//���⿡ �Ŵ��� ��� �߰�


//-------------------------------------------------------
//��Ÿ ���**********************************************
//-------------------------------------------------------
//���⿡ ��Ÿ ��� �߰�
#include "Terrain.h"
#include "CubeDra.h"
#include "CubeCol.h"

#include "Texture.h"
#include "TerrainTex.h"
#include "CubeTex.h"

#include "ForestLand.h"

#include "Particle.h"		//�ӽ�. ��ƼŬ �������� �����ϸ� �߰��ϰ� ���� ��.
//-------------------------------------------------------




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

	//�̸� ���� ���� m_vecParticle�� ��� ��ƼŬ ȿ���� ������ ������ ���� �Լ�
	void	Load_Particle();

	//Particle �����¿��� Ŭ���� ��ƼŬ�� Layer�� �����ϴ� �Լ�
	void	Ready_Particle(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pTextureTag,
							PARTICLEID _ePartID,
							float _fSize,
							BoundingBox _boundingBox,
							_vec3 m_vOrigin);

	void	Render_Buffer(const _ushort& wContainerIdx,
							const _tchar* pBufferTag);

	
	
	CResources*		Clone(const _ushort& wContainerIdx, 
							const _tchar* pResourceTag);
	
	

private:
	CResources*		Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag);

private:
	map<const _tchar*, CResources*>*		m_pmapResource = nullptr;
	vector<CResources*>						m_vecParticle;
	_ushort									m_sMaxContainer;

public:
	virtual void Free(void);
};

END
#endif // ResourcesMgr_h__
