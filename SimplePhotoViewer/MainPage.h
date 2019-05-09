﻿#pragma once

#include "MainPage.g.h"
#include "Utility.h"
#include "PageNavigationParameter.h"
#include "ExplorerItemTemplateSelector.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus() const;

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> TreeViewFolders() const;

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainPage::BufferImageSkus() const; //-
	
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> SearchResults() const
		{
			return this->m_searchResults;
		}

		hstring CurrentSelectedFolder() const
		{
			return this->m_currentSelectedFolderName;
		}
		void CurrentSelectedFolder(hstring const& value)
		{
			this->m_currentSelectedFolderName = value;
			this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CurrentSelectedFolder" });
		}

		uint32_t CurrentFolderImageNumber() const
		{
			return this->m_currentFolderImageNumber;
		}
		uint32_t CurrentFolderSelectedImageNumber() const
		{
			return this->m_currentFolderSelectedImageNumber;
		}

		void SplitViewButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) {}

		void ParentFolderButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) {}

		Windows::Foundation::IAsyncAction Copy_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{
			Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
			contentDialog.PrimaryButtonText(L"复制");
			contentDialog.CloseButtonText(L"取消");
			contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
			if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
				return;
			WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);
			this->m_bufferImageSkus.Clear();
			auto currentSelectedItems = this->ImageGridView().SelectedItems();
			//auto deleteCounter = 0;

			auto totalDelteTimes = currentSelectedItems.Size();
			auto imageSku = currentSelectedItems.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
			this->m_bufferImageSkus.Append(imageSku);
		}
		void Shear_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) {}
		Windows::Foundation::IAsyncAction Paste_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
			contentDialog.PrimaryButtonText(L"粘贴");
			contentDialog.CloseButtonText(L"取消");
			contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
			if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
				return;
			WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);

			auto currentSelectedItems = this->ImageGridView().SelectedItems();

			auto imageSku = this->m_bufferImageSkus.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
			winrt::Windows::Storage::IStorageFolder filefold;
			hstring copyFileName = imageSku.ImageNameWithType();

			Windows::Storage::StorageFolder targetFolder = co_await this->LoadDefaultFolder();
			imageSku.ImageFile().CopyAsync(targetFolder, copyFileName, Windows::Storage::NameCollisionOption::GenerateUniqueName);
			//winrt::Microsoft::UI::Xaml::Controls::TreeViewItem args;
			//args.TreeViewItemInvokedEventArgs args;
			this->m_imageSkus.Append(imageSku);
			this->m_imageSkus = single_threaded_observable_vector<Windows::Foundation::IInspectable>();


			currentSelectedItems.Clear();
		}
		Windows::Foundation::IAsyncAction Rename_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{
			Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
			contentDialog.Title(box_value(L"确认修改为" + this->nameInput().Text()));
			contentDialog.CloseButtonText(L"取消");
			contentDialog.PrimaryButtonText(L"确认");
			contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
			if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
				return;
			WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);

			auto currentSelectedItems = this->ImageGridView().SelectedItems();
			//auto deleteCounter = 0;

			auto TotalTimes = currentSelectedItems.Size();
			auto imageSku = currentSelectedItems.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
			auto index = currentSelectedItems.GetAt(0);

			//enum class winrt::Windows::Storage::NameCollisionOption::GenerateUniqueName;
			imageSku.ImageFile().RenameAsync(this->nameInput().Text() + L".jpg", Windows::Storage::NameCollisionOption::GenerateUniqueName);
			imageSku.ImageName(this->nameInput().Text());
			imageSku.ImageFileType(L"jpg");
			imageSku.ImageNameWithType(this->nameInput().Text() + L".jpg");
			for (auto renameCounter = 1; renameCounter <= TotalTimes; ++renameCounter)
			{
				auto imageSku = currentSelectedItems.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
				auto curItem = currentSelectedItems.GetAt(0);
				auto curItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [curItem](auto const& item)->bool
				{
					return item == curItem;
				});
				this->m_imageSkus.SetAt(curItemIndex, imageSku);
				//currentSelectedItems.RemoveAt(deleteCounter++);
			}
			currentSelectedItems.Clear();
		}
		Windows::Foundation::IAsyncAction OpenFile_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
		void SlidePlay_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{
			/*Get the first selected item index*/
			/*auto curItem = this->ImageGridView().SelectedItems().GetAt(0);
			auto curItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [curItem](auto const& item)->bool
			{
				return item == curItem;
			});*/
			auto curIndex = this->ImageGridView().SelectedIndex();
			if (curIndex == -1)
				//select the first item of m_imageSkus
				curIndex = 0;
			auto pageParameter = make<PageNavigationParameter>(this->m_imageSkus, curIndex);//get -1 while selected item is empty
			Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::DetailPage>(), pageParameter);
		}
		Windows::Foundation::IAsyncAction Delete_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);

		void SearchBox_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void SearchBox_SuggestionChosen(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		void SearchBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);

		Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e);
		Windows::Foundation::IAsyncAction DirectoryItem_Expanding(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewExpandingEventArgs const args);
		void DirectoryItem_Collapsed(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewCollapsedEventArgs const args);
		Windows::Foundation::IAsyncAction DirectoryItem_Invoked(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const args);

		void SelectionListView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e){}

		void GridViewItem_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void GridViewItem_DoubleTapped(winrt::Windows::Foundation::IInspectable const& , Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e)
		{
			auto curIndex = this->ImageGridView().SelectedIndex();
			if (curIndex == -1)
				//select the first item of m_imageSkus
				curIndex = 0;
			auto pageParameter = make<PageNavigationParameter>(this->m_imageSkus, curIndex);//get -1 while selected item is empty
			Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::DetailPage>(), pageParameter);
			e.Handled(true);
		}

		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
		{
			return this->m_propertyChanged.add(handler);
		}
		void PropertyChanged(winrt::event_token const& token) noexcept
		{
			this->m_propertyChanged.remove(token);
		}

		void Windows_MouseDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void Windows_MouseHold(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void Windows_MouseUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void InitDragSelectionRect(winrt::Windows::Foundation::Point const& p1, winrt::Windows::Foundation::Point const& p2);
		void UpdateDragSelectionRect(winrt::Windows::Foundation::Point const& pt1, winrt::Windows::Foundation::Point const& pt2);
		void ApplyDragSelectionRect();
	private:
		Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> LoadDefaultFolder();
		Windows::Foundation::IAsyncAction FillTreeNodes(Microsoft::UI::Xaml::Controls::TreeViewNode const node);

		Windows::Foundation::IAsyncAction RefreshCurrentFolder(Windows::Storage::StorageFolder const storageFolder);

		/*TODO:should author and cosume relevant event for elegance.*/
		void CurrentFolderImageNumber(uint32_t value)
		{
			this->m_currentFolderImageNumber = value;
			this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CurrentFolderImageNumber" });
		}

		void CurrentFolderSelectedImageNumber(uint32_t value)
		{
			this->m_currentFolderSelectedImageNumber = value;
			this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CurrentFolderSelectedImageNumber" });
		}

		

	private:
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_imageSkus{ nullptr };
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_treeViewFolders{ nullptr };

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_bufferImageSkus{ nullptr };

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_searchResults{ nullptr };

		hstring currentSelectedFolderPathName;
		hstring m_currentSelectedFolderName;
		int32_t m_currentFolderImageNumber = 0;
		int32_t m_currentFolderSelectedImageNumber = 0;

		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

		bool isLeftMouseButtonDownOnWindow = false;
		bool isDraggingSelectionRect = false;
		Windows::UI::Input::PointerPoint origMouseDownPoint{ nullptr };
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
