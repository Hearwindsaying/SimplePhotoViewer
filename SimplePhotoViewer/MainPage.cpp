#include "pch.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

#include "Utility.h"
#include "MainPage.h"

#include "ImageSku.h"
#include "DirectoryItem.h"

namespace winrt::SimplePhotoViewer::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
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
		/*this->myButton().Content(box_value(L"Clicked"));*/
		using TreeViewNode = Microsoft::UI::Xaml::Controls::TreeViewNode;
		using StorageFolder = Windows::Storage::StorageFolder;

		/*Tests for TreeView control*/
		
		StorageFolder rootFolder = co_await StorageFolder::GetFolderFromPathAsync(L"D:\\");

		auto subFolderDirectoryItemsToRoot = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
		auto rootHardDiskDriverDirectoryItem = winrt::make<DirectoryItem>(hstring(L"软件(D:)"), subFolderDirectoryItemsToRoot, rootFolder);
		this->m_treeViewFolders.Append(rootHardDiskDriverDirectoryItem);
		//StorageFolder subFolder1 = co_await StorageFolder::GetFolderFromPathAsync(L"D:\\Download");

		//auto subFoldersToRoot = co_await rootFolder.GetFoldersAsync();
		//
		//
		//StorageFolder subFolder2 = subFoldersToRoot.GetAt(0);

		//subFolderDirectoryItemsToRoot.Append(winrt::make<DirectoryItem>(subFolder2.Name(), subFolder2));
		///*for (auto subFolder : subFoldersToRoot)
		//{
		//	SimplePhotoViewer::DirectoryItem subFolderDirectoryItem = winrt::make<DirectoryItem>(subFolder.Name(), subFolder);
		//	subFolderDirectoryItemsToRoot.Append(subFolderDirectoryItem);
		//}*/
		//subFolderDirectoryItemsToRoot.Append(winrt::make<DirectoryItem>(subFolder1.Name(), subFolder1));
		


		/*Tests for TreeView control*/


		/*auto treeViewRootNodes = this->DirectoryTreeView().RootNodes();

		auto sizet = treeViewRootNodes.Size();
		for (const auto& treeViewRootNodeRaw : treeViewRootNodes)
		{
			auto treeViewRootNode = treeViewRootNodeRaw.try_as<TreeViewNode>();

			if (treeViewRootNode)
			{
				auto myContent = treeViewRootNode.HasChildren();
			
			}
		}*/

		wchar_t testchar[20] = { '6','6','e' };
		OutputDebugString(testchar);
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
		if (this->m_imageSkus.Size() == 0)
		{
			auto defaultFolder = co_await this->LoadDefaultFolder();

			Windows::Storage::Search::QueryOptions options{};
			options.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);
			options.FileTypeFilter().Append(L".jpg");
			options.FileTypeFilter().Append(L".png");


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
			wchar_t testchar[20] = { '6','6','e' };
			OutputDebugString(testchar);
		}
	}
	
	Windows::Foundation::IAsyncAction MainPage::DirectoryItem_Expanding(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewExpandingEventArgs const args)
	{
		using StorageFolder = Windows::Storage::StorageFolder;
		SimplePhotoViewer::DirectoryItem expandingItem = args.Item().try_as<SimplePhotoViewer::DirectoryItem>();
		if (expandingItem)
		{
			auto itemFolder = expandingItem.ItemFolder();
			auto subfolders = co_await itemFolder.GetFoldersAsync();
			if (!subfolders.Size())
			{
				args.Node().HasUnrealizedChildren(false);
			}
			else
			{
				args.Node().HasUnrealizedChildren(true);

				for (auto singlefolder : subfolders)
				{
					//todo:perhaps getFoldersAsync again to set its hasunrealizedchildren property.
					expandingItem.SubItems().Append(winrt::make<DirectoryItem>(singlefolder.Name(), singlefolder));
				}
			}
		}
	}
	void MainPage::DirectoryItem_Collapsed(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewCollapsedEventArgs const args)
	{
		using StorageFolder = Windows::Storage::StorageFolder;
		SimplePhotoViewer::DirectoryItem collapsedItem = args.Item().try_as<SimplePhotoViewer::DirectoryItem>();
		if (collapsedItem)
		{
			collapsedItem.SubItems().Clear();
		}
	}
	Windows::Foundation::IAsyncAction MainPage::DirectoryItem_Invoked(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const args)
	{
		auto itemFolder = args.InvokedItem().try_as<SimplePhotoViewer::DirectoryItem>().ItemFolder();
		this->currentSelectedFolderPathName = itemFolder.Path();
		this->CurrentSelectedFolder(itemFolder.Name());

		this->m_imageSkus.Clear();

		auto defaultFolder = co_await this->LoadDefaultFolder();

		Windows::Storage::Search::QueryOptions options{};
		options.FolderDepth(Windows::Storage::Search::FolderDepth::Shallow);
		options.FileTypeFilter().Append(L".jpg");
		options.FileTypeFilter().Append(L".png");


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
	
	void MainPage::GridViewItem_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		auto selectedNum = this->ImageGridView().SelectedItems().Size();
		this->CurrentFolderSelectedImageNumber(selectedNum);
		this->DeleteButton().IsEnabled(selectedNum ? true : false);
	}

	Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> MainPage::LoadDefaultFolder()
	{
		//std::wstring level2FolderName{ L"D:\\Project\\TestResource" };

		/*Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(level2FolderName) };*/
		Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(this->currentSelectedFolderPathName) };

		return folder;
	}



}
