#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagVertexColor
	{
		_vec3		vPosition;
		_ulong		dwColor;

	}VTXCOL;

	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;


	typedef struct tagVertexTex
	{
		_vec3		vPosition;
		_vec3		vNormal;
		_vec2		vTexUV;

		tagVertexTex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v) {
			vPosition.x = _x;
			vPosition.y = _y;
			vPosition.z = _z;

			vNormal.x = _nx;
			vNormal.y = _ny;
			vNormal.z = _nz;

			vTexUV.x = _u;
			vTexUV.y = _v;
		}

	}VTXTEX;

	const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_TEX1;

	typedef struct INDEX16
	{
		_ushort		_0;
		_ushort		_1;
		_ushort		_2;

	}INDEX16;

	typedef struct INDEX32
	{
		_ulong		_0;
		_ulong		_1;
		_ulong		_2;

	}INDEX32;

	//각각의 부품 정보를 저장할 구조체
	typedef struct CUBE {
		//큐브의 너비, 높이, 깊이
		_float fCubeWidth;
		_float fCubeHeight;
		_float fCubeDepth;

		_float fCubeRotX;
		_float fCubeRotY;
		_float fCubeRotZ;
	}_cube;

	typedef struct SPHERE {

	}_sphere;

	typedef struct CYLINDER {

	}_cylinder;
}


#endif // Engine_Struct_h__
