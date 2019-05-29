#pragma once
#include <windows.h>
#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>

#include "Win2D/winrt/Microsoft.Graphics.Canvas.h"
#include "Win2D/winrt/Microsoft.Graphics.Canvas.Effects.h"
#include "Win2D/winrt/Microsoft.Graphics.Canvas.Text.h"
#include "Win2D/winrt/Microsoft.Graphics.Canvas.UI.Xaml.h"
#include "Win2D/winrt/Microsoft.Graphics.Canvas.Brushes.h"

#include "WinUILib/winrt/Microsoft.UI.Xaml.Automation.Peers.h"
#include "WinUILib/winrt/Microsoft.UI.Xaml.Controls.h"
#include "WinUILib/winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "WinUILib/winrt/Microsoft.UI.Xaml.Media.h"
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include "WinUILib/winrt/Microsoft.UI.Xaml.XamlTypeInfo.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>

#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.Graphics.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Graphics.Display.h>


#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Search.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.AccessCache.h>

#include <winrt/Windows.UI.Xaml.Hosting.h>

struct __declspec(uuid("905a0fef-bc53-11df-8c49-001e4fc686da")) IBufferByteAccess : ::IUnknown
{
	virtual HRESULT __stdcall Buffer(uint8_t** value) = 0;
};