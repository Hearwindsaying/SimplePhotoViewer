#include "pch.h"
#include "BackdropBlurBrush.h"

#include <winrt/Windows.UI.Core.h>

namespace winrt::SimplePhotoViewer::implementation
{
	Windows::UI::Xaml::DependencyProperty BackdropBlurBrush::m_blurAmountProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"BlurAmount",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropBlurBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropBlurBrush::OnBlurAmountChanged } }
	);

	void BackdropBlurBrush::OnBlurAmountChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto brush{ d.as<SimplePhotoViewer::BackdropBlurBrush>() };
		// Unbox and set a new blur amount if the CompositionBrush exists.
		if (brush.CompositionBrush() != nullptr)
		{
			brush.CompositionBrush().Properties().InsertScalar(L"Blur.BlurAmount", (float)winrt::unbox_value<double>(e.NewValue()));
		}
	}

	void BackdropBlurBrush::OnConnected()
	{
		// Delay creating composition resources until they're required.
		if (!CompositionBrush())
		{
			auto backdrop{ Windows::UI::Xaml::Window::Current().Compositor().CreateBackdropBrush() };

			// Use a Win2D blur affect applied to a CompositionBackdropBrush.
			Microsoft::Graphics::Canvas::Effects::GaussianBlurEffect graphicsEffect{};

			graphicsEffect.Name(L"Blur");
			graphicsEffect.BlurAmount(this->BlurAmount());
			graphicsEffect.Source(Windows::UI::Composition::CompositionEffectSourceParameter(L"backdrop"));

			auto effectFactory{ Windows::UI::Xaml::Window::Current().Compositor().CreateEffectFactory(graphicsEffect, { L"Blur.BlurAmount" }) };
			auto effectBrush{ effectFactory.CreateBrush() };

			effectBrush.SetSourceParameter(L"backdrop", backdrop);

			CompositionBrush(effectBrush);
		}
	}

	void BackdropBlurBrush::OnDisconnected()
	{
		// Dispose of composition resources when no longer in use.
		if (CompositionBrush())
		{
			CompositionBrush(nullptr);
		}
	}
}
