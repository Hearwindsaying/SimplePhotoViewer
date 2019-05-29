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

using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Effects;
using namespace Microsoft::Graphics::Canvas::Text;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas::UI;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Composition;

using namespace Windows::ApplicationModel::DataTransfer;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;

namespace winrt::SimplePhotoViewer::implementation
{
    DetailPage::DetailPage():m_compositor(Window::Current().Compositor())
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
		this->shouldPausePlay = false;
		auto pageParameter = /*unbox_value<PageNavigationParameter>(e.Parameter());*/
			e.Parameter().try_as<SimplePhotoViewer::PageNavigationParameter>();
		
		this->m_imageSkus = pageParameter.ImageSkus();
		auto mainPageSelectedIndex = pageParameter.MainPageCurrentSelectedIndex();

		
		//this->m_imageSkus = e.Parameter().try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();

		//this->m_imageSkus = pageParameter.GetAt(0).try_as< Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>();
		//auto selectedIndex = unbox_value<int>( pageParameter.GetAt(1));
		constexpr int nextNumConst = 3;
		for (auto i = 0; i < nextNumConst; ++i)
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
			singleImageSku.IsVirtualizing(false);
		}

		/*this->DetailPageFlipView().SelectedIndex(1);*/
		/*auto myContent = this->m_imageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>().ImageContent();*/
		//this->ThumbnailListView().SelectedIndex(0);

		/*Issue fixed:corruption due to the non-initalization of ThumbnailListView*/
		/*Note that we'd better register the SelectionChanged event manually after loading items.
		/*If binding in xaml, be careful that ThumbnailListView may not have been initialized yet.*/
		this->DetailPageFlipView().SelectionChanged([this, nextNumConst](winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)->Windows::Foundation::IAsyncAction
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

							auto selectedIndexVector = std::vector<int>(3);
							auto selectedIndexBase = 0;

							/*Load the current and next 2 images*/
							for (auto i = 0; i < nextNumConst; ++i)
							{
								auto flipViewSelectedItem = flipView.SelectedItem();
								auto selectedImageSkuItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [flipViewSelectedItem](auto const& item)->bool
								{
									return item == flipViewSelectedItem;
								});
								

								if ((i + selectedImageSkuItemIndex) >= this->m_imageSkus.Size())
									break;
								auto singleItem = this->m_imageSkus.GetAt(i + selectedImageSkuItemIndex);
								/*selectedIndexVector[i] = i + selectedImageSkuItemIndex;*/
								selectedIndexBase = selectedImageSkuItemIndex;

								auto singleImageSku = singleItem.try_as<SimplePhotoViewer::ImageSku>();
								if (singleImageSku.ImageContent() && !singleImageSku.IsVirtualizing())/*current imageSku does have content so just skip the very item*/
								{
									/*Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
									if(singleImageSku.ImageContent() != bitmapImage)*/
										continue;
								}
									

								Windows::Storage::Streams::IRandomAccessStream stream{ co_await singleImageSku.ImageFile().OpenAsync(Windows::Storage::FileAccessMode::Read) };
								Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
								bitmap.SetSource(stream);
								singleImageSku.ImageContent(bitmap);
								//stream.Close();
								singleImageSku.IsVirtualizing(false);
								
								/*for (auto&& imageSku : this->m_imageSkus)
								{
									auto selectorItem = this->DetailPageFlipView().ContainerFromItem(imageSku).try_as<Windows::UI::Xaml::Controls::FlipViewItem>();
									if (!selectorItem)
									{
										Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
										
										imageSku.as<SimplePhotoViewer::ImageSku>().ImageContent(bitmapImage);
									}
								}*/
							}

							auto imageSkuSize = this->m_imageSkus.Size();
							for (auto i = 0; i < imageSkuSize; ++i)
							{
#define CHECK_INDEX(x) (x>=0&&x<imageSkuSize)
#define IS_INDEX(x) (x == i)
								if ((CHECK_INDEX(selectedIndexBase - 3) && IS_INDEX(selectedIndexBase - 3)) ||
									(CHECK_INDEX(selectedIndexBase - 2) && IS_INDEX(selectedIndexBase - 2)) ||
									(CHECK_INDEX(selectedIndexBase - 1) && IS_INDEX(selectedIndexBase - 1)) ||
									(IS_INDEX(selectedIndexBase)) ||
									(CHECK_INDEX(selectedIndexBase + 1) && IS_INDEX(selectedIndexBase + 1)) ||
									(CHECK_INDEX(selectedIndexBase + 2) && IS_INDEX(selectedIndexBase + 2)) ||
									(CHECK_INDEX(selectedIndexBase + 3) && IS_INDEX(selectedIndexBase + 3)))
								{
									//this->m_imageSkus.GetAt(i).as<SimplePhotoViewer::ImageSku>().IsVirtualizing(false);
									continue;
								}
									
								
								Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};

								this->m_imageSkus.GetAt(i).as<SimplePhotoViewer::ImageSku>().ImageContent(bitmapImage);
								this->m_imageSkus.GetAt(i).as<SimplePhotoViewer::ImageSku>().IsVirtualizing(true);
