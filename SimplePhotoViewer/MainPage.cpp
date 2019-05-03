#include "pch.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>

#include <winrt/Windows.UI.Core.h>
#include <chrono>
#include <ppltasks.h>
#include <ppl.h>

#include "Utility.h"
#include "MainPage.h"

#include "ImageSku.h"
#include "DirectoryItem.h"
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Input.h>

using namespace std::chrono;

namespace winrt::SimplePhotoViewer::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();

		auto coreTitleBar = Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar();//获取应用程序的活动视图->的标题栏对象//获取的是一个CoreApplicationViewTitleBar对象，主要控制标题栏相关功能。
		auto appTitleBar = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();//获取的是一个ApplicationViewTitleBar对象，主要用于控制标题栏显示样式。
		coreTitleBar.ExtendViewIntoTitleBar(true);//标题栏对象里面的扩充标题栏属性
		Windows::UI::Xaml::Window::Current().SetTitleBar(this->RealFolderPath_Grid());//文件夹名那一栏就可以正常拖拽

		this->m_imageSkus = single_threaded_observable_vector<Windows::Foundation::IInspectable>();
		this->m_treeViewFolders = single_threaded_observable_vector<Windows::Foundation::IInspectable>();
		this->currentSelectedFolderPathName = L"D:\\Project\\TestResource";
		//this->currentSelectedFolderPathName = L"D:\\";
		this->m_currentSelectedFolderName = L"TestResource";
		//auto defaultFolder = this->LoadDefaultFolder();
	}

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainPage::ImageSkus() const 
    {
		return this->m_imageSkus;
    }
	void MainPage::ImageSkus(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value)
	{
		this->m_imageSkus = value;
		this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ImageSkus" });
	}

	Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainPage::TreeViewFolders() const
	{
		return this->m_treeViewFolders;
	}

	Windows::Foundation::IAsyncAction MainPage::ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const)
	{
		co_return;
		//using TreeViewNode = Microsoft::UI::Xaml::Controls::TreeViewNode;
		//using StorageFolder = Windows::Storage::StorageFolder;

		///*Tests for TreeView control*/

		////try
		////{
		////	StorageFolder rootFolder2 = co_await StorageFolder::GetFolderFromPathAsync(L"I:\\");
		////}
		////catch (winrt::hresult_error const& ex)
		////{
		////	winrt::hresult hr = ex.to_abi(); // HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND).
		////	winrt::hstring message = ex.message();
		////}
		//{
		//	for (auto curDiskName = 'C'; curDiskName <= 'Z'; ++curDiskName)
		//	{
		//		auto validlstr_tmp = std::wstring(1, curDiskName) + L":\\";

		//		StorageFolder rootFolder = co_await StorageFolder::GetFolderFromPathAsync(validlstr_tmp);
		//		auto subFolderDirectoryItemsToRoot = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
		//		auto friendlyName = rootFolder.DisplayName();

		//		auto rootHardDiskDriverDirectoryItem = winrt::make<DirectoryItem>(friendlyName, subFolderDirectoryItemsToRoot, rootFolder);
		//		this->m_treeViewFolders.Append(rootHardDiskDriverDirectoryItem);

		//	}
		//	
		//}
		//wchar_t testchar[20] = { '6','6','e' };
		//OutputDebugString(testchar);
	}
	void MainPage::PlayButton_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::DetailPage>(), this->m_imageSkus);
	}
	Windows::Foundation::IAsyncAction MainPage::DeleteButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
		contentDialog.Title(box_value(L"删除选中的图片文件"));
		contentDialog.Content(box_value(L"所选中的图片文件将被删除到回收站中"));
		contentDialog.CloseButtonText(L"取消");
		contentDialog.PrimaryButtonText(L"删除");
		contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

		Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
		if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
			return;
		WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);


		auto currentSelectedItems = this->ImageGridView().SelectedItems();
		//auto deleteCounter = 0;

		auto totalDelteTimes = currentSelectedItems.Size();
		for (auto deleteCounter = 1; deleteCounter <= totalDelteTimes; ++deleteCounter)
		{
			auto imageSku = currentSelectedItems.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
			imageSku.ImageFile().DeleteAsync();
			auto curItem = currentSelectedItems.GetAt(0);
			auto curItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [curItem](auto const& item)->bool
			{
				return item == curItem;
			});
			this->m_imageSkus.RemoveAt(curItemIndex);
			//currentSelectedItems.RemoveAt(deleteCounter++);
		}
		//for (const auto& curItem : currentSelectedItems)
		//{
		//	auto imageSku = curItem.try_as<SimplePhotoViewer::ImageSku>();
		//	imageSku.ImageFile().DeleteAsync();
		//	auto curItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [curItem](auto const& item)->bool
		//	{
		//		return item == curItem;
		//	});
		//	//this->m_imageSkus.RemoveAt(curItemIndex);
		//	//currentSelectedItems.RemoveAt(deleteCounter++);
		//}
		currentSelectedItems.Clear();
	}

	void MainPage::SearchBox_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
		using AutoSuggestionBoxTextChangeReason = Windows::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason;
		if (sender.Text() == L"")
			if (this->ImageGridView().ItemsSource() != this->m_imageSkus)
				this->ImageGridView().ItemsSource(this->m_imageSkus);


		if (args.Reason() == AutoSuggestionBoxTextChangeReason::UserInput)
		{
			//perform searching and update corresponding ItemSource
			this->m_searchResults = single_threaded_observable_vector<Windows::Foundation::IInspectable>();
			SimplePhotoViewer::find_all(this->m_imageSkus.First(), 
				[sender](Windows::Foundation::IInspectable const& imageSku)->bool
				{
					auto imageSkuItem = imageSku.try_as<SimplePhotoViewer::ImageSku>();
					std::wstring_view imageName = imageSkuItem.ImageName();
					std::wstring_view searchText = sender.Text();
					auto it = std::search(imageName.begin(), imageName.end(),
						std::boyer_moore_searcher(
							searchText.begin(), searchText.end()));
					if (imageSkuItem)
					{
						/*return imageSkuItem.ImageName() == sender.Text();*/
						return it != imageName.end();
					}
					return false;
				},
				this->m_searchResults);
			//this->SearchAutoSuggetsBox().ItemsSource(results);

			if (this->m_searchResults.Size())
			{
				this->SearchAutoSuggetsBox().ItemsSource(this->m_searchResults);
			}
			else
			{
				/*Alternatively, we could use TemplateSelector*/
				auto tipVector = single_threaded_observable_vector<Windows::Foundation::IInspectable>();
				tipVector.Append(make<ImageSku>(L"无法找到结果"));
				this->SearchAutoSuggetsBox().ItemsSource(tipVector);
			}
			
		}
		/*else if (args.Reason() == AutoSuggestionBoxTextChangeReason::SuggestionChosen)
		{
			wchar_t testchar[20] = { 's','g','c' };
			OutputDebugString(testchar);
		}*/
	}

	void MainPage::SearchBox_SuggestionChosen(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
	{
		auto selectedResult = args.SelectedItem().try_as<SimplePhotoViewer::ImageSku>();
		if (selectedResult)
		{
			if (selectedResult.ImageNameWithType() == L"无法找到结果")
				return;
			sender.Text(selectedResult.ImageNameWithType());
		}
	}

	void MainPage::SearchBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args)
	{
		//you need to raise propertyChanged event or UI won't get responsed;
		//failed using:
		//this->ImageSkus(this->searchResults);
		//this->m_imageSkus = this->searchResults;
		/*auto test = this->m_searchResults;
		
		this->ImageSkus(test);*/
		this->ImageGridView().ItemsSource(this->m_searchResults);
	}


	void MainPage::Node_ClickHandler(Microsoft::UI::Xaml::Controls::TreeView const&, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& args)
	{
		auto myContent = args.try_as<winrt::Microsoft::UI::Xaml::Controls::TreeViewNode>();
	}

	Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e)
	{
		if (this->m_treeViewFolders.Size() == 0)
		{
			using StorageFolder = Windows::Storage::StorageFolder;
			for (auto curDiskName = 'C'; curDiskName <= 'H'; ++curDiskName)
			{
				auto validlstr_tmp = std::wstring(1, curDiskName) + L":\\";

				StorageFolder rootFolder = co_await StorageFolder::GetFolderFromPathAsync(validlstr_tmp);
				
				auto subFolderDirectoryItemsToRoot = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
				auto friendlyName = rootFolder.DisplayName();
				auto rootHardDiskDriverDirectoryItem = winrt::make<DirectoryItem>(friendlyName, subFolderDirectoryItemsToRoot, rootFolder);
				this->m_treeViewFolders.Append(rootHardDiskDriverDirectoryItem);
			}

			for (const auto& rootNode : this->DirectoryTreeView().RootNodes())
			{
				//rootNode.IsExpanded(true);
				rootNode.HasUnrealizedChildren(true);
				/*co_await this->FillTreeNodes(rootNode);*/
			}
		}

		//if (this->m_imageSkus.Size() == 0)
		//{
		//	auto defaultFolder = co_await this->LoadDefaultFolder();

		//	Windows::Storage::Search::QueryOptions options{};
		//	options.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);
		//	options.FileTypeFilter().Append(L".jpg");
		//	options.FileTypeFilter().Append(L".png");
		//	options.FileTypeFilter().Append(L".bmp");
		//	options.FileTypeFilter().Append(L".tif");
		//	options.FileTypeFilter().Append(L".gif");


		//	auto result = defaultFolder.CreateFileQueryWithOptions(options);
		//	auto imageFiles = co_await result.GetFilesAsync();
		//	this->CurrentFolderImageNumber(imageFiles.Size());

		//	//// Populate Photos collection.
		//	for (auto&& file : imageFiles)
		//	{
		//		auto imageProperties = co_await file.Properties().GetImagePropertiesAsync();


		//		auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem);
		//		//or:auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
		//		Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
		//		bitmapImage.SetSource(thumbnail);
		//		thumbnail.Close();
		//		auto imageSku = winrt::make<ImageSku>(imageProperties, file, file.DisplayName(), file.DisplayType(), bitmapImage, file.Name());

		//		/*Windows::Storage::Streams::IRandomAccessStream stream{ co_await file.OpenAsync(Windows::Storage::FileAccessMode::Read) };
		//		Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
		//		bitmap.SetSource(stream);
		//		imageSku.ImageContent(bitmap);*/



		//		this->ImageSkus().Append(imageSku);


		//	}
		//	wchar_t testchar[20] = { '6','6','e' };
		//	OutputDebugString(testchar);
		//}
	}
	
	/*Refresh current displaying folder using specified storageFolder*/
	/*See also:DirectoryItem_Invoked()*/
	Windows::Foundation::IAsyncAction MainPage::RefreshCurrentFolder(Windows::Storage::StorageFolder const storageFolder)
	{
		this->m_imageSkus.Clear();

		auto defaultFolder = co_await this->LoadDefaultFolder();

		Windows::Storage::Search::QueryOptions options{};
		options.FolderDepth(Windows::Storage::Search::FolderDepth::Shallow);
		options.FileTypeFilter().Append(L".jpg");
		options.FileTypeFilter().Append(L".png");
		options.FileTypeFilter().Append(L".bmp");
		options.FileTypeFilter().Append(L".tif");
		options.FileTypeFilter().Append(L".gif");


		auto result = defaultFolder.CreateFileQueryWithOptions(options);
		auto imageFiles = co_await result.GetFilesAsync();

		this->CurrentFolderImageNumber(imageFiles.Size());

		//// Populate Photos collection.
		for (auto&& file : imageFiles)
		{
			auto imageProperties = co_await file.Properties().GetImagePropertiesAsync();


			auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem);
			//or:auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
			bitmapImage.SetSource(thumbnail);
			thumbnail.Close();

			auto imageSku = winrt::make<ImageSku>(imageProperties, file, file.DisplayName(), file.DisplayType(), bitmapImage, file.Name());

			/*Windows::Storage::Streams::IRandomAccessStream stream{ co_await file.OpenAsync(Windows::Storage::FileAccessMode::Read) };
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmap{};
			bitmap.SetSource(stream);
			imageSku.ImageContent(bitmap);*/
			this->ImageSkus().Append(imageSku);
		}
	}

	Windows::Foundation::IAsyncAction MainPage::DirectoryItem_Expanding(Windows::UI::Xaml::Controls::TreeView const sender, Windows::UI::Xaml::Controls::TreeViewExpandingEventArgs const args)
	{
		using StorageFolder = Windows::Storage::StorageFolder;
		SimplePhotoViewer::DirectoryItem expandingItem = args.Item().try_as<SimplePhotoViewer::DirectoryItem>();
		
		/*if (args.Node().HasUnrealizedChildren())
		{
			co_await this->FillTreeNodes(args.Node());
		}*/
		
		if (expandingItem)
		{
			expandingItem.SubItems().Clear();
			
			//expandingItem.SubItems(single_threaded_observable_vector<Windows::Foundation::IInspectable>());
			auto itemFolder = expandingItem.ItemFolder();
			try
			{
				auto subfolders_feedOp = itemFolder.GetFoldersAsync();
				/*auto subfolders = co_await subfolders_feedOp;*/
				/*create_task([] {
					return DoWork().get();
				}).get();*/
				auto subfolders = concurrency::create_task([&subfolders_feedOp] {return subfolders_feedOp.get(); }).get();
				//auto subfolders = subfolders_feedOp.get();

				if (!subfolders.Size())
				{
					args.Node().HasUnrealizedChildren(false);
				}
				else
				{
					args.Node().HasUnrealizedChildren(true);

					auto itemContainer = this->DirectoryTreeView().ContainerFromItem(expandingItem);
					
					
					for (auto j = 0; j < subfolders.Size(); ++j)
					{
						const auto& singlefolder = subfolders.GetAt(j);
						//todo:perhaps getFoldersAsync again to set its hasunrealizedchildren property.
						auto subDirectoryItem = winrt::make<DirectoryItem>(singlefolder.Name(), singlefolder);
						
						expandingItem.SubItems().Append(subDirectoryItem);
						
						//expandingItem.SubItems(expandingItem.SubItems());
						/*co_await 1ms;

						co_await winrt::resume_foreground(this->DirectoryTreeView().Dispatcher());*/

						//auto nodeFromContainer = this->DirectoryTreeView().NodeFromContainer(itemContainer);
						//if (nodeFromContainer)
						//{
						//	auto childrenNodes = nodeFromContainer.Children();

						//	for (auto i = 0; i < childrenNodes.Size(); ++i)
						//	{
						//		auto subTreeViewNode = childrenNodes.GetAt(i);
						//		
						//		auto subDirectoryItem = subTreeViewNode.Content().try_as<SimplePhotoViewer::DirectoryItem>();
						//		auto subDirectoryItemFolder = subDirectoryItem.ItemFolder();
						//		if (subDirectoryItem)
						//		{
						//			/*auto secondaryFolders = concurrency::create_task(
						//				[&subDirectoryItemFolder]
						//				{
						//					return subDirectoryItemFolder.GetFoldersAsync().get();
						//				}).get();*/
						//			auto secondaryFolders = co_await subTreeViewNode.Content().try_as<SimplePhotoViewer::DirectoryItem>().ItemFolder().GetFoldersAsync();
						//			if (secondaryFolders.Size() != 0)
						//				subTreeViewNode.HasUnrealizedChildren(true);
						//		}
						//		
						//	}
						//}
					}
				}
			}
			catch(hresult_error const& ex)
			{
				HRESULT hr = ex.to_abi();
				hstring message = ex.message();
			}

		}
		co_return;
	}
	void MainPage::DirectoryItem_Collapsed(Windows::UI::Xaml::Controls::TreeView const sender, Windows::UI::Xaml::Controls::TreeViewCollapsedEventArgs const args)
	{
		using StorageFolder = Windows::Storage::StorageFolder;
		args.Node().Children().Clear();
		args.Node().HasUnrealizedChildren(true);
		//SimplePhotoViewer::DirectoryItem collapsedItem = args.Item().try_as<SimplePhotoViewer::DirectoryItem>();
		//if (collapsedItem)
		//{
		//	//collapsedItem.SubItems().Clear();
		//	/*args.Node().HasUnrealizedChildren(true);*/
		//}
	}
	Windows::Foundation::IAsyncAction MainPage::DirectoryItem_Invoked(Windows::UI::Xaml::Controls::TreeView const sender, Windows::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const args)
	{
		auto itemContainer = this->DirectoryTreeView().ContainerFromItem(args.InvokedItem());
		if (itemContainer)
		{
			auto node = this->DirectoryTreeView().NodeFromContainer(itemContainer);
			node.IsExpanded(!node.IsExpanded());
		}
		else
		{
			wchar_t testchar[20] = { 'e','r','3' };
			OutputDebugString(testchar);
		}

		auto itemFolder = args.InvokedItem().try_as<SimplePhotoViewer::DirectoryItem>().ItemFolder();
		this->currentSelectedFolderPathName = itemFolder.Path();
		this->CurrentSelectedFolder(itemFolder.Name());

		co_await this->RefreshCurrentFolder(nullptr);

	}
	
	void MainPage::GridViewItem_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		auto selectedNum = this->ImageGridView().SelectedItems().Size();
		this->CurrentFolderSelectedImageNumber(selectedNum);
		this->DeleteButton().IsEnabled(selectedNum ? true : false);
	}

	/*Load current folder selected by TreeViewItem*/
	Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> MainPage::LoadDefaultFolder()
	{
		//std::wstring level2FolderName{ L"D:\\Project\\TestResource" };

		/*Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(level2FolderName) };*/
		Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(this->currentSelectedFolderPathName) };

		return folder;
	}

	Windows::Foundation::IAsyncAction MainPage::FillTreeNodes(Windows::UI::Xaml::Controls::TreeViewNode const node/*, Windows::UI::Xaml::Controls::TreeViewItem const item*/)
	{
		using StorageFolder = Windows::Storage::StorageFolder;
		if (node.HasUnrealizedChildren())
		{
			auto nodeContainer = this->DirectoryTreeView().ContainerFromNode(node);
			if (nodeContainer)
			{
				auto treeViewItem = this->DirectoryTreeView().ItemFromContainer(nodeContainer);
				auto directoryItem = treeViewItem.try_as<SimplePhotoViewer::DirectoryItem>();

				if (directoryItem)
				{
					StorageFolder storageFolder = directoryItem.ItemFolder();
					auto folderList = co_await storageFolder.GetFoldersAsync();
					if (!folderList.Size())
						return;

					for (const auto& folder : folderList)
					{
						auto subFolderDirectoryItemsToRoot = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
						auto friendlyName = folder.DisplayName();
						auto subDirectoryItem = winrt::make<DirectoryItem>(friendlyName, subFolderDirectoryItemsToRoot, folder);
						directoryItem.SubItems().Append(subDirectoryItem);
					}

					for (const auto& subDirectoryItem : node.Children())
					{
						subDirectoryItem.HasUnrealizedChildren(true);
					}

					node.HasUnrealizedChildren(false);
				}
				else
				{
					wchar_t testchar[20] = { 'e','r','1' };
					OutputDebugString(testchar);
					return;
				}
			}
			else
			{
				wchar_t testchar[20] = { 'e','r','r' };
				OutputDebugString(testchar);
				return;
			}
		}
		else
		{
			return;
		}
	}


	void MainPage::Windows_MouseDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
	{
		this->isLeftMouseButtonDownOnWindow = true;
		this->origMouseDownPoint = e.GetCurrentPoint(this->PointerDetectedGrid());
		e.Handled(true);
	}
	void MainPage::Windows_MouseHold(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
	{
		if (this->isDraggingSelectionRect)
		{
			//
			// Drag selection is in progress.
			//
			auto curMouseDownPoint = e.GetCurrentPoint(this->PointerDetectedGrid());
			this->UpdateDragSelectionRect(this->origMouseDownPoint.Position(), curMouseDownPoint.Position());
		}
		else if (this->isLeftMouseButtonDownOnWindow)
		{
			/*helper functions*/
			struct float2 { float x, y; };
			auto make_float2 = [](const float x, const float y)->float2
			{
				float2 result;
				result.x = x;
				result.y = y;
				return result;
			};
			auto dot = [](const float2 &a, const float2 &b)->float
			{
				return a.x*b.x + a.y*b.y;
			};
			auto length = [dot](const float2 & v)->float
			{
				return sqrtf(dot(v, v));
			};

			auto curMouseDownPoint = e.GetCurrentPoint(this->PointerDetectedGrid());
			auto dragDelta = make_float2(curMouseDownPoint.Position().X - this->origMouseDownPoint.Position().X,
				curMouseDownPoint.Position().Y - this->origMouseDownPoint.Position().Y);
			auto dragDistance = length(dragDelta);

			if (dragDistance > 1.f)
			{
				this->isDraggingSelectionRect = true;
				//todo:delete me
				//this->ImageGridView().DeselectRange(ItemIndexRange(0,ImageGridView().Length());
				this->InitDragSelectionRect(this->origMouseDownPoint.Position(), curMouseDownPoint.Position());
			}

		}
		e.Handled(true);
	}
	void MainPage::Windows_MouseUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
	{
		if (this->isDraggingSelectionRect)
		{
			this->isDraggingSelectionRect = false;
			this->ApplyDragSelectionRect();
			e.Handled(true);
		}
		if (this->isLeftMouseButtonDownOnWindow)
		{
			this->isLeftMouseButtonDownOnWindow = false;
			e.Handled(true);
		}
	}

	void MainPage::ApplyDragSelectionRect()
	{
		this->dragSelectionCanvas().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

		double width = this->dragSelectionBorder().Width();
		double height = this->dragSelectionBorder().Height();

		auto rectTransform = this->dragSelectionBorder().TransformToVisual(nullptr);
		Windows::Foundation::Point rectCoords = rectTransform.TransformPoint(Windows::Foundation::Point(0, 0));

		Windows::Foundation::Rect dragRect{ rectCoords.X, rectCoords.Y, (float)width, (float)height };

		this->ImageGridView().SelectedItems().Clear();

		for (auto i = 0; i < this->ImageGridView().Items().Size(); ++i)
		{
			auto selectorItem = this->ImageGridView().ContainerFromIndex(i).try_as<Windows::UI::Xaml::Controls::GridViewItem>();
			auto itemTransform = selectorItem.TransformToVisual(nullptr);
			Windows::Foundation::Point itemCoords = itemTransform.TransformPoint(Windows::Foundation::Point(0,0));
			
			double itemheight = selectorItem.ActualHeight();
			double itemwidth = selectorItem.ActualWidth();

			Windows::Foundation::Rect itemRect{ itemCoords.X, itemCoords.Y, (float)itemwidth, (float)itemheight };

			auto intersectedRect = Windows::UI::Xaml::RectHelper::Intersect(dragRect, itemRect);
			if (intersectedRect.Height != 0 || intersectedRect.Width != 0)
			{
				if (!std::isinf(intersectedRect.Height) && !std::isinf(intersectedRect.Width))
				{
					this->ImageGridView().SelectRange(Windows::UI::Xaml::Data::ItemIndexRange(i, 1));
				}
			}
		}
	}


	void MainPage::InitDragSelectionRect(winrt::Windows::Foundation::Point const& p1, winrt::Windows::Foundation::Point const& p2)
	{
		this->UpdateDragSelectionRect(p1, p2);
		this->dragSelectionCanvas().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
	}
	void MainPage::UpdateDragSelectionRect(winrt::Windows::Foundation::Point const& pt1, winrt::Windows::Foundation::Point const& pt2)
	{
		double x, y, width, height;

		//
		// Determine x,y,width and height
		// of the rect inverting the points if necessary.
		// 

		if (pt2.X < pt1.X)
		{
			x = pt2.X;
			width = pt1.X - pt2.X;
		}
		else
		{
			x = pt1.X;
			width = pt2.X - pt1.X;
		}

		if (pt2.Y < pt1.Y)
		{
			y = pt2.Y;
			height = pt1.Y - pt2.Y;
		}
		else
		{
			y = pt1.Y;
			height = pt2.Y - pt1.Y;
		}

		this->dragSelectionCanvas().SetLeft(this->dragSelectionBorder(), x);
		this->dragSelectionCanvas().SetTop(this->dragSelectionBorder(), y);
		this->dragSelectionBorder().Width(width);
		this->dragSelectionBorder().Height(height);
	}
}
