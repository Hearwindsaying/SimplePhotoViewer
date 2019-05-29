//
// Declaration of the DetailPage class.
//

#pragma once

#include "BackdropBlurBrush.h"
#include "BackdropExposureBrush.h"
#include "BackdropExposureBrush.h"
#include "BackdropSaturationBrush.h"
#include "BackdropSepiaBrush.h"
#include "BackdropTemperatureAndTintBrush.h"
#include "ImageSku.h"
#include "DetailPage.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct DetailPage : DetailPageT<DetailPage>
    {
        DetailPage();

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus() const;

		SimplePhotoViewer::ImageSku SelectedItem() const;
		void SelectedItem(SimplePhotoViewer::ImageSku const& value);

		Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e);
		void GoBack_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&);
		void ImageGridView_ItemClick(Windows::Foundation::IInspectable const sender, Windows::UI::Xaml::Controls::ItemClickEventArgs const e);
		Windows::Foundation::IAsyncAction ThumbnailListView_OnContainerContentChanging(Windows::UI::Xaml::Controls::ListViewBase sender, Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs args);
		void FlipView_CleanUpVirtualizedItem(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::CleanUpVirtualizedItemEventArgs const& e);

		Windows::Foundation::IAsyncAction PlayButton_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		void PauseButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
		void Counterclockwise_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		Windows::Foundation::IAsyncAction Save_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		void Cancel_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
		void ZoomIn_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			if (this->FlipViewScrollViewer())
			{
				this->FlipViewScrollViewer().ChangeView(nullptr, nullptr, this->FlipViewScrollViewer().ZoomFactor() + 0.05f);
			}
		}
		void ZoomOut_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			if (this->FlipViewScrollViewer())
			{
				this->FlipViewScrollViewer().ChangeView(nullptr, nullptr, this->FlipViewScrollViewer().ZoomFactor() - 0.05f);
			}
		}
		Windows::Foundation::IAsyncAction Edit_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		Windows::Foundation::IAsyncAction InformationAppBarButton_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		void BlurAmountSlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);
		void ExposureSlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);
		void SaturationSlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);
		void SepiaIntensitySlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);
		void TemperatureSlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);
		void TintSlider_ValueChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&);

		void Checkbox_Checked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			auto checkbox = sender.try_as<Windows::UI::Xaml::Controls::CheckBox>();
			auto rectangle = this->rtg();
			if(checkbox.Name() == L"BlurCheckBox")
				rectangle = this->rtg();
			else if (checkbox.Name() == L"ExposureCheckBox")
				rectangle = this->rtgexp();
			else if (checkbox.Name() == L"SaturationCheckBox")
				rectangle = this->rtgsat();
			else if (checkbox.Name() == L"SepiaCheckBox")
				rectangle = this->rtgsep();
			else if (checkbox.Name() == L"TaTCheckBox" || checkbox.Name() == L"TaTCheckBox2")
				rectangle = this->rtgtem();

			//if(checkbox.IsChecked())
				rectangle.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
			//else
			//	rectangle.Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
		void Checkbox_UnChecked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			auto checkbox = sender.try_as<Windows::UI::Xaml::Controls::CheckBox>();
			auto rectangle = this->rtg();
			if (checkbox.Name() == L"BlurCheckBox")
				rectangle = this->rtg();
			else if (checkbox.Name() == L"ExposureCheckBox")
				rectangle = this->rtgexp();
			else if (checkbox.Name() == L"SaturationCheckBox")
				rectangle = this->rtgsat();
			else if (checkbox.Name() == L"SepiaCheckBox")
				rectangle = this->rtgsep();
			else if (checkbox.Name() == L"TaTCheckBox" || checkbox.Name() == L"TaTCheckBox2")
				rectangle = this->rtgtem();

			//if (checkbox.IsChecked())
			//	rectangle.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
			//else
				rectangle.Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
	

	private:
		void ConcentrateControls()
		{
			this->ThumbnailListView().IsEnabled(false);
			this->DetailPageFlipView().IsEnabled(false);
			this->ZoomInAppBarButton().IsEnabled(false);
			this->ZoomOutAppBarButton().IsEnabled(false);
			this->EditAppBarButton().IsEnabled(false);
			this->CancelAppBarButton().IsEnabled(true);
			this->SaveAppBarButton().IsEnabled(true);
		}
		void RestoreControls()
		{
			this->ThumbnailListView().IsEnabled(true);
			this->DetailPageFlipView().IsEnabled(true);
			this->ZoomInAppBarButton().IsEnabled(true);
			this->ZoomOutAppBarButton().IsEnabled(true);
			this->EditAppBarButton().IsEnabled(true);
			this->CancelAppBarButton().IsEnabled(false);
			this->SaveAppBarButton().IsEnabled(false);
		}

	private:
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_imageSkus{ nullptr };
		SimplePhotoViewer::ImageSku m_SelectedItem{ nullptr };

		bool shouldPausePlay{ false };

		Windows::UI::Composition::Compositor m_compositor{ nullptr };
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DetailPage : DetailPageT<DetailPage, implementation::DetailPage>
    {
    };
}
