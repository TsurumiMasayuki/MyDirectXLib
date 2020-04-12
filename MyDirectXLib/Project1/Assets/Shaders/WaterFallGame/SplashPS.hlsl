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

	if (block.w == 0) discard;

	return splash;
}