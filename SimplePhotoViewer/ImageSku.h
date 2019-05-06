#pragma once

#include "ImageSku.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
	///<summary>
	///ImageSku is used to represent an image file and related its properties.Several properties are designed to be observable.Whenever their values change, PropertyChangedEvent should be raised and the corresponding xaml controls or widgets should be updated duly.
	///</summary>
    struct ImageSku : ImageSkuT<ImageSku>
    {
		//Constructors 
		ImageSku() = default;
		ImageSku(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type, Windows::UI::Xaml::Media::Imaging::BitmapImage const& imageThumbnail, hstring const& nameWithType);
		ImageSku(hstring const& defaultTipString) :m_imageNameWithType(defaultTipString) {}

		//Properties
		Windows::Storage::StorageFile ImageFile() const;

		Windows::Storage::FileProperties::ImageProperties ImageProperties() const;
		Windows::UI::Xaml::Media::Imaging::BitmapImage ImageThumbnail()const;
		/*void ImageThumbnail(Windows::UI::Xaml::Media::Imaging::BitmapImage imageThumbnail);*/
		hstring ImageName() const;
		hstring ImageFileType() const;
		hstring ImageNameWithType() const;
		Windows::UI::Xaml::Media::Imaging::BitmapImage ImageContent() const;
		void ImageNameWithType(hstring const & imageNameWithType); //-
		void ImageFileType(hstring const & imageFileType); //-
		void ImageName(hstring const & imageName); //-
		void ImageFile(Windows::Storage::StorageFile const & value); //-
		void ImageContent(Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);

		//Observable property related event register and revoker, note that it's automatically registered by MVVM framework.
		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;


	private:
		Windows::Storage::StorageFile m_imageFile{ nullptr };
		Windows::Storage::FileProperties::ImageProperties m_imageProps{ nullptr };
		Windows::UI::Xaml::Media::Imaging::BitmapImage m_imageThumbnail{ nullptr };
		Windows::UI::Xaml::Media::Imaging::BitmapImage m_imageContent{ nullptr };
		hstring m_imageName;
		hstring m_imageFileType;
		hstring m_imageNameWithType;

		//Delegate for observable property
		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct ImageSku : ImageSkuT<ImageSku, implementation::ImageSku>
    {
    };
}
