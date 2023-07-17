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
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Automation::Peers;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Interop;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::UI::Xaml::Navigation;

namespace winrt::SDKTemplate::implementation
{
    SDKTemplate::MainPage MainPage::current{ nullptr };

	std::string MainPage::LapKey(FILE* f_Stream)
	{
		std::string f_ref_CurrentPath = g_ref_global_start + "MainPage::LapKey";

		if(g_Wallet->m_Start == true)
			{ //////////////////
			 // Start Wallet //
			std::string f_StringBuf = g_Wallet->Prepare_Start();

			g_Wallet->StartCPS();

			return f_StringBuf;
			}
		else
			{
			int f_WalletVersion = 0;

			fseek(f_Stream, 0, SEEK_END);
			int len = ftell(f_Stream);
			unsigned char* f_buf = new unsigned char[len + 1];
			fseek(f_Stream, 0, SEEK_SET);
			fread(f_buf, len, 1, f_Stream);
			fclose(f_Stream);

			std::string f_Char = std::string((char*)f_buf);

			uint* f_Chk = new uint(0);

			if(f_Char.length() > 1)
				{
				g_WALLETBANK = acBufreadValueDouble(f_Char, f_Chk);
				ecoin::g_HESHSAVEID = acBufreadValueInteger(f_Char, f_Chk);
				acBufreadValueInteger(f_Char, f_Chk);

				f_WalletVersion = 1;

				g_Wallet->m_ChangeIdx = acBufreadValueInteger(f_Char, f_Chk);
				int f_KeyNom = acBufreadValueInteger(f_Char, f_Chk);

				if(f_KeyNom >= 5)
					{
					f_WalletVersion = 3;
					}

				if(f_KeyNom > 1)
					{
					f_WalletVersion = 3;

					int f_prefix = acBufreadValueInteger(f_Char, f_Chk);
					std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
					std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
					std::string f_owner = acBufreadValueString(f_Char, f_Chk);

					unsigned char *f_p = new unsigned char[8];
					Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

#ifdef ECOIN_REFLECTED_WALLET
					ag_StatusLive(f_ref_CurrentPath, "key");
					std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();
#else
					std::shared_ptr<CKey> key = std::make_shared<CKey>();
#endif

					for(int f_lm = 0; f_lm < 8; f_lm++)
						{
						key->keydata[f_lm] = f_p[f_lm];
						}

					key->m_prefix = f_prefix;
					key->m_owner = f_owner;
					key->m_pubkey = f_pubkey;
					g_Wallet->m_Bank_Adr = f_owner;

					g_Wallet->m_vec_Key.push_back(key);
					}
				else if(f_KeyNom == 1) //early version
					{
					f_WalletVersion = 2;

					std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
					std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
					std::string f_owner = acBufreadValueString(f_Char, f_Chk);

					unsigned char *f_p = new unsigned char[8];
					Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

#ifdef ECOIN_REFLECTED_WALLET
					ag_StatusLive(f_ref_CurrentPath, "key");
					std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();
#else
					std::shared_ptr<CKey> key = std::make_shared<CKey>();
#endif

					for(int f_lm = 0; f_lm < 8; f_lm++)
						{
						key->keydata[f_lm] = f_p[f_lm];
						}

					key->m_prefix = 1;
					key->m_owner = f_owner;
					key->m_pubkey = f_pubkey;
					g_Wallet->m_Bank_Adr = f_owner;

					g_Wallet->m_vec_Key.push_back(key);
					}
						
				for(int f_m = 1; f_m < f_KeyNom; f_m++)
					{
					int f_prefix = acBufreadValueInteger(f_Char, f_Chk);
					std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
					std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
					std::string f_owner = acBufreadValueString(f_Char, f_Chk);

					unsigned char *f_p = new unsigned char[8];
					Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

#ifdef ECOIN_REFLECTED_WALLET
					ag_StatusLive(f_ref_CurrentPath, "key");
					std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();
#else
					std::shared_ptr<CKey> key = std::make_shared<CKey>();
#endif

					for(int f_lm = 0; f_lm < 8; f_lm++)
						{
						key->keydata[f_lm] = f_p[f_lm];
						}

					key->m_prefix = f_prefix;
					key->m_owner = f_owner;
					key->m_pubkey = f_pubkey;

					g_Wallet->m_vec_Key.push_back(key);
					}
				}

				///////////////////////
			   // ecoin Wallet
			  // check
			 // upgrade
			// save
			switch(f_WalletVersion)
				{
				case 1:	//empty broken
					{
					g_Wallet->m_Bank_ecoin = 0.0f;
					g_Wallet->m_Bank_ecoin_constant = 0.0f;
					g_WALLETBANK = 0.0f;
					g_HESHSAVEID = 0;

#ifndef DISABLE_ECC
					std::shared_ptr<CKey> f_1key = ag_GenerateAddress(1);

					g_Wallet->m_vec_Key.push_back(f_1key);

					g_Wallet->m_Bank_Adr = f_1key->m_owner;
#endif
					}

				case 2: //version 1
					{
					g_Wallet->m_ChangeIdx = 0;

#ifndef DISABLE_ECC
					std::shared_ptr<CKey> f_key = ag_GenerateAddress(2);

					g_Wallet->m_vec_Key.push_back(f_key);

					f_key = ag_GenerateAddress(2);

					g_Wallet->m_vec_Key.push_back(f_key);

					f_key = ag_GenerateAddress(2);

					g_Wallet->m_vec_Key.push_back(f_key);

					f_key = ag_GenerateAddress(2);

					g_Wallet->m_vec_Key.push_back(f_key);
#endif

					g_Wallet->m_Bank_ecoin = g_WALLETBANK;
					g_Wallet->m_Bank_ecoin_constant = 0.0f;
					g_Wallet->m_OK = true;
					g_Wallet->m_Repeat = false;

					printf("Wallet fully loaded OK updating...\n");

					g_Wallet->Update();
					};

				case 3:
					{
					g_Wallet->m_Bank_ecoin = g_WALLETBANK;
					g_Wallet->m_Bank_ecoin_constant = 0.0f;
					g_Wallet->m_OK = true;
					g_Wallet->m_Repeat = false;

					printf("Wallet fully loaded OK updating...\n");

					g_WalletOpen = true;
					}break;
				}

			return std::string("X");
			}
	}

