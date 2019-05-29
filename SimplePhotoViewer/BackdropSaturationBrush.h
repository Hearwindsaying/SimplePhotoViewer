#pragma once

#include "BackdropSaturationBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropSaturationBrush : BackdropSaturationBrushT<BackdropSaturationBrush>
    {
        BackdropSaturationBrush() = default;

		double Saturation()
		{
			return winrt::unbox_value<double>(GetValue(m_saturationProperty));
		}
		void Saturation(double value)
		{
			SetValue(m_saturationProperty, winrt::box_value(value));
		}

		static Windows::UI::Xaml::DependencyProperty SaturationProperty() { return m_saturationProperty; }

		static void OnSaturationChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
		{
			auto brush{ d.as<SimplePhotoViewer::BackdropSaturationBrush>() };
			// Unbox and set a new blur amount if the CompositionBrush exists.
			if (brush.CompositionBrush() != nullptr)
			{
				brush.CompositionBrush().Properties().InsertScalar(L"Saturation.Saturation", (double)winrt::unbox_value<double>(e.NewValue()));
			}
		}

		void OnConnected();
		void OnDisconnected();

	private:
		static Windows::UI::Xaml::DependencyProperty m_saturationProperty;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropSaturationBrush : BackdropSaturationBrushT<BackdropSaturationBrush, implementation::BackdropSaturationBrush>
    {
    };
}
