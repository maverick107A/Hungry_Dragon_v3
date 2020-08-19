#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagVertexColor
	{
		_vec3		vPosition;
		_ulong		dwColor;

		tagVertexColor() {}
		tagVertexColor(_float _x, _float _y, _float _z, _ulong _c) {
			vPosition.x = _x;
			vPosition.y = _y;
			vPosition.z = _z;

			dwColor = _c;
		}

	}VTXCOL;

	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;


	typedef struct tagVertexUV
	{
		_vec3		vPosition;
		_vec2		vTexUV;

		tagVertexUV(_float _x, _float _y, _float _z, _float _u, _float _v) {
			vPosition.x = _x;
			vPosition.y = _y;
			vPosition.z = _z;

			vTexUV.x = _u;
			vTexUV.y = _v;
		}

	}VTXUV;

	const _ulong	FVF_UV = D3DFVF_XYZ | D3DFVF_TEX1;


	typedef struct tagVertexCube
	{
		_vec3		vPosition;
		_vec3		vTexUV;

	}VTXCUBE;

	const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);	// 텍스쳐 UV를 FLOAT형 3개의 값으로 표현하겠다는 옵션

	

	typedef struct tagVertexTex
	{
		_vec3		vPosition;
		_vec3		vNormal;
		_vec2		vTexUV;

		tagVertexTex(_float _x, _float _y, _float _z, _float _nx, _float _ny, _float _nz, _float _u, _float _v) {
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

	typedef struct PARTICLE {
		_vec3				vPosition;
		D3DCOLOR			tColor;
	}PARTICLE;

	static const _ulong	FVF_PART = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	struct ATTRIBUTE {
		ATTRIBUTE() {
			fLifeTime = 0.f;
			fAge = 0.f;
			bAlive = true;
		}

		_vec3 vPosition;
		_vec3 vVelocity;
		_vec3 vAccel;

		float fLifeTime;
		float fAge;

		int		iShape;
		int		iFrameIndex;
		bool	bFrameUp;

		D3DXCOLOR tColor;
		D3DXCOLOR tColorFade;

		bool	bAlive;
	};

	typedef struct BoundingBox {

		bool isPointInside(_vec3& position) {
			if (position.x >= vMin.x && position.y >= vMin.y && position.z >= vMin.z &&
				position.x <= vMax.x && position.y <= vMax.y && position.z <= vMax.z) {
				return true;
			}
			else {
				return false;
			}
		}

		_vec3 vMin;
		_vec3 vMax;
	}BoundingBox;

	typedef struct tagAddress{
		//각 자리수를 통해 종류를 판단.
		//1000	xxxx -> 레이어
		//0100	xxxx -> 게임오브젝트
		//0010	xxxx -> 컴포넌트
		_char	StateFlag;
		void*	LayerAddress;
		void*	ObjAddress;
		void*	ComponentAddress;
	}tagAdd;


	typedef struct tagFrame
	{
		float fStartFrame;
		float fMaxFrame;
		float fFrameSpeed;

	}FRAME;

	typedef struct tagMovement
	{
		_vec3 vecScale;
		_vec3 vecRot;
		_vec3 vecTrans;
		_vec3 vecRevParent;
		_vec3 vecRevolution;
		_vec3 vecParent;
		_int	tFrame;
	}MOVEMENT;
}


#endif // Engine_Struct_h__
