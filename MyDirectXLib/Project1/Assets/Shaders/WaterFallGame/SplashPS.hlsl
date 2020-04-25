struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

Texture2D splashTexture : register(t0);
Texture2D blockTexture : register(t1);
SamplerState mySampler : register(s0);

float4 main(PS_IN input) : SV_Target
{
	float4 splash = splashTexture.Sample(mySampler, input.tex);
	float4 block = blockTexture.Sample(mySampler, input.tex);

	if (splash.w == 0 || block.w == 0) discard;
	float gradation = 1 - splash.w;

	return lerp(splash, float4(0.0, 0.54, 0.54, 1), gradation);
}