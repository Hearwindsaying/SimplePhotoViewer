#include "pch.h"
#include "MainPage.h"

#include "ImageSku.h"

namespace winrt::SimplePhotoViewer::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
		this->m_imageSkus = single_threaded_observable_vector<Windows::Foundation::IInspectable>();

		//auto defaultFolder = this->LoadDefaultFolder();
	}

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainPage::ImageSkus() const 
    {
		return this->m_imageSkus;
    }

	void MainPage::ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		this->myButton().Content(box_value(L"Clicked"));
	}
	Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e)
	{
		auto defaultFolder = co_await this->LoadDefaultFolder();

		Windows::Storage::Search::QueryOptions options{};
		options.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);
		options.FileTypeFilter().Append(L".jpg");
		options.FileTypeFilter().Append(L".png");


		auto result = defaultFolder.CreateFileQueryWithOptions(options);
		auto imageFiles = co_await result.GetFilesAsync();

		// Populate Photos collection.
		for (auto&& file : imageFiles)
		{
			auto imageProperties = co_await file.Properties().GetImagePropertiesAsync();
			auto imageSku = winrt::make<ImageSku>(imageProperties, file, file.DisplayName(), file.DisplayType());
			this->ImageSkus().Append(imageSku);
		}
	}
	Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> MainPage::LoadDefaultFolder()
	{
		std::wstring level2FolderName{ L"D:\\Project\\TestResource" };

		Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(level2FolderName) };

		return folder;
	}
}
