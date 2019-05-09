#pragma once

#include "ImageSku.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct ImageSku : ImageSkuT<ImageSku>
    {
        ImageSku() = delete;
        ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type, Windows::UI::Xaml::Media::Imaging::BitmapImage const& imageThumbnail, hstring const& nameWithType);
        ImageSku(hstring const& defaultTipString);

        Windows::Storage::StorageFile ImageFile();
        void ImageFile(Windows::Storage::StorageFile const& value);
        Windows::Storage::FileProperties::ImageProperties ImageProperties();
        hstring ImageName();
        void ImageName(hstring const& value);
        hstring ImageFileType();
        void ImageFileType(hstring const& value);
        hstring ImageNameWithType();
        void ImageNameWithType(hstring const& value);
        Windows::UI::Xaml::Media::Imaging::BitmapImage ImageThumbnail();
        Windows::UI::Xaml::Media::Imaging::BitmapImage ImageContent();
        void ImageContent(Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
        double RenderRotation();
        void RenderRotation(double value);
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
