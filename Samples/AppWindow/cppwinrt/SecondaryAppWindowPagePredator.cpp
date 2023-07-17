//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "pch.h"
#include "SecondaryAppWindowPagePredator.h"
#include "SecondaryAppWindowPagePredator.g.cpp"
#include <Code\CLS\Target.h>

#include "SecondaryAppWindowPageDX.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"

using namespace std;
using namespace DX;

winrt::Windows::UI::WindowManagement::AppWindow appWindowPredator{ nullptr };
winrt::Windows::UI::Xaml::Controls::TextBox appWindowPredatorTextBox{ nullptr };

bool g_PopOnce = false;

namespace winrt::SDKTemplate::implementation
{
    SecondaryAppWindowPagePredator::SecondaryAppWindowPagePredator() :
		m_windowVisible(true),
		m_DPI(96.f),
		m_logicalWidth(800.f),
		m_logicalHeight(600.f),
		m_nativeOrientation(winrt::Windows::Graphics::Display::DisplayOrientations::None),
		m_currentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations::None)
	{
		std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPagePredator::SecondaryAppWindowPagePredator";

		InitializeComponent();

		g_CopyStackPageN = 0;

		OnCreateNewCopyStackPage();

		ag_StatusLive(f_ref_CurrentPath, "g_vec_PredatorManager");
		g_vec_PredatorManager.push_back(std::make_shared_reflect<predatorInstanceManager>());

		// Register event handlers for page lifecycle.
		appWindowPredator.Changed({ this, &SecondaryAppWindowPagePredator::OnSizeChanged });

		IVectorView<DisplayRegion> f_Sizeion = appWindowPredator.GetDisplayRegions();
		winrt::Windows::Foundation::Size f_Size = f_Sizeion.First().Current().WorkAreaSize();

		m_logicalWidth = f_Size.Width;
		m_logicalHeight = f_Size.Height;

		m_outputWidth = ConvertDipsToPixels(m_logicalWidth);
		m_outputHeight = ConvertDipsToPixels(m_logicalHeight);

		winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

		m_nativeOrientation = currentDisplayInformation.NativeOrientation();
		m_currentOrientation = currentDisplayInformation.CurrentOrientation();

		DXGI_MODE_ROTATION rotation = ComputeDisplayRotation();

		appWindowPredatorTextBox = predatortextBox();

		//// Legend of Cube Builder
		//// Begin ESL

		//stat vars
		std::string f_StringLine[88];

		std::string f_FunctionNew = "Function%%EcomNative&*LegendBuilder%%";

		f_StringLine[0] = "Var%%float&&VertexCounter%%0.0&%Opr%%Plus**XT%%Var%%float&&ICXVertexCount1%%1.0&%";
		f_StringLine[1] = "Var%%float&&CountCube%%0.0&%Opr%%Plus**XS%%Var%%float&&ICXCount1%%1.0&%";
		f_StringLine[2] = "Var%%float&&V8Y%%0.0&%";
		f_StringLine[3] = "Var%%float&&V8Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V7Y%%";
		f_StringLine[4] = "Var%%float&&V7Y%%0.0&%";
		f_StringLine[5] = "Var%%float&&V7Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V6Y%%";
		f_StringLine[6] = "Var%%float&&V6Y%%0.0&%";
		f_StringLine[7] = "Var%%float&&V6Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V5Y%%";
		f_StringLine[8] = "Var%%float&&V5Y%%0.0&%";
		f_StringLine[9] = "Var%%float&&V5Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V4Y%%";
		f_StringLine[10] = "Var%%float&&V4Y%%0.0&%";
		f_StringLine[11] = "Var%%float&&V4Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V3Y%%";
		f_StringLine[12] = "Var%%float&&V3Y%%0.0&%";
		f_StringLine[13] = "Var%%float&&V3Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V2Y%%";
		f_StringLine[14] = "Var%%float&&V2Y%%0.0&%";
		f_StringLine[15] = "Var%%float&&V2Y%%0.0&%Opr%%Plus**ORVX87%%Var%%float&&V1Y%%";
		f_StringLine[16] = "Var%%float&&V1Y%%0.0&%";
		f_StringLine[17] = "Var%%float&&V1Y%%0.0&%Opr%%Plus**ORVX87%%Sys%%float&&PosY%%";
		f_StringLine[18] = "Var%%float&&CountCube%%0.0&%Cond%%==^^XC%%Var%%float&&TXCUBECheck%%9.0&%";
		f_StringLine[19] = "Function%%IFSCC&*Success%%";
		f_StringLine[20] = "Var%%float&&V2Y%%0.0&%";
		f_StringLine[21] = "Var%%float&&V3Y%%0.0&%";
		f_StringLine[22] = "Var%%float&&V4Y%%0.0&%";
		f_StringLine[23] = "Var%%float&&V5Y%%0.0&%";
		f_StringLine[24] = "Var%%float&&V6Y%%0.0&%";
		f_StringLine[25] = "Var%%float&&V7Y%%0.0&%";
		f_StringLine[26] = "Var%%float&&V8Y%%0.0&%";
		f_StringLine[27] = "Var%%float&&CubeCount%%0.0&%";

		//Engage
		f_StringLine[28] = "Function%%IFFCC&*Failure%%";
		f_StringLine[29] = "Var%%float&&CountCube%%0.0&%Cond%%==^^XA%%Var%%float&&TWOSMOOTHCheck%%2.0&%";
		f_StringLine[30] = "Function%%IFSCC2&*Success%%";
		f_StringLine[31] = "Sys%%float&&Posy%%0.0&%Cond%%>=^^XTXT%%Var%%float&&EvensCheck%%0.0&%";
		f_StringLine[32] = "Function%%IFSEVENSCHKHigh&*Success%%";
		f_StringLine[33] = "Sys%%float&&Posy%%3.0&%";
		f_StringLine[34] = "Function%%IFSEVENSCHKLow&*Failure%%";
		f_StringLine[35] = "Sys%%float&&Posy%%-3.0&%";

		std::string f_StrLineCompile = f_FunctionNew;

		for(int f_Cor = 0; f_Cor < 36; f_Cor++)
			{
			f_StrLineCompile += f_StringLine[f_Cor];
			}

		std::string f_StrLineCompileSP;
		f_StrLineCompileSP.clear();

		for(int f_Cor = 0; f_Cor < 36; f_Cor++)
			{
			f_StrLineCompileSP += f_StringLine[f_Cor] + "\n";
			}

		f_StrLineCompileSP += f_FunctionNew + "\n";

		std::string f_StringLines = f_StrLineCompile;
		std::string f_StringLinesText = f_StrLineCompileSP;

		g_Tab[0] = f_StringLinesText;

		std::string f_String = f_StringLines;
		std::string f_StringText = f_StringLinesText;

		predatortextBox().Text(StrUsingStr(f_StringText));
	}

	void SecondaryAppWindowPagePredator::acClick(std::string f_CurrentFunction)
	{
		ag_Click(f_CurrentFunction);

		Qpo->Sound_Play_Default(Medias->S_Click, 0.6f);
	}

	int SecondaryAppWindowPagePredator::ConvertDipsToPixels(float dips)
	{
		return int(dips * m_DPI / 96.f + 0.5f);
	}

	float SecondaryAppWindowPagePredator::ConvertPixelsToDips(int pixels)
	{
		return (float(pixels) * 96.f / m_DPI);
	}

	DXGI_MODE_ROTATION SecondaryAppWindowPagePredator::ComputeDisplayRotation(void)
    {
        DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

        switch (m_nativeOrientation)
			{
			case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
				{
				switch (m_currentOrientation)
					{
					case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
						{
						rotation = DXGI_MODE_ROTATION_IDENTITY;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
						{
						rotation = DXGI_MODE_ROTATION_ROTATE270;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
						{
						rotation = DXGI_MODE_ROTATION_ROTATE180;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
						{
						rotation = DXGI_MODE_ROTATION_ROTATE90;
						}break;
					}
				}break;

			case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
				{
				switch (m_currentOrientation)
					{
					case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
						{
						rotation = DXGI_MODE_ROTATION_ROTATE90;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
						{
						rotation = DXGI_MODE_ROTATION_IDENTITY;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped: 
						{
						rotation = DXGI_MODE_ROTATION_ROTATE270;
						}break;

					case winrt::Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
						{
						rotation = DXGI_MODE_ROTATION_ROTATE180;
						}break;
					}
				}break;
			}

        return rotation;
    }

	void SecondaryAppWindowPagePredator::OnVisibilityChanged(winrt::AppWindow sender, winrt::VisibilityChangedEventArgs args)
	{
		winrt::Windows::Foundation::Size f_Size = sender.GetPlacement().Size();

		m_logicalWidth = f_Size.Width;
		m_logicalHeight = f_Size.Height;

		winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

		m_nativeOrientation = currentDisplayInformation.NativeOrientation();
		m_currentOrientation = currentDisplayInformation.CurrentOrientation();

		float f_Height = m_logicalHeight;

		float f_NewHeightScaled = (f_Height - 527.0f) * 1.0f;

		float f_predHeight = f_NewHeightScaled;
		float f_predStkHeight = 0;
		float f_predGridHeight = 0;

		if(f_predHeight < 200.0f)
			{
			f_predHeight = 947.0f;
			f_predStkHeight = 1077.0f;
			f_predGridHeight = 1077.0f;
			}
		else
			{
			f_predStkHeight = f_NewHeightScaled + 130.0f;
			f_predGridHeight = f_NewHeightScaled + 130.0f;
			}

		predatortextBox().Height(f_predHeight);
		predatorStackPanelB().Height(f_predStkHeight);
		predatorGridB().Height(f_predGridHeight);
	}

	void SecondaryAppWindowPagePredator::OnSizeChanged(winrt::AppWindow sender, winrt::AppWindowChangedEventArgs args)
	{
		if(args.DidSizeChange() == true)
			{
			winrt::Windows::Foundation::Size f_Size = sender.GetPlacement().Size();

			m_logicalWidth = f_Size.Width;
			m_logicalHeight = f_Size.Height;

			winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

			m_nativeOrientation = currentDisplayInformation.NativeOrientation();
			m_currentOrientation = currentDisplayInformation.CurrentOrientation();

			float f_Height = m_logicalHeight;

			float f_NewHeightScaled = (f_Height - 527.0f) * 1.0f;

			float f_predHeight = f_NewHeightScaled;
			float f_predStkHeight = 0;
			float f_predGridHeight = 0;

			if(f_predHeight < 200.0f)
				{
				f_predHeight = 947.0f;
				f_predStkHeight = 1077.0f;
				f_predGridHeight = 1077.0f;
				}
			else
				{
				f_predStkHeight = f_NewHeightScaled + 130.0f;
				f_predGridHeight = f_NewHeightScaled + 130.0f;
				}

			predatortextBox().Height(f_predHeight);
			predatorStackPanelB().Height(f_predStkHeight);
			predatorGridB().Height(f_predGridHeight);
			}
	}

	void SecondaryAppWindowPagePredator::SizeChanged(winrt::Windows::Foundation::Size f_size)
	{
		m_logicalWidth = f_size.Width;
		m_logicalHeight = f_size.Height;

		winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

		m_nativeOrientation = currentDisplayInformation.NativeOrientation();
		m_currentOrientation = currentDisplayInformation.CurrentOrientation();

		float f_Height = m_logicalHeight;

		float f_NewHeightScaled = (f_Height - 527.0f) * 1.0f;

		float f_predHeight = f_NewHeightScaled;
		float f_predStkHeight = 0;
		float f_predGridHeight = 0;

		if(f_predHeight < 200.0f)
			{
			f_predHeight = 947.0f;
			f_predStkHeight = 1077.0f;
			f_predGridHeight = 1077.0f;
			}
		else
			{
			f_predStkHeight = f_NewHeightScaled + 130.0f;
			f_predGridHeight = f_NewHeightScaled + 130.0f;
			}

		predatortextBox().Height(f_predHeight);
		predatorStackPanelB().Height(f_predStkHeight);
		predatorGridB().Height(f_predGridHeight);
	}

	auto CreateComboBoxItem = [](hstring const& name, IInspectable const& tag = nullptr)
	{
		Windows::UI::Xaml::Controls::ComboBoxItem item;
		item.Content(box_value(name));
		item.Tag(tag);
		return item;
	};

	std::byte SecondaryAppWindowPagePredator::HexToByteUsingByteManipulation(std::string s)
	{
		std::byte byte_result;

		int hi = s[0] - 65;
		hi = hi + 10 + ((hi >> 31) & 7);

		int lo = s[1] - 65;
		lo = lo + 10 + ((lo >> 31) & 7) & 0x0f;

		byte_result = (std::byte) (lo | hi << 4);

		return byte_result;
	}

	double SecondaryAppWindowPagePredator::atodi(std::string f_String)
	{
		return 0.0 + (double)atoi(f_String.c_str());
	}

	void SecondaryAppWindowPagePredator::OnClickWindow(IInspectable sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs e)
	{
	//.
	}

	void SecondaryAppWindowPagePredator::OnReleaseWindow(IInspectable sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs e)
	{
	//.
	}

	void SecondaryAppWindowPagePredator::OnRightClickWindow(IInspectable sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e)
	{
	//.
	}

	void SecondaryAppWindowPagePredator::acLoadShare(int f_LShare, int f_ServLay)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPagePredator::acLoadShare";

		int f_ShareID = 0;
		bool f_L = false;

		if(f_LShare == 0)
			{
#if 0
			std::shared_ptr<ShareContainer> f_ShareContainer = ag_SelectPeerGraph(g_JobID, f_ServLay, 0, g_CurrentShareOffset, g_PEER);

			ag_BuildVecTier(f_ShareContainer);

			int f_PeerCount = f_ShareContainer->m_Peer.size();

			if(f_PeerCount > 0)
				{
				if(g_CurrentShareOffset < f_ShareContainer->m_Peer[g_PEER]->m_Share.size())
					{
					f_ShareID = f_ShareContainer->m_espo_ID;
					g_espo_ShareOffset = g_CurrentShareOffset;
					g_espo_Peer = g_PEER;
					g_espo_Owner = f_ShareContainer->m_espo_Owner;
					g_espo_Date = f_ShareContainer->m_espo_Date;
					g_espo_Score = f_ShareContainer->m_espo_Score;
					g_espo_Score = f_ShareContainer->m_Peer[g_PEER]->m_Share[g_CurrentShareOffset]->m_Score;
					g_espo_Amount = f_ShareContainer->m_Peer[g_PEER]->m_Share[g_CurrentShareOffset]->m_Amount;
					g_espo_ECN_Amount = f_ShareContainer->m_Peer[g_PEER]->m_Share[g_CurrentShareOffset]->m_ECN_Amount;

					f_L = true;
					}
				else
					{
					f_L = false;
					}
				}
			else
				{
				f_L = false;
				}
#endif
			}
		else
			{
			f_ShareID = g_ShareID;

			f_L = true;
			}

		if(f_L)
			{
			g_ShareID = f_ShareID;
			printf("ECN::Displaying Share f_ShareID = %i", f_ShareID);

			char* query = (char*)malloc(sizeof(char) * 1024);
			sprintf(query, "SELECT id, mark, assetid, assetofficeid, jobid, eslid, targetid, eslcode, difficulty, shareledger, jobledger, owner, bckred, bckgreen, bckblue FROM share WHERE id = %i", f_ShareID);
			g_SafeL[f_ServLay]->acSelectCommand(query, false, false);
			free(query);

			int f_ShareEXCNT = 0;

			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_ShareEXCNT = 0;
				}
			else
				{
				f_ShareEXCNT = g_Schedular[0]->acEntrySize();
				}

			if(f_ShareEXCNT >= 1)
				{
				g_CurrentShareID = atoi(g_Schedular[f_ServLay]->acEntry(0)[0].c_str());

				Cube::BiVector f_BCK(atof(g_Schedular[f_ServLay]->acEntry(0)[12].c_str()), atof(g_Schedular[f_ServLay]->acEntry(0)[13].c_str()), atof(g_Schedular[f_ServLay]->acEntry(0)[14].c_str()));

				std::string f_ESL_Code = g_Schedular[f_ServLay]->acEntry(0)[7];

				char* cubequery = (char*)malloc(sizeof(char) * 4024);
				sprintf(cubequery, "SELECT id, vert1x, vert1y, vert1z, vert2x, vert2y, vert2z, vert3x, vert3y, vert3z, vert4x, vert4y, vert4z, vert5x, vert5y, vert5z, vert6x, vert6y, vert6z, vert7x, vert7y, vert7z, vert8x, vert8y, vert8z, vert1r, vert1g, vert1b, vert2r, vert2g, vert2b, vert3r, vert3g, vert3b, vert4r, vert4g, vert4b, vert5r, vert5g, vert5b, vert6r, vert6g, vert6b, vert7r, vert7g, vert7b, vert8r, vert8g, vert8b, shareid, jobid, eslid, targetid, eslcode, difficulty FROM cube WHERE shareid = %i ORDER BY eslid ASC#", f_ShareID);
				g_SafeL[f_ServLay]->acSelectCommand(cubequery, false, false);
				free(cubequery);

				int f_adCount = 0;

				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_adCount = 0;
					}
				else
					{
					f_adCount = g_Schedular[0]->acEntrySize();
					}

				if(f_adCount >= 26)
					{
					f_adCount = 26;
					}

				//ECN::f_adCount
				//...
				//ECN::Form Hesh

				ag_StatusLive(f_ref_CurrentPath, "f_Heshr");
				std::shared_ptr<Cube::CubeHESH> f_Heshr = ::std::make_shared<Cube::CubeHESH>();

				for(int f_Int = 0; f_Int < f_adCount; f_Int++)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_Bike");
					std::shared_ptr<Cube::CubeBicycle> f_Bike = ::std::make_shared<Cube::CubeBicycle>();

					f_Bike->acClear();

					for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_Vector");
						std::shared_ptr<Cube::BiVector> f_Vector = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + (f_Int2 * 3)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 1)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 2)].c_str()));

						if(f_Vector->m_X < -4.0f)
							{
							f_Vector->m_X = -2.3f;
							}

						if(f_Vector->m_Y < -4.0f)
							{
							f_Vector->m_Y = -2.3f;
							}

						if(f_Vector->m_Z < -4.0f)
							{
							f_Vector->m_Z = -2.3f;
							}

						if(f_Vector->m_X > 4.0f)
							{
							f_Vector->m_X = 2.3f;
							}

						if(f_Vector->m_Y > 4.0f)
							{
							f_Vector->m_Y = 2.3f;
							}

						if(f_Vector->m_Z > 4.0f)
							{
							f_Vector->m_Z = 2.3f;
							}

						f_Bike->vec_Vertex.push_back(f_Vector);
						}

					f_Bike->vec_Color.clear();

					for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_Color");
						std::shared_ptr<Cube::BiVector> f_Color = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + (f_Int3 * 3)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 1)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 2)].c_str()));

						while(f_Color->m_X <= 0.15)
							{
							f_Color->m_X = 0.15;
							}

						while(f_Color->m_Y <= 0.15)
							{
							f_Color->m_Y = 0.15;
							}

						while(f_Color->m_Z <= 0.15)
							{
							f_Color->m_Z = 0.15;
							}

						f_Bike->vec_Color.push_back(f_Color);
						}

					f_Heshr->vec_Bicycle.push_back(f_Bike);
					}

				  //////////
				 // HESH //
				//////////
				int f_PortCNTR = 0;
				while(f_Heshr->m_adIndex.size() < f_adCount)
					{
					f_Heshr->m_adIndex.push_back(f_PortCNTR);
					f_PortCNTR++;
					}

				f_Heshr->m_bckred = f_BCK.m_X;
				f_Heshr->m_bckgreen = f_BCK.m_Y;
				f_Heshr->m_bckblue = f_BCK.m_Z;

				g_TargetedHesh->ac_IsOK();

				g_TargetedHesh = f_Heshr;

				g_RenderHesh = true;

