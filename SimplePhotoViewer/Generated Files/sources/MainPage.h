#pragma once

#include "MainPage.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage() = default;

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
