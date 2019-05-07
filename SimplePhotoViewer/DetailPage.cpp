#include "pch.h"
#include "DetailPage.h"
#include "ImageSku.h"
#include "Utility.h"
#include "PageNavigationParameter.h"

#include <winrt/Windows.UI.Core.h>

#include <chrono>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace std::chrono;

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
		auto pageParameter = /*unbox_value<PageNavigationParameter>(e.Parameter());*/
			e.Parameter().try_as<SimplePhotoViewer::PageNavigationParameter>();
		
		this->m_imageSkus = pageParameter.ImageSkus();
		auto mainPageSelectedIndex = pageParameter.MainPageCurrentSelectedIndex();
		//this->m_imageSkus = e.Parameter().try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();

		//this->m_imageSkus = pageParameter.GetAt(0).try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();
		//auto selectedIndex = unbox_value<int>( pageParameter.GetAt(1));

		for (auto i = 0; i < 5; ++i)
		{
			/*Load next 5 images*/
			if ((i + mainPageSelectedIndex) >= this->m_imageSkus.Size())
				break;

			auto singleItem = this->m_imageSkus.GetAt(i + mainPageSelectedIndex);
			auto singleImageSku = singleItem.try_as<SimplePhotoViewer::ImageSku>();
			Windows::Storage::Streams::IRandomAccessStream stream{ co_await singleImageSku.ImageFile().OpenAsync(Windows::Storage::FileAccessMode::Read) };
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
			bitmap.SetSource(stream);
			singleImageSku.ImageContent(bitmap);
			//stream.Close();
		}

		/*this->DetailPageFlipView().SelectedIndex(1);*/
		/*auto myContent = this->m_imageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>().ImageContent();*/
		//this->ThumbnailListView().SelectedIndex(0);

		/*Issue fixed:corruption due to the non-initalization of ThumbnailListView*/
		/*Note that we'd better register the SelectionChanged event manually after loading all items.
		/*If binding in xaml, be careful that ThumbnailListView may not get initialized yet.*/
		this->DetailPageFlipView().SelectionChanged([this](winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)->Windows::Foundation::IAsyncAction
		{
			auto flipView = sender.try_as<Windows::UI::Xaml::Controls::FlipView>();
			if (flipView.SelectedItem())
			{
				auto addedItemsSize = e.AddedItems().Size();
				if (addedItemsSize > 0)
				{
					this->ThumbnailListView().SelectedItem(flipView.SelectedItem());
					/*this->ThumbnailListView().UpdateLayout();
					this->ThumbnailListView().ScrollIntoView(ThumbnailListView().SelectedItem());*/

					auto scrollViewer = this->ThumbnailScrollViewer();
					auto selectedItemInListView = this->ThumbnailListView().SelectedItem();
					
					auto thumbnailScrollViewer = this->ThumbnailScrollViewer();
					thumbnailScrollViewer.UpdateLayout();
					
					auto selectorItem = this->ThumbnailListView().ContainerFromItem(selectedItemInListView).try_as<Windows::UI::Xaml::Controls::Primitives::SelectorItem>();
					
					if (!selectorItem)
						return;

					/*weak reference,might not exist any more*/
					auto thumbnailScrollViewerContent = this->ThumbnailScrollViewer().Content();
					if (thumbnailScrollViewerContent)
					{
						auto thumbnailScrollViewerUIElement = thumbnailScrollViewerContent.try_as<Windows::UI::Xaml::UIElement>();
						if (thumbnailScrollViewerUIElement)
						{
							auto transform = selectorItem.TransformToVisual(thumbnailScrollViewerUIElement);

							auto position = transform.TransformPoint(Windows::Foundation::Point(0, 0));
							this->ThumbnailScrollViewer().ChangeView(position.X, position.Y, nullptr);

							/*Load the next 5 images*/
							for (auto i = 0; i < 5; ++i)
							{
								auto flipViewSelectedItem = flipView.SelectedItem();
								auto selectedImageSkuItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [flipViewSelectedItem](auto const& item)->bool
								{
									return item == flipViewSelectedItem;
								});

								if ((i + selectedImageSkuItemIndex) >= this->m_imageSkus.Size())
									break;
								auto singleItem = this->m_imageSkus.GetAt(i + selectedImageSkuItemIndex);

								auto singleImageSku = singleItem.try_as<SimplePhotoViewer::ImageSku>();
								if (singleImageSku.ImageContent())
									continue;

								Windows::Storage::Streams::IRandomAccessStream stream{ co_await singleImageSku.ImageFile().OpenAsync(Windows::Storage::FileAccessMode::Read) };
								Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
								bitmap.SetSource(stream);
								singleImageSku.ImageContent(bitmap);
								//stream.Close();
							}
						}
						else
						{
							wchar_t testchar[20] = { 'e','r','4' };
							OutputDebugString(testchar);
						}
					}
					
				}
			}
		});

		//this->DetailPageFlipView().SelectedIndex(mainPageSelectedIndex);
		this->ThumbnailListView().SelectedIndex(0);
	}

	void DetailPage::ImageGridView_ItemClick(Windows::Foundation::IInspectable const sender, Windows::UI::Xaml::Controls::ItemClickEventArgs const e)
	{
		auto clickedItem = e.ClickedItem();
		this->DetailPageFlipView().SelectedItem(clickedItem);

		//this->DetailPageFlipView().ItemTemplate().
		/*this->ThumbnailListView().ScrollIntoView();*/
		/*this->ThumbnailListView().ScrollIntoView(m_imageSkus.GetAt(10));*/
	}

	/*void DetailPage::ImageFlipView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		
	}*/

	void DetailPage::GoBack_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::MainPage>());
	}

	Windows::Foundation::IAsyncAction DetailPage::PlayButton_ClickHandler(Windows::Foundation::IInspectable const param, Windows::UI::Xaml::RoutedEventArgs const)
	{
		/*todo:note that even clicking goback button,caching the detail page,this background thread is still running!*/
		auto currentSelectedIndex = this->DetailPageFlipView().SelectedIndex();
		for (; currentSelectedIndex < this->m_imageSkus.Size(); )
		{
			co_await 1s;

			co_await winrt::resume_foreground(this->DetailPageFlipView().Dispatcher());
			this->DetailPageFlipView().SelectedIndex(++currentSelectedIndex);

			wchar_t testchar[20] = { 'w','t','a' };
			OutputDebugString(testchar);
		}
	}
}
