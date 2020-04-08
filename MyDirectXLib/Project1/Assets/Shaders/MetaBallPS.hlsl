struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

static float threshold = 0.3;
static float outlineThreshold = 0.5;

static float4 baseColor = float4(0.25, 0.5, 1, 1);
static float4 outlineColor = float4(0, 0, 1, 1);

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