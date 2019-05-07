#pragma once

#include "PageNavigationParameter.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct PageNavigationParameter : PageNavigationParameterT<PageNavigationParameter>
    {
        PageNavigationParameter() = delete;
        PageNavigationParameter(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& imageSkus, uint32_t mainPageCurrentSelectedIndex);

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus();
        uint32_t MainPageCurrentSelectedIndex();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct PageNavigationParameter : PageNavigationParameterT<PageNavigationParameter, implementation::PageNavigationParameter>
    {
    };
}
