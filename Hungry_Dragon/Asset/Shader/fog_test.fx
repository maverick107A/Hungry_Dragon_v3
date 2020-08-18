// 
// Effect
//

technique Fog
{
    pass P0
    {
        //
        // Set Misc render states.

        pixelshader      = null;
        vertexshader     = null;
        fvf              = XYZ | Diffuse;
        Lighting         = false;
        NormalizeNormals = true;
        SpecularEnable   = false;

        //
        // Fog States

        FogVertexMode = LINEAR; // linear fog function
        FogStart      = 2000.0f;  
        FogEnd        = 12000.0f;

        FogColor      = 0x00CCCCCC; // gray
        FogEnable     = true;       // enable
    }
}
