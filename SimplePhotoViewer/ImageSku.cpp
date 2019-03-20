#include "pch.h"
#include "ImageSku.h"

namespace winrt::SimplePhotoViewer::implementation
{
    ImageSku::ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type)
    {
		this->m_imageProps = imageProps;
		this->m_imageFile = imageFile;
		this->m_imageName = name;
		this->m_imageFileType = type;
    }

    Windows::Storage::StorageFile ImageSku::ImageFile() const
    {
		return this->m_imageFile;
    }

    Windows::Storage::FileProperties::ImageProperties ImageSku::ImageProperties() const
    {
		return this->m_imageProps;
    }

    hstring ImageSku::ImageName() const
    {
		return this->m_imageName;
    }

    hstring ImageSku::ImageFileType() const
    {
		return this->m_imageFileType;
    }

    winrt::event_token ImageSku::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
		return this->m_propertyChanged.add(handler);
    }

    void ImageSku::PropertyChanged(winrt::event_token const& token) noexcept
    {
		this->m_propertyChanged.remove(token);
    }
}
