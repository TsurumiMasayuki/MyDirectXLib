struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer ConstantBuffer : register(b0)
{
	float4 texelSize;
}

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

static const float weight[7] = { 0.002, 0.04, 0.08, 0.085, 0.08, 0.04, 0.002 };
static const float threshold = 0.8;

float4 luminanceFilter(float4 color)
{
	float luminance = length(color.xyz);
	return color * step(luminance, threshold);
}

float4 main(PS_IN input) : SV_Target
{
	float4 sampled = float4(0.0, 0.0, 0.0, 1.0);

	for (int i = -3; i < 4; i++)
	{
		for (int j = -3; j < 4; j++)
		{
			sampled += luminanceFilter(myTexture.Sample(mySampler, input.tex + float2(texelSize.x * i, texelSize.y * j)) * weight[j + 3]);
		}
	}

	return sampled;
}