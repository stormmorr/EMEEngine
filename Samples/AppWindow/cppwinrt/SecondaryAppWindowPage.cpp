/*

SecondaryAppWindowPage.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "SecondaryAppWindowPage.h"
#include "SecondaryAppWindowPage.g.cpp"

#include "Scenario1_SecondaryWindow.h"

#include "Wallet/Wallet.h"

using namespace ecoin;

namespace winrt::SDKTemplate::implementation
{
    SecondaryAppWindowPage::SecondaryAppWindowPage()
	{
		InitializeComponent();

#ifdef ECOIN_REFLECTION_EXP

		     /////////////////////////////////////////////////////////////////////////////////
		    //// Qcom Script Driven String PathName for Variable or Function Reflection. ////
		   //// Execute Programmatic Instant Reflection From Gathered NamePath          ////
		  //// [AQUIRE] mamQcom from last generated in QcomMngr->ag_MotherCom()        ////
		 ////     Path Syntax Readability in Debugger -> ":G:classmember:|:m_Member"  ////
		/////////////////////////////////////////////////////////////////////////////////

		std::string f_mamQcom_String = g_ref_global_start + "SecondaryAppWindowPage::SecondaryAppWindowPage:|:QcomManager::QcomManager:|:ag_MotherCom" + g_ref_Path_Div + "g_QcomManager->mam_Qcom" + g_ref_Div + "class Cube::Qcom" + g_ref_Div + "0" + g_ref_Div;

		if(g_Map_ecomRefBase.find(f_mamQcom_String) != g_Map_ecomRefBase.end())
			{
			 //////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////
			std::shared_ptr<ecom_base> f_mamQcom = g_Map_ecomRefBase[f_mamQcom_String];
			
			  ////////////////////////////////////////////
			 ////////////////////////////////////////////
			// MamQcom Member Boolean "m_HighLighted" //
			std::string f_MamCom_HighLighted_Bool_Str = "Qcom::Qcom" + g_ref_Div + "m_HighLighted";

			bool* f_HighLighted = f_mamQcom->m_Map_Bool[f_MamCom_HighLighted_Bool_Str];

			  /////////////////////////////////////////
			 /////////////////////////////////////////
			// MamQcom Member Boolean "m_Selected" //
			std::string f_Mam_Selected_Bool_Str = "Qcom::Qcom" + g_ref_Div + "m_Selected";

			bool* f_Selected = f_mamQcom->m_Map_Bool[f_Mam_Selected_Bool_Str];

			  ///////////////////////////////////////////////////////////////////////////////////////
			 /////////////-=={{{[[[[FUNCTION REFERENCE POINTERS]]]]}}}==-///////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////

			    //////////////////////////////////////////
			   //////////////////////////////////////////
			  // [AQUIRE1] function "acHighLight" //
			 //////////////////////////////////////
			//////////////////////////////////////
			std::string f_acHighLlight_pach = "Qcom::Qcom" + g_ref_fun_Div + "acHighLight" + g_ref_fun_Append;

			//[INPUT]
			bool f_BoolHighLight = true;

			std::shared_ptr<FunctionBeam> f_BeamHighLight = std::make_shared<FunctionBeam>();

			//[PACH]
			f_BeamHighLight->ac_PachON(f_BoolHighLight);

			//[EXEC]
			//f_mamQcom->ac_Invoke(f_acHighLlight_pach, f_BeamHighLight);

			    ///////////////////////////////////
			   ///////////////////////////////////
			  // CHECK [MamCom->m_HighLighted] //
			 ///////////////////////////////////
			///////////////////////////////////

			if(*(f_HighLighted) == true) //correct = true
				{
				__debugbreak();

				*(f_HighLighted) = false;

				__debugbreak();
				}
			else
				{
				__debugbreak();

				*(f_HighLighted) = true;

				__debugbreak();
				}

			   //------------------//--------//----------------------//////
			  ////////////////////////////////////////////////////////////
			 //-=(([AQUIRE2]))=- //function// -===[{acSelect}]===- //
			////////////////////////////////////////////////////////
			std::string f_acSelect_pach = "Qcom::Qcom" + g_ref_fun_Div + "acSelect" + g_ref_fun_Append;

			//[INPUT]
			bool f_BoolSelect = true;

			//[]
			//std::shared_ptr<FunctionBeam> f_BeamSelect = std::make_shared<FunctionBeam>();

			//[PACH]
			//f_BeamSelect->ac_PachON(f_BoolSelect);

			//[EXEC]
			//f_mamQcom->ac_Invoke(f_acSelect_pach, f_BeamSelect);

			    ////////////////////////////////
			   ////////////////////////////////
			  // CHECK [MamCom->f_Selected] //
			 ////////////////////////////////
			////////////////////////////////

			if(*(f_Selected) == true) //correct = true
				{
				__debugbreak();

				*(f_Selected) = false;

				__debugbreak();
				}
			else 
				{
				__debugbreak();

				*(f_Selected) = true;

				__debugbreak();
				}

			  /////////////////////////////////////////////////////
			 //[AQUIRE] function ---=={[acSelectNone]}==--- //////
			/////////////////////////////////////////////////
			std::string f_acSelectNone = "Qcom::Qcom" + g_ref_fun_Div + "acSelectNone";

			//['0'INPUT!]//
			//['0'PACH!]//
			  
			  ///////////////////////
			 ///////////////////////
			//[EXEC] Select None //
			//f_mamQcom->ac_Invoke(f_acSelectNone);
			 ////////////////////////////////////////////////
			////////////////////////////////////////////////

			    ////////////////////////////////
			   ////////////////////////////////
			  // CHECK [MamCom->f_Selected] //
			 ////////////////////////////////
			////////////////////////////////

			if(*(f_Selected) == true) //correct = true
				{
				__debugbreak();

				*(f_Selected) = false;

				__debugbreak();
				}
			else 
				{
				__debugbreak();

				*(f_Selected) = true;

				__debugbreak();
				}

			   ///////////////////////////////////////////////////////////////////////////////
			  /// Full Any Primary Variable Type. Reflected Reference Counted Object from ///
			 /// Map String -> ":G:Qcom::Qcom:|:m_HighLighted" /////////////////////////////
			/// Shown dialing single com highlighted on/off   /////////////////////////////
			std::string f_HL_Bool_MapString = "Qcom::Qcom" + g_ref_Div + "m_HighLighted";

			if(f_mamQcom->m_Map_Bool.find(f_HL_Bool_MapString) != f_mamQcom->m_Map_Bool.end())
				{
				__debugbreak();

				bool* f_Bool = f_mamQcom->m_Map_Bool[f_HL_Bool_MapString];

				__debugbreak();

				*(f_Bool) = true;

				__debugbreak();

				if(*(f_Bool) == true)
					{
					__debugbreak();

					*(f_Bool) = false;

					__debugbreak();
					}
				}
			}
#endif
	}

	void SecondaryAppWindowPage::acClick(std::string f_ButtonName)
	{
		ag_Click(f_ButtonName);
	}

	fire_and_forget SecondaryAppWindowPage::OnStartecoin(IInspectable const& sender, winrt::RoutedEventArgs const&)
		{
		if(ecoin::g_Pressed == false)
			{
			ecoin::g_Pressed = true;

			std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

			acClick(f_buttonName);

			auto lifetime = get_strong();

			g_Wallet->m_Start = true;

			::winrt::Windows::Storage::Pickers::FileSavePicker savePicker;

			savePicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

			// Dropdown of file types the user can save the file as
			savePicker.FileTypeChoices().Insert(L"ecoin Wallet", winrt::single_threaded_vector<winrt::hstring>({ L".eco" }));

			// Default file name if the user does not type one in or select a file to replace
			savePicker.SuggestedFileName(L"ecoinWallet");

			::winrt::Windows::Storage::StorageFile file = co_await savePicker.PickSaveFileAsync();

			if(file != nullptr)
				{
				if(file.IsAvailable() == true)
					{
					  //////////////
					 // Start ECN-CPS
					//  Wallet
					std::string f_StringBuf = g_Wallet->Prepare_Start();

					g_Wallet->StartCPS();

					::winrt::Windows::Storage::CachedFileManager::DeferUpdates(file);

					// write to file
					await winrt::Windows::Storage::FileIO::WriteTextAsync(file, StrUsingStr(f_StringBuf));

					// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
					// Completing updates may require Windows to ask for user input.
					::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);

					if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
						{
						g_Wallet->m_OK = true;
						g_Wallet->m_Repeat = false;
						g_WalletOpen = true;
						}
					else if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
						{
						g_Wallet->m_OK = true;
						g_Wallet->m_Repeat = false;
						g_WalletOpen = true;
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}

					this->Frame().Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());
					}
				}

			ecoin::g_Pressed = false;
			}
		}


	fire_and_forget SecondaryAppWindowPage::OnClickOpenecoin(IInspectable const& sender, winrt::RoutedEventArgs const&)
		{
		if(ecoin::g_Pressed == false)
			{
			ecoin::g_Pressed = true;

			std::string f_ref_CurrentPath = "SecondaryAppWindowPage::OnClickOpenecoin";

			std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

			acClick(f_buttonName);

			auto lifetime = get_strong();

			g_Wallet->m_Start = false;

			::winrt::Windows::Storage::Pickers::FileOpenPicker openPicker;

			openPicker.ViewMode(::winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().Append({ L".eco" });

			::winrt::Windows::Storage::StorageFile file = co_await openPicker.PickSingleFileAsync();

			if(file != nullptr)
				{
				if(file.IsAvailable() == true)
					{
					int f_WalletVersion = 0;

					winrt::hstring fileContent = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);
					std::string f_Char = to_string(fileContent);

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

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

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

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

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

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

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

						//////////////////////////////
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
							//m_Bank_egold = 5000;

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

					this->Frame().Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());
					}
				else
					{
					g_Wallet->m_Repeat = true;
					}
				}

			ecoin::g_Pressed = false;
			}
		}

};
