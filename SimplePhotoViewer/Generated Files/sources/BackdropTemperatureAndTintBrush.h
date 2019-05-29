#pragma once

#include "BackdropTemperatureAndTintBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropTemperatureAndTintBrush : BackdropTemperatureAndTintBrushT<BackdropTemperatureAndTintBrush>
    {
        BackdropTemperatureAndTintBrush() = default;

        double Temperature();
        void Temperature(double value);
        double Tint();
        void Tint(double value);

        static Windows::UI::Xaml::DependencyProperty TemperatureProperty();
        static Windows::UI::Xaml::DependencyProperty TintProperty();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropTemperatureAndTintBrush : BackdropTemperatureAndTintBrushT<BackdropTemperatureAndTintBrush, implementation::BackdropTemperatureAndTintBrush>
    {
    };
}
