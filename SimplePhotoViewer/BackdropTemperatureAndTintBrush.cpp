#include "pch.h"
#include "BackdropTemperatureAndTintBrush.h"

namespace winrt::SimplePhotoViewer::implementation
{
	Windows::UI::Xaml::DependencyProperty BackdropTemperatureAndTintBrush::m_temperatureProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Temperature",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropTemperatureAndTintBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropTemperatureAndTintBrush::OnTemperatureChanged } }
	);

	Windows::UI::Xaml::DependencyProperty BackdropTemperatureAndTintBrush::m_tintProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Tint",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropTemperatureAndTintBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropTemperatureAndTintBrush::OnTintChanged } }
	);

	void BackdropTemperatureAndTintBrush::OnConnected()
	{
		// Delay creating composition resources until they're required.
		if (!CompositionBrush())
		{
			auto backdrop{ Windows::UI::Xaml::Window::Current().Compositor().CreateBackdropBrush() };

			// Use a Win2D blur affect applied to a CompositionBackdropBrush.
			Microsoft::Graphics::Canvas::Effects::TemperatureAndTintEffect graphicsEffect{};

			auto paramsVector = winrt::single_threaded_vector<hstring>();
			paramsVector.Append(L"TemperatureAndTint.Temperature");
			paramsVector.Append(L"TemperatureAndTint.Tint");

			graphicsEffect.Name(L"TemperatureAndTint");
			graphicsEffect.Temperature(this->Temperature());
			graphicsEffect.Tint(this->Tint());
			graphicsEffect.Source(Windows::UI::Composition::CompositionEffectSourceParameter(L"backdrop"));

			auto effectFactory{ Windows::UI::Xaml::Window::Current().Compositor().CreateEffectFactory(graphicsEffect, { L"TemperatureAndTint.Temperature", L"TemperatureAndTint.Tint"}) };
			auto effectBrush{ effectFactory.CreateBrush() };

			effectBrush.SetSourceParameter(L"backdrop", backdrop);

			CompositionBrush(effectBrush);
		}
	}

	void BackdropTemperatureAndTintBrush::OnDisconnected()
	{
		// Dispose of composition resources when no longer in use.
		if (CompositionBrush())
		{
			CompositionBrush(nullptr);
		}
	}
}
