#include "pch.h"
#include "SampleFpsTextRenderer.h"

//#include "Common/DirectXHelper.h"

using namespace ecoin;
using namespace Microsoft::WRL;

// Initializes D2D resources used for text rendering.
SampleFpsTextRenderer::SampleFpsTextRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) : 
	m_text(L"")
{
	m_deviceResources = deviceResources;

	ZeroMemory(&m_textMetrics, sizeof(DWRITE_TEXT_METRICS));

	DX::ThrowIfFailed(
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory3), &m_dwriteFactory)
        );

    // Create the IDWriteTextLayout.

    ComPtr<IDWriteTextFormat> textFormat;
    DX::ThrowIfFailed(
        m_dwriteFactory->CreateTextFormat(
			L"Audiowide",
            nullptr,    // default font collection
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
			20.0f,
			L"en-US",
			m_textFormat.GetAddressOf()
            )
        );

	// Center the text horizontally.
	winrt::check_hresult(
		m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
	);

	// Center the text vertically.
	winrt::check_hresult(
		m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
	);

	winrt::check_hresult(
		m_deviceResources->m_d2dFactory->CreateDrawingStateBlock(&m_stateBlock)
	);

	CreateDeviceDependentResources();

	time(&g_Storetime);
}

// Updates the text to be displayed.
void SampleFpsTextRenderer::Update(void)
{
	for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
		{
		std::shared_ptr<Qcom> f_com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

		// Update display text.
		StringToWString(m_text, f_com->m_name);

		ComPtr<IDWriteTextLayout> textLayout;
		DX::ThrowIfFailed(
			m_dwriteFactory->CreateTextLayout(
				m_text.c_str(),
				m_text.length(),
				m_textFormat.Get(),
				240.0f, // Max width of the input text.
				50.0f, // Max height of the input text.
				&textLayout
				)
			);

		DX::ThrowIfFailed(
			textLayout.As(&m_textLayout)
			);

		DX::ThrowIfFailed(
			m_textLayout->GetMetrics(&m_textMetrics)
			);

		float f_com_position_X = f_com->m_position->m_X * 2.355f;
		float f_com_position_Y = f_com->m_position->m_Y * 2.355f;

		int f_ColorOverride = 0;

		if(f_com->m_HighLighted == true)
			{
			if(f_com->m_Selected == true)
				{
				f_ColorOverride = 3; // both pink
				}
			else
				{
				f_ColorOverride = 2; // highlighted red
				}
			}
		else
			{
			if(f_com->m_Selected == true)
				{
				f_ColorOverride = 1; // selected blue
				}
			}

		Render(f_com_position_X + 2.15f, f_com_position_Y - 0.12f, f_ColorOverride);

		for(int f_Helly = 0; f_Helly < f_com->m_vec_Input.size(); f_Helly++)
			{
			std::shared_ptr<QcomInput> f_Input = f_com->m_vec_Input[f_Helly];

			StringToWString(m_text, f_Input->m_name);

			ComPtr<IDWriteTextLayout> textLayout1;
			DX::ThrowIfFailed(
				m_dwriteFactory->CreateTextLayout(
					m_text.c_str(),
					m_text.length(),
					m_textFormat.Get(),
					240.0f, // Max width of the input text.
					50.0f, // Max height of the input text.
					&textLayout1
					)
				);

			DX::ThrowIfFailed(
				textLayout1.As(&m_textLayout)
				);

			DX::ThrowIfFailed(
				m_textLayout->GetMetrics(&m_textMetrics)
				);

			int f_LocalColor = f_ColorOverride;

			if(f_Input->m_HighLighted == true)
				{
				if(f_Input->m_Selected == true)
					{
					f_LocalColor = 3; // both pink
					}
				else
					{
					f_LocalColor = 2; // highlighted red
					}
				}
			else
				{
				if(f_Input->m_Selected == true)
					{
					if(f_ColorOverride == 1)
						{
						f_LocalColor = 4; // com selected blue / input selected also purple or dark blue
						}
					else
						{
						f_LocalColor = 1; // selected blue
						}
					}
				}

			Render(((f_com_position_X + (f_Input->m_position->m_X * g_ComICOPositionToComPositionX)) - g_CarriageReturnX) + 1.75f, (f_com_position_Y - (f_Input->m_position->m_Y * g_ComICOPositionToComPositionY)) - 0.6f, f_LocalColor);
			}

		for(int f_Helly = 0; f_Helly < f_com->m_vec_Output.size(); f_Helly++)
			{
			std::shared_ptr<QcomOutput> f_Output = f_com->m_vec_Output[f_Helly];

			StringToWString(m_text, f_Output->m_name);

			ComPtr<IDWriteTextLayout> textLayout2;
			DX::ThrowIfFailed(
				m_dwriteFactory->CreateTextLayout(
					m_text.c_str(),
					m_text.length(),
					m_textFormat.Get(),
					240.0f, // Max width of the input text.
					50.0f, // Max height of the input text.
					&textLayout2
					)
				);

			DX::ThrowIfFailed(
				textLayout2.As(&m_textLayout)
				);

			DX::ThrowIfFailed(
				m_textLayout->GetMetrics(&m_textMetrics)
				);

			int f_LocalColor = f_ColorOverride;

			if(f_Output->m_HighLighted == true)
				{
				if(f_Output->m_Selected == true)
					{
					f_LocalColor = 3; // both pink
					}
				else
					{
					f_LocalColor = 2; // highlighted red
					}
				}
			else
				{
				if(f_Output->m_Selected == true)
					{
					if(f_ColorOverride == 1)
						{
						f_LocalColor = 4; // com selected blue / input selected also purple or dark blue
						}
					else
						{
						f_LocalColor = 1; // selected blue
						}
					}
				}

			Render((f_com_position_X + (f_Output->m_position->m_X * g_ComICOPositionToComPositionX)) - g_CarriageReturnX, f_com_position_Y - (f_Output->m_position->m_Y * g_ComICOPositionToComPositionY), f_LocalColor);
			}

#if 0
		std::shared_ptr<QcomOutput> f_Output = f_com->m_vec_Output[f_com->m_vec_Output.size() - 1];

		std::string f_Text = "";

		char* f_Char = ag_ClearChar(1024);

		sprintf(f_Char, "COM INFO ID = %i\nX=%f Y=%f\nm_X=%f m_Y=%f\nInput1xy %f %f\n", f_com->m_ID, f_com->m_position->m_X, f_com->m_position->m_Y, g_vec_DecisionsManager[0]->m_Wheel->m_position.m_X, g_vec_DecisionsManager[0]->m_Wheel->m_position.m_Y, f_com->m_vec_Input[0]->m_position.m_X, f_com->m_vec_Input[0]->m_position.m_Y);

		f_Text = f_Char;

		StringToWString(m_text, f_Text);

		ComPtr<IDWriteTextLayout> textLayout2;
		DX::ThrowIfFailed(
			m_dwriteFactory->CreateTextLayout(
				m_text.c_str(),
				m_text.length(),
				m_textFormat.Get(),
				240.0f, // Max width of the input text.
				50.0f, // Max height of the input text.
				&textLayout2
				)
			);

		DX::ThrowIfFailed(
			textLayout2.As(&m_textLayout)
			);

		DX::ThrowIfFailed(
			m_textLayout->GetMetrics(&m_textMetrics)
			);

		Render((f_com_position_X + (f_Output->m_position->m_X * g_ComICOPositionToComPositionX)) - g_CarriageReturnX, (f_com_position_Y - (f_Output->m_position->m_Y * g_ComICOPositionToComPositionY)) + 1.5f, 0);
#endif
		}
}

