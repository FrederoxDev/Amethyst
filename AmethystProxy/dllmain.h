#pragma once

#pragma comment(linker, "/export:ApplyCompatResolutionQuirking=c:\\windows\\system32\\dxgi.ApplyCompatResolutionQuirking,@1")
#pragma comment(linker, "/export:CompatString=c:\\windows\\system32\\dxgi.CompatString,@2")
#pragma comment(linker, "/export:CompatValue=c:\\windows\\system32\\dxgi.CompatValue,@3")
#pragma comment(linker, "/export:CreateDXGIFactory=c:\\windows\\system32\\dxgi.CreateDXGIFactory,@10")
#pragma comment(linker, "/export:CreateDXGIFactory1=c:\\windows\\system32\\dxgi.CreateDXGIFactory1,@11")
#pragma comment(linker, "/export:CreateDXGIFactory2=c:\\windows\\system32\\dxgi.CreateDXGIFactory2,@12")
#pragma comment(linker, "/export:DXGID3D10CreateDevice=c:\\windows\\system32\\dxgi.DXGID3D10CreateDevice,@13")
#pragma comment(linker, "/export:DXGID3D10CreateLayeredDevice=c:\\windows\\system32\\dxgi.DXGID3D10CreateLayeredDevice,@14")
#pragma comment(linker, "/export:DXGID3D10GetLayeredDeviceSize=c:\\windows\\system32\\dxgi.DXGID3D10GetLayeredDeviceSize,@15")
#pragma comment(linker, "/export:DXGID3D10RegisterLayers=c:\\windows\\system32\\dxgi.DXGID3D10RegisterLayers,@16")
#pragma comment(linker, "/export:DXGIDeclareAdapterRemovalSupport=c:\\windows\\system32\\dxgi.DXGIDeclareAdapterRemovalSupport,@17")
#pragma comment(linker, "/export:DXGIDumpJournal=c:\\windows\\system32\\dxgi.DXGIDumpJournal,@4")
#pragma comment(linker, "/export:DXGIGetDebugInterface1=c:\\windows\\system32\\dxgi.DXGIGetDebugInterface1,@18")
#pragma comment(linker, "/export:DXGIReportAdapterConfiguration=c:\\windows\\system32\\dxgi.DXGIReportAdapterConfiguration,@19")
#pragma comment(linker, "/export:PIXBeginCapture=c:\\windows\\system32\\dxgi.PIXBeginCapture,@5")
#pragma comment(linker, "/export:PIXEndCapture=c:\\windows\\system32\\dxgi.PIXEndCapture,@6")
#pragma comment(linker, "/export:PIXGetCaptureState=c:\\windows\\system32\\dxgi.PIXGetCaptureState,@7")
#pragma comment(linker, "/export:SetAppCompatStringPointer=c:\\windows\\system32\\dxgi.SetAppCompatStringPointer,@8")
#pragma comment(linker, "/export:UpdateHMDEmulationStatus=c:\\windows\\system32\\dxgi.UpdateHMDEmulationStatus,@9")

#include "filesystem"
#include "fstream"
#include "ios"
#include "windows.h"
#include <amethyst/Config.h>
#include <amethyst/Log.h>
#include <shlobj_core.h>

#pragma warning(disable: 4996)
#include "iostream"

#define PROXY_VERSION "1.0.0"

void Shutdown();
void ShutdownWait();