#pragma once

#include "BackdropTemperatureAndTintBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropTemperatureAndTintBrush : BackdropTemperatureAndTintBrushT<BackdropTemperatureAndTintBrush>
    {
        BackdropTemperatureAndTintBrush() = default;

		static Windows::UI::Xaml::DependencyProperty TemperatureProperty() { return m_temperatureProperty; }
		static Windows::UI::Xaml::DependencyProperty TintProperty() { return m_tintProperty; }

		double Temperature()
		{
			return winrt::unbox_value<double>(GetValue(m_temperatureProperty));
		}

		void Temperature(double value)
		{
			SetValue(m_temperatureProperty, winrt::box_value(value));
		}

		double Tint()
		{
			return winrt::unbox_value<double>(GetValue(m_tintProperty));
		}

		void Tint(double value)
		{
			SetValue(m_tintProperty, winrt::box_value(value));
		}

		void OnConnected();
		void OnDisconnected();

		static void OnTemperatureChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
		{
			auto brush{ d.as<SimplePhotoViewer::BackdropTemperatureAndTintBrush>() };
			// Unbox and set a new blur amount if the CompositionBrush exists.
			if (brush.CompositionBrush() != nullptr)
			{
				brush.CompositionBrush().Properties().InsertScalar(L"TemperatureAndTint.Temperature", (double)winrt::unbox_value<double>(e.NewValue()));
			}
		}
		static void OnTintChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
		{
			auto brush{ d.as<SimplePhotoViewer::BackdropTemperatureAndTintBrush>() };
			// Unbox and set a new blur amount if the CompositionBrush exists.
			if (brush.CompositionBrush() != nullptr)
			{
				brush.CompositionBrush().Properties().InsertScalar(L"TemperatureAndTint.Tint", (double)winrt::unbox_value<double>(e.NewValue()));
			}
		}
	private:
		static Windows::UI::Xaml::DependencyProperty m_temperatureProperty;
		static Windows::UI::Xaml::DependencyProperty m_tintProperty;
	};
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropTemperatureAndTintBrush : BackdropTemperatureAndTintBrushT<BackdropTemperatureAndTintBrush, implementation::BackdropTemperatureAndTintBrush>
    {
    };
}
