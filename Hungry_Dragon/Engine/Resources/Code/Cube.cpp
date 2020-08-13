#include "Cube.h"

USING(Engine)

CCube::CCube(LPDIRECT3DDEVICE9 pGraphicDev) 
	:CVIBuffer(pGraphicDev)
{
}

CCube::CCube(const CCube & rhs) 
	:CVIBuffer(rhs)
{
	m_tagCubeInfo = rhs.m_tagCubeInfo;
	for (int i = 0; i < 8; ++i) {
		m_vertexInfo[i] = rhs.m_vertexInfo[i];
	}

	for (int i = 0; i < 10; ++i) {
		m_indexInfo[i] = rhs.m_indexInfo[i];
	}
}

CCube::~CCube(void) {
}

void CCube::Set_Cube(_float _width, _float _height, _float _depth, _float _rotX, _float _rotY, _float _rotZ) {
	m_tagCubeInfo.fCubeWidth = _width;
	m_tagCubeInfo.fCubeHeight = _height;
	m_tagCubeInfo.fCubeDepth = _depth;

	m_tagCubeInfo.fCubeRotX = _rotX;
	m_tagCubeInfo.fCubeRotY = _rotY;
	m_tagCubeInfo.fCubeRotZ = _rotZ;

	m_vertexInfo[0] = { _width*-0.5f, _height*0.5f, _depth*-0.5f };
	m_vertexInfo[1] = { _width*0.5f, _height*0.5f, _depth*-0.5f };
	m_vertexInfo[2] = { _width*0.5f, _height*-0.5f, _depth*-0.5f };
	m_vertexInfo[3] = { _width*-0.5f, _height*-0.5f, _depth*-0.5f };

	m_vertexInfo[4] = { _width*0.5f, _height*0.5f, _depth*0.5f };
	m_vertexInfo[5] = { _width*-0.5f, _height*0.5f, _depth*0.5f };
	m_vertexInfo[6] = { _width*-0.5f, _height*-0.5f, _depth*0.5f };
	m_vertexInfo[7] = { _width*0.5f, _height*-0.5f, _depth*0.5f };

	
	//앞면
	m_indexInfo[0]._0 = 0; m_indexInfo[0]._1 = 1; m_indexInfo[0]._2 = 2;
	m_indexInfo[1]._0 = 0; m_indexInfo[1]._1 = 2; m_indexInfo[1]._2 = 3;

	//우면
	m_indexInfo[2]._0 = 1; m_indexInfo[2]._1 = 4; m_indexInfo[2]._2 = 7;
	m_indexInfo[3]._0 = 1; m_indexInfo[3]._1 = 7; m_indexInfo[3]._2 = 2;

	//후면
	m_indexInfo[4]._0 = 4; m_indexInfo[4]._1 = 5; m_indexInfo[4]._2 = 6;
	m_indexInfo[5]._0 = 4; m_indexInfo[5]._1 = 6; m_indexInfo[5]._2 = 7;

	//좌면
	m_indexInfo[6]._0 = 5; m_indexInfo[6]._1 = 0; m_indexInfo[6]._2 = 3;
	m_indexInfo[7]._0 = 5; m_indexInfo[7]._1 = 3; m_indexInfo[7]._2 = 6;

	//상면
	m_indexInfo[8]._0 = 5; m_indexInfo[8]._1 = 4; m_indexInfo[8]._2 = 1;
	m_indexInfo[9]._0 = 5; m_indexInfo[9]._1 = 1; m_indexInfo[9]._2 = 0;

	//후면
	m_indexInfo[10]._0 = 3; m_indexInfo[10]._1 = 2; m_indexInfo[10]._2 = 7;
	m_indexInfo[11]._0 = 3; m_indexInfo[11]._1 = 7; m_indexInfo[11]._2 = 6;
}

HRESULT CCube::Ready_Buffer(void) {
	m_dwVtxCnt = 8;
	m_dwIdxSize = 12;
	m_dwVtxSize = sizeof(VTXTEX);
	return S_OK;
}

void CCube::Render_Buffer(void) {
}

CComponent * CCube::Clone(void) {
	return nullptr;
}

void CCube::Free(void) {
}
