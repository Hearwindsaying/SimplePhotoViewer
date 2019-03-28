#include "pch.h"
#include "DetailPage.h"
#include "ImageSku.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SimplePhotoViewer::implementation
{
    DetailPage::DetailPage()
    {
        InitializeComponent();
		this->m_imageSkus = single_threaded_observable_vector<Windows::Foundation::IInspectable>();
    }

	Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> DetailPage::ImageSkus() const
	{
		return this->m_imageSkus;
	}

	SimplePhotoViewer::ImageSku DetailPage::SelectedItem()const
	{
		return this->m_SelectedItem;
	}

	void DetailPage::SelectedItem(SimplePhotoViewer::ImageSku const& value)
	{
		this->m_SelectedItem = value;
	}

	Windows::Foundation::IAsyncAction DetailPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e)
	{
		/*Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> imageCollection = e.Parameter().try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();*/

		this->m_imageSkus = e.Parameter().try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();

		/*if (this->m_imageSkus.Size() > 0)
		{
			SimplePhotoViewer::ImageSku isk = this->m_imageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();

			
		}*/
		for (auto&& singleItem : this->m_imageSkus)
		{
			auto singleImageSku = singleItem.try_as<SimplePhotoViewer::ImageSku>();
			Windows::Storage::Streams::IRandomAccessStream stream{ co_await singleImageSku.ImageFile().OpenAsync(Windows::Storage::FileAccessMode::Read) };
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
			bitmap.SetSource(stream);
			singleImageSku.ImageContent(bitmap);

		}
		/*auto myContent = this->m_imageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>().ImageContent();*/

	}

	void DetailPage::GoBack_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::MainPage>());
	}
}
