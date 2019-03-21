﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.180821.2

#pragma once

#include "winrt/base.h"


static_assert(winrt::check_version(CPPWINRT_VERSION, "1.0.180821.2"), "Mismatched component and base headers.");
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/impl/Windows.UI.2.h"
#include "winrt/impl/Windows.UI.Xaml.2.h"
#include "winrt/impl/Windows.UI.Composition.2.h"
#include "winrt/impl/Windows.UI.Xaml.Media.2.h"
#include "impl/Microsoft.UI.Xaml.Media.2.h"

namespace winrt::impl {

template <typename D> Microsoft::UI::Xaml::Media::AcrylicBackgroundSource consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::BackgroundSource() const
{
    Microsoft::UI::Xaml::Media::AcrylicBackgroundSource value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->get_BackgroundSource(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::BackgroundSource(Microsoft::UI::Xaml::Media::AcrylicBackgroundSource const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->put_BackgroundSource(get_abi(value)));
}

template <typename D> Windows::UI::Color consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintColor() const
{
    Windows::UI::Color value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->get_TintColor(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintColor(Windows::UI::Color const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->put_TintColor(get_abi(value)));
}

template <typename D> double consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintOpacity() const
{
    double value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->get_TintOpacity(&value));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintOpacity(double value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->put_TintOpacity(value));
}

template <typename D> Windows::Foundation::TimeSpan consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintTransitionDuration() const
{
    Windows::Foundation::TimeSpan value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->get_TintTransitionDuration(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::TintTransitionDuration(Windows::Foundation::TimeSpan const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->put_TintTransitionDuration(get_abi(value)));
}

template <typename D> bool consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::AlwaysUseFallback() const
{
    bool value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->get_AlwaysUseFallback(&value));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IAcrylicBrush<D>::AlwaysUseFallback(bool value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrush)->put_AlwaysUseFallback(value));
}

template <typename D> Microsoft::UI::Xaml::Media::AcrylicBrush consume_Microsoft_UI_Xaml_Media_IAcrylicBrushFactory<D>::CreateInstance(Windows::Foundation::IInspectable const& baseInterface, Windows::Foundation::IInspectable& innerInterface) const
{
    Microsoft::UI::Xaml::Media::AcrylicBrush value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushFactory)->CreateInstance(get_abi(baseInterface), put_abi(innerInterface), put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IAcrylicBrushStatics<D>::BackgroundSourceProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushStatics)->get_BackgroundSourceProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IAcrylicBrushStatics<D>::TintColorProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushStatics)->get_TintColorProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IAcrylicBrushStatics<D>::TintOpacityProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushStatics)->get_TintOpacityProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IAcrylicBrushStatics<D>::TintTransitionDurationProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushStatics)->get_TintTransitionDurationProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IAcrylicBrushStatics<D>::AlwaysUseFallbackProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IAcrylicBrushStatics)->get_AlwaysUseFallbackProperty(put_abi(value)));
    return value;
}

template <typename D> Microsoft::UI::Xaml::Media::RevealBackgroundBrush consume_Microsoft_UI_Xaml_Media_IRevealBackgroundBrushFactory<D>::CreateInstance(Windows::Foundation::IInspectable const& baseInterface, Windows::Foundation::IInspectable& innerInterface) const
{
    Microsoft::UI::Xaml::Media::RevealBackgroundBrush value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory)->CreateInstance(get_abi(baseInterface), put_abi(innerInterface), put_abi(value)));
    return value;
}

