#pragma once

#include "MainPage.g.h"

namespace winrt::SimplePhotoViewer::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage() = default;

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ImageSkus();
        void ImageSkus(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value);
        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> BufferImageSkus();
        void BufferImageSkus(Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> const& value);
        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> TreeViewFolders();
        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> SearchResults();
        hstring CurrentSelectedFolder();
        void CurrentSelectedFolder(hstring const& value);
        uint32_t CurrentFolderImageNumber();
        uint32_t CurrentFolderSelectedImageNumber();
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    };
}

namespace winrt::SimplePhotoViewer::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
