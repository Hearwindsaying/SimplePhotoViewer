#pragma once

#include "BackdropBlurBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropBlurBrush : BackdropBlurBrushT<BackdropBlurBrush>
    {
        BackdropBlurBrush() = default;

        double BlurAmount();
        void BlurAmount(double value);

        static Windows::UI::Xaml::DependencyProperty BlurAmountProperty();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropBlurBrush : BackdropBlurBrushT<BackdropBlurBrush, implementation::BackdropBlurBrush>
    {
    };
}
