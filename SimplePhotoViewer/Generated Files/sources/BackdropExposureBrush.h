#pragma once

#include "BackdropExposureBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropExposureBrush : BackdropExposureBrushT<BackdropExposureBrush>
    {
        BackdropExposureBrush() = default;

        double Exposure();
        void Exposure(double value);

        static Windows::UI::Xaml::DependencyProperty ExposureProperty();
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropExposureBrush : BackdropExposureBrushT<BackdropExposureBrush, implementation::BackdropExposureBrush>
    {
    };
}
