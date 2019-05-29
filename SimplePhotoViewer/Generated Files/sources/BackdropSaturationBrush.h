#pragma once

#include "BackdropSaturationBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropSaturationBrush : BackdropSaturationBrushT<BackdropSaturationBrush>
    {
        BackdropSaturationBrush() = default;

        double Saturation();
        void Saturation(double value);

        static Windows::UI::Xaml::DependencyProperty SaturationProperty();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropSaturationBrush : BackdropSaturationBrushT<BackdropSaturationBrush, implementation::BackdropSaturationBrush>
    {
    };
}
