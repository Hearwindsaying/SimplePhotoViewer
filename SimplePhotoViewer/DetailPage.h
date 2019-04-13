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

	private:
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_imageSkus{ nullptr };
		SimplePhotoViewer::ImageSku m_SelectedItem{ nullptr };
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DetailPage : DetailPageT<DetailPage, implementation::DetailPage>
    {
    };
}
