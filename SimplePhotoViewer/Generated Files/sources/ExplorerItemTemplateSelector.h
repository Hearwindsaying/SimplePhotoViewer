#pragma once

#include "ExplorerItemTemplateSelector.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct ExplorerItemTemplateSelector : ExplorerItemTemplateSelectorT<ExplorerItemTemplateSelector>
    {
        ExplorerItemTemplateSelector() = default;

        Windows::UI::Xaml::DataTemplate SelectTemplateCore(Windows::Foundation::IInspectable const& item);
        Windows::UI::Xaml::DataTemplate FolderTemplate();
        void FolderTemplate(Windows::UI::Xaml::DataTemplate const& value);
        Windows::UI::Xaml::DataTemplate FileTemplate();
        void FileTemplate(Windows::UI::Xaml::DataTemplate const& value);
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct ExplorerItemTemplateSelector : ExplorerItemTemplateSelectorT<ExplorerItemTemplateSelector, implementation::ExplorerItemTemplateSelector>
    {
    };
}