template <typename D> Microsoft::UI::Xaml::Media::RevealBorderBrush consume_Microsoft_UI_Xaml_Media_IRevealBorderBrushFactory<D>::CreateInstance(Windows::Foundation::IInspectable const& baseInterface, Windows::Foundation::IInspectable& innerInterface) const
{
    Microsoft::UI::Xaml::Media::RevealBorderBrush value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory)->CreateInstance(get_abi(baseInterface), put_abi(innerInterface), put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Color consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::Color() const
{
    Windows::UI::Color value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->get_Color(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::Color(Windows::UI::Color const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->put_Color(get_abi(value)));
}

template <typename D> Windows::UI::Xaml::ApplicationTheme consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::TargetTheme() const
{
    Windows::UI::Xaml::ApplicationTheme value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->get_TargetTheme(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::TargetTheme(Windows::UI::Xaml::ApplicationTheme const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->put_TargetTheme(get_abi(value)));
}

template <typename D> bool consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::AlwaysUseFallback() const
{
    bool value{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->get_AlwaysUseFallback(&value));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IRevealBrush<D>::AlwaysUseFallback(bool value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrush)->put_AlwaysUseFallback(value));
}

template <typename D> Microsoft::UI::Xaml::Media::RevealBrush consume_Microsoft_UI_Xaml_Media_IRevealBrushProtectedFactory<D>::CreateInstance(Windows::Foundation::IInspectable const& baseInterface, Windows::Foundation::IInspectable& innerInterface) const
{
    Microsoft::UI::Xaml::Media::RevealBrush value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory)->CreateInstance(get_abi(baseInterface), put_abi(innerInterface), put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::ColorProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->get_ColorProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::TargetThemeProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->get_TargetThemeProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::AlwaysUseFallbackProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->get_AlwaysUseFallbackProperty(put_abi(value)));
    return value;
}

template <typename D> Windows::UI::Xaml::DependencyProperty consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::StateProperty() const
{
    Windows::UI::Xaml::DependencyProperty value{ nullptr };
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->get_StateProperty(put_abi(value)));
    return value;
}

template <typename D> void consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::SetState(Windows::UI::Xaml::UIElement const& element, Microsoft::UI::Xaml::Media::RevealBrushState const& value) const
{
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->SetState(get_abi(element), get_abi(value)));
}

