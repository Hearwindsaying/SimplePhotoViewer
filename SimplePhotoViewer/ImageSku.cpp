#include "pch.h"
#include "ImageSku.h"

namespace winrt::SimplePhotoViewer::implementation
{
    ImageSku::ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type)
    {
        throw hresult_not_implemented();
    }

    Windows::Storage::StorageFile ImageSku::ImageFile()
    {
        throw hresult_not_implemented();
    }

    Windows::Storage::FileProperties::ImageProperties ImageSku::ImageProperties()
    {
        throw hresult_not_implemented();
    }

    hstring ImageSku::ImageName()
    {
        throw hresult_not_implemented();
    }

    hstring ImageSku::ImageFileType()
    {
        throw hresult_not_implemented();
    }

    winrt::event_token ImageSku::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        throw hresult_not_implemented();
    }

    void ImageSku::PropertyChanged(winrt::event_token const& token) noexcept
    {
        throw hresult_not_implemented();
    }
}
