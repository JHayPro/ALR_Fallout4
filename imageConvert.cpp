#include "pch.h"
#include "ImageConvert.h"

ImageConvert::ImageConvert(PathDataParent& _pathData) : pathData(&_pathData)
{
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);

	createOverlay();
	convert();
}
void ImageConvert::createOverlay()
{
	hr = overlayImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 1024, 1, 0, CP_FLAGS_NONE);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	hr = SaveToDDSFile(*overlayImage.GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->overlayPath.c_str());
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);
}

void ImageConvert::convert() {

	for (int i = 0; i < MAX_INPUTS; i+=5) {

		hr = LoadFromWICFile(pathData->inputFilePaths.at(i).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i), screenshotImageIn.at(i));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = resultImage.at(i).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))message::displayCOMErrorMessage(hr);

		Rect r0(0, 0, screenshotImageInfo.at(i).width, screenshotImageInfo.at(i).height);
		hr = CopyRectangle(*screenshotImageIn.at(i).GetImage(0, 0, 0), r0, *resultImage.at(i).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = SaveToDDSFile(*resultImage.at(i).GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->outputPaths.at(i).c_str());
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		//

		hr = LoadFromWICFile(pathData->inputFilePaths.at(i+1).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i + 1), screenshotImageIn.at(i + 1));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = resultImage.at(i + 1).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))message::displayCOMErrorMessage(hr);

		Rect r1(0, 0, screenshotImageInfo.at(i + 1).width, screenshotImageInfo.at(i + 1).height);
		hr = CopyRectangle(*screenshotImageIn.at(i + 1).GetImage(0, 0, 0), r1, *resultImage.at(i + 1).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = SaveToDDSFile(*resultImage.at(i + 1).GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->outputPaths.at(i + 1).c_str());
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		//

		hr = LoadFromWICFile(pathData->inputFilePaths.at(i + 2).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i + 2), screenshotImageIn.at(i + 2));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = resultImage.at(i + 2).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))message::displayCOMErrorMessage(hr);

		Rect r2(0, 0, screenshotImageInfo.at(i + 2).width, screenshotImageInfo.at(i + 2).height);
		hr = CopyRectangle(*screenshotImageIn.at(i + 2).GetImage(0, 0, 0), r2, *resultImage.at(i + 2).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = SaveToDDSFile(*resultImage.at(i + 2).GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->outputPaths.at(i + 2).c_str());
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		//

		hr = LoadFromWICFile(pathData->inputFilePaths.at(i + 3).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i + 3), screenshotImageIn.at(i + 3));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = resultImage.at(i + 3).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))message::displayCOMErrorMessage(hr);

		Rect r3(0, 0, screenshotImageInfo.at(i + 3).width, screenshotImageInfo.at(i + 3).height);
		hr = CopyRectangle(*screenshotImageIn.at(i + 3).GetImage(0, 0, 0), r3, *resultImage.at(i + 3).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = SaveToDDSFile(*resultImage.at(i + 3).GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->outputPaths.at(i + 3).c_str());
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		//

		hr = LoadFromWICFile(pathData->inputFilePaths.at(i + 4).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i + 4), screenshotImageIn.at(i + 4));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = resultImage.at(i + 4).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))message::displayCOMErrorMessage(hr);

		Rect r4(0, 0, screenshotImageInfo.at(i + 4).width, screenshotImageInfo.at(i).height);
		hr = CopyRectangle(*screenshotImageIn.at(i + 4).GetImage(0, 0, 0), r4, *resultImage.at(i + 4).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		hr = SaveToDDSFile(*resultImage.at(i + 4).GetImage(0, 0, 0), DDS_FLAGS_NONE, pathData->outputPaths.at(i + 4).c_str());
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);

		//
	}
}