    MainPage::MainPage()
    {
        InitializeComponent();

        std::string f_ref_CurrentPath = g_ref_global_start + "MainPage::MainPage";

         /////////////////
        // ecoinWallet //
		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[0]", true);
		g_Schedular[0] = std::make_shared_reflect<Schedular>(0);
		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[1]", true);
		g_Schedular[1] = std::make_shared_reflect<Schedular>(1);
		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[2]", true);
		g_Schedular[2] = std::make_shared_reflect<Schedular>(2);

#ifdef ECOIN_REFLECTED_WALLET
        ag_StatusLive(f_ref_CurrentPath, "g_Wallet", true);
        g_Wallet = std::make_shared_reflect<Wallet>();
#else
		g_Wallet = std::make_shared<Wallet>();
#endif

		std::string f_String = "\\KeyData.eco";

		winrt::Windows::Storage::StorageFolder f_LocalFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

		winrt::hstring f_FolderPath = f_LocalFolder.Path();

		g_Wallet->m_FullPath = to_string(f_FolderPath) + f_String;

		//##### - Open our Wallet Data File
		g_Wallet->m_Stream = fopen(g_Wallet->m_FullPath.c_str(), "r");

		if(g_Wallet->m_Stream)
			{	// Win conditions wallet file found!
			g_Wallet->m_Start = false;

			g_Schedular[0]->m_WalletSave = false;
			}
		else
			{
			g_Wallet->m_Start = true;

			g_Schedular[0]->m_WalletSave = true;
			}

        // This is a static public property that allows downstream pages to get a handle to the MainPage instance
        // in order to call methods that are in this class.
        MainPage::current = *this;

#if 0
		//Login Async Keep Alive Generator
		std::thread f_Thread(&MainPage::Frame_OnCount, this);

		f_Thread.detach();
#endif
    }

