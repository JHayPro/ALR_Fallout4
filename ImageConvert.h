#pragma once
#include "pch.h"
#include "PathData.h"
#include "UI.cpp"

class ImageConvertParent {
public:

};

class ImageConvert : public ImageConvertParent {
private:

	HRESULT hr;
	PathDataParent* pathData = NULL;

	array<ScratchImage, MAX_INPUTS> screenshotImageIn,
		resultImage;
	array<TexMetadata, MAX_INPUTS> screenshotImageInfo;

	ScratchImage overlayImage;

	void convert(),
		createOverlay();

public:

	ImageConvert(PathDataParent& _pathData);
};