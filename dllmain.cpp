// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PathBuilder.h"
#include "PathDestroyer.h"
#include "ImageConvert.h"
#include "PathData.h"

IDebugLog glog;
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

__declspec(dllexport) PathDataParent* PathDataCreate()
{
	return new PathData();
}
__declspec(dllexport) PathBuilderParent* PathBuilderCreate(PathDataParent& PathData)
{
	return new PathBuilder(PathData);
}
__declspec(dllexport) PathDestoryerParent* PathDestoryerCreate(PathDataParent& PathData)
{
	return new PathDestoryer(PathData);
}
__declspec(dllexport) ImageConvertParent* ImageConvertCreate(PathDataParent& PathData)
{
	return new ImageConvert(PathData);
}
PathDataParent* pathData = PathDataCreate();

extern "C"
{
	__declspec(dllexport) bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
	{
		char logPath[MAX_PATH];
		sprintf_s(logPath, MAX_PATH, "%s%s.log", "\\My Games\\Fallout4\\F4SE\\", PLUGIN_NAME);
		glog.OpenRelative(CSIDL_MYDOCUMENTS, logPath);

		_MESSAGE("%s", PLUGIN_NAME, PLUGIN_VERSION);

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = PLUGIN_NAME;
		info->version = PLUGIN_VERSION;

		g_pluginHandle = f4se->GetPluginHandle();

		if (f4se->runtimeVersion < RUNTIME_VERSION_1_10_163) {
			_MESSAGE("ERROR: Version ", CURRENT_RELEASE_RUNTIME, " Required!");
			return false;
		}

		if (f4se->isEditor)
		{
			_MESSAGE("ERROR: isEditor Is True");
			return false;
		}

		return true;
	}

	__declspec(dllexport) bool F4SEPlugin_Load(const F4SEInterface* f4se)
	{
		_MESSAGE("%s loaded", PLUGIN_NAME);

		PathBuilderParent* PBinst = PathBuilderCreate(*pathData);
		ImageConvertParent* IMinst = ImageConvertCreate(*pathData);

		delete PBinst;
		delete IMinst;
		return true;
	}
};

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:

		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:

		PathDestoryerParent* PDinst = PathDestoryerCreate(*pathData);
		delete PDinst;
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}