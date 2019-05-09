#pragma once

#include "DirectoryItem.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct DirectoryItem : DirectoryItemT<DirectoryItem>
    {
        DirectoryItem() = delete;
		DirectoryItem(hstring const& itemName, Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& subItems, Windows::Storage::StorageFolder const& itemFolder):m_item(itemName), m_subItems(subItems), m_ItemFolder(itemFolder){}
		DirectoryItem(hstring const& itemName, Windows::Storage::StorageFolder const& itemFolder) :m_item(itemName), m_ItemFolder(itemFolder)
		{
			this->m_subItems = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();
		}

        hstring Item() const;
        void Item(hstring const& value);
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> SubItems() const;
		Windows::Storage::StorageFolder ItemFolder() const;
		void ItemFolder(Windows::Storage::StorageFolder const& value);
		bool IsFolder() const { return this->m_isFolder; };
		void IsFolder(bool const value) { this->m_isFolder = value; };

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

	private:
		hstring m_item;
		Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_subItems;
		Windows::Storage::StorageFolder m_ItemFolder;
		bool m_isFolder{ true };

		//Delegate for observable property
		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DirectoryItem : DirectoryItemT<DirectoryItem, implementation::DirectoryItem>
    {
    };
}
