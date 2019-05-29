#include "pch.h"
#include "BackdropSaturationBrush.h"

namespace winrt::SimplePhotoViewer::implementation
{
	Windows::UI::Xaml::DependencyProperty BackdropSaturationBrush::m_saturationProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Saturation",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropSaturationBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropSaturationBrush::OnSaturationChanged } }
	);

	void BackdropSaturationBrush::OnConnected()
	{
		// Delay creating composition resources until they're required.
		if (!CompositionBrush())
		{
			auto backdrop{ Windows::UI::Xaml::Window::Current().Compositor().CreateBackdropBrush() };

			// Use a Win2D blur affect applied to a CompositionBackdropBrush.
			Microsoft::Graphics::Canvas::Effects::SaturationEffect graphicsEffect{};

			graphicsEffect.Name(L"Saturation");
			graphicsEffect.Saturation(this->Saturation());
			graphicsEffect.Source(Windows::UI::Composition::CompositionEffectSourceParameter(L"backdrop"));

			auto effectFactory{ Windows::UI::Xaml::Window::Current().Compositor().CreateEffectFactory(graphicsEffect, { L"Saturation.Saturation" }) };
			auto effectBrush{ effectFactory.CreateBrush() };

			effectBrush.SetSourceParameter(L"backdrop", backdrop);

			CompositionBrush(effectBrush);
		}
	}

	void BackdropSaturationBrush::OnDisconnected()
	{
		// Dispose of composition resources when no longer in use.
		if (CompositionBrush())
		{
			CompositionBrush(nullptr);
		}
	}
}
