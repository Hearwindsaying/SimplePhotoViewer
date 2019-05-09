#pragma once

#include "DirectoryItem.h"
#include "ExplorerItemTemplateSelector.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct ExplorerItemTemplateSelector : ExplorerItemTemplateSelectorT<ExplorerItemTemplateSelector>
    {
	public:

		ExplorerItemTemplateSelector() = default;

		Windows::UI::Xaml::DataTemplate SelectTemplateCore(Windows::Foundation::IInspectable const& item)
		{
			auto explorerItem = item.try_as<SimplePhotoViewer::DirectoryItem>();
			if (explorerItem)
			{
				return explorerItem.IsFolder() ? this->m_folderTemplate : this->m_fileTemplate;
			}
			return this->m_folderTemplate;
		}
		Windows::UI::Xaml::DataTemplate SelectTemplateCore(winrt::Windows::Foundation::IInspectable item, Windows::UI::Xaml::DependencyObject container) const
		{
			return __super::SelectTemplateCore(item,container);
		}
		Windows::UI::Xaml::DataTemplate FolderTemplate()
		{
			return this->m_folderTemplate;
		}
		void FolderTemplate(Windows::UI::Xaml::DataTemplate const& value)
		{
			this->m_folderTemplate = value;
		}
        Windows::UI::Xaml::DataTemplate FileTemplate()
		{
			return this->m_fileTemplate;
		}
		void FileTemplate(Windows::UI::Xaml::DataTemplate const& value)
		{
			this->m_fileTemplate = value;
		}

	private:
		Windows::UI::Xaml::DataTemplate m_folderTemplate;
		Windows::UI::Xaml::DataTemplate m_fileTemplate;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
	struct ExplorerItemTemplateSelector : ExplorerItemTemplateSelectorT<ExplorerItemTemplateSelector, implementation::ExplorerItemTemplateSelector>
	{
	};
}
