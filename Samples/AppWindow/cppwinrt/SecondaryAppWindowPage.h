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

#include "SecondaryAppWindowPage.g.h"

#include "Wallet/Wallet.h"

namespace winrt::SDKTemplate::implementation
{
    struct SecondaryAppWindowPage : SecondaryAppWindowPageT<SecondaryAppWindowPage>
    {
        SecondaryAppWindowPage();

        void acClick(std::string f_ButtonName);

        fire_and_forget OnStartecoin(IInspectable const&, winrt::RoutedEventArgs const&);
        fire_and_forget OnClickOpenecoin(IInspectable const&, winrt::RoutedEventArgs const&);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct SecondaryAppWindowPage : SecondaryAppWindowPageT<SecondaryAppWindowPage, implementation::SecondaryAppWindowPage>
    {
    };
}
