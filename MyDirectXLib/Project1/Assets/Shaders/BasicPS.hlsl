struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

float4 main(PS_IN input) : SV_Target
{
	float4 sampled = myTexture.Sample(mySampler, input.tex);

	// if (sampled.w == 0) discard;

	return sampled;
}