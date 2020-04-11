struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

static const float2 center = float2(0.5, 0.5);

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

float4 main(PS_IN input) : SV_Target
{
	float dist = distance(input.tex, center);
	float4 sampled = color * dist;

	return sampled;
}