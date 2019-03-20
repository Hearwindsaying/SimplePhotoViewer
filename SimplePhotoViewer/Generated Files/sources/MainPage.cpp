#include "pch.h"
#include "MainPage.h"

namespace winrt::SimplePhotoViewer::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
	}

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainPage::ImageSkus()
    {
        throw hresult_not_implemented();
    }

	void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		myButton().Content(box_value(L"Clicked"));
	}
}
