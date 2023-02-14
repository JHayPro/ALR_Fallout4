#pragma once
#include "pch.h"
#include "cmd.cpp"
#include "pathData.h"

class PathDestoryerParent {
public:

};

class PathDestoryer : public PathDestoryerParent {

private:
	string overlayPath, ALRDirPath, backgroundPath;
	HRESULT hr;
	bool backgroundReplace;

public:
	PathDestoryer(PathDataParent& _pathData);
	void deleteFiles(), deleteEmptyFolders();
};