///Shader used to render debug information.
///Authors: Chris Peters

float4x4 WorldViewProj : WorldViewProjection;
float4 color = {1,1,1,1};

struct VS_INPUT
{
    float3 position	: POSITION;
};

struct VS_OUTPUT
{
	float4 screenposition : POSITION;
};

VS_OUTPUT VertexShaderLine( VS_INPUT IN )
{
	VS_OUTPUT OUT;
	OUT.screenposition = mul( float4(IN.position, 1) , WorldViewProj);
	return OUT;
}

float4 PixelShaderLine( VS_OUTPUT IN ) : COLOR
{	
	return color;	
}

technique Technique0
{
	pass Pass0
	{
		Lighting = FALSE;
		AlphaBlendEnable = TRUE;
		VertexShader = compile vs_2_0 VertexShaderLine();
		PixelShader  = compile ps_2_0 PixelShaderLine();
	}
}