#include "pch.h"
#include "ImageConvert.h"

ImageConvert::ImageConvert(PathDataParent& _pathData) : pathData(&_pathData)
{
	message::checkForError(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED));

	sizeImageData = imageData(pathData->outputWidth, pathData->outputHeight);
	maxDisplayImageData = imageData(sizeImageData.ar, sizeImageData.arMul, sizeImageData.resMul);
	outputAR = AR(1, 1);
	
	createOverlay(path::to_wstring(pathData->overlayPath));
	
	for (int i = 0; i < MAX_INPUTS; i++) 
		convert(path::to_wstring(pathData->inputFilePaths.at(i)), path::to_wstring(pathData->outputPaths.at(i)));

	if (pathData->backgroundReplace) {
		maxDisplayImageData = imageData(AR(2, 1), sizeImageData.res4k);
		outputAR = AR(2, 1);
		convert(path::to_wstring(pathData->inputFilePaths.at(0)), path::to_wstring(pathData->backgroundPath));
	}
}

ImageConvert::~ImageConvert()
{
	delete pathData;
}

void ImageConvert::createOverlay(wstring _outputFilePath)
{
	ScratchImage overlayImage;
	message::checkForError(overlayImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, maxDisplayImageData.res.width, maxDisplayImageData.res.height, 1, 0, CP_FLAGS_NONE));
	message::checkForError(SaveToDDSFile(*overlayImage.GetImage(0, 0, 0), DDS_FLAGS_NONE, _outputFilePath.c_str()));
}

void ImageConvert::convert(wstring _inputFilePath, wstring _outputFilePath) {

	TexMetadata inImageInfo;
	ScratchImage inImage, outImage;
	imageData inImageData, outImageData;

	if (path::getExtension(_inputFilePath) == L"dds") 
		message::checkForError(LoadFromDDSFile(_inputFilePath.c_str(), DDS_FLAGS_NONE, &inImageInfo, inImage));
	else 
		message::checkForError(LoadFromWICFile(_inputFilePath.c_str(), WIC_FLAGS_NONE, &inImageInfo, inImage));

	if (IsCompressed(inImage.GetMetadata().format))
		message::checkForError(Decompress(*inImage.GetImage(0, 0, 0), DXGI_FORMAT_UNKNOWN, inImage));
	
	inImageData = imageData(inImage.GetMetadata().width, inImage.GetMetadata().height);
	if (!(inImageData.ar == maxDisplayImageData.ar) || inImageData.resMul > maxDisplayImageData.resMul) {
		message::checkForError(Resize(*inImage.GetImage(0, 0, 0), maxDisplayImageData.res.width, maxDisplayImageData.res.height, TEX_FILTER_DEFAULT, inImage));
		inImageData = imageData(maxDisplayImageData.res.width, maxDisplayImageData.res.height);
	}
	
	outImageData = imageData(inImageData.arMul, inImageData.resMul, inImageData.off, outputAR);
	message::checkForError(outImage.Initialize2D(inImage.GetMetadata().format, outImageData.res.width, outImageData.res.height, 1, 0, CP_FLAGS_NONE));

	Rect r0(0, 0, inImageData.res.width, inImageData.res.height);
	message::checkForError(CopyRectangle(*inImage.GetImage(0, 0, 0), r0, *outImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, outImageData.off.width, outImageData.off.height));

	message::checkForError(SaveToDDSFile(*outImage.GetImage(0, 0, 0), DDS_FLAGS_NONE, _outputFilePath.c_str()));
}

AR_MUL::AR_MUL(AR _ar)
{
	for(auto& pair : ARtupleArray)
		if (get<0>(pair) == _ar) {
			res2kMul = get<1>(pair).res2kMul;
			res4kMul = get<1>(pair).res4kMul;
			break;
		}
}

OFF_CON::OFF_CON(AR _ar)
{
	for (auto& pair : ARtupleArray)
		if (get<0>(pair) == _ar) {
			off2k = get<2>(pair).off2k;
			off4k = get<2>(pair).off4k;
			break;
		}
};