#if 0
				classTargetScript* f_TargetScript = new classTargetScript(f_Heshr);

				f_TargetScript->acPrint();

				//...

				if(f_Heshr->vec_Bicycle.size() >= 2)
					{
					std::shared_ptr<classTarget_JScript> f_TargetScript = ::std::make_shared<classTarget_JScript>();

					f_TargetScript->acGatherNames();
					f_TargetScript->acLoad_Biscuit();
					f_TargetScript->acMerge_ICOtoName();

					g_MasterTarget = ::std::make_shared<classTarget_JScript>(); //Build here

					g_MasterTarget->acGatherNames();
					g_MasterTarget->acLoad_Biscuit();
					g_MasterTarget->acMerge_ICOtoName();

					f_TargetScript->acFromHesh(f_Heshr, g_MasterTarget);

					scriptoutputtextBox.Text(StrUsingStr(f_TargetScript->m_String);
					scriptoutputtextBox->IsReadOnly = true;
					}
#endif

				g_Once = true;

#if 0			//Chakra Core Desktop WinAPI Family... only :(
				unsigned int currentSourceContext = 0;

				std::string f_String = "var f_FirstInput = 'HelloWorld';return f_FirstInput;";

				wstring wide_string1 = wstring(f_String.begin(), f_String.end());
				const wchar_t* f_wcharstring = wide_string1.c_str();

				std::string f_String2 = "";

				wstring wide_string2 = wstring(f_String2.begin(), f_String2.end());
				const wchar_t* f_wcharstring2 = wide_string2.c_str();

				JsValueRef result;
				JsErrorCode errorCode = JsRunScript(f_wcharstring, currentSourceContext++, f_wcharstring2, &result);
#endif

				g_currentLaunchTypeName = f_ESL_Code;

				int f_Type = ag_FindTypefromCode(f_ESL_Code);

				g_currentLaunchType = f_Type;

				g_currentLaunchPrefix = ag_FindPrefixfromCode(f_ESL_Code);

				g_currentLaunch = false;

				//g_Type Switch
				switch(f_Type)
					{
					case 2:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_1");
						g_Target_1 = ::std::make_shared<classTarget>(f_Heshr);
						ag_StatusLive(f_ref_CurrentPath, "g_Target_2");
						g_Target_2 = ::std::make_shared<classTarget>(f_Heshr);

						if((g_Type == 0) || (g_Type == 1))
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(2)[" + g_currentLaunchPrefix + "]";

							g_currentLaunch = true;
							}
						}break;

					case 4:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_3");
						g_Target_3 = ::std::make_shared<classTarget_Ecom>();

						g_Target_3->acFromHesh(f_Heshr, g_Target_3);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_4");
						g_Target_4 = ::std::make_shared<classTarget_Ecom>();

						g_Target_4->acFromHesh(f_Heshr, g_Target_4);

						if(g_Type == 3)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(4)[" + g_currentLaunchPrefix + "]";

							g_currentLaunch = true;
							}
						}break;

					case 6:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_5");
						g_Target_5 = ::std::make_shared<classTarget_ESL_Script>();

						g_Target_5->acFromHesh(f_Heshr, g_Target_5);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_6");
						g_Target_6 = ::std::make_shared<classTarget_ESL_Script>();

						g_Target_6->acFromHesh(f_Heshr, g_Target_6);

						if(g_Type == 5)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(6)[" + g_currentLaunchPrefix + "]";

							g_currentLaunch = true;
							}
						}break;

					case 8:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_7");
						g_Target_7 = ::std::make_shared<classTarget_Generation_Script>();

						g_Target_7->acFromHesh(f_Heshr, g_Target_7);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_8");
						g_Target_8 = ::std::make_shared<classTarget_Generation_Script>();

						g_Target_8->acFromHesh(f_Heshr, g_Target_8);

						if(g_Type == 7)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(8)[" + g_currentLaunchPrefix + "]";

							g_currentLaunch = true;
							}
						}break;

					case 10:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_9");
						g_Target_9 = ::std::make_shared<classTarget_JScript>();

						g_Target_9->acFromHesh(f_Heshr, g_Target_9);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_10");
						g_Target_10 = ::std::make_shared<classTarget_JScript>();

						g_Target_10->acFromHesh(f_Heshr, g_Target_10);

						if(g_Type == 9)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(10)[" + g_currentLaunchPrefix + "]";

							g_currentLaunch = true;
							}
						}break;
					}

				if(g_currentLaunch == false)
					{
					g_Found_Msg = 15;
					g_Found_Text = "[" + g_currentLaunchPrefix + "]";
					}
				}
			else
				{
				//ECN::requested share doesnt exist shareid g_ShareID
				}
			}
		else
			{
			//ECN::Zero shares on job
			}
	}

	//Begin [Predator Delegates]
	void SecondaryAppWindowPagePredator::OnClickComFunction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		std::vector<std::shared_ptr<BiPacket>> f_Packet = g_QcomManager->acSearch_PacketbyName(f_ButtonName);

		for(int f_XY = 0; f_XY < f_Packet.size(); f_XY++)
			{
			if(f_Packet[f_XY]->m_Name.length() > 0)
				{
				std::shared_ptr<Qcom> f_com = f_Packet[f_XY]->m_Operator_Com;

				f_com->ac_Execute();
				}
			}
	}

