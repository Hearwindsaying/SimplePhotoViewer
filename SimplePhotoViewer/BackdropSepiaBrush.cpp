#include "pch.h"
#include "BackdropSepiaBrush.h"

namespace winrt::SimplePhotoViewer::implementation
{
	Windows::UI::Xaml::DependencyProperty BackdropSepiaBrush::m_intensityProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Intensity",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropSepiaBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropSepiaBrush::OnIntensityChanged } }
	);

	void BackdropSepiaBrush::OnConnected()
	{
		// Delay creating composition resources until they're required.
		if (!CompositionBrush())
		{
			auto backdrop{ Windows::UI::Xaml::Window::Current().Compositor().CreateBackdropBrush() };

			// Use a Win2D blur affect applied to a CompositionBackdropBrush.
			Microsoft::Graphics::Canvas::Effects::SepiaEffect graphicsEffect{};

			graphicsEffect.Name(L"Sepia");
			graphicsEffect.Intensity(this->Intensity());
			graphicsEffect.Source(Windows::UI::Composition::CompositionEffectSourceParameter(L"backdrop"));

			auto effectFactory{ Windows::UI::Xaml::Window::Current().Compositor().CreateEffectFactory(graphicsEffect, { L"Sepia.Intensity" }) };
			auto effectBrush{ effectFactory.CreateBrush() };

			effectBrush.SetSourceParameter(L"backdrop", backdrop);

			CompositionBrush(effectBrush);
		}
	}

	void BackdropSepiaBrush::OnDisconnected()
	{
		// Dispose of composition resources when no longer in use.
		if (CompositionBrush())
		{
			CompositionBrush(nullptr);
		}
	}
}
