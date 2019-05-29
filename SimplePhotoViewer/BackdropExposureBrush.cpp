#include "pch.h"
#include "BackdropExposureBrush.h"

#include <winrt/Windows.UI.Core.h>

namespace winrt::SimplePhotoViewer::implementation
{
	Windows::UI::Xaml::DependencyProperty BackdropExposureBrush::m_exposureProperty = 
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Exposure",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<SimplePhotoViewer::BackdropExposureBrush>(),
			Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.), Windows::UI::Xaml::PropertyChangedCallback{ &BackdropExposureBrush::OnExposureChanged } }
		);

	void BackdropExposureBrush::OnConnected()
	{
		// Delay creating composition resources until they're required.
		if (!CompositionBrush())
		{
			auto backdrop{ Windows::UI::Xaml::Window::Current().Compositor().CreateBackdropBrush() };

			// Use a Win2D blur affect applied to a CompositionBackdropBrush.
			Microsoft::Graphics::Canvas::Effects::ExposureEffect graphicsEffect{};

			graphicsEffect.Name(L"Exposure");
			graphicsEffect.Exposure(this->Exposure());
			graphicsEffect.Source(Windows::UI::Composition::CompositionEffectSourceParameter(L"backdrop"));

			auto effectFactory{ Windows::UI::Xaml::Window::Current().Compositor().CreateEffectFactory(graphicsEffect, { L"Exposure.Exposure" }) };
			auto effectBrush{ effectFactory.CreateBrush() };

			effectBrush.SetSourceParameter(L"backdrop", backdrop);

			CompositionBrush(effectBrush);
		}
	}

	void BackdropExposureBrush::OnDisconnected()
	{
		// Dispose of composition resources when no longer in use.
		if (CompositionBrush())
		{
			CompositionBrush(nullptr);
		}
	}
}
