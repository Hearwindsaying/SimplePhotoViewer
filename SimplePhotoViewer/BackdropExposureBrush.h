#pragma once

#include "BackdropExposureBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
	struct BackdropExposureBrush : BackdropExposureBrushT<BackdropExposureBrush>
	{
		BackdropExposureBrush() = default;

		double Exposure()
		{
			return winrt::unbox_value<double>(GetValue(m_exposureProperty));
		}
		void Exposure(double value)
		{
			SetValue(m_exposureProperty, winrt::box_value(value));
		}

		static Windows::UI::Xaml::DependencyProperty ExposureProperty() { return m_exposureProperty; }

		static void OnExposureChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
		{
			auto brush{ d.as<SimplePhotoViewer::BackdropExposureBrush>() };
			// Unbox and set a new blur amount if the CompositionBrush exists.
			if (brush.CompositionBrush() != nullptr)
			{
				brush.CompositionBrush().Properties().InsertScalar(L"Exposure.Exposure", (float)winrt::unbox_value<double>(e.NewValue()));
			}
		}

		void OnConnected();
		void OnDisconnected();

	private:
		static Windows::UI::Xaml::DependencyProperty m_exposureProperty; 
	};
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
	struct BackdropExposureBrush : BackdropExposureBrushT<BackdropExposureBrush, implementation::BackdropExposureBrush>
	{
	};
}
