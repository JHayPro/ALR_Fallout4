#pragma once
#include "pch.h"
#include "cmd.cpp"

class PathDataParent {

public:
	vector<string> inputFilePaths;
	array<string, MAX_INPUTS> outputPaths;
	string overlayPath, backgroundPath;
	string iniPath;
	int outputHeight, outputWidth;
	bool backgroundReplace = false;
};

class PathData : public PathDataParent {

public:
	PathData() {};
};