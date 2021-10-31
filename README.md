## SimplePhotoViewer
![featured](https://github.com/Hearwindsaying/zihong/blob/master/content/project/simple-photo-viewer/featured.png)

## Overview
This is our final assignment for the 'Object Oriented Programming' course.
It is a UWP (Universal Windows Platform) application for simple image viewing written in C++17/WinRT and XAML.
Except for the UI layout and design by [@ArtlexKylin](https://github.com/ArtlexKylin), I did all the implementation and optimization.

## Features
- Common image format supports: png, jpg, git, bmp, tif, tga.
- Directory tree support for UWP and folder import support (for security purpose)[^2].
- Image file manipulations. 
    - Selective: single/multiple/invert selections, click and drag selection (dragable rectangle selection)[^1].
    - File system: copy, cut, move, paste, remove, rename and rename in batch.
    - Efficient image searching with suggestions.
    - Simple image viewing and edits: scaling, rotations, filters (Gaussian Blur, Exposure, Temperature etc.).
- Image gallery viewing.
    - Automatic slide show images.
    - Efficient thumbnails and full images showing.
- Fluent UI design with acrylic material and adaptive layout powered by WinUI 2.0.
- ListView and GridView optimizations for thousands of items.
    - UI virtualization and update items on demand.
    - Native C++17 implementation with XAML data binding support. 

[^1]: Note that dragable rectangle selection is common in traditional win32 application (e.g. explorer.exe), but it is not compatible with fluent UI design. I still implemented this widget from scratch due to its functional convenience and assignment requirement.
[^2]: UWP app is notable at its security and safeness. In other words, it cannot access extra resources not authorized by users. So you could import the folder explicitly to give the accessibility or just turn on privacy settings for UWP app in windows settings to enable the directory tree working. Please see also https://support.microsoft.com/en-us/windows/-windows-file-system-access-and-privacy-a7d90b20-b252-0e7b-6a29-a3a688e5c7be for instructions.

## Build
Currently it supports from Windows 10 version 1809 (OS build 17763) and a Windows SDK >= 10.0.17763.0 is required.
Both Visual Studio 2017 (v141) and 2019 (v142) could be used and Visual Studio's retarget solution should provide you with the available SDK/project verisons.
It depends on Microsoft.UI.Xaml, Microsoft.Windows.CppWinRT and Win2D.uwp by nuget packages.

## Gallery

![4](https://github.com/Hearwindsaying/zihong/blob/master/content/project/simple-photo-viewer/4.png)
![2](https://github.com/Hearwindsaying/zihong/blob/master/content/project/simple-photo-viewer/2.png)
![3](https://github.com/Hearwindsaying/zihong/blob/master/content/project/simple-photo-viewer/3.png)

