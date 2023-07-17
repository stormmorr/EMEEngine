// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float BORDER_WIDTH = 0.1;

	float4 f_White = float4(1.0, 1.0, 1.0, 1.0);
	
	float f_Xsl = input.color.r * 1.0;
	float f_Ysl = input.color.g * 1.0;
	float f_Zsl = input.color.b * 1.0;

	float f_AlphaX = 1.0;
	float f_AlphaY = 1.0;
	float f_Alpha = 1.0;

	if(f_Zsl > 0.0)
		{
		f_Alpha = 1.0;
		}
	else
		{
		if(f_Xsl < 0.1)
			{
			if(f_Ysl < 0.1)
				{
				f_AlphaX = 1.0 - (f_Xsl / BORDER_WIDTH);
				f_AlphaY = 1.0 - (f_Ysl / BORDER_WIDTH);
				f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
				}
			else if(f_Ysl > 0.9)
				{
				f_AlphaX = 1.0 - (f_Xsl / BORDER_WIDTH);
				f_AlphaY = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
				}
			else
				{
				f_Alpha = 1.0 - (f_Xsl / BORDER_WIDTH); 
				}
			}
		else if(f_Xsl > 0.9)
			{
			if(f_Ysl < 0.1)
				{
				f_AlphaX = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				f_AlphaY = 1.0 - (f_Ysl / BORDER_WIDTH);
				f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
				}
			else if(f_Ysl > 0.9)
				{
				f_AlphaX = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				f_AlphaY = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
				}
			else
				{
				f_Alpha = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				}
			}
		else
			{
			if(f_Ysl < 0.1)
				{
				f_Alpha = 1.0 - (f_Ysl / BORDER_WIDTH);
				}
			else if(f_Ysl > 0.9)
				{
				f_Alpha = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
				}
			else
				{
				f_Alpha = 1.0;
				}
			}
		}

	//Starts Inner 0 - 1 <=> Outer 3 - 4

	float f_TrueAlpha = 1.0;

	float4 f_GradientColor0 = float4(0.1, 0.1, 0.1, f_TrueAlpha);
	float4 f_GradientColor1 = float4(0.53, 0.37, 0.9, f_TrueAlpha);
	float4 f_GradientColor2 = float4(0.703, 0.17, 0.3, f_TrueAlpha);
	float4 f_GradientColor3 = float4(0.2, 0.17, 0.4, f_TrueAlpha);
	float4 f_GradientColor4 = float4(0.8, 0.8, 0.8, f_TrueAlpha);
	float f_GradientLength1 = 0.3;
	float f_GradientLength2 = 0.5;
	float f_GradientLength3 = 0.8;

	if((f_Alpha >= 0.0) && (f_Alpha < f_GradientLength1))
		{
		return f_GradientColor0 * (f_GradientColor1 * (f_Alpha / f_GradientLength1));
		}
	else if((f_Alpha > f_GradientLength1) && (f_Alpha < f_GradientLength2))
		{
		return f_GradientColor1 * (f_GradientColor2 * (f_Alpha / f_GradientLength2));
		}
	else if((f_Alpha > f_GradientLength2) && (f_Alpha < f_GradientLength3))
		{
		return f_GradientColor2 * (f_GradientColor3 * (f_Alpha / f_GradientLength3));
		}
	else if((f_Alpha > f_GradientLength3) && (f_Alpha < 1.0))
		{
		return f_GradientColor3 * (f_GradientColor4 * f_Alpha);
		}
	else
		{
		return f_White;
		}
}