#undef CHECK_INDEX
#undef IS_INDEX
							}
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

		/*for (auto&& imageSku : this->m_imageSkus)
		{
			auto selectorItem = this->DetailPageFlipView().ContainerFromItem(imageSku).try_as<Windows::UI::Xaml::Controls::FlipViewItem>();
			if (!selectorItem)
			{
				auto i = 0;
			}
		}*/
	}

	Windows::Foundation::IAsyncAction DetailPage::ThumbnailListView_OnContainerContentChanging(Windows::UI::Xaml::Controls::ListViewBase sender, Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs args)
	{
		auto image = args.ItemContainer().ContentTemplateRoot().as<Windows::UI::Xaml::Controls::Image>();

		if (args.InRecycleQueue())
		{
			image.Source(nullptr);
		}

		if (args.Phase() == 0)
		{
			args.RegisterUpdateCallback([&](auto sender, auto args)
			{
				this->ThumbnailListView_OnContainerContentChanging(sender, args);
			});

			args.Handled(true);
		}

		if (args.Phase() == 1)
		{
			// It's phase 1, so show this item's image.
			image.Opacity(100);

			auto item = unbox_value<SimplePhotoViewer::ImageSku>(args.Item());
			ImageSku* impleType = from_abi<ImageSku>(item);

			try
			{
				auto thumbnail = co_await impleType->ImageFile().GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem);
				Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
				bitmapImage.SetSource(thumbnail);
				thumbnail.Close();
				image.Source(bitmapImage);
			}
			catch (winrt::hresult_error)
			{
				// File could be corrupt, or it might have an image file
				// extension, but not really be an image file.
				Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
				//Uri uri{ image.BaseUri().AbsoluteUri(), L"Assets/StoreLogo.png" };
				//bitmapImage.UriSource(uri);
				image.Source(bitmapImage);
			}
		}
	}

	void DetailPage::FlipView_CleanUpVirtualizedItem(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::CleanUpVirtualizedItemEventArgs const& e)
	{
		auto imageSku = e.Value().as<SimplePhotoViewer::ImageSku>();
		imageSku.ImageContent(nullptr);
	}

	void DetailPage::GoBack_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		this->shouldPausePlay = true;
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::MainPage>());
	}

	Windows::Foundation::IAsyncAction DetailPage::PlayButton_ClickHandler(Windows::Foundation::IInspectable const param, Windows::UI::Xaml::RoutedEventArgs const)
	{
		this->shouldPausePlay = false;

		this->SlidePlay().IsEnabled(false);
		this->SlidePause().IsEnabled(true);
		/*todo:note that even clicking goback button,caching the detail page,this background thread is still running!*/
		auto currentSelectedIndex = this->DetailPageFlipView().SelectedIndex();
		for (; currentSelectedIndex < this->m_imageSkus.Size(); )
		{
			if (this->shouldPausePlay)
				break;
			co_await 1s;

			co_await winrt::resume_foreground(this->DetailPageFlipView().Dispatcher());

			if (currentSelectedIndex + 1 >= this->m_imageSkus.Size())
				break;
			this->DetailPageFlipView().SelectedIndex(++currentSelectedIndex);
		}

		this->SlidePlay().IsEnabled(true);
		this->SlidePause().IsEnabled(false);
	}
	void DetailPage::PauseButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		this->SlidePlay().IsEnabled(true);
		this->SlidePause().IsEnabled(false);
		this->shouldPausePlay = true;
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
			auto rotatedAngle = currentImageSku.RenderRotation();
			auto getRotateAngle = [](int const inputAngle)
			{
				switch (inputAngle)
				{
				case 0:
					return BitmapRotation::None;
				case 90:
					return BitmapRotation::Clockwise90Degrees;
				case 180:
					return BitmapRotation::Clockwise180Degrees;
				case 270:
					return BitmapRotation::Clockwise270Degrees;
				default:
					return BitmapRotation::None;
				}
			};
			auto rotatedEnum = getRotateAngle(rotatedAngle);

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

			// Otherwise, perform a hard rotate using BitmapTransform.
			encoder.BitmapTransform().Rotation(rotatedEnum);


			//// Attempt to generate a new thumbnail to reflect any rotation operation.
			encoder.IsThumbnailGenerated(false);

			//try
			//{
			//	co_await encoder.FlushAsync();
			//}
			//catch (hresult_error const& ex)
			//{
			//	HRESULT hr = ex.to_abi();
			//	switch (hr)
			//	{
			//	case WINCODEC_ERR_UNSUPPORTEDOPERATION:
			//		// If the encoder does not support writing a thumbnail, then try again
			//		// but disable thumbnail generation.
			//		encoder.IsThumbnailGenerated(false);
			//		break;
			//	default:
			//		throw;
			//	}
			//}

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

			//Update Rotated Image File
			Windows::Storage::Streams::IRandomAccessStream stream{ co_await currentImageSku.ImageFile().OpenAsync(Windows::Storage::FileAccessMode::Read) };
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
			bitmap.SetSource(stream);
			currentImageSku.ImageContent(bitmap);
			
			auto file = currentImageSku.ImageFile();
			auto imageProperties = co_await file.Properties().GetImagePropertiesAsync();
			auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem);
			//or:auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
			bitmapImage.SetSource(thumbnail);
			currentImageSku.ImageThumbnail(bitmapImage);
		}
	}

	void DetailPage::Cancel_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		auto currentSelectedItem = this->DetailPageFlipView().SelectedItem();
		auto currentImageSku = currentSelectedItem.try_as<SimplePhotoViewer::ImageSku>();
		if (currentImageSku)
		{
			currentImageSku.RenderRotation(0.0);
			this->RestoreControls();
		}
	}

	Windows::Foundation::IAsyncAction DetailPage::Edit_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		co_return;
	}

	Windows::Foundation::IAsyncAction DetailPage::InformationAppBarButton_ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		//auto dataPackage = DataPackage{};

		//RenderTargetBitmap renderTargetBitmap{};
		//co_await renderTargetBitmap.RenderAsync(Display());

		//IBuffer pixelBuffer = co_await renderTargetBitmap.GetPixelsAsync();
		//auto softwareBitmap = SoftwareBitmap::CreateCopyFromBuffer
		//(pixelBuffer, BitmapPixelFormat::Bgra8, 1024,768);

		//auto softwareBitmapsource = SoftwareBitmapSource{};
		//auto correctSB = softwareBitmap.Convert(softwareBitmap, BitmapPixelFormat::Bgra8, BitmapAlphaMode::Premultiplied);
		//softwareBitmapsource.SetBitmapAsync(correctSB);
		//this->testBrush().ImageSource(renderTargetBitmap);
		//this->test().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);


		//auto ms = InMemoryRandomAccessStream();
		//{
		//	BitmapEncoder encoder = co_await BitmapEncoder::CreateAsync(BitmapEncoder::JpegEncoderId(), ms);
		//	encoder.SetSoftwareBitmap(softwareBitmap);

		//	try
		//	{
		//		co_await encoder.FlushAsync();
		//	}
		//	catch (...) {}

		//	dataPackage.SetBitmap(RandomAccessStreamReference::CreateFromStream(ms));

		//	Clipboard::SetContent(dataPackage);
		//	//array = new byte[ms.Size];
		//	//co_await ms.ReadAsync(array.AsBuffer(), (uint)ms.Size, InputStreamOptions.None);
		//}
		// COMMENT OUT EXACTLY ONE OF TECHNIQUE 1/2
		// TECHNIQUE 1; QI for IBufferByteAccess.
		//auto bufferByteAccess{ pixelBuffer.as<::IBufferByteAccess>() };
		//uint8_t * pTargetBytes{ nullptr };
		//bufferByteAccess->Buffer(&pTargetBytes);
		//// TECHNIQUE 2; use a C++/WinRT helper function (and delete the definition of IBufferByteAccess in pch.h).
		////uint8_t * pTargetBytes{ m_writeableBitmap.PixelBuffer().data() };
		//std::vector<uint8_t> dst;
		//for (auto i=0;i<100*100*4;++i)
		//{
		//	dst.push_back(*(pTargetBytes++));
		//}


		//anyExampleImage().Source(m_writeableBitmap);
		co_return;
	}

	void DetailPage::BlurAmountSlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bsh().BlurAmount(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}

	void DetailPage::ExposureSlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bshexp().Exposure(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}
	void DetailPage::SaturationSlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bshsat().Saturation(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}
	void DetailPage::SepiaIntensitySlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bshsep().Intensity(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}
	void DetailPage::TemperatureSlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bshtemp().Temperature(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}
	void DetailPage::TintSlider_ValueChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const&)
	{
		//this->ConcentrateControls();
		auto slider = sender.try_as<Windows::UI::Xaml::Controls::Slider>();
		if (slider)
			this->bshtemp().Tint(slider.Value());
		//auto fillBrush = this->BackdropBlur_Rectangle().Fill();
	}

}