#if 1
		///////////////////////////////////////////
	   // Ecom Building Generation Script
	  //
	void SecondaryAppWindowPagePredator::acBuild_ExcomPackaging(void)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPagePredator::acBuild_ExcomPackaging";

		winrt::Windows::UI::Xaml::Controls::Grid g_ecomGrid;
		winrt::Windows::UI::Xaml::Controls::StackPanel g_ecomStackPanel;

		for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Packet.size(); f_XY++)
			{
			std::shared_ptr<BiPacket> f_Packet = g_QcomManager->m_vec_Packet[f_XY];

			if(f_Packet->m_Activate_Status == COM_PAK_UNACTIVATED)
				{
				bool f_Fail_PacketIncomplete = false;

				switch(f_Packet->m_InsertElementType)
					{
					case COM_PAK_TYPE_INSERT:
						{
						switch(f_Packet->m_ClassType)
							{
							case ctVariable:
								{
								}break;

							case ctCClass:
								{
								}break;

							case ctQcom:
								{
								}break;

							case ctQcomInput:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								std::vector<std::string> f_vec_Package_XElement_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Data;

								f_vec_Package_XElement_Title.clear();
								f_vecvec_Package_Arg_Title.clear();
								f_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													f_Packets.clear();
													f_Some = false;
													}
												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_vec_Package_XElement_Title[f_IDX].compare("QcomInput") == 0 ||
											f_vec_Package_XElement_Title[f_IDX].compare("ecomInput") == 0 ||
											f_vec_Package_XElement_Title[f_IDX].compare("Input") == 0)
											{
											ag_StatusLive(f_ref_CurrentPath, "f_Input");
											std::shared_ptr<QcomInput> f_Input = ::std::make_shared<QcomInput>();

											f_Input->m_name = f_Packet->m_Name;

											f_Packet->m_Operator_Com->m_vec_Input.push_back(f_Input);
											g_QcomManager->m_vec_Input.push_back(f_Input);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positionx") == 0)
													{
													float f_Float = atof(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Input->m_position->m_X = f_Float;
													}
												else if(f_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positiony") == 0)
													{
													float f_Float = atof(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Input->m_position->m_Y = f_Float;
													}
												}
											}
										}
									}
								}break;

							case ctQcomOutput:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								std::vector<std::string> f_vec_Package_XElement_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Data;

								f_vec_Package_XElement_Title.clear();
								f_vecvec_Package_Arg_Title.clear();
								f_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													f_Packets.clear();
													f_Some = false;
													}
												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_vec_Package_XElement_Title[f_IDX].compare("QcomOutput") == 0 ||
											f_vec_Package_XElement_Title[f_IDX].compare("ecomOutput") == 0 ||
											f_vec_Package_XElement_Title[f_IDX].compare("Output") == 0)
											{
											ag_StatusLive(f_ref_CurrentPath, "f_Output");
											std::shared_ptr<QcomOutput> f_Output = ::std::make_shared<QcomOutput>();

											f_Output->m_name = f_Packet->m_Name;

											f_Packet->m_Operator_Com->m_vec_Output.push_back(f_Output);
											g_QcomManager->m_vec_Output.push_back(f_Output);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positionx") == 0)
													{
													float f_Float = atof(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Output->m_position->m_X = f_Float;
													}
												else if(f_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positiony") == 0)
													{
													float f_Float = atof(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Output->m_position->m_Y = f_Float;
													}
												}
											}
										}
									}
								}break;

							case ctComFunctionX:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								std::vector<std::string> f_vec_Package_XElement_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Title;
								std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Data;

								f_vec_Package_XElement_Title.clear();
								f_vecvec_Package_Arg_Title.clear();
								f_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vec_Package_XElement_Title.push_back(f_Packets);

													f_Packets.clear();
													f_Some = false;
													}
												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_vec_Package_XElement_Title[f_IDX].compare("Button") == 0)
											{
											//set knowns
											winrt::Windows::UI::Xaml::Controls::Button g_ecomButton({});
											g_ecomButton.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

											g_ecomButton.FontFamily(myFont);

											g_ecomButton.Click({ this, &SecondaryAppWindowPagePredator::OnClickComFunction });

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vec_Package_XElement_Title[f_IDX].compare("Content") == 0)
													{
													g_ecomButton.Content(box_value(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet])));
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Foreground") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomButton.Foreground(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Background") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomButton.Background(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("BorderBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomButton.BorderBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomButton.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomButton.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFont({ StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

													g_ecomButton.FontFamily(myFont);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
													{
													g_ecomButton.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
													{
													g_ecomButton.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													g_ecomButton.Margin(myThickness);
													}
												}

											g_swapChainPanel.Children().Append(g_ecomButton);
											}
										else if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
											{
											//set knowns
											winrt::Windows::UI::Xaml::Controls::StackPanel g_ecomStackPanel({});

											g_ecomStackPanel.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											//g_ecomStackPanel.Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vec_Package_XElement_Title[f_IDX].compare("Background") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomStackPanel.Background(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("BorderBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomStackPanel.BorderBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomStackPanel.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomStackPanel.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
													{
													g_ecomStackPanel.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
													{
													g_ecomStackPanel.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														g_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														g_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														g_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														g_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													g_ecomStackPanel.Margin(myThickness);
													}
												}

											g_swapChainPanel.Children().Append(g_ecomStackPanel);
											}
										else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
											{
											//set knowns
											Windows::UI::Xaml::Controls::Grid g_ecomGrid({});
											g_ecomGrid.Name(StrUsingStr(f_Packet->m_Name));

											Windows::UI::Xaml::Controls::ColumnDefinition myCollumn({});
											Windows::UI::Xaml::Controls::RowDefinition myRow({});

											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.ColumnDefinitions().Append(myCollumn);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);
											g_ecomGrid.RowDefinitions().Append(myRow);

											//set defaults
											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vec_Package_XElement_Title[f_XY].compare("Background") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomGrid.Background(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("BorderBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomGrid.BorderBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomGrid.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													g_ecomGrid.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Height") == 0)
													{
													g_ecomGrid.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Width") == 0)
													{
													g_ecomGrid.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("VerticalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														g_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														g_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("HorizontalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														g_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														g_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														g_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														g_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													g_ecomGrid.Margin(myThickness);
													}
												}

											g_swapChainPanel.Children().Append(g_ecomGrid);
											}
										else if(f_vec_Package_XElement_Title[0].compare("TextBlock") == 0)
											{
											Windows::UI::Xaml::Controls::TextBlock f_TextBlock({});

											//set knowns
											f_TextBlock.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" }); 

											f_TextBlock.FontFamily(myFont);

											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vec_Package_XElement_Title[f_XY].compare("Text") == 0)
													{
													f_TextBlock.Text(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Foreground") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.Foreground(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.SelectionHighlightColor(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFont({ StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

													f_TextBlock.FontFamily(myFont);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Height") == 0)
													{
													f_TextBlock.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Width") == 0)
													{
													f_TextBlock.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("VerticalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("HorizontalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_TextBlock.Margin(myThickness);
													}
												}

											g_swapChainPanel.Children().Append(f_TextBlock);
											}
										else if(f_vec_Package_XElement_Title[0].compare("TextBox") == 0)
											{
											Windows::UI::Xaml::Controls::TextBox f_TextBox;

											//set knowns
											f_TextBox.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

											f_TextBox.FontFamily(myFont);

											for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_vec_Package_XElement_Title[f_XY].compare("Text") == 0)
													{
													f_TextBox.Text(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Foreground") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.Foreground(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.SelectionHighlightColor(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFont(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));

													f_TextBox.FontFamily(myFont);
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Height") == 0)
													{
													f_TextBox.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Width") == 0)
													{
													f_TextBox.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("VerticalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("HorizontalAlignment") == 0)
													{
													if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_vec_Package_XElement_Title[f_XY].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_TextBox.Margin(myThickness);
													}
												}

											g_swapChainPanel.Children().Append(f_TextBox);
											}
										}
									}
								}break;

							case ctEClass:
								{
								}break;

							case ctShare:
								{
								}break;

							case ctElement:
								{
								}break;

							default:
								{
								//g_ExcomPexMain->acExecute(EXCOM_MAIN_INSERT_IDX, 0, f_Packet->m_ClassType);
								}break;
							}

						for(int f_LP = 0; f_LP < f_Packet->m_vec_Packet.size(); f_LP++)
							{
							std::shared_ptr<BiPacket> f_PacketLP = f_Packet->m_vec_Packet[f_LP];

							if(f_PacketLP->m_InsertElementType == COM_PAK_TYPE_COMPLETE)
								{
								switch(f_PacketLP->m_ClassType)
									{
									case ctVariable:
										{
										}break;

									case ctCClass:
										{
										}break;

									case ctQcom:
										{
										}break;

									case ctQcomInput:
										{
										ag_StatusLive(f_ref_CurrentPath, "f_Input");
										std::shared_ptr<QcomInput> f_Input = ::std::make_shared<QcomInput>();
										}break;

									case ctQcomOutput:
										{
										}break;

									case ctComFunctionX:
										{
										std::string f_DefaultPacket = f_Packet->m_DefaultValue;

										std::vector<std::string> f_vec_Package_XElement_Title;
										std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Title;
										std::vector<std::vector<std::string>> f_vecvec_Package_Arg_Data;

										f_vec_Package_XElement_Title.clear();
										f_vecvec_Package_Arg_Title.clear();
										f_vecvec_Package_Arg_Data.clear();

										std::string f_Packets = "";
										bool f_Some = false;
										int f_InputStage = 0;

										for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
											{
											if(f_Fail_PacketIncomplete == false)
												{
												char f_c = f_DefaultPacket.at(f_CCount);

												switch(f_InputStage)
													{
													case COM_PAKX_STAGE_TITLE:
														{
														if(f_c == '_')
															{
															f_vec_Package_XElement_Title.push_back(f_Packets);

															std::vector<std::string> f_vec_String;
															f_vec_String.clear();

															f_vecvec_Package_Arg_Title.push_back(f_vec_String);
															f_vecvec_Package_Arg_Data.push_back(f_vec_String);

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '-')
															{
															f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=') //win
															{
															if(f_vec_Package_XElement_Title.size() >= 1)
																{
																if(f_vecvec_Package_Arg_Title.size() >= 1)
																	{
																	f_vecvec_Package_Arg_Title[f_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
																	}
																else
																	{
		#ifdef ECOIN_SECURE
																	throw;
		#endif
																	}
																}

															f_InputStage = COM_PAKX_STAGE_EQUAL;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;

													case COM_PAKX_STAGE_EQUAL:
														{
														if(f_c == '_')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_InputStage = COM_PAKX_STAGE_QUOTE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}

														if(f_CCount >= f_DefaultPacket.length() - 1)
															{
															f_vec_Package_XElement_Title.push_back(f_Packets);

															f_Packets.clear();
															f_Some = false;
															}
														}break;

													case COM_PAKX_STAGE_QUOTE:
														{
														if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

															f_InputStage = COM_PAKX_STAGE_TITLE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}

														if(f_CCount >= f_DefaultPacket.length() - 1)
															{
															f_vecvec_Package_Arg_Data[f_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

															f_InputStage = COM_PAKX_STAGE_TITLE;

															f_Packets.clear();
															f_Some = false;
															}
														}break;
													}
												}
											}

										if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_vec_Package_XElement_Title.size() <= 0))
											{
											f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
											throw;
#endif
											}

										if(f_Fail_PacketIncomplete == false)
											{
											for(int f_IDX = 0; f_IDX < f_vec_Package_XElement_Title.size(); f_IDX++)
												{
												if(f_vec_Package_XElement_Title[f_IDX].compare("Button") == 0)
													{
													//set knowns
													Windows::UI::Xaml::Controls::Button g_ecomButton({});

													g_ecomButton.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

													g_ecomButton.FontFamily(myFont);

													g_ecomButton.Click({ this, &SecondaryAppWindowPagePredator::OnClickComFunction });

													for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
														{
														if(f_vec_Package_XElement_Title[f_IDX].compare("Content") == 0)
															{
															g_ecomButton.Content(box_value(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet])));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Foreground") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															g_ecomButton.Foreground(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Background") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															g_ecomButton.Background(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("BorderBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															g_ecomButton.BorderBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															g_ecomButton.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															g_ecomButton.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFont(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));

															g_ecomButton.FontFamily(myFont);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
															{
															g_ecomButton.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
															{
															g_ecomButton.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
																{
																g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
																{
																g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																g_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
																{
																g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
																{
																g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																g_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_PacketLPss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });
															
															g_ecomButton.Margin(myThickness);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRow(g_ecomButton, f_Data);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumn(g_ecomButton, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(g_ecomButton, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(g_ecomButton, f_Data);
															}
														}

													if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(g_ecomButton);
														}
													else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(g_ecomButton);
														}
													}
												else if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Controls::StackPanel f_Stack;
													f_Stack.Name(StrUsingStr(f_PacketLP->m_Name));

													for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
														{
														if(f_vec_Package_XElement_Title[f_IDX].compare("Background") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.Background(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("BorderBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.BorderBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
															{
															f_Stack.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
															{
															f_Stack.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_PacketLPss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_Stack.Margin(myThickness);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRow(f_Stack, f_Data);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_Stack, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_Stack, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_Stack, f_Data);
															}
														}

													if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_Stack);
														}
													else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_Stack);
														}

													g_ecomStackPanel = f_Stack;
													}
												else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Controls::Grid f_Grid({});

													f_Grid.Name(StrUsingStr(f_PacketLP->m_Name));

													Windows::UI::Xaml::Controls::ColumnDefinition myCollumn({});
													Windows::UI::Xaml::Controls::RowDefinition myRow({});

													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);

													//set defaults
													for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
														{
														if(f_vec_Package_XElement_Title[f_IDX].compare("Background") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.Background(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("BorderBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.BorderBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
															{
															f_Grid.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
															{
															f_Grid.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_Packetss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_Grid.Margin(myThickness);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRow(f_Grid, f_Data);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_Grid, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_Grid, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_Grid, f_Data);
															}
														}

													if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_Grid);
														}
													else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_Grid);
														}

													g_ecomGrid = f_Grid;
													}
												else if(f_vec_Package_XElement_Title[0].compare("TextBlock") == 0)
													{
													winrt::Windows::UI::Xaml::Controls::TextBlock f_TextBlock({});

													//set knowns
													f_TextBlock.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont(L"Audiowide");

													f_TextBlock.FontFamily(myFont);

													for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
														{
														if(f_vec_Package_XElement_Title[f_IDX].compare("Text") == 0)
															{
															f_TextBlock.Text(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Foreground") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.Foreground(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.SelectionHighlightColor(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFont({ StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

															f_TextBlock.FontFamily(myFont);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
															{
															f_TextBlock.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
															{
															f_TextBlock.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_Packetss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_TextBlock.Margin(myThickness);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRow(f_TextBlock, f_Data);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_TextBlock, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_TextBlock, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_TextBlock, f_Data);
															}
														}

													if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_TextBlock);
														}
													else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_TextBlock);
														}
													}
												else if(f_vec_Package_XElement_Title[0].compare("TextBox") == 0)
													{
													winrt::Windows::UI::Xaml::Controls::TextBox f_TextBox({});

													//set knowns
													f_TextBox.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont(L"Audiowide");

													f_TextBox.FontFamily(myFont);

													for(int f_Jet = 0; f_Jet < f_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
														{
														if(f_vec_Package_XElement_Title[f_IDX].compare("Text") == 0)
															{
															f_TextBox.Text(StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Foreground") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.Foreground(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.SelectionHighlightColor(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFont({ StrUsingStr(f_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

															f_TextBox.FontFamily(myFont);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Height") == 0)
															{
															f_TextBox.Height(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Width") == 0)
															{
															f_TextBox.Width(atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("VerticalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("HorizontalAlignment") == 0)
															{
															if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_vecvec_Package_Arg_Data[f_IDX][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_Packetss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_TextBox.Margin(myThickness);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRow(f_TextBox, f_Data);
															}
														else if(f_vec_Package_XElement_Title[f_IDX].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_TextBox, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_TextBox, f_Data);
															}
														else if (f_vec_Package_XElement_Title[f_IDX].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_TextBox, f_Data);
															}
														}

													if(f_vec_Package_XElement_Title[0].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_TextBox);
														}
													else if(f_vec_Package_XElement_Title[0].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_TextBox);
														}
													}
												}
											}
										}break;

									case ctEClass:
										{
										}break;

									case ctShare:
										{
										}break;

									case ctElement:
										{
										}break;

									default:
										{
										//g_ExcomPexMain->acExecute(EXCOM_MAIN_COMPLETE_IDX, 0, f_PacketLP->m_ClassType);
										}break;
									}
								}
							}
						}break;

					case COM_PAK_TYPE_DELETE:
						{
						//not yet implemented
						}break;
					}

				if(f_Fail_PacketIncomplete == false)
					{
					f_Packet->m_Activate_Status = COM_PAK_ACTIVATED;
					}
				}
			}
	}
