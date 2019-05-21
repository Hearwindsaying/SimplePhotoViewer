﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.180821.2

#pragma once
#include "Microsoft.Graphics.Canvas.0.h"
#include "winrt/impl/Windows.UI.0.h"
#include "winrt/impl/Windows.Foundation.0.h"
#include "Microsoft.Graphics.Canvas.Brushes.0.h"

WINRT_EXPORT namespace winrt::Microsoft::Graphics::Canvas::Brushes {

struct WINRT_EBO ICanvasBrush :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasBrush>,
    impl::require<ICanvasBrush, Windows::Foundation::IClosable>
{
    ICanvasBrush(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasImageBrush :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasImageBrush>,
    impl::require<ICanvasImageBrush, Microsoft::Graphics::Canvas::Brushes::ICanvasBrush, Windows::Foundation::IClosable>
{
    ICanvasImageBrush(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasImageBrushFactory :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasImageBrushFactory>
{
    ICanvasImageBrushFactory(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasLinearGradientBrush :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasLinearGradientBrush>,
    impl::require<ICanvasLinearGradientBrush, Microsoft::Graphics::Canvas::Brushes::ICanvasBrush, Windows::Foundation::IClosable>
{
    ICanvasLinearGradientBrush(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasLinearGradientBrushFactory :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasLinearGradientBrushFactory>
{
    ICanvasLinearGradientBrushFactory(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasLinearGradientBrushStatics :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasLinearGradientBrushStatics>
{
    ICanvasLinearGradientBrushStatics(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasRadialGradientBrush :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasRadialGradientBrush>,
    impl::require<ICanvasRadialGradientBrush, Microsoft::Graphics::Canvas::Brushes::ICanvasBrush, Windows::Foundation::IClosable>
{
    ICanvasRadialGradientBrush(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasRadialGradientBrushFactory :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasRadialGradientBrushFactory>
{
    ICanvasRadialGradientBrushFactory(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasRadialGradientBrushStatics :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasRadialGradientBrushStatics>
{
    ICanvasRadialGradientBrushStatics(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasSolidColorBrush :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasSolidColorBrush>,
    impl::require<ICanvasSolidColorBrush, Microsoft::Graphics::Canvas::Brushes::ICanvasBrush, Windows::Foundation::IClosable>
{
    ICanvasSolidColorBrush(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasSolidColorBrushFactory :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasSolidColorBrushFactory>
{
    ICanvasSolidColorBrushFactory(std::nullptr_t = nullptr) noexcept {}
};

struct WINRT_EBO ICanvasSolidColorBrushStatics :
    Windows::Foundation::IInspectable,
    impl::consume_t<ICanvasSolidColorBrushStatics>
{
    ICanvasSolidColorBrushStatics(std::nullptr_t = nullptr) noexcept {}
};

}