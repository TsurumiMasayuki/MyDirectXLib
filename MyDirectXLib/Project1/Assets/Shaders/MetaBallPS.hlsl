struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

cbuffer ColorBuffer : register(b0)
{
	float4 baseColor;
	float4 outlineColor;
}

float4 main(PS_IN input) : SV_Target
{
	float4 sampled = myTexture.Sample(mySampler, input.tex);

	if (sampled.w == 0) discard;

	float baseGradetion = pow(sampled.w, 2);
	float outlineGradetion = 1 - pow(sampled.w, 5);
	
	float4 result;
	result.xyz = lerp(outlineColor.xyz * outlineGradetion, baseColor.xyz * baseGradetion, 0.5);
	result.w = 1;

	return result;
}