﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.180821.2

#pragma once

#include "winrt/Windows.Storage.h"
#include "winrt/Windows.Storage.FileProperties.h"
#include "winrt/Windows.UI.Xaml.Data.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Media.Imaging.h"
#include "winrt/Windows.UI.Composition.h"
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/SimplePhotoViewer.h"

namespace winrt::SimplePhotoViewer::implementation {

template <typename D, typename... I>
struct WINRT_EBO ImageSku_base : implements<D, SimplePhotoViewer::IImageSku, Windows::UI::Xaml::Data::INotifyPropertyChanged, I...>
{
    using base_type = ImageSku_base;
    using class_type = SimplePhotoViewer::ImageSku;
    using implements_type = typename ImageSku_base::implements_type;
    using implements_type::implements_type;
    
#if _MSC_VER < 1914
    operator class_type() const noexcept
    {
        static_assert(std::is_same_v<typename impl::implements_default_interface<D>::type, default_interface<class_type>>);
        class_type result{ nullptr };
        attach_abi(result, detach_abi(static_cast<default_interface<class_type>>(*this)));
        return result;
    }
#else
    operator impl::producer_ref<class_type> const() const noexcept
    {
        return { to_abi<default_interface<class_type>>(this) };
    }
#endif

    hstring GetRuntimeClassName() const
    {
        return L"SimplePhotoViewer.ImageSku";
    }
};

}

namespace winrt::SimplePhotoViewer::factory_implementation {

template <typename D, typename T, typename... I>
struct WINRT_EBO ImageSkuT : implements<D, Windows::Foundation::IActivationFactory, SimplePhotoViewer::IImageSkuFactory, I...>
{
    using instance_type = SimplePhotoViewer::ImageSku;

    hstring GetRuntimeClassName() const
    {
        return L"SimplePhotoViewer.ImageSku";
    }

    Windows::Foundation::IInspectable ActivateInstance() const
    {
        throw hresult_not_implemented();
    }

    SimplePhotoViewer::ImageSku CreateInstance(Windows::Storage::FileProperties::ImageProperties const& imageProps, Windows::Storage::StorageFile const& imageFile, hstring const& name, hstring const& type, Windows::UI::Xaml::Media::Imaging::BitmapImage const& imageThumbnail, hstring const& nameWithType)
    {
        return make<T>(imageProps, imageFile, name, type, imageThumbnail, nameWithType);
    }
};

}

#if defined(WINRT_FORCE_INCLUDE_IMAGESKU_XAML_G_H) || __has_include("ImageSku.xaml.g.h")

#include "ImageSku.xaml.g.h"

#else

namespace winrt::SimplePhotoViewer::implementation
{
    template <typename D, typename... I>
    using ImageSkuT = ImageSku_base<D, I...>;
}

#endif
