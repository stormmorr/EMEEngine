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

#pragma once

#include "MainPage.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        static hstring FEATURE_NAME();
        static Windows::Foundation::Collections::IVector<Scenario> scenarios() { return scenariosInner; }
        static SDKTemplate::MainPage Current() { return current; }

        std::string LapKey(FILE* f_Stream);

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Navigate(Windows::UI::Xaml::Interop::TypeName const& typeName, Windows::Foundation::IInspectable const& parameter);

        void Frame_OnCount(void);

        void Web_Connect(void);

        // These methods are public so they can be called by binding.
        void ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

        fire_and_forget Logon_Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        fire_and_forget QLogon_Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        fire_and_forget EQLogon_Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        static SDKTemplate::MainPage current;
        static winrt::Windows::Foundation::Collections::IVector<Scenario> scenariosInner;

        bool navigating = false;
        void NavigateTo(Windows::UI::Xaml::Interop::TypeName const& typeName, Windows::Foundation::IInspectable const& parameter);

        bool m_Scan;
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
        //...
    };
}
