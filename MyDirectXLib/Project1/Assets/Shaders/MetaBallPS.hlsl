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

static float4 baseColor = float4(0, 0.2, 1, 1);
static float4 outlineColor = float4(0.1, 0.5, 1, 1);

float4 main(PS_IN input) : SV_Target
{
	float4 sampled = myTexture.Sample(mySampler, input.tex);

	clip(sampled.w - threshold);

	return sampled.w <= outlineThreshold ? baseColor : outlineColor;
}