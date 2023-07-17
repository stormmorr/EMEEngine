// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float TEN_WIDTH = 0.0025;
	float ONE_LENGTH = 0.96;

	float4 f_RGBA = float4(0.65, 0.65, 0.65, 1.0);
	float4 f_TenGridColor = float4(0.1, 0.1, 0.1, 1.0);
	float4 f_OneGridColor = float4(0.45, 0.45, 0.45, 1.0);
	
	float f_Xsl = frac(input.color.r * 25.0);
	float f_Ysl = frac(input.color.g * 25.0);

	float f_Half = (1.0 - ONE_LENGTH) / 2.0;

	if(f_Xsl > ONE_LENGTH && f_Ysl > ONE_LENGTH)
		return f_OneGridColor;

	if(f_Xsl > ONE_LENGTH)
		{
		float f_Distl = (f_Xsl - ONE_LENGTH);

		float f_Str = abs(f_Half - f_Distl) / f_Half;

		float4 f_REDGRBLUE = f_RGBA - f_OneGridColor;

		return f_OneGridColor + (f_REDGRBLUE * f_Str);
		}

	if(f_Ysl > ONE_LENGTH)
		{
		float f_Distl = (f_Ysl - ONE_LENGTH);

		float f_Str = abs(f_Half - f_Distl) / f_Half;

		float4 f_REDGRBLUE = f_RGBA - f_OneGridColor;

		return f_OneGridColor + (f_REDGRBLUE * f_Str);
		}

	for(int f_XY = 1; f_XY < 10; f_XY++)
		{
		float f_XYZ = float(f_XY);

		if((f_Xsl > (0.1 * f_XYZ) - TEN_WIDTH) && (f_Xsl < (0.1 * f_XYZ) + TEN_WIDTH))
			return f_TenGridColor;

		if ((f_Ysl > (0.1 * f_XYZ) - TEN_WIDTH) && (f_Ysl < (0.1 * f_XYZ) + TEN_WIDTH))
			return f_TenGridColor;
		}

	return f_RGBA;
}