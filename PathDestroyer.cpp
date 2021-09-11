#include "pch.h"
#include "PathDestroyer.h"

PathDestoryer::PathDestoryer(PathDataParent& _pathData)
{
	ifstream in(_pathData.iniPath);
	if (!in.is_open()) message::displayErrorMessage("ALR_ERROR", "ALR.ini Not Found");
	in.ignore((numeric_limits<streamsize>::max)(), ';');
	in.ignore((numeric_limits<streamsize>::max)(), ';');
	in.ignore((numeric_limits<streamsize>::max)(), ';');
	in.ignore((numeric_limits<streamsize>::max)(), ':');

	if (in.get() == '0') {
		overlayPath = string(_pathData.overlayPath.begin(), _pathData.overlayPath.end());
		ALRDirPath = string(_pathData.outputPaths.at(0).begin(), _pathData.outputPaths.at(0).end() - 6);

		deleteFiles();
		deleteEmptyFolders();
	}
}

void PathDestoryer::deleteFiles()
{
	hr = filesystem::remove_all(ALRDirPath);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);

	hr = filesystem::remove(overlayPath);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);
}

void PathDestoryer::deleteEmptyFolders()
{
	string overlayDirPath = overlayPath.substr(0, overlayPath.size() - 16);
	for (auto& i : filesystem::directory_iterator(overlayDirPath)) {
		if (i.exists())
			return;
	}
	hr = filesystem::remove(overlayDirPath);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);

	overlayDirPath = overlayPath.substr(0, overlayPath.size() - 27);
	for (auto& i : filesystem::directory_iterator(overlayDirPath)) {
		if (i.exists())
			return;
	}
	hr = filesystem::remove(overlayDirPath);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);

	overlayDirPath = overlayPath.substr(0, overlayPath.size() - 35);
	for (auto& i : filesystem::directory_iterator(overlayDirPath)) {
		if (i.exists())
			return;
	}
	hr = filesystem::remove(overlayDirPath);

	overlayDirPath = overlayPath.substr(0, overlayPath.size() - 45);
	for (auto& i : filesystem::directory_iterator(overlayDirPath)) {
		if (i.exists())
			return;
	}
	hr = filesystem::remove(overlayDirPath);
	if (FAILED(hr)) message::displayCOMErrorMessage(hr);
}