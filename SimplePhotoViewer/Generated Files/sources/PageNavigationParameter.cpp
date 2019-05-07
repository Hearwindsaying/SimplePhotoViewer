#include "pch.h"
#include "PageNavigationParameter.h"

namespace winrt::SimplePhotoViewer::implementation
{
    PageNavigationParameter::PageNavigationParameter(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& imageSkus, uint32_t mainPageCurrentSelectedIndex)
    {
        throw hresult_not_implemented();
    }

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> PageNavigationParameter::ImageSkus()
    {
        throw hresult_not_implemented();
    }

    uint32_t PageNavigationParameter::MainPageCurrentSelectedIndex()
    {
        throw hresult_not_implemented();
    }
}
