struct VS_IN
{
	float4 pos : POSITION0;
	float2 tex : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 wvp;

	float2 uvOffset;
	float2 uvSize;
	float4 color;
	float4 pivot;
}

VS_OUT main(VS_IN input)
{
	VS_OUT output;

	output.pos = input.pos - pivot;
	output.pos = mul(output.pos, wvp);

	output.tex = input.tex * uvSize + uvOffset;
	output.color = color;
	return output;
}