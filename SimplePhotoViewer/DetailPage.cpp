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
    DetailPage::DetailPage()/*m_imageRenderTransform(Windows::UI::Xaml::Media::RotateTransform())*/
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

	/*Windows::UI::Xaml::Media::RotateTransform DetailPage::ImageRenderTransform()
	{
		return this->m_imageRenderTransform;
	}

	void DetailPage::ImageRenderTransform(Windows::UI::Xaml::Media::RotateTransform const& value)
	{
		this->m_imageRenderTransform = value;
		this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ImageRenderTransform" });
	}*/

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

		/*Deleteme*/
		/*auto singleItem = this->m_imageSkus.GetAt(mainPageSelectedIndex);
		auto singleImageSku = singleItem.try_as<SimplePhotoViewer::ImageSku>();
		this->EditingImage().Source(singleImageSku.ImageContent());*/
		
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

		if (mainPageSelectedIndex != -1)
		{
			this->ThumbnailListView().SelectedIndex(mainPageSelectedIndex);
			this->DetailPageFlipView().SelectedIndex(mainPageSelectedIndex);
		}
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

	void DetailPage::Counterclockwise_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		auto currentSelectedItem = this->DetailPageFlipView().SelectedItem();
		auto currentImageSku = currentSelectedItem.try_as<SimplePhotoViewer::ImageSku>();
		if (currentImageSku)
		{
			auto getRotateAngle = [](int const inputAngle)->double
			{
				switch (inputAngle)
				{
				case 0:
					return 90;
				case 90:
					return 180;
				case 180:
					return 270;
				default:
					return 0;
				}
			};

			currentImageSku.RenderRotation(getRotateAngle(static_cast<int>(currentImageSku.RenderRotation())));
			this->ConcentrateControls();
		}
	}

	Windows::Foundation::IAsyncAction DetailPage::Save_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		using StorageFile = Windows::Storage::StorageFile;
		using FileAccessMode = Windows::Storage::FileAccessMode;
		using InMemoryAccessStream = Windows::Storage::Streams::InMemoryRandomAccessStream;
		using RandomAccessStream = Windows::Storage::Streams::RandomAccessStream;
		using BitmapDecoder = Windows::Graphics::Imaging::BitmapDecoder;
		using BitmapEncoder = Windows::Graphics::Imaging::BitmapEncoder;
		using BitmapInterpolationMode = Windows::Graphics::Imaging::BitmapInterpolationMode;
		using BitmapRotation = Windows::Graphics::Imaging::BitmapRotation;

		auto currentSelectedItem = this->DetailPageFlipView().SelectedItem();
		auto currentImageSku = currentSelectedItem.try_as<SimplePhotoViewer::ImageSku>();
		if (currentImageSku)
		{
			currentImageSku.RenderRotation(0.0);

			auto currentStorageFile = currentImageSku.ImageFile();
			auto fileStream = co_await currentStorageFile.OpenAsync(FileAccessMode::ReadWrite);
			auto memStream = InMemoryAccessStream();

			auto bitmapDecoder = co_await BitmapDecoder::CreateAsync(fileStream);


			// Use the native (no orientation applied) image dimensions because we want to handle
					// orientation ourselves.
			uint32_t originalWidth = bitmapDecoder.PixelWidth();
			uint32_t originalHeight = bitmapDecoder.PixelHeight();

			// Set the encoder's destination to the temporary, in-memory stream.
			BitmapEncoder encoder = co_await BitmapEncoder::CreateForTranscodingAsync(memStream, bitmapDecoder);

			// Scaling occurs before flip/rotation, therefore use the original dimensions
			// (no orientation applied) as parameters for scaling.
			// Dimensions are rounded down by BitmapEncoder to the nearest integer.
			auto m_scaleFactor = 1.f;
			if (m_scaleFactor != 1.0)
			{
				encoder.BitmapTransform().ScaledWidth(static_cast<uint32_t>(originalWidth * m_scaleFactor));
				encoder.BitmapTransform().ScaledHeight(static_cast<uint32_t>(originalHeight * m_scaleFactor));

				// Fant is a relatively high quality interpolation mode.
				encoder.BitmapTransform().InterpolationMode(BitmapInterpolationMode::Fant);
			}

			// Otherwise, perform a hard rotate using BitmapTransform.
			encoder.BitmapTransform().Rotation(/*Helpers.ConvertToBitmapRotation(m_userRotation);*/BitmapRotation::Clockwise180Degrees);


			//// Attempt to generate a new thumbnail to reflect any rotation operation.
			encoder.IsThumbnailGenerated(true);

			try
			{
				co_await encoder.FlushAsync();
			}
			catch (hresult_error const& ex)
			{
				HRESULT hr = ex.to_abi();
				switch (hr)
				{
				case WINCODEC_ERR_UNSUPPORTEDOPERATION:
					// If the encoder does not support writing a thumbnail, then try again
					// but disable thumbnail generation.
					encoder.IsThumbnailGenerated(false);
					break;
				default:
					throw;
				}
			}

			if (encoder.IsThumbnailGenerated() == false)
			{
				co_await encoder.FlushAsync();
			}

			// Now that the file has been written to the temporary stream, copy the data to the file.
			memStream.Seek(0);
			fileStream.Seek(0);
			fileStream.Size(0);
			co_await RandomAccessStream::CopyAsync(memStream, fileStream);

			this->RestoreControls();
		}
	}

	void DetailPage::Cancel_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		auto currentSelectedItem = this->DetailPageFlipView().SelectedItem();
		auto currentImageSku = currentSelectedItem.try_as<SimplePhotoViewer::ImageSku>();
		if (currentImageSku)
		{
			currentImageSku.RenderRotation(0.0);
			this->RestoreControls();
		}
	}
}
