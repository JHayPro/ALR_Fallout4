#pragma once
#include "pch.h"
#include "cmd.cpp"
#include "PathData.h"

class PathBuilderParent {
public:

};

class PathBuilder : public PathBuilderParent {

private:
	PathDataParent* pathData = NULL;
	vector<string> inputFiles;
	string inputPath, overlayPath, outputPath, backgroundPath, prefPath;
	ostringstream dataPathSS, prefPathSS;

	void readInis(),
		findInputFiles(),
		generateInputPaths(),
		correctFiles(),
		generateOutputPaths(),
		firstTimeCheck(),
		findDLLPath(),
		findPrefPath(),
		rebuildIni(),
		verifyFiles(),
		findImgDir(),
		HFPSPFpatch();

	void buildTextureDir();

	bool verifyImages(),
		HFPSPFsearch,
		HFPSPFapplied,
		dImageRD,
		dOverlayRD,
		rebuildIniFlag;

public:

	PathBuilder(PathDataParent& _pathData);
	~PathBuilder();
};