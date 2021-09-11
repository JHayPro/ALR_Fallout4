#include "pch.h"
#include "PathBuilder.h"

PathBuilder::PathBuilder(PathDataParent& _pathData) : pathData(&_pathData)
{
	rebuildIniFlag = dImageRD = dOverlayRD = false;

	findDLLPath();
	readIni();
	if (rebuildIniFlag) rebuildIni();
	generateOutputPaths();

	if(dImageRD)
		if (!verifyImages()) 
			dImageRD = false;

	//if (dOverlayRD)
	//	if (!verifyOverlay())
	//		dOverlayRD = false;

	if (!dImageRD && !dOverlayRD) {
		if (!buildTextureDir()) message::displayErrorMessage("ALR_ERROR", "Unable to install file directories Textures\\Interface\\ALR_Backgrounds, try adding them manually");
		verifyImgFiles();
		verifyOvLFiles();
		findInputFiles();
		if (inputFiles.size() == 0) message::displayErrorMessage("ALR_ERROR", "No Files Found In ALR.ini's Path \n Ensure A Full Path Is Being Used EX.\n C:\Program Files (x86)\Steam\screenshots");
		if (pathData->inputFilePaths.size() != MAX_INPUTS) correctFiles();
		generateInputPaths();
	}
	//else if (!dOverlayRD) {

	//}
	//else if (!dImageRD) {

	//}
}

void PathBuilder::readIni()
{
	ifstream in(pathData->iniPath);
	if (!in.is_open()) message::displayErrorMessage("ALR_ERROR", "ALR.ini Not Found");

	in.ignore((numeric_limits<streamsize>::max)(), '\n');
	getline(in, inputPath);
	if (inputPath == "default") 
		findImgDir();
					
	else if (inputPath.at(inputPath.size() - 1) != '\\') {
		inputPath.push_back('\\');
		rebuildIniFlag = true;
	}
	
	in.ignore((numeric_limits<streamsize>::max)(), ';');
	in.ignore((numeric_limits<streamsize>::max)(), ':');

	if (in.get() == '0')
		firstTimeCheck();

	in.ignore((numeric_limits<streamsize>::max)(), ':');
	
	if (in.get() == '1')
		dImageRD = true;

	//in.ignore((numeric_limits<streamsize>::max)(), ':');

	//if (in.get() == '1')
	//	dOverlayRD = true;

	in.close();
}

void PathBuilder::verifyOvLFiles()
{
	if (!filesystem::exists(overlayPath))
		message::displayErrorMessage("ALR_ERROR", "Textures\\Interface\\Objects\\LoadScreen was not created");
}

void PathBuilder::verifyImgFiles()
{
	if (!filesystem::exists(inputPath)) {
		inputPath.pop_back();
		string tempS = "";
		int tempI;
		for (tempI = 1; inputPath.at(inputPath.size() - tempI) != '\\'; tempI++) { }
		for (int i = 1; i < tempI; i++)
			tempS.push_back(inputPath.at(inputPath.size() - tempI + i));

		message::displayErrorMessage("ALR_ERROR", tempS + " Folder Not Found\nEither enter a new path in ALR.ini or use 'default' path and add ALR_Image_Dir to F4SE/Plugins");
	}

	if (!filesystem::exists(outputPath)) 
		message::displayErrorMessage("ALR_ERROR", "Textures\\Interface\\ALR_Backgrounds was not created");
}

void PathBuilder::rebuildIni()
{
	ofstream outF(pathData->iniPath);
	outF << ";Enter path to images below, type 'default' to use default path\n" + inputPath + "\n\n;First Time Install Check Success:1\n\n;Disable image reload and delete (better performance):" + to_string(dImageRD); //+ "\n\n;Disable overlay reload and delete (better performance):" + to_string(dOverlayRD);
	outF.close();
}

void PathBuilder::findImgDir()
{
	inputPath = pathSS.str() + "F4SE\\Plugins\\ALR_Image_Dir\\";
	rebuildIniFlag = true;
}

void PathBuilder::firstTimeCheck()
{
	if (!verifyDataFiles())
		message::displayErrorMessage("ALR_ERROR", "ALR esp and or Main ba2 is missing, check the mod was installed properly");

	rebuildIniFlag = true;
}