template <typename D> Microsoft::UI::Xaml::Media::RevealBrushState consume_Microsoft_UI_Xaml_Media_IRevealBrushStatics<D>::GetState(Windows::UI::Xaml::UIElement const& element) const
{
    Microsoft::UI::Xaml::Media::RevealBrushState result{};
    check_hresult(WINRT_SHIM(Microsoft::UI::Xaml::Media::IRevealBrushStatics)->GetState(get_abi(element), put_abi(result)));
    return result;
}

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IAcrylicBrush> : produce_base<D, Microsoft::UI::Xaml::Media::IAcrylicBrush>
{
    int32_t WINRT_CALL get_BackgroundSource(Microsoft::UI::Xaml::Media::AcrylicBackgroundSource* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(BackgroundSource, WINRT_WRAP(Microsoft::UI::Xaml::Media::AcrylicBackgroundSource));
            *value = detach_from<Microsoft::UI::Xaml::Media::AcrylicBackgroundSource>(this->shim().BackgroundSource());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_BackgroundSource(Microsoft::UI::Xaml::Media::AcrylicBackgroundSource value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(BackgroundSource, WINRT_WRAP(void), Microsoft::UI::Xaml::Media::AcrylicBackgroundSource const&);
            this->shim().BackgroundSource(*reinterpret_cast<Microsoft::UI::Xaml::Media::AcrylicBackgroundSource const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintColor(struct struct_Windows_UI_Color* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintColor, WINRT_WRAP(Windows::UI::Color));
            *value = detach_from<Windows::UI::Color>(this->shim().TintColor());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_TintColor(struct struct_Windows_UI_Color value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintColor, WINRT_WRAP(void), Windows::UI::Color const&);
            this->shim().TintColor(*reinterpret_cast<Windows::UI::Color const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintOpacity(double* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintOpacity, WINRT_WRAP(double));
            *value = detach_from<double>(this->shim().TintOpacity());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_TintOpacity(double value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintOpacity, WINRT_WRAP(void), double);
            this->shim().TintOpacity(value);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintTransitionDuration(Windows::Foundation::TimeSpan* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintTransitionDuration, WINRT_WRAP(Windows::Foundation::TimeSpan));
            *value = detach_from<Windows::Foundation::TimeSpan>(this->shim().TintTransitionDuration());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_TintTransitionDuration(Windows::Foundation::TimeSpan value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintTransitionDuration, WINRT_WRAP(void), Windows::Foundation::TimeSpan const&);
            this->shim().TintTransitionDuration(*reinterpret_cast<Windows::Foundation::TimeSpan const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_AlwaysUseFallback(bool* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallback, WINRT_WRAP(bool));
            *value = detach_from<bool>(this->shim().AlwaysUseFallback());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_AlwaysUseFallback(bool value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallback, WINRT_WRAP(void), bool);
            this->shim().AlwaysUseFallback(value);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IAcrylicBrushFactory> : produce_base<D, Microsoft::UI::Xaml::Media::IAcrylicBrushFactory>
{
    int32_t WINRT_CALL CreateInstance(void* baseInterface, void** innerInterface, void** value) noexcept final
    {
        try
        {
            if (innerInterface) *innerInterface = nullptr;
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            Windows::Foundation::IInspectable __local_innerInterface;
            WINRT_ASSERT_DECLARATION(CreateInstance, WINRT_WRAP(Microsoft::UI::Xaml::Media::AcrylicBrush), Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable&);
            *value = detach_from<Microsoft::UI::Xaml::Media::AcrylicBrush>(this->shim().CreateInstance(*reinterpret_cast<Windows::Foundation::IInspectable const*>(&baseInterface), __local_innerInterface));
            if (innerInterface) *innerInterface = detach_abi(__local_innerInterface);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics> : produce_base<D, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>
{
    int32_t WINRT_CALL get_BackgroundSourceProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(BackgroundSourceProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().BackgroundSourceProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintColorProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintColorProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().TintColorProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintOpacityProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintOpacityProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().TintOpacityProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TintTransitionDurationProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TintTransitionDurationProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().TintTransitionDurationProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_AlwaysUseFallbackProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallbackProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().AlwaysUseFallbackProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBackgroundBrush> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBackgroundBrush>
{};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory>
{
    int32_t WINRT_CALL CreateInstance(void* baseInterface, void** innerInterface, void** value) noexcept final
    {
        try
        {
            if (innerInterface) *innerInterface = nullptr;
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            Windows::Foundation::IInspectable __local_innerInterface;
            WINRT_ASSERT_DECLARATION(CreateInstance, WINRT_WRAP(Microsoft::UI::Xaml::Media::RevealBackgroundBrush), Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable&);
            *value = detach_from<Microsoft::UI::Xaml::Media::RevealBackgroundBrush>(this->shim().CreateInstance(*reinterpret_cast<Windows::Foundation::IInspectable const*>(&baseInterface), __local_innerInterface));
            if (innerInterface) *innerInterface = detach_abi(__local_innerInterface);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBorderBrush> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBorderBrush>
{};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory>
{
    int32_t WINRT_CALL CreateInstance(void* baseInterface, void** innerInterface, void** value) noexcept final
    {
        try
        {
            if (innerInterface) *innerInterface = nullptr;
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            Windows::Foundation::IInspectable __local_innerInterface;
            WINRT_ASSERT_DECLARATION(CreateInstance, WINRT_WRAP(Microsoft::UI::Xaml::Media::RevealBorderBrush), Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable&);
            *value = detach_from<Microsoft::UI::Xaml::Media::RevealBorderBrush>(this->shim().CreateInstance(*reinterpret_cast<Windows::Foundation::IInspectable const*>(&baseInterface), __local_innerInterface));
            if (innerInterface) *innerInterface = detach_abi(__local_innerInterface);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBrush> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBrush>
{
    int32_t WINRT_CALL get_Color(struct struct_Windows_UI_Color* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(Color, WINRT_WRAP(Windows::UI::Color));
            *value = detach_from<Windows::UI::Color>(this->shim().Color());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_Color(struct struct_Windows_UI_Color value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(Color, WINRT_WRAP(void), Windows::UI::Color const&);
            this->shim().Color(*reinterpret_cast<Windows::UI::Color const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TargetTheme(Windows::UI::Xaml::ApplicationTheme* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TargetTheme, WINRT_WRAP(Windows::UI::Xaml::ApplicationTheme));
            *value = detach_from<Windows::UI::Xaml::ApplicationTheme>(this->shim().TargetTheme());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_TargetTheme(Windows::UI::Xaml::ApplicationTheme value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TargetTheme, WINRT_WRAP(void), Windows::UI::Xaml::ApplicationTheme const&);
            this->shim().TargetTheme(*reinterpret_cast<Windows::UI::Xaml::ApplicationTheme const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_AlwaysUseFallback(bool* value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallback, WINRT_WRAP(bool));
            *value = detach_from<bool>(this->shim().AlwaysUseFallback());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL put_AlwaysUseFallback(bool value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallback, WINRT_WRAP(void), bool);
            this->shim().AlwaysUseFallback(value);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory>
{
    int32_t WINRT_CALL CreateInstance(void* baseInterface, void** innerInterface, void** value) noexcept final
    {
        try
        {
            if (innerInterface) *innerInterface = nullptr;
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            Windows::Foundation::IInspectable __local_innerInterface;
            WINRT_ASSERT_DECLARATION(CreateInstance, WINRT_WRAP(Microsoft::UI::Xaml::Media::RevealBrush), Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable&);
            *value = detach_from<Microsoft::UI::Xaml::Media::RevealBrush>(this->shim().CreateInstance(*reinterpret_cast<Windows::Foundation::IInspectable const*>(&baseInterface), __local_innerInterface));
            if (innerInterface) *innerInterface = detach_abi(__local_innerInterface);
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

template <typename D>
struct produce<D, Microsoft::UI::Xaml::Media::IRevealBrushStatics> : produce_base<D, Microsoft::UI::Xaml::Media::IRevealBrushStatics>
{
    int32_t WINRT_CALL get_ColorProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(ColorProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().ColorProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_TargetThemeProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(TargetThemeProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().TargetThemeProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_AlwaysUseFallbackProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(AlwaysUseFallbackProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().AlwaysUseFallbackProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL get_StateProperty(void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(StateProperty, WINRT_WRAP(Windows::UI::Xaml::DependencyProperty));
            *value = detach_from<Windows::UI::Xaml::DependencyProperty>(this->shim().StateProperty());
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL SetState(void* element, Microsoft::UI::Xaml::Media::RevealBrushState value) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(SetState, WINRT_WRAP(void), Windows::UI::Xaml::UIElement const&, Microsoft::UI::Xaml::Media::RevealBrushState const&);
            this->shim().SetState(*reinterpret_cast<Windows::UI::Xaml::UIElement const*>(&element), *reinterpret_cast<Microsoft::UI::Xaml::Media::RevealBrushState const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }

    int32_t WINRT_CALL GetState(void* element, Microsoft::UI::Xaml::Media::RevealBrushState* result) noexcept final
    {
        try
        {
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(GetState, WINRT_WRAP(Microsoft::UI::Xaml::Media::RevealBrushState), Windows::UI::Xaml::UIElement const&);
            *result = detach_from<Microsoft::UI::Xaml::Media::RevealBrushState>(this->shim().GetState(*reinterpret_cast<Windows::UI::Xaml::UIElement const*>(&element)));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

}

WINRT_EXPORT namespace winrt::Microsoft::UI::Xaml::Media {

inline AcrylicBrush::AcrylicBrush()
{
    Windows::Foundation::IInspectable baseInterface, innerInterface;
    *this = impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushFactory>([&](auto&& f) { return f.CreateInstance(baseInterface, innerInterface); });
}

inline Windows::UI::Xaml::DependencyProperty AcrylicBrush::BackgroundSourceProperty()
{
    return impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>([&](auto&& f) { return f.BackgroundSourceProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty AcrylicBrush::TintColorProperty()
{
    return impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>([&](auto&& f) { return f.TintColorProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty AcrylicBrush::TintOpacityProperty()
{
    return impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>([&](auto&& f) { return f.TintOpacityProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty AcrylicBrush::TintTransitionDurationProperty()
{
    return impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>([&](auto&& f) { return f.TintTransitionDurationProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty AcrylicBrush::AlwaysUseFallbackProperty()
{
    return impl::call_factory<AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushStatics>([&](auto&& f) { return f.AlwaysUseFallbackProperty(); });
}

inline RevealBackgroundBrush::RevealBackgroundBrush()
{
    Windows::Foundation::IInspectable baseInterface, innerInterface;
    *this = impl::call_factory<RevealBackgroundBrush, Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory>([&](auto&& f) { return f.CreateInstance(baseInterface, innerInterface); });
}

inline RevealBorderBrush::RevealBorderBrush()
{
    Windows::Foundation::IInspectable baseInterface, innerInterface;
    *this = impl::call_factory<RevealBorderBrush, Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory>([&](auto&& f) { return f.CreateInstance(baseInterface, innerInterface); });
}

inline Windows::UI::Xaml::DependencyProperty RevealBrush::ColorProperty()
{
    return impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.ColorProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty RevealBrush::TargetThemeProperty()
{
    return impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.TargetThemeProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty RevealBrush::AlwaysUseFallbackProperty()
{
    return impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.AlwaysUseFallbackProperty(); });
}

inline Windows::UI::Xaml::DependencyProperty RevealBrush::StateProperty()
{
    return impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.StateProperty(); });
}

inline void RevealBrush::SetState(Windows::UI::Xaml::UIElement const& element, Microsoft::UI::Xaml::Media::RevealBrushState const& value)
{
    impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.SetState(element, value); });
}

inline Microsoft::UI::Xaml::Media::RevealBrushState RevealBrush::GetState(Windows::UI::Xaml::UIElement const& element)
{
    return impl::call_factory<RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushStatics>([&](auto&& f) { return f.GetState(element); });
}

template <typename D, typename... Interfaces>
struct AcrylicBrushT :
    implements<D, Windows::UI::Xaml::Media::IBrushOverrides2, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverrides, composing, Interfaces...>,
    impl::require<D, Microsoft::UI::Xaml::Media::IAcrylicBrush, Windows::UI::Composition::IAnimationObject, Windows::UI::Xaml::IDependencyObject, Windows::UI::Xaml::IDependencyObject2, Windows::UI::Xaml::Media::IBrush, Windows::UI::Xaml::Media::IXamlCompositionBrushBase, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseProtected>,
    impl::base<D, Microsoft::UI::Xaml::Media::AcrylicBrush, Windows::UI::Xaml::Media::XamlCompositionBrushBase, Windows::UI::Xaml::Media::Brush, Windows::UI::Xaml::DependencyObject>,
    Windows::UI::Xaml::Media::IBrushOverrides2T<D>, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverridesT<D>
{
    using composable = AcrylicBrush;

protected:
    AcrylicBrushT()
    {
        impl::call_factory<Microsoft::UI::Xaml::Media::AcrylicBrush, Microsoft::UI::Xaml::Media::IAcrylicBrushFactory>([&](auto&& f) { f.CreateInstance(*this, this->m_inner); });
    }
};

template <typename D, typename... Interfaces>
struct RevealBackgroundBrushT :
    implements<D, Windows::UI::Xaml::Media::IBrushOverrides2, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverrides, composing, Interfaces...>,
    impl::require<D, Microsoft::UI::Xaml::Media::IRevealBackgroundBrush, Microsoft::UI::Xaml::Media::IRevealBrush, Windows::UI::Composition::IAnimationObject, Windows::UI::Xaml::IDependencyObject, Windows::UI::Xaml::IDependencyObject2, Windows::UI::Xaml::Media::IBrush, Windows::UI::Xaml::Media::IXamlCompositionBrushBase, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseProtected>,
    impl::base<D, Microsoft::UI::Xaml::Media::RevealBackgroundBrush, Microsoft::UI::Xaml::Media::RevealBrush, Windows::UI::Xaml::Media::XamlCompositionBrushBase, Windows::UI::Xaml::Media::Brush, Windows::UI::Xaml::DependencyObject>,
    Windows::UI::Xaml::Media::IBrushOverrides2T<D>, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverridesT<D>
{
    using composable = RevealBackgroundBrush;

protected:
    RevealBackgroundBrushT()
    {
        impl::call_factory<Microsoft::UI::Xaml::Media::RevealBackgroundBrush, Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory>([&](auto&& f) { f.CreateInstance(*this, this->m_inner); });
    }
};

template <typename D, typename... Interfaces>
struct RevealBorderBrushT :
    implements<D, Windows::UI::Xaml::Media::IBrushOverrides2, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverrides, composing, Interfaces...>,
    impl::require<D, Microsoft::UI::Xaml::Media::IRevealBorderBrush, Microsoft::UI::Xaml::Media::IRevealBrush, Windows::UI::Composition::IAnimationObject, Windows::UI::Xaml::IDependencyObject, Windows::UI::Xaml::IDependencyObject2, Windows::UI::Xaml::Media::IBrush, Windows::UI::Xaml::Media::IXamlCompositionBrushBase, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseProtected>,
    impl::base<D, Microsoft::UI::Xaml::Media::RevealBorderBrush, Microsoft::UI::Xaml::Media::RevealBrush, Windows::UI::Xaml::Media::XamlCompositionBrushBase, Windows::UI::Xaml::Media::Brush, Windows::UI::Xaml::DependencyObject>,
    Windows::UI::Xaml::Media::IBrushOverrides2T<D>, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverridesT<D>
{
    using composable = RevealBorderBrush;

protected:
    RevealBorderBrushT()
    {
        impl::call_factory<Microsoft::UI::Xaml::Media::RevealBorderBrush, Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory>([&](auto&& f) { f.CreateInstance(*this, this->m_inner); });
    }
};

template <typename D, typename... Interfaces>
struct RevealBrushT :
    implements<D, Windows::UI::Xaml::Media::IBrushOverrides2, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverrides, composing, Interfaces...>,
    impl::require<D, Microsoft::UI::Xaml::Media::IRevealBrush, Windows::UI::Composition::IAnimationObject, Windows::UI::Xaml::IDependencyObject, Windows::UI::Xaml::IDependencyObject2, Windows::UI::Xaml::Media::IBrush, Windows::UI::Xaml::Media::IXamlCompositionBrushBase, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseProtected>,
    impl::base<D, Microsoft::UI::Xaml::Media::RevealBrush, Windows::UI::Xaml::Media::XamlCompositionBrushBase, Windows::UI::Xaml::Media::Brush, Windows::UI::Xaml::DependencyObject>,
    Windows::UI::Xaml::Media::IBrushOverrides2T<D>, Windows::UI::Xaml::Media::IXamlCompositionBrushBaseOverridesT<D>
{
    using composable = RevealBrush;

protected:
    RevealBrushT()
    {
        impl::call_factory<Microsoft::UI::Xaml::Media::RevealBrush, Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory>([&](auto&& f) { f.CreateInstance(*this, this->m_inner); });
    }
};

}

WINRT_EXPORT namespace std {

template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrushFactory> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrushFactory> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrushStatics> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IAcrylicBrushStatics> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBackgroundBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBackgroundBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBackgroundBrushFactory> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBorderBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBorderBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBorderBrushFactory> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBrushProtectedFactory> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::IRevealBrushStatics> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::IRevealBrushStatics> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::AcrylicBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::AcrylicBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::RevealBackgroundBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::RevealBackgroundBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::RevealBorderBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::RevealBorderBrush> {};
template<> struct hash<winrt::Microsoft::UI::Xaml::Media::RevealBrush> : winrt::impl::hash_base<winrt::Microsoft::UI::Xaml::Media::RevealBrush> {};

}
