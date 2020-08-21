// -------------------------------------------------------------
// 높이포그
// 
// Copyright (c) 2002,2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// 전역변수
// -------------------------------------------------------------
float4   vFog;		// (Far/(Far-Near), -1/(Far-Near))

// -------------------------------------------------------------
// 정점셰이더에서 픽셀셰이더로 넘기는 데이터
// -------------------------------------------------------------
struct VS_INPUT
{
	 vector position : POSITION;
  	 float diffuse  : COLOR;
};

struct VS_OUTPUT
{
	 vector position : POSITION;
  	 float diffuse  : COLOR;
	 //float  Fog      : FOG;
};

// -------------------------------------------------------------
// 정점셰이더
// -------------------------------------------------------------
VS_OUTPUT VS (VS_INPUT _input)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 출력데이터
	
	Out.position = _input.position;
	Out.diffuse = _input.diffuse;
	//Out.Col = vCol * max( dot(vLightDir, Normal), 0);	// 조명계산
	
	
	//Out.Fog = vFog.x - _input.position.y * vFog.y;	// 포그

	
	return Out;
}
// -------------------------------------------------------------
// 테크닉
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // 셰이더
        //VertexShader = compile vs_1_1 VS();
        
        FogEnable = true;			// 포그사용
	FogStart      = 50000.0f;  
        FogEnd        = 60000.0f;
        FogVertexMode = Linear;		// 선형포그
        FogColor = 0xd8e3fe;		// 포그색
    }
}
