#ifndef GENERAL_H
#define GENERAL_H

#include <Windows.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <winioctl.h>
#include <iostream>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <dwmapi.h>
#include <d3d11.h>
#include <string>
#include <sstream>
#include <shlobj.h>

#pragma comment(lib, "ntdll.lib")

#include "driver_resource.h"


#include "service.h"
#include "nt.h"
#include "intel_driver.h"
#include "utils.h"
#include "magic.h"
#include "memory.h"
namespace global
{
	inline uint64_t GameBase = 0;
	inline bool unloaddrv = true;
	inline int sleeptime = 1;

}

#endif
