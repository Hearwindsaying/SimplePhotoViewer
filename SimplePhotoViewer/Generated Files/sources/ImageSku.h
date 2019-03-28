#pragma once

#include "ImageSku.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct ImageSku : ImageSkuT<ImageSku>
    {
        ImageSku() = delete;
        ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type, Windows::UI::Xaml::Media::Imaging::BitmapImage const& imageThumbnail, hstring const& nameWithType);

        Windows::Storage::StorageFile ImageFile();
        Windows::Storage::FileProperties::ImageProperties ImageProperties();
        hstring ImageName();
        hstring ImageFileType();
        hstring ImageNameWithType();
        Windows::UI::Xaml::Media::Imaging::BitmapImage ImageThumbnail();
        Windows::UI::Xaml::Media::Imaging::BitmapImage ImageContent();
        void ImageContent(Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
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
