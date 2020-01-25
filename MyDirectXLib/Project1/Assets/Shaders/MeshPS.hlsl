struct PS_IN
{
	float4 pos : SV_POSITION;
};

float4 main(PS_IN input) : SV_Target
{
	float4 output;
	output.x = 1.0;
	output.y = 1.0;
	output.z = 1.0;
	output.w = 1.0;
	return output;
}