// Renders a frame to the screen.
void SampleFpsTextRenderer::Render(float f_X, float f_Y, int f_ColorIndex)
{
	ID2D1DeviceContext* context = m_deviceResources->m_d2dContext.Get();

	context->SaveDrawingState(m_stateBlock.Get());
	context->BeginDraw();

	// Position on the bottom right corner
	D2D1::Matrix3x2F screenTranslation = D2D1::Matrix3x2F::Translation(
		m_textMetrics.layoutWidth,
		m_textMetrics.height
		);

	context->SetTransform(screenTranslation * m_deviceResources->GetOrientationTransform2D());

	DX::ThrowIfFailed(
		m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING)
		);

	float f_Div = 5.0f;

	f_X *= ((10.81f / 127.0f) + 1.0f);
	f_Y *= ((10.4f / 127.0f) + 1.0f);

	float f_addX = (1.0f / 12.7f) + (9200.0f / 127.0f);
	float f_addY = (11000.0f / 127.0f);

	float f_One = m_deviceResources->m_d3dRenderTargetSize.Width / 127.0f;

	float f_scalingX = m_deviceResources->m_d3dRenderTargetSize.Width / 11.595f;
	float f_scalingY = m_deviceResources->m_d3dRenderTargetSize.Height / 4.8f;

	float f_pushX = (((g_QcomManager->m_current_X * -1.0f) / f_Div) * 0.53f);
	float f_pushY = ((g_QcomManager->m_current_Y / f_Div) * 0.68f); //1

	float f_pushscaledX = f_pushX * f_scalingX;
	float f_pushscaledY = f_pushY * f_scalingY;
																																									 //2
	float f_eyeLKX = (((((((g_QcomManager->m_current_X * -1.0f) / f_Div) * m_deviceResources->m_d3dRenderTargetSize.Width) + (m_deviceResources->m_d3dRenderTargetSize.Width * 6.0f) + (f_One * 12.3f)) / 13.5f) + f_pushscaledX) * 0.6667f);
	float f_eyeLKY = ((((((g_QcomManager->m_current_Y / f_Div) * m_deviceResources->m_d3dRenderTargetSize.Height) + (m_deviceResources->m_d3dRenderTargetSize.Height * 2.5f) + (f_One * 10.0f)) / 13.5f) + f_pushscaledY) * 0.6667f);

	float f_rangeX = f_eyeLKX + (f_X * 16.0f);
	float f_rangeY = f_eyeLKY + (f_Y * -16.0f);

	float f_kX = f_rangeX + f_addX;
	float f_kY = (f_rangeY + f_addY) + (g_BoardPushHeightAdjust * g_ComPositionToPoint2fFactor);

	if(f_ColorIndex == 0)
		{
		context->DrawTextLayout(
			D2D1::Point2F(f_kX, f_kY),
			m_textLayout.Get(),
			m_blackBrush.Get()
			);
		}
	else if(f_ColorIndex == 1)
		{
		context->DrawTextLayout(
			D2D1::Point2F(f_kX, f_kY),
			m_textLayout.Get(),
			m_deepblueBrush.Get()
			);
		}
	else if(f_ColorIndex == 2)
		{
		context->DrawTextLayout(
			D2D1::Point2F(f_kX, f_kY),
			m_textLayout.Get(),
			m_redBrush.Get()
			);
		}
	else if(f_ColorIndex == 3)
		{
		context->DrawTextLayout(
			D2D1::Point2F(f_kX, f_kY),
			m_textLayout.Get(),
			m_pinkBrush.Get()
			);
		}
	else
		{
		context->DrawTextLayout(
			D2D1::Point2F(f_kX, f_kY),
			m_textLayout.Get(),
			m_lightblueBrush.Get()
			);
		}

	// Ignore D2DERR_RECREATE_TARGET here. This error indicates that the device
	// is lost. It will be handled during the next call to Present.
	HRESULT hr = context->EndDraw();
	if(hr != D2DERR_RECREATE_TARGET)
		{
		DX::ThrowIfFailed(hr);
		}

	context->RestoreDrawingState(m_stateBlock.Get());
}

void SampleFpsTextRenderer::CreateDeviceDependentResources()
{
	DX::ThrowIfFailed(m_deviceResources->m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_blackBrush));
	DX::ThrowIfFailed(m_deviceResources->m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DeepSkyBlue), &m_deepblueBrush));
	DX::ThrowIfFailed(m_deviceResources->m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_redBrush));
	DX::ThrowIfFailed(m_deviceResources->m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumPurple), &m_pinkBrush));
	DX::ThrowIfFailed(m_deviceResources->m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightBlue), &m_lightblueBrush));
}

void SampleFpsTextRenderer::ReleaseDeviceDependentResources()
{
	m_blackBrush.Reset();
	m_deepblueBrush.Reset();
	m_redBrush.Reset();
	m_pinkBrush.Reset();
	m_lightblueBrush.Reset();
}