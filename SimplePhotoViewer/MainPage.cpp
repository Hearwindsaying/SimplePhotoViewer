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
		/*this->myButton().Content(box_value(L"Clicked"));*/

	}
	void MainPage::PlayButton_ClickHandler(Windows::Foundation::IInspectable const& param, Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Frame().Navigate(winrt::xaml_typename<SimplePhotoViewer::DetailPage>(), this->m_imageSkus);
	}

	void MainPage::Node_ClickHandler(Microsoft::UI::Xaml::Controls::TreeView const&, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& args)
	{
		auto myContent = args.try_as<winrt::Microsoft::UI::Xaml::Controls::TreeViewNode>();
	}

	Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e)
	{
		/*auto treeViewNodes = this->myTreeView().RootNodes();
		Microsoft::UI::Xaml::Controls::TreeViewNode firstNode{};
		firstNode.Content(winrt::box_value(L"flavor"));
		auto firstRootNodeChildren = treeViewNodes.GetAt(0).Children();
		auto getTreeViewNode = firstRootNodeChildren.GetAt(0);

		treeViewNodes.GetAt(0).Children().Append(firstNode);

		hstring myContent = winrt::unbox_value<hstring>(firstRootNodeChildren.GetAt(3).Content());*/

		

		auto defaultFolder = co_await this->LoadDefaultFolder();

		Windows::Storage::Search::QueryOptions options{};
		options.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);
		options.FileTypeFilter().Append(L".jpg");
		options.FileTypeFilter().Append(L".png");


		auto result = defaultFolder.CreateFileQueryWithOptions(options);
		auto imageFiles = co_await result.GetFilesAsync();

		//// Populate Photos collection.
		for (auto&& file : imageFiles)
		{
			auto imageProperties = co_await file.Properties().GetImagePropertiesAsync();


			auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem);
			//or:auto thumbnail = co_await file.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
			Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage{};
			bitmapImage.SetSource(thumbnail);
			thumbnail.Close();

			auto imageSku = winrt::make<ImageSku>(imageProperties, file, file.DisplayName(), file.DisplayType(), bitmapImage, file.Name());

			this->ImageSkus().Append(imageSku);
		}
		wchar_t testchar[20] = { '6','6','e' };
		OutputDebugString(testchar);

		//Retrieve thumbnail of images, set image source:
		
		 
	}
	Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFolder> MainPage::LoadDefaultFolder()
	{
		std::wstring level2FolderName{ L"D:\\Project\\TestResource" };

		Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(level2FolderName) };

		return folder;
	}
}
