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
#include "Scenario1_SecondaryWindow.h"
#include "Scenario1_SecondaryWindow.g.cpp"

winrt::Windows::UI::WindowManagement::AppWindow appWindow{ nullptr };

namespace winrt::SDKTemplate::implementation
{
    Scenario1_SecondaryWindow::Scenario1_SecondaryWindow()
    {
        InitializeComponent();

        winrt::Windows::UI::Xaml::Controls::Frame rootFrame = Window::Current().Content().as<winrt::Windows::UI::Xaml::Controls::Frame>();

        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPage>());
    }

    fire_and_forget Scenario1_SecondaryWindow::OnNavigatedFrom(NavigationEventArgs const&)
    {
        if(appWindow != nullptr)
            {
            co_await appWindow.CloseAsync();
            }
    }

    fire_and_forget Scenario1_SecondaryWindow::Button_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

        winrt::Windows::UI::Xaml::Controls::Frame rootFrame = Window::Current().Content().as<winrt::Windows::UI::Xaml::Controls::Frame>();

        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPage>());

        winrt::fire_and_forget f_FF;

        return f_FF;
    }

    void Scenario1_SecondaryWindow::OnWindowClosed(AppWindow const&, IInspectable const&)
    {
        // Make sure we release the reference to this window, and release XAML resources.
        appWindow = nullptr;
        appWindowFrame.Content(nullptr);

        for(int f_XY = 0; f_XY < 3; f_XY++)
		    {
		    g_Schedular[f_XY]->acShutdown();
		    }
    }

}
