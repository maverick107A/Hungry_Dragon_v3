// -------------------------------------------------------------
// ��������
// 
// Copyright (c) 2002,2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------
float4   vFog;		// (Far/(Far-Near), -1/(Far-Near))

// -------------------------------------------------------------
// �������̴����� �ȼ����̴��� �ѱ�� ������
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
// �������̴�
// -------------------------------------------------------------
VS_OUTPUT VS (VS_INPUT _input)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// ��µ�����
	
	Out.position = _input.position;
	Out.diffuse = _input.diffuse;
	//Out.Col = vCol * max( dot(vLightDir, Normal), 0);	// ������
	
	
	//Out.Fog = vFog.x - _input.position.y * vFog.y;	// ����

	
	return Out;
}
// -------------------------------------------------------------
// ��ũ��
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // ���̴�
        //VertexShader = compile vs_1_1 VS();
        
        FogEnable = true;			// ���׻��
	FogStart      = 50000.0f;  
        FogEnd        = 60000.0f;
        FogVertexMode = Linear;		// ��������
        FogColor = 0xd8e3fe;		// ���׻�
    }
}
