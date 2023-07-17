// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;

	float3 f_Rand = float3(model[1][0] * model[0][1] - model[0][1], model[2][0] * model[0][2] * model[2][1], model[0][2] * model[1][1] * model[2][0]);

	float f_A = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand = float3(f_A, f_A, f_A);

	float f_B = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand = float3(f_B, f_B, f_B);

	float f_C = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand = float3(f_C, f_C, f_C);

	float4 pos = float4(input.pos.x, input.pos.y, input.pos.z, 1.0f);

	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	float3 f_Rand2 = float3(model[1][2] * model[2][2] - model[1][1], model[2][1] * model[1][0] * model[0][2], model[2][1] * model[2][2] * model[0][1]);

	float f_A2 = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand2 = float3(f_A2, f_A2, f_A2);

	float f_B2 = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand2 = float3(f_B2, f_B2, f_B2);

	float f_C2 = frac(sin(dot(f_Rand.xyz, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
	f_Rand2 = float3(f_C2, f_C2, f_C2);

	output.pos = float4(pos.x, pos.y, pos.z, 1.0f);

	// Pass the color through without modification.
	output.color = float3(input.color.r * sin(f_B * f_C), input.color.g * sin(f_C * f_A), input.color.b * sin(f_B * f_B));

	return output;
}
