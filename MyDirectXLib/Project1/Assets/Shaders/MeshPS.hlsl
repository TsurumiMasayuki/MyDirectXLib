struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 worldPos : POSITION0;
	float4 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

Texture2D meshTexture : register(t0);
SamplerState textureSampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float4 color;
	float4 lightPos;			//光源座標
	float4 lightAttenuation;	//光の減衰
	float4 lightColor;			//光の色
}

float4 main(PS_IN input) : SV_Target
{
	const float ambient = 0.4;								//環境光
	float3 lightDir = lightPos.xyz - input.worldPos.xyz;	//光の当たる方向

	float3 n = normalize(input.normal.xyz);		//法線ベクトルを正規化
	float3 l = normalize(lightDir);				//光のベクトルを正規化
	float diffuse = max(0, dot(n, l));			//法線と光の内積

	//光の減衰
	float len = length(lightDir);
	float attenuation = saturate(
		1.0 / (lightAttenuation.x + lightAttenuation.y * len + lightAttenuation.z * len * len));

	//テクスチャの色取得
	float4 sampled = meshTexture.Sample(textureSampler, input.texCoord);	

	//光の倍率
	float light = max(diffuse * attenuation, ambient);
	//色決定
	float4 output = saturate(sampled * color + lightColor * diffuse);
	//光を当てる
	output.xyz = output.xyz * light;
	return output;
}