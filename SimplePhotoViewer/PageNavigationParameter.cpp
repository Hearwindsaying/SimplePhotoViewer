#include "pch.h"
#include "PageNavigationParameter.h"

namespace winrt::SimplePhotoViewer::implementation
{
	PageNavigationParameter::PageNavigationParameter(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& imageSkus, uint32_t mainPageCurrentSelectedIndex)
	{
		this->m_imageSkus = imageSkus;
		this->m_mainPageCurrentSelectedIndex = mainPageCurrentSelectedIndex;
	}

	Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> PageNavigationParameter::ImageSkus()
	{
		return this->m_imageSkus;
	}

	uint32_t PageNavigationParameter::MainPageCurrentSelectedIndex()
	{
		return this->m_mainPageCurrentSelectedIndex;
	}
}
