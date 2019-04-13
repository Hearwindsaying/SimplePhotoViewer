#include "pch.h"
#include "DirectoryItem.h"

namespace winrt::SimplePhotoViewer::implementation
{
    DirectoryItem::DirectoryItem(hstring const& itemName, Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& subItems, Windows::Storage::StorageFolder const& itemFolder)
    {
        throw hresult_not_implemented();
    }

    DirectoryItem::DirectoryItem(hstring const& itemName, Windows::Storage::StorageFolder const& itemFolder)
    {
        throw hresult_not_implemented();
    }

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> DirectoryItem::SubItems()
    {
        throw hresult_not_implemented();
    }

    void DirectoryItem::SubItems(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value)
    {
        throw hresult_not_implemented();
    }

    hstring DirectoryItem::Item()
    {
        throw hresult_not_implemented();
    }

    void DirectoryItem::Item(hstring const& value)
    {
        throw hresult_not_implemented();
    }

    Windows::Storage::StorageFolder DirectoryItem::ItemFolder()
    {
        throw hresult_not_implemented();
    }

    void DirectoryItem::ItemFolder(Windows::Storage::StorageFolder const& value)
    {
        throw hresult_not_implemented();
    }

    winrt::event_token DirectoryItem::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        throw hresult_not_implemented();
    }

    void DirectoryItem::PropertyChanged(winrt::event_token const& token) noexcept
    {
        throw hresult_not_implemented();
    }
}
