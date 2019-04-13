﻿#pragma once

#include "MainPage.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus() const;
		void ImageSkus(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value);
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> TreeViewFolders() const;
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

		//default ClickHandler generated by BlankApp
		//delete this
		Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const, Windows::UI::Xaml::RoutedEventArgs const);
		
		void PlayButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
		Windows::Foundation::IAsyncAction DeleteButton_ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);

		void Node_ClickHandler(Microsoft::UI::Xaml::Controls::TreeView const&, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const&);

		void SearchBox_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void SearchBox_SuggestionChosen(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		void SearchBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);

		Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e);
		Windows::Foundation::IAsyncAction DirectoryItem_Expanding(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewExpandingEventArgs const args);
		void DirectoryItem_Collapsed(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewCollapsedEventArgs const args);
		Windows::Foundation::IAsyncAction DirectoryItem_Invoked(Microsoft::UI::Xaml::Controls::TreeView const sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const args);

		void GridViewItem_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
		{
			return this->m_propertyChanged.add(handler);
		}
		void PropertyChanged(winrt::event_token const& token) noexcept
		{
			this->m_propertyChanged.remove(token);
		}
	private:
		Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> LoadDefaultFolder();

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

		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_searchResults{ nullptr };

		hstring currentSelectedFolderPathName;
		hstring m_currentSelectedFolderName;
		int32_t m_currentFolderImageNumber = 0;
		int32_t m_currentFolderSelectedImageNumber = 0;

		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
