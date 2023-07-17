 ///////////////////////////////////////////
// Scaling Com Wire Curve Shader

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

float sign(float2 p1, float2 p2, float2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(float2 pt, float2 v1, float2 v2, float2 v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

float4 ag_RightArrow(float f_Xsl, float f_Ysl, float f_Length, float f_Height, float f_Time, float4 f_StartColor, float4 f_EndColor)
{
	float f_Xslo = frac((f_Xsl * 10.0 * f_Length) + (1.0 - f_Time));
	float f_Yslo = f_Ysl * 5.0;

	//f_Xslo += ; //CONSTANT

	float2 f_pt = float2(f_Xslo, f_Yslo);

	float4 f_Color = f_StartColor;
	f_Color.w -= f_Yslo;

	float2 f_Pos[3];
	f_Pos[0].x = 0.2;
	f_Pos[0].y = 0.0;
	f_Pos[1].x = 0.2;
	f_Pos[1].y = 1.0;
	f_Pos[2].x = 1.0;
	f_Pos[2].y = 0.5;

	bool f_Result1 = PointInTriangle(f_pt, f_Pos[0], f_Pos[1], f_Pos[2]);

	f_pt.x -= 0.1;

	bool f_Result2 = PointInTriangle(f_pt, f_Pos[0], f_Pos[1], f_Pos[2]);

	if(f_Result1 == true)
		{
		float f_CStrength = 1.0 - f_Yslo;

		if(f_CStrength >= 0.5)
			{
			f_CStrength = 1.0 - ((f_CStrength - 0.5) * 2.0);
			}

		f_Color = f_EndColor;
		
		f_Color.w *= f_CStrength * 1.7;
		}

	if((f_Result2 == true) && (f_Result1 == false))
		{
		f_Color += f_EndColor;

		f_Color.w /= 3.0;
		}

	return f_Color;
}

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float f_Xsl = input.color.r;
	float f_Ysl = 1.0 - input.color.g;
	float f_Zsl = input.color.b;

	//the following should eventually become uniforms or constants
	float3 f_UP = float3(0.0, 1.0, 0.0);
	float3 f_LEFT = float3(-1.0, 0.0, 0.0);
	float3 f_RIGHT = float3(1.0, 0.0, 0.0);
	float3 f_IN = float3(0.0, 0.0, 1.0);
	float3 f_NORMAL = float3(0.0, 0.0, -1.0);
	//bin prolly legacy

	float4 f_ALph = float4(1.0, 1.0, 1.0, 0.0);
	float4 f_Color = float4(1.0, 1.0, 1.0, 1.0 - f_Ysl);

	/*if(f_Xsl > input.Max.x)
		{
		return f_ALph;
		}

	if(f_Ysl > input.Max.y)
		{
		return f_ALph;
		}

	if(f_Xsl < input.Min.x)
		{
		return f_ALph;
		}

	if(f_Ysl < input.Min.y)
		{
		return f_ALph;
		}

	if(f_Zsl > 0.0)
		{
		return f_ALph;
		}*/

	if(((f_Ysl >= 0.0) && (f_Ysl < 0.2)))
		{
		return ag_RightArrow(f_Xsl, f_Ysl, input.Length, input.Height, input.Time, float4(1.0, 0.2, 0.2, 1.0), float4(0.7, 0.45, 0.9, 1.0));
		}
	else if(((f_Ysl >= 0.8) && (f_Ysl < 1.0)))
		{
		return ag_RightArrow(f_Xsl, f_Ysl - 0.8, input.Length, input.Height, input.Time, float4(0.5, 0.5, 0.0, 1.0), float4(0.2, 0.2, 0.2, 0.7));
		}

	return f_Color;
}