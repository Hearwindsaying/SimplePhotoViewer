#pragma once

#include "DirectoryItem.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct DirectoryItem : DirectoryItemT<DirectoryItem>
    {
        DirectoryItem() = delete;
        DirectoryItem(hstring const& itemName, Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& subItems, Windows::Storage::StorageFolder const& itemFolder);
        DirectoryItem(hstring const& itemName, Windows::Storage::StorageFolder const& itemFolder);

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> SubItems();
        hstring Item();
        void Item(hstring const& value);
        Windows::Storage::StorageFolder ItemFolder();
        void ItemFolder(Windows::Storage::StorageFolder const& value);
        bool IsFolder();
        void IsFolder(bool value);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct DirectoryItem : DirectoryItemT<DirectoryItem, implementation::DirectoryItem>
    {
    };
}
