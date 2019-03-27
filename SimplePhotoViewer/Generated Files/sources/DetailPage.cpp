#include "pch.h"
#include "DetailPage.h"

namespace winrt::SimplePhotoViewer::implementation
{
    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> DetailPage::ImageSkus()
    {
        throw hresult_not_implemented();
    }

    SimplePhotoViewer::ImageSku DetailPage::SelectedItem()
    {
        throw hresult_not_implemented();
    }

    void DetailPage::SelectedItem(SimplePhotoViewer::ImageSku const& value)
    {
        throw hresult_not_implemented();
    }
}
