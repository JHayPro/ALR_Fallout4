#pragma once
#include "pch.h"
#include "UI.cpp"
#include "pathData.h"

class PathDestoryerParent {
public:
	virtual void deleteFiles() = 0,
		deleteEmptyFolders()  = 0;
};

class PathDestoryer : public PathDestoryerParent {

private:
	string overlayPath, ALRDirPath;
	HRESULT hr;

public:
	PathDestoryer(PathDataParent& _pathData);
	void deleteFiles(), deleteEmptyFolders();
};