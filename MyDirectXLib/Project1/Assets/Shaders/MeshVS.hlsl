struct VS_IN
{
	float4 pos : POSITION0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 wvp;
}

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.pos = mul(input.pos, wvp);
	return output;
}