#include "pch.h"
#include "ExplorerItemTemplateSelector.h"

namespace winrt::SimplePhotoViewer::implementation
{
    Windows::UI::Xaml::DataTemplate ExplorerItemTemplateSelector::SelectTemplateCore(Windows::Foundation::IInspectable const& item)
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Xaml::DataTemplate ExplorerItemTemplateSelector::FolderTemplate()
    {
        throw hresult_not_implemented();
    }

    void ExplorerItemTemplateSelector::FolderTemplate(Windows::UI::Xaml::DataTemplate const& value)
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Xaml::DataTemplate ExplorerItemTemplateSelector::FileTemplate()
    {
        throw hresult_not_implemented();
    }

    void ExplorerItemTemplateSelector::FileTemplate(Windows::UI::Xaml::DataTemplate const& value)
    {
        throw hresult_not_implemented();
    }
}
