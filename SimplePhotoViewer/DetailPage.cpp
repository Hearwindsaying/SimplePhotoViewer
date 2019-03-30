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
		/*this->DetailPageFlipView().SelectedIndex(1);*/
		/*auto myContent = this->m_imageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>().ImageContent();*/
		this->ThumbnailListView().SelectedIndex(0);

		/*Issue fixed:corruption due to the non-initalization of ThumbnailListView*/
		/*Note that we'd better register the SelectionChanged event manually after loading all items.
		/*If binding in xaml, be careful that ThumbnailListView may not get initialized yet.*/
		this->DetailPageFlipView().SelectionChanged([this](winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
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

					bool isVirtualizing = false;
					double previousHorizontalOffset = 0.0, previousVerticalOffset = 0.0;

					auto scrollViewer = this->ThumbnailScrollViewer();
					auto selectedItemInListView = this->ThumbnailListView().SelectedItem();
					 //bool isVirtualizing = default(bool);
					 //double previousHorizontalOffset = default(double), previousVerticalOffset = default(double);

					 //// get the ScrollViewer withtin the ListView/GridView
					 //var scrollViewer = listViewBase.GetScrollViewer();
					 //// get the SelectorItem to scroll to
					 //var selectorItem = listViewBase.ContainerFromItem(item) as SelectorItem;

					 //// when it's null, means virtualization is on and the item hasn't been realized yet
					 //if (selectorItem == null)
					 //{
						// isVirtualizing = true;

						// previousHorizontalOffset = scrollViewer.HorizontalOffset;
						// previousVerticalOffset = scrollViewer.VerticalOffset;

						// // call task-based ScrollIntoViewAsync to realize the item
						// await listViewBase.ScrollIntoViewAsync(item);

						// // this time the item shouldn't be null again
						// selectorItem = (SelectorItem)listViewBase.ContainerFromItem(item);
					 //}
					/*var sv = new ScrollViewerHelper().GetScrollViewer(listView);
					sv.UpdateLayout();
					sv.ChangeView(0, sv.ExtentHeight, null);*/
					auto thumbnailScrollViewer = this->ThumbnailScrollViewer();
					thumbnailScrollViewer.UpdateLayout();
					//thumbnailScrollViewer.ChangeView(thumbnailScrollViewer.ExtentWidth(), 0.f, nullptr);

					
					auto selectorItem = this->ThumbnailListView().ContainerFromItem(selectedItemInListView).try_as<Windows::UI::Xaml::Controls::Primitives::SelectorItem>();

					/*auto uielement = selectorItem.try_as<Windows::UI::Xaml::UIElement>();
					auto pos = uielement.Translation();
					thumbnailScrollViewer.ChangeView(pos.x, 0.f, nullptr);*/
					auto transform = selectorItem.TransformToVisual(this->ThumbnailScrollViewer().Content().try_as<Windows::UI::Xaml::UIElement>());
					auto position = transform.TransformPoint(Windows::Foundation::Point(0, 0));
					this->ThumbnailScrollViewer().ChangeView(position.X, position.Y, nullptr);

					 //// calculate the position object in order to know how much to scroll to
					 //var transform = selectorItem.TransformToVisual((UIElement)scrollViewer.Content);
					 //var position = transform.TransformPoint(new Point(0, 0));

					 //// when virtualized, scroll back to previous position without animation
					 //if (isVirtualizing)
					 //{
						// await scrollViewer.ChangeViewAsync(previousHorizontalOffset, previousVerticalOffset, true);
					 //}

					 //// scroll to desired position with animation!
					 //scrollViewer.ChangeView(position.X, position.Y, null);
				}
			}
		});
	}

	void DetailPage::ImageGridView_ItemClick(Windows::Foundation::IInspectable const sender, Windows::UI::Xaml::Controls::ItemClickEventArgs const e)
	{
		auto clickedItem = e.ClickedItem();
		this->DetailPageFlipView().SelectedItem(clickedItem);

		/*this->ThumbnailListView().ScrollIntoView();*/
		/*this->ThumbnailListView().ScrollIntoView(m_imageSkus.GetAt(10));*/
	}

	void DetailPage::ImageFlipView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		
	}

	void DetailPage::GoBack_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::MainPage>());
	}
}