	void MainPage::Frame_OnCount(void)
	{
		time_t f_Time;
		time(&f_Time);

		int f_ScanTimer = f_Time;

		m_Scan = true;
		while(m_Scan == true)
			{
			time(&f_Time);

			if(f_Time >= f_ScanTimer + (SCHEDULE_TIME_OUT_SECONDS + SCHEDULE_THREAD_GRACE))
				{
				//Send Keep Alive Message to all other Servers
				g_SafeL[0]->acKeepAliveCommand("UploadServerConnectionKeepAlive", false);
				g_SafeL[1]->acKeepAliveCommand("ReceiveServerConnectionKeepAlive", false);
				g_SafeL[2]->acKeepAliveCommand("QuantumServerConnectionKeepAlive", false);

				time(&f_Time);

				f_ScanTimer = f_Time;
				}
			}
	}

    void MainPage::OnNavigatedTo(NavigationEventArgs const&)
    {
		//...
    }

    void MainPage::Navigate(TypeName const& typeName, IInspectable const& parameter)
    {
        int index;
        for(index = static_cast<int>(scenarios().Size()) - 1; index >= 0; --index)
			{
            if(scenarios().GetAt(index).ClassName == typeName)
				{
                break;
				}
			}

        navigating = false;

        NavigateTo(typeName, parameter);
    }

    void MainPage::NavigateTo(TypeName const& typeName, IInspectable const& parameter)
    {
        if(Window::Current().Bounds().Width < 640)
            {
            Splitter().IsPaneOpen(false);
            }
    }

    void MainPage::ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const&)
    {
        ListBox scenarioListBox = sender.as<ListBox>();
        IInspectable selectedItem = scenarioListBox.SelectedItem();

        if(selectedItem && !navigating)
            {
            Scenario s = unbox_value<Scenario>(selectedItem);
            NavigateTo(s.ClassName, IInspectable{ nullptr });
            }
    }

    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&)
    {        
        Uri uri{ unbox_value<hstring>(sender.as<HyperlinkButton>().Tag()) };
        Windows::System::Launcher::LaunchUriAsync(uri);
    }

    void MainPage::Button_Click(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        Splitter().IsPaneOpen(!Splitter().IsPaneOpen());
    }

    fire_and_forget MainPage::Logon_Button_Click(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

		Web_Connect();

		m_Scan = false;

        winrt::Windows::UI::Xaml::Controls::Frame rootFrame = Window::Current().Content().as<winrt::Windows::UI::Xaml::Controls::Frame>();

        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());

        winrt::fire_and_forget f_FF;

        return f_FF;
    }

    fire_and_forget MainPage::QLogon_Button_Click(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

		Web_Connect();

		m_Scan = false;

		g_EngineMode = QEngineMode::QEngine_World;

        winrt::Windows::UI::Xaml::Controls::Frame rootFrame = Window::Current().Content().as<winrt::Windows::UI::Xaml::Controls::Frame>();

        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageOGL>());

        winrt::fire_and_forget f_FF;

        return f_FF;
    }

	fire_and_forget MainPage::EQLogon_Button_Click(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

		Web_Connect();

		m_Scan = false;

		g_EngineMode = QEngineMode::QEngine_Minimal;

        winrt::Windows::UI::Xaml::Controls::Frame rootFrame = Window::Current().Content().as<winrt::Windows::UI::Xaml::Controls::Frame>();

        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageOGL>());

        winrt::fire_and_forget f_FF;

        return f_FF;
    }

	void MainPage::Web_Connect(void)
	{
		g_Wallet->Open();

        std::string f_Buffer = LapKey(g_Wallet->m_Stream);

		if(g_Wallet->m_Start == true)
			{
			g_Schedular[0]->acShutdown_WalletSave();

			g_Schedular[0]->m_WalletSave = false;

			//##### - Open our Wallet Data File
			g_Wallet->m_Stream = fopen(g_Wallet->m_FullPath.c_str(), "w");

			fprintf(g_Wallet->m_Stream, "%s", f_Buffer.c_str());

			fclose(g_Wallet->m_Stream);
			}

		//###- Connect Servers -###//
		Connect_Main();
	}
}
