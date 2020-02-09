struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

Texture2D meshTexture : register(t0);
SamplerState textureSampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float4 color;
}

float4 main(PS_IN input) : SV_Target
{
	const float ambient = 0.50;					//環境光
	const float lightDir = float3(1, 1, 0);		//光の当たる方向

	float3 n = normalize(input.normal.xyz);		//法線ベクトルを正規化
	float3 l = normalize(lightDir);				//光のベクトルを正規化
	float diffuse = max(0, dot(n, -l)) * 0.5;	//法線と光(逆方向)の内積

	float4 sampled = meshTexture.Sample(textureSampler, input.texCoord);
	// float4 sampled = {1.0, 1.0, 1.0, 1.0};
	float4 output = sampled * color;
	output.xyz = output.xyz * (ambient + diffuse);
	return output;
}