bool PathBuilder::verifyDataFiles()
{
	if (!filesystem::exists(pathSS.str() + "ALR - All DLC.esp"))
		return false;
	if (!filesystem::exists(pathSS.str() + "ALR - All DLC - Main.ba2"))
		return false;

	return true;
}

bool PathBuilder::buildTextureDir()
{
	if (!filesystem::is_directory(outputPath.substr(0, outputPath.size() - 26))) {
		hr = filesystem::create_directories(outputPath.substr(0, outputPath.size() - 26));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	}
	if (!filesystem::is_directory(outputPath.substr(0, outputPath.size() - 16))) {
		hr = filesystem::create_directories(outputPath.substr(0, outputPath.size() - 16));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	}
	if (!filesystem::is_directory(outputPath)) {
		hr = filesystem::create_directories(outputPath);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	}
	if (!filesystem::is_directory(overlayPath.substr(0, overlayPath.size() - 11))) {
		hr = filesystem::create_directories(overlayPath.substr(0, overlayPath.size() - 11));
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	}
	if (!filesystem::is_directory(overlayPath)) {
		hr = filesystem::create_directories(overlayPath);
		if (FAILED(hr)) message::displayCOMErrorMessage(hr);
	}
	return filesystem::is_directory(outputPath) && filesystem::is_directory(overlayPath);
}

void PathBuilder::findDLLPath() {
	TCHAR path[_MAX_PATH + 1];
	GetModuleFileName(GetModuleHandle(("ALR.dll")), path, sizeof(path) / sizeof(path[0]));
	for (int i = 0; path[i + PLUGIN_PATH_LEN] != 0; i++)
		pathSS << path[i];

	outputPath = pathSS.str() + "Textures\\Interface\\ALR_Backgrounds\\";
	pathData->iniPath = pathSS.str() + "F4SE\\Plugins\\ALR.ini";
	overlayPath = pathSS.str() + "Textures\\Interface\\Objects\\LoadScreen\\";
}

void PathBuilder::findInputFiles() {
	for (auto& i : std::filesystem::directory_iterator(inputPath)) {
		if (i.path().extension() == ".jpg" || i.path().extension() == ".png" || i.path().extension() == ".JPG" || i.path().extension() == ".PNG")
			inputFiles.emplace_back(i.path().stem().string() + i.path().extension().string());
	}
}

void PathBuilder::correctFiles() {

	random_device rd;
	mt19937 g(rd());

	if (inputFiles.size() > MAX_INPUTS) {
		shuffle(inputFiles.begin(), inputFiles.end(), g);
		inputFiles.resize(MAX_INPUTS);

	} else if (inputFiles.size() < MAX_INPUTS) {

		vector<string> tCopy = inputFiles;
		for (int i = 0; inputFiles.size() < MAX_INPUTS; i++) {
			shuffle(tCopy.begin(), tCopy.end(), g);
			inputFiles.insert(inputFiles.end(), tCopy.begin(), tCopy.end());
		}
		inputFiles.resize(MAX_INPUTS);
	}
}

void PathBuilder::generateInputPaths() {
	for (_int64 i = 0; i < MAX_INPUTS; i++) {
		string temp = inputPath + inputFiles.at(i);
		pathData->inputFilePaths.emplace_back(wstring(temp.begin(), temp.end()));
	}
}

void PathBuilder::generateOutputPaths() {
	for (int i = 0; i < MAX_INPUTS; i++) {
		string temp = outputPath + to_string(i) + ".dds";
		pathData->outputPaths.at(i) = wstring(temp.begin(), temp.end());
	}
	string temp = overlayPath + "Overlay01_d.DDS";
	pathData->overlayPath = wstring(temp.begin(), temp.end());
}

bool PathBuilder::verifyImages()
{
	for (int i = 0; i < MAX_INPUTS; i++) 
		if (!filesystem::exists(pathData->outputPaths.at(i)))
			return false;
	return true;
}

bool PathBuilder::verifyOverlay()
{
	return filesystem::exists(pathData->overlayPath);
}
