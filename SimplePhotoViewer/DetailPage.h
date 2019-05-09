//
// Declaration of the DetailPage class.
//

#pragma once

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
		void ImageFlipView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

		Windows::Foundation::IAsyncAction PlayButton_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		void Counterclockwise_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		Windows::Foundation::IAsyncAction Save_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		void Cancel_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);

		/*Windows::UI::Xaml::Media::RotateTransform ImageRenderTransform();
		void ImageRenderTransform(Windows::UI::Xaml::Media::RotateTransform const& value);

		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
		{
			return this->m_propertyChanged.add(handler);
		}
		void PropertyChanged(winrt::event_token const& token) noexcept
		{
			this->m_propertyChanged.remove(token);
		}*/
	private:
		void ConcentrateControls()
		{
			this->DetailPageFlipView().IsEnabled(false);
			this->ZoomInAppBarButton().IsEnabled(false);
			this->ZoomOutAppBarButton().IsEnabled(false);
			this->EditAppBarButton().IsEnabled(false);
			this->InformationAppBarButton().IsEnabled(false);
			this->CancelAppBarButton().IsEnabled(true);
			this->SaveAppBarButton().IsEnabled(true);
		}
		void RestoreControls()
		{
			this->DetailPageFlipView().IsEnabled(true);
			this->ZoomInAppBarButton().IsEnabled(true);
			this->ZoomOutAppBarButton().IsEnabled(true);
			this->EditAppBarButton().IsEnabled(true);
			this->InformationAppBarButton().IsEnabled(true);
			this->CancelAppBarButton().IsEnabled(false);
			this->SaveAppBarButton().IsEnabled(false);
		}

	private:
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_imageSkus{ nullptr };
		SimplePhotoViewer::ImageSku m_SelectedItem{ nullptr };

		/*Windows::UI::Xaml::Media::RotateTransform m_imageRenderTransform;

		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;*/
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DetailPage : DetailPageT<DetailPage, implementation::DetailPage>
    {
    };
}
