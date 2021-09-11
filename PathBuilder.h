#pragma once
#include "pch.h"
#include "UI.cpp"
#include "PathData.h"

class PathBuilderParent {
public:

	virtual void findInputFiles() = 0,
		generateInputPaths() = 0,
		correctFiles() = 0,
		generateOutputPaths() = 0,
		findDLLPath() = 0,
		firstTimeCheck() = 0,
		readIni() = 0;

	virtual bool verifyDataFiles() = 0, 
		buildTextureDir() = 0;
};

class PathBuilder : public PathBuilderParent {

private:
	PathDataParent* pathData = NULL;
	vector<string> inputFiles;
	string inputPath, overlayPath, outputPath;
	ostringstream pathSS;
	HRESULT hr;

	void readIni(),
		findInputFiles(),
		generateInputPaths(),
		correctFiles(),
		generateOutputPaths(),
		firstTimeCheck(),
		findDLLPath(),
		rebuildIni(),
		verifyImgFiles(),
		verifyOvLFiles(),
		findImgDir();

	bool verifyDataFiles(),
		buildTextureDir(),
		verifyImages(),
		verifyOverlay(),

		dImageRD,
		dOverlayRD,
		rebuildIniFlag;

public:

	PathBuilder(PathDataParent& _pathData);
};