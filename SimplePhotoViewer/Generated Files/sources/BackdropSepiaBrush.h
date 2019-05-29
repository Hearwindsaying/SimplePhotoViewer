#pragma once

#include "BackdropSepiaBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropSepiaBrush : BackdropSepiaBrushT<BackdropSepiaBrush>
    {
        BackdropSepiaBrush() = default;

        double Intensity();
        void Intensity(double value);

        static Windows::UI::Xaml::DependencyProperty IntensityProperty();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropSepiaBrush : BackdropSepiaBrushT<BackdropSepiaBrush, implementation::BackdropSepiaBrush>
    {
    };
}
