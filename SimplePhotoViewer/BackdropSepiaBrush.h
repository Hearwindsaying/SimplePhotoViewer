#pragma once

#include "BackdropSepiaBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropSepiaBrush : BackdropSepiaBrushT<BackdropSepiaBrush>
    {
        BackdropSepiaBrush() = default;

		double Intensity()
		{
			return winrt::unbox_value<double>(GetValue(m_intensityProperty));
		}
		void Intensity(double value)
		{
			SetValue(m_intensityProperty, winrt::box_value(value));
		}

		static Windows::UI::Xaml::DependencyProperty IntensityProperty() { return m_intensityProperty; }

		static void OnIntensityChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
		{
			auto brush{ d.as<SimplePhotoViewer::BackdropSepiaBrush>() };
			// Unbox and set a new blur amount if the CompositionBrush exists.
			if (brush.CompositionBrush() != nullptr)
			{
				brush.CompositionBrush().Properties().InsertScalar(L"Sepia.Intensity", (double)winrt::unbox_value<double>(e.NewValue()));
			}
		}

		void OnConnected();
		void OnDisconnected();

	private:
		static Windows::UI::Xaml::DependencyProperty m_intensityProperty;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropSepiaBrush : BackdropSepiaBrushT<BackdropSepiaBrush, implementation::BackdropSepiaBrush>
    {
    };
}
