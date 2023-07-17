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
	float2 Min : TEXCOORD0;
	float2 Max : TEXCOORD1;
	float Time : TEXCOORD2;
	float Length : TEXCOORD3;
	float Height : TEXCOORD4;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;

	output.Min = float2(model[0].x, model[1].x);
	output.Max = float2(model[0].y, model[1].y);
	output.Time = model[0].z;
	output.Length = model[2].x;
	output.Height = model[3].x;

	float4 pos = float4(input.pos.x, input.pos.y, input.pos.z, 1.0f);

	// Transform the vertex position into projected space.
	//pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);

	pos = float4(pos.x, pos.y, pos.z, pos.w);

	//float4 f_Origin = float4(0.0, 0.0, 0.0, 0.0);

	//if(output.Length == 10.0)
	//	{
		output.pos = pos;
	//	}
	//else
	//	{
	//	output.pos = f_Origin;
	//	}

	// Pass the color through without modification.
	output.color = float3(input.color.r, input.color.g, input.color.b);

	return output;
}