#endif

#if 0
	void SecondaryAppWindowPagePredator::OnHoverPredatorMain(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		if(g_PopOnce == false)
			{
			g_PopOnce = true;

			std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::TextBox>().Name());

			acClick(f_ButtonName);

			winrt::Windows::Foundation::Size f_size = appWindowPredator.GetPlacement().Size();

			f_size.Height += 60;

			appWindowPredator.RequestSize(f_size);
			}
	}
#endif

};

std::string winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::ac_AB(std::string f_StringIn, int f_CursorPosition)
{
	std::string f_StringResult = "";

	for(int f_XY = 0; f_XY < f_CursorPosition; f_XY++)
		{
		f_StringResult.push_back(f_StringIn.at(f_XY));
		}

	return f_StringResult;
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack11(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("1") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[0][0];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack12(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("2") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[0][1];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack13(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("3") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[0][2];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack21(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("4") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[1][0];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack22(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("5") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[1][1];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack23(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("6") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[1][2];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack31(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("7") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[2][0];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack32(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("8") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[2][1];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack33(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("9") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[2][2];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}


void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack41(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("10") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[3][0];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack42(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("11") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[3][1];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStack43(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	if(g_CopyStack[0][0].compare("12") == 0)
		{
		std::string f_String = to_string(predatortextBox().Text());

		std::string f_StringResult = ac_AB(f_String, predatortextBox().SelectionStart());
		
		//.
		f_StringResult += g_CopyStack[3][2];

		predatortextBox().Text(StrUsingStr(f_StringResult));
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnPrintCopyStackPage(void)
{
	for(int f_YY = 0; f_YY < 4; f_YY++)
		{
		for(int f_XX = 0; f_XX < 3; f_XX++)
			{
			int f_C = (f_YY * 3) + f_XX;

			g_CopyStack[f_YY][f_XX].clear();

			char* f_Char = new char[64];

			sprintf(f_Char, "%i", f_C);

			g_CopyStack[f_YY][f_XX] = f_Char;

			delete[] f_Char;
			}
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStackPrevPage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	g_CopyStackPageN--;

	if(g_CopyStackPageN < 0)
		{
		g_CopyStackPageN = 0;
		}

	OnPrintCopyStackPage();
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStackCommandPrev(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStackCommandNext(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStackNextPage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	g_CopyStackPageN++;

	if(g_CopyStackPageN >= (g_CopyStack.size() / 4))
		{
		OnCreateNewCopyStackPage();
		}

	OnPrintCopyStackPage();
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnCreateNewCopyStackPage(void)
{
	for(int f_YY = (g_CopyStackPageN * 4); f_YY < ((g_CopyStackPageN * 4) + 4); f_YY++)
		{
		std::vector<std::string> f_vec_String;

		for(int f_XX = 0; f_XX < 3; f_XX++)
			{
			int f_C = (f_YY * 3) + f_XX;

			char* f_Char = new char[64];

			sprintf(f_Char, "%i", f_C);

			f_vec_String.push_back(f_Char);

			delete[] f_Char;
			}

		g_CopyStack.push_back(f_vec_String);
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickCopyStackClear(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_buttonName);

	for(int f_YY = (g_CopyStackPageN * 4); f_YY < ((g_CopyStackPageN * 4) + 4); f_YY++)
		{
		for(int f_XX = 0; f_XX < 3; f_XX++)
			{
			int f_C = (f_YY * 3) + f_XX;

			g_CopyStack[f_YY][f_XX].clear();

			char* f_Char = new char[64];

			sprintf(f_Char, "%i", f_C);

			g_CopyStack[f_YY][f_XX] = f_Char;

			delete[] f_Char;
			}
		}
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickSaveComplete(IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::string f_TextString = to_string(predatortextBox().Text());

	g_vec_PredatorManager[0]->m_PredatorIns->m_Panel->m_Text = f_TextString;

	g_vec_PredatorManager[0]->acSave();

	g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
        {
		winrt::Windows::UI::Xaml::Controls::StackPanel f_saveCompleteStack = g_swapChainPanel.FindName(StrUsingStr("SavecompleteStackPanel")).as<winrt::Windows::UI::Xaml::Controls::StackPanel>();

		f_saveCompleteStack.Visibility(Windows::UI::Xaml::Visibility::Visible);
        });
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::string f_TextString = to_string(predatortextBox().Text());

	g_vec_PredatorManager[0]->m_PredatorIns->m_Panel->m_Text = f_TextString;

	g_vec_PredatorManager[0]->acSave();
}


void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnClickSaveAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::string f_TextString = to_string(predatortextBox().Text());

	g_vec_PredatorManager[0]->m_PredatorIns->m_Panel->m_Text = f_TextString;

	g_vec_PredatorManager[0]->acSaveAll();
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnGotFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = false;
}

void winrt::SDKTemplate::implementation::SecondaryAppWindowPagePredator::OnLostFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = true;
}