#pragma once
#include "pch.h"

class PathDataParent {

public:
	vector<wstring> inputFilePaths;
	array<wstring, MAX_INPUTS> outputPaths;
	wstring overlayPath;
	string iniPath;
};

class PathData : public PathDataParent {

public:
	PathData() {};

};