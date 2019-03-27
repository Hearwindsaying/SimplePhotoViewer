#pragma once

#include "DetailPage.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct DetailPage : DetailPageT<DetailPage>
    {
        DetailPage() = default;

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus();
        SimplePhotoViewer::ImageSku SelectedItem();
        void SelectedItem(SimplePhotoViewer::ImageSku const& value);
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DetailPage : DetailPageT<DetailPage, implementation::DetailPage>
    {
    };
}
