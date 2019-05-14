#pragma once

#include "BackdropBlurBrush.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct BackdropBlurBrush : BackdropBlurBrushT<BackdropBlurBrush>
    {
		BackdropBlurBrush() = default;

		static Windows::UI::Xaml::DependencyProperty BlurAmountProperty() { return m_blurAmountProperty; }

		double BlurAmount()
		{
			return winrt::unbox_value<double>(GetValue(m_blurAmountProperty));
		}

		void BlurAmount(double value)
		{
			SetValue(m_blurAmountProperty, winrt::box_value(value));
		}

		void OnConnected();
		void OnDisconnected();

		static void OnBlurAmountChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

	private:
		static Windows::UI::Xaml::DependencyProperty m_blurAmountProperty;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct BackdropBlurBrush : BackdropBlurBrushT<BackdropBlurBrush, implementation::BackdropBlurBrush>
    {
    };
}
