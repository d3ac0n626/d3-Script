#pragma once
#ifndef COMMON_H
#define COMMON_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>
#include <dwmapi.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3d9.h>
#include <DirectX9/Include/d3dx9tex.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx9.h>
#include <ImGui/imgui_impl_win32.h>



#include "utils.hpp"
#endif // !COMMON_H


