struct VS_IN
{
	float4 pos : POSITION0;
	float4 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 worldPos : POSITION0;
	float4 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 world;
	float4x4 viewProj;
	float4x4 world_inv;
}

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.worldPos = mul(input.pos, world);		//頂点 * ワールド変換行列
	output.pos = mul(output.worldPos, viewProj);	//ワールド変換済み頂点 * View * Proj
	output.normal = normalize(mul(input.normal, world_inv));	//法線 * ワールド変換行列の逆行列
	output.texCoord = input.texCoord;
	return output;
}