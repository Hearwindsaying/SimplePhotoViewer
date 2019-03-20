#pragma once

#include "ImageSku.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct ImageSku : ImageSkuT<ImageSku>
    {
        ImageSku() = delete;
        ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type);

        Windows::Storage::StorageFile ImageFile();
        Windows::Storage::FileProperties::ImageProperties ImageProperties();
        hstring ImageName();
        hstring ImageFileType();
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct ImageSku : ImageSkuT<ImageSku, implementation::ImageSku>
    {
    };
}
