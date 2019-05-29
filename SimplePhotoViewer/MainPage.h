#pragma once

#include "MainPage.g.h"
#include "Utility.h"
#include "PageNavigationParameter.h"
#include "ExplorerItemTemplateSelector.h"

#include <sstream>

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

		void SplitViewButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{ this->splitView().IsPaneOpen(!this->splitView().IsPaneOpen()); }


		Windows::Foundation::IAsyncAction ParentFolderButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{
			Windows::Storage::StorageFolder targetFolder = co_await this->LoadDefaultFolder();
			auto parentFolder = co_await targetFolder.GetParentAsync();
			if (parentFolder)
			{
				Windows::Storage::StorageFolder parentfolder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(parentFolder.Path());
				this->currentSelectedFolderPathName = parentfolder.Path();
				this->CurrentSelectedFolder(parentfolder.Name());
			}

			if (this->refreshCurrentFolder_async)
			{
				if (this->refreshCurrentFolder_async.Status() != Windows::Foundation::AsyncStatus::Completed)
					this->refreshCurrentFolder_async.Cancel();
			}
			this->refreshCurrentFolder_async = this->RefreshCurrentFolder(nullptr);
			co_await this->refreshCurrentFolder_async;
		}

		Windows::Foundation::IAsyncAction Copy_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) 
		{
			Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
			contentDialog.PrimaryButtonText(L"复制");
			contentDialog.CloseButtonText(L"取消");
			contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			//CutFlag = false;
			Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
			if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
				return;
			WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);
			this->m_bufferImageSkus.Clear();
			auto currentSelectedItems = this->ImageGridView().SelectedItems();
			//auto deleteCounter = 0;

			auto totalTimes = currentSelectedItems.Size();
			for (int i = 0; i < totalTimes; i++) {
				auto imageSku = currentSelectedItems.GetAt(i).try_as<SimplePhotoViewer::ImageSku>();
				this->m_bufferImageSkus.Append(imageSku);
			}
		}

		Windows::Foundation::IAsyncAction Paste_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
		{
			/*Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
			contentDialog.PrimaryButtonText(L"粘贴");
			contentDialog.CloseButtonText(L"取消");
			contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
			if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
				return;
			WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);*/

			auto currentSelectedItems = this->ImageGridView().SelectedItems();
			Windows::Storage::StorageFolder targetFolder = co_await this->LoadDefaultFolder();
			for (int i = 0; i < this->m_bufferImageSkus.Size(); i++) {
				auto imageSku = this->m_bufferImageSkus.GetAt(i).try_as<SimplePhotoViewer::ImageSku>();
				hstring copyFileName = imageSku.ImageNameWithType();
				imageSku.ImageFile().CopyAsync(targetFolder, copyFileName, Windows::Storage::NameCollisionOption::GenerateUniqueName);
				this->m_imageSkus.Append(imageSku);

			}

			if (this->refreshCurrentFolder_async)
			{
				if (this->refreshCurrentFolder_async.Status() != Windows::Foundation::AsyncStatus::Completed)
					this->refreshCurrentFolder_async.Cancel();
			}
			this->refreshCurrentFolder_async = this->RefreshCurrentFolder(nullptr);
			co_await this->refreshCurrentFolder_async;

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

			std::stringstream buf1, buf2;
			std::string temp1 = to_string(this->DigitNum().Text());
			std::string temp2 = to_string(this->FirstCode().Text());
			buf1 << temp1;
			buf2 << temp2;
			int firstcode = 0;
			int digitnum = 0;

			auto currentSelectedItems = this->ImageGridView().SelectedItems();
			auto TotalTimes = currentSelectedItems.Size();
			if ((!buf1 >> digitnum) || (!buf2 >> firstcode) || (pow(10, digitnum) - firstcode < TotalTimes)) {
				Windows::UI::Xaml::Controls::ContentDialog contentDialog{};
				contentDialog.Title(box_value(L"输入有误请重新输入"));
				contentDialog.CloseButtonText(L"确认");
				contentDialog.DefaultButton(Windows::UI::Xaml::Controls::ContentDialogButton::Close);

				Windows::UI::Xaml::Controls::ContentDialogResult contentDialogResult = co_await contentDialog.ShowAsync();
				if (contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::None)
					return;
				WINRT_ASSERT(contentDialogResult == Windows::UI::Xaml::Controls::ContentDialogResult::Primary);
			}
			buf1 >> digitnum; buf2 >> firstcode;

			for (int i = 0; i < TotalTimes; ++i)
			{
				auto imageSku = currentSelectedItems.GetAt(0).try_as<SimplePhotoViewer::ImageSku>();
				auto current_ImageFileType = L".jpg";
				hstring Textname = this->nameInput().Text();
				hstring code = L"";
				code = to_hstring(i + firstcode);
				for (int count = code.size(); count < this->DigitNum().Text().size(); count++) {
					Textname = Textname + L"0";
				}
				auto index = currentSelectedItems.GetAt(0);
				imageSku.ImageFile().RenameAsync(Textname + current_ImageFileType, Windows::Storage::NameCollisionOption::GenerateUniqueName);
				imageSku.ImageName(Textname);
				imageSku.ImageFileType(current_ImageFileType);
				imageSku.ImageNameWithType(Textname + current_ImageFileType);
				auto curItemIndex = SimplePhotoViewer::find_index(this->m_imageSkus.First(), [index](auto const& item)->bool
				{
					return item == index;
				});
				this->m_imageSkus.SetAt(curItemIndex, imageSku);
				//currentSelectedItems.RemoveAt(deleteCounter++);
			}
			if (this->refreshCurrentFolder_async)
			{
				if (this->refreshCurrentFolder_async.Status() != Windows::Foundation::AsyncStatus::Completed)
					this->refreshCurrentFolder_async.Cancel();
			}
			this->refreshCurrentFolder_async = this->RefreshCurrentFolder(nullptr);
			co_await this->refreshCurrentFolder_async;

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
		void DirectoryItem_Expanding(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewExpandingEventArgs const args);
		void DirectoryItem_Collapsed(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewCollapsedEventArgs const args);
		Windows::Foundation::IAsyncAction DirectoryItem_Invoked(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const args);

		void SelectionListView_ItemClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
		{
			auto itemStackPanel = e.ClickedItem().try_as<Windows::UI::Xaml::Controls::StackPanel>();
			if (itemStackPanel)
			{
				if (unbox_value<hstring>(itemStackPanel.Tag()) == L"all_select") {
					this->ImageGridView().SelectAll();
				}
				else if (unbox_value<hstring>(itemStackPanel.Tag()) == L"clear_select") {
					this->ImageGridView().SelectedItems().Clear();
				}
				else if (unbox_value<hstring>(itemStackPanel.Tag()) == L"opposite_select") {
					for (auto i = 0; i < this->ImageGridView().SelectedItems().Size(); ++i)
					{
						auto curItem = this->ImageGridView().SelectedItems().GetAt(i).try_as<SimplePhotoViewer::ImageSku>();
						curItem.ImageIsSelected(true);
					}
					this->ImageGridView().SelectedItems().Clear();
					for (auto i = 0; i < this->ImageGridView().Items().Size(); ++i)
					{
						auto this_item = this->ImageGridView().Items().GetAt(i).try_as<SimplePhotoViewer::ImageSku>();
						if (!this_item.ImageIsSelected()) {
							auto is = this_item.ImageIsSelected();
							this->ImageGridView().SelectedItems().Append(this_item);
						}
						else if (this_item.ImageIsSelected())
						{
							this_item.ImageIsSelected(false);
						}
					}
				}
			}
		}

		Windows::Foundation::IAsyncAction OnContainerContentChanging(Windows::UI::Xaml::Controls::ListViewBase sender, Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs args);
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
		//Windows::Foundation::IAsyncAction CancellationPropagatorAsync();

		//Optimization:
		Windows::Foundation::IAsyncOperation<SimplePhotoViewer::ImageSku> LoadImageInfoAsync(Windows::Storage::StorageFile file);

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

		Windows::Foundation::IAsyncAction refreshCurrentFolder_async{ nullptr };

		hstring currentSelectedFolderPathName;
		hstring m_currentSelectedFolderName;
		int32_t m_currentFolderImageNumber = 0;
		int32_t m_currentFolderSelectedImageNumber = 0;

		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

		/*private members for implementation of "Drag Canvs Selection"*/
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
