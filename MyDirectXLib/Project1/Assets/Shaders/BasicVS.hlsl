//最低限の機能の頂点シェーダ
struct VS_IN
{
	float4 pos : POSITION0;
	float2 tex : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

cbuffer WVPBuffer : register(b0)
{
	float4x4 wvp;
}

VS_OUT main(VS_IN input)
{
	VS_OUT output;

	output.pos = mul(input.pos, wvp);
	output.tex = input.tex;
	return output;
}