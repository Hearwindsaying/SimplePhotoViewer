#include "pch.h"
#include "DirectoryItem.h"

namespace winrt::SimplePhotoViewer::implementation
{
    hstring DirectoryItem::Item() const
    {
		return this->m_item;
    }

    void DirectoryItem::Item(hstring const& value)
    {
		this->m_item = value;
		this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Item" });
    }

	Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> DirectoryItem::SubItems() const
	{
		return this->m_subItems;
	}

	void DirectoryItem::SubItems(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value)
	{
		this->m_subItems = value;
		this->m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"SubItems" });
	}

	Windows::Storage::StorageFolder DirectoryItem::ItemFolder() const
	{
		return this->m_ItemFolder;
	}

	void DirectoryItem::ItemFolder(Windows::Storage::StorageFolder const & value)
	{
		throw hresult_not_implemented();
	}

    winrt::event_token DirectoryItem::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
		return this->m_propertyChanged.add(handler);
    }

    void DirectoryItem::PropertyChanged(winrt::event_token const& token) noexcept
    {
		this->m_propertyChanged.remove(token);
    }
}
