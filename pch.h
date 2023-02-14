#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define _WIN32_WINNT_WIN10 0x0A00

#define PLUGIN_VERSION 1
#define PLUGIN_NAME "ALR"

#define PLUGIN_PATH_LEN 20
#define MAX_INPUTS 25

#include <Windows.h>
#include <DirectXTex-master/DirectXTex/DirectXTex.h>
#include <comdef.h>
#include <memory>
#include <thread>
#include <process.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <random>
#include <vector>
#include <array>
#include <shlobj.h>
#include <limits>
#include <numeric>

#include "F4SE/PluginAPI.h"
#include "f4se_common/f4se_version.h"

using namespace std;
using namespace DirectX;