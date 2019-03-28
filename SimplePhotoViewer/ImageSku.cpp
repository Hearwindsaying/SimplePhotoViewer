#include "pch.h"
#include "ImageSku.h"

namespace winrt::SimplePhotoViewer::implementation
{
    ImageSku::ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type, Windows::UI::Xaml::Media::Imaging::BitmapImage const& imageThumbnail, hstring const& nameWithType)
    {
		this->m_imageProps = imageProps;
		this->m_imageFile = imageFile;
		this->m_imageName = name;
		this->m_imageFileType = type;

		this->m_imageThumbnail = imageThumbnail;
		this->m_imageNameWithType = nameWithType;
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

	hstring ImageSku::ImageNameWithType() const
	{
		return this->m_imageNameWithType;
	}

	Windows::UI::Xaml::Media::Imaging::BitmapImage ImageSku::ImageThumbnail()const
	{
		return this->m_imageThumbnail;
	}

	//void ImageSku::ImageThumbnail(Windows::UI::Xaml::Media::Imaging::BitmapImage imageThumbnail)
	//{
	//	this->m_imageThumbnail = imageThumbnail;
	//	//raise property change;
	//}

	Windows::UI::Xaml::Media::Imaging::BitmapImage ImageSku::ImageContent()const
	{
		return this->m_imageContent;
	}

	void ImageSku::ImageContent(Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
	{
		this->m_imageContent = value;
		this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ImageContent" });
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
