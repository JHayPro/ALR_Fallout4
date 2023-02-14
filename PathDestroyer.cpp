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
		overlayPath = _pathData.overlayPath;
		backgroundPath = _pathData.backgroundPath;
		ALRDirPath = path::getDirectoryFromBegin(_pathData.outputPaths.at(0), 6);
		backgroundReplace = _pathData.backgroundReplace;

		deleteFiles();
		deleteEmptyFolders();
	}
}

void PathDestoryer::deleteFiles()
{
	message::checkForError(filesystem::remove_all(ALRDirPath));
	message::checkForError(filesystem::remove(overlayPath));

	if(backgroundReplace)
		message::checkForError(filesystem::remove(backgroundPath));
}

void PathDestoryer::deleteEmptyFolders()
{
	string overlayDirPath = path::getDirectoryFromBegin(overlayPath, 16);
	for (auto& dir : filesystem::directory_iterator(overlayDirPath)) {
		if (dir.exists())
			return;
	}
	message::checkForError(filesystem::remove(overlayDirPath));

	overlayDirPath = path::getDirectoryFromBegin(overlayPath, 27);
	for (auto& dir : filesystem::directory_iterator(overlayDirPath)) {
		if (dir.exists())
			return;
	}
	message::checkForError(filesystem::remove(overlayDirPath));

	overlayDirPath = path::getDirectoryFromBegin(overlayPath, 35);
	for (auto& dir : filesystem::directory_iterator(overlayDirPath)) {
		if (dir.exists())
			return;
	}
	message::checkForError(filesystem::remove(overlayDirPath));

	overlayDirPath = path::getDirectoryFromBegin(overlayPath, 45);
	for (auto& dir : filesystem::directory_iterator(overlayDirPath)) {
		if (dir.exists())
			return;
	}
	message::checkForError(filesystem::remove(overlayDirPath));
}