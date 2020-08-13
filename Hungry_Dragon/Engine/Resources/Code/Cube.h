#ifndef CUBE_H__
#define CUBE_H__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCube :public CVIBuffer {
private:
	explicit CCube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCube(const CCube& rhs);
	virtual ~CCube(void);

public:
	//큐브 구조체에 설정한 값을 넣어주는 함수. 아무것도 설정하지 않으면 기본값으로 들어간다.
	void Set_Cube(_float _width=1, _float _height=1, _float _depth=1, _float _rotX = 0, _float _rotY = 0, _float _rotZ = 0);

public:
	virtual HRESULT Ready_Buffer(void);
	virtual void	Render_Buffer(void);

public:
	virtual CComponent* Clone(void);
	virtual void Free(void);

private:
	_cube m_tagCubeInfo;
	_vec3 m_vertexInfo[8];
	INDEX32  m_indexInfo[12];
};

END

#endif
