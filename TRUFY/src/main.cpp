#include "core/config.hpp"
#include "script/script.hpp"
#include "utils/encrypt.h"
#include "widgets/widgets.hpp"
#include "core/graphics_api.hpp"

bool g_open = true;
bool g_bInfoOverlay = true;
bool g_crosshair = true;
bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return true;
}
ImFont* pLarge = nullptr;
ImFont* pMini = nullptr;
ImVec4 crosshairCol = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
void InitUI()
{
	// get()->fonts
	ImGuiStyle& s = ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();
	// these are fonts 
	io.Fonts->AddFontDefault();
	pLarge = io.Fonts->AddFontFromFileTTF(encrypt("C:\\Windows\\Fonts\\tahoma.ttf"), 30.f);
	pMini = io.Fonts->AddFontFromFileTTF(encrypt("C:\\Windows\\Fonts\\tahoma.ttf"), 25.f);
	// set styles
	s.WindowRounding = 0.f;
	s.WindowPadding = { 10.f, 10.f };
	s.GrabMinSize = 0.5f;
	s.Alpha = 1.f;
	// set colors
	const ImColor accentCol = ImColor(232, 113, 142, 255);
	const ImColor bgSecondary = ImColor(15, 15, 15, 255);
	s.Colors[ImGuiCol_WindowBg] = ImColor(24, 24, 24, 255);
	s.Colors[ImGuiCol_ChildBg] = bgSecondary;
	s.Colors[ImGuiCol_FrameBg] = ImColor(65, 64, 64, 255); // top of gradient
	s.Colors[ImGuiCol_FrameBgActive] = ImColor(35, 37, 39, 255); // bottom of gradient
	s.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_CheckMark] = accentCol;
	s.Colors[ImGuiCol_SliderGrab] = accentCol;
	s.Colors[ImGuiCol_SliderGrabActive] = accentCol;
	s.Colors[ImGuiCol_ScrollbarBg] = bgSecondary;

	// ^^ this are the colors
}
void crosshair(ImVec2 size, ImVec4 color) // scuffed
{
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(GAPI::GetWindowSize().x / 2 - 1, GAPI::GetWindowSize().y / 2), ImVec2(GAPI::GetWindowSize().x / 2 - size.x, GAPI::GetWindowSize().y / 2), ImGui::ColorConvertFloat4ToU32(color));
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(GAPI::GetWindowSize().x / 2, GAPI::GetWindowSize().y / 2 - 1), ImVec2(GAPI::GetWindowSize().x / 2, GAPI::GetWindowSize().y / 2 - size.y), ImGui::ColorConvertFloat4ToU32(color));
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(GAPI::GetWindowSize().x / 2 + 2, GAPI::GetWindowSize().y / 2), ImVec2(GAPI::GetWindowSize().x / 2 + size.x + 1, GAPI::GetWindowSize().y / 2), ImGui::ColorConvertFloat4ToU32(color));
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(GAPI::GetWindowSize().x / 2, GAPI::GetWindowSize().y / 2 + 2), ImVec2(GAPI::GetWindowSize().x / 2, GAPI::GetWindowSize().y / 2 + size.y + 1), ImGui::ColorConvertFloat4ToU32(color));
}
void RenderUI() 
{
	/* get()-> mPos*/
	POINT mPos;
	GetCursorPos(&mPos);
	// window size 
	ImGui::SetNextWindowSize(ImVec2(420, 335));
	/* create :p */
	ImGui::Begin(encrypt("d3 script"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{	
		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		auto isHovering = mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= (pos.x + size.x) && mPos.y <= (pos.y + size.y);
		if (isHovering)
			GAPI::EnableInput();
		if (!isHovering)
			GAPI::DisableInput();
		static auto tab = 1;
		ImGui::PushFont(pLarge);
		ImGui::Text(encrypt("D3 Script"));
		ImGui::PopFont();
		ImGui::SetCursorPosY(55);

		if (ImGui::Button(encrypt("Main"), ImVec2(75, 25))) tab = 1;
		ImGui::SameLine();
		if ( ImGui::Button(encrypt("Keybinds"), ImVec2(75, 25))) tab = 2;
		ImGui::SameLine();
		if (ImGui::Button(encrypt("User"), ImVec2(75, 25))) tab = 3;
		ImGui::SameLine();
		if (ImGui::Button(encrypt("Exit"), ImVec2(75, 25))) exit(-1);
		ImGui::SetCursorPosY(95);
		if (tab == 1)
		{
			/* single group box*/
			if (ImGui::BeginGroupBox(encrypt("Main"), ImVec2(400, 225)))
			{
				ImGui::Combo(encrypt("weapon"), &script::active::weapon, script::weaponStr, IM_ARRAYSIZE(script::weaponStr));
				ImGui::Combo(encrypt("scope"), &script::active::scope, script::scopesStr, IM_ARRAYSIZE(script::scopesStr));
				ImGui::Combo(encrypt("barrel"), &script::active::barrel, script::barrelStr, IM_ARRAYSIZE(script::barrelStr));
				ImGui::Text("");
				ImGui::Checkbox("enable recoil", &vars::recoil);

				ImGui::SliderFloat(encrypt("control x"), &vars::control_x, 0, 100, "%.0f");
				ImGui::SliderFloat(encrypt("control y"), &vars::control_y, 0, 100, "%.0f");
				ImGui::Text("bc1qecx9r0lvgq5u3n5c5quvg88c0wy66cvxnadx46 ");
				ImGui::Text("BTC for donations lmao");
				ImGui::EndGroupBox();
			}
		}
		if (tab == 2)
		{
			/* create more than 1 group box pretty much */
			if (ImGui::BeginGroupBox(encrypt("weapons"), ImVec2(180, 225)))
			{
				ImGui::Hotkey(encrypt("ak"), &vars::keys::ak);
				ImGui::Hotkey(encrypt("lr"), &vars::keys::lr);
				ImGui::Hotkey(encrypt("mp5"), &vars::keys::mp5);
				ImGui::Hotkey(encrypt("tommy"), &vars::keys::tommy);
				ImGui::Hotkey(encrypt("custom"), &vars::keys::custom);
				ImGui::Hotkey(encrypt("m249"), &vars::keys::m249);
				ImGui::Hotkey(encrypt("sar"), &vars::keys::semi);				
				ImGui::EndGroupBox();
			}
			/*horizontal spacing example*/
			ImGui::SameLine();
			if (ImGui::BeginGroupBox(encrypt("scopes"), ImVec2(212, 130)))
			{
				ImGui::Hotkey(encrypt("holo"), &vars::keys::holo);
				ImGui::Hotkey(encrypt("8x"), &vars::keys::x8);
				ImGui::Hotkey(encrypt("16x"), &vars::keys::x16);
				ImGui::Hotkey(encrypt("simple"), &vars::keys::simple);
				ImGui::EndGroupBox();
			}
			/*verical spacing example */
			ImGui::SetCursorPos(ImVec2( /*+*/ 200 - /*size of space*/ ( 2 ) /*gui border scaling*/ , 235));
			if (ImGui::BeginGroupBox(encrypt("barrels"), ImVec2(212, 85)))
			{
    			ImGui::Hotkey(encrypt("silencer"), &vars::keys::silencer);
				ImGui::Hotkey(encrypt("boost"), &vars::keys::boost);
				ImGui::EndGroupBox();
			}
		}
		if (tab == 3)
		{
			ImColor color;
			/* group box without name (make sure to push and pop ID's or they will function as one silly trufy */
			ImGui::PushID(1);
			if (ImGui::BeginGroupBox(encrypt("user"), ImVec2(400, 225)))
			{
				ImGui::PopID();
				ImGui::SliderFloat(encrypt("sensitivity"), &vars::sensitivity, 0, 2, "%.2f");
				ImGui::SetNextItemWidth(200);
				ImGui::ColorPicker4("crosshair color", (float*)&crosshairCol), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoSmallPreview;
				ImGui::SameLine();
				ImGui::Checkbox("enable crosshair", &g_crosshair);
				ImGui::SetCursorPos(ImVec2(222, 55));
				ImGui::Checkbox("info overlay", &g_bInfoOverlay);
				ImGui::EndGroupBox();
			}
		}
	}ImGui::End();	
	if (g_crosshair)
		crosshair(ImVec2(5, 5), ImVec4(crosshairCol));
	auto* pBgDrawList = ImGui::GetBackgroundDrawList();
	if (g_bInfoOverlay)
	{
		ImGui::PushFont(pMini);
		std::vector<std::pair<std::string, ImColor>> overlayInfoText = {
			{script::weaponStr[script::active::weapon], ImColor(255, 255, 255)}, // col
			{script::scopesStr[script::active::scope] , ImColor(255, 255, 255)},
			{script::barrelStr[script::active::barrel], ImColor(255, 255, 255)}
		};
		ImVec2 maxSize = { 0, 0 };
		for (auto& infoText : overlayInfoText) {
			auto size = ImGui::CalcTextSize(infoText.first.c_str());
			if (size.x >= maxSize.x)
				maxSize.x = size.x;
			if (size.y >= maxSize.y)
				maxSize.y = size.y;
		}
		constexpr int padding = 8;
		int startPosX =  padding * 2;
		ImVec2 bgStart = { (float)startPosX - padding, padding * 0.5f };
		ImVec2 bgEnd = { bgStart.x + maxSize.x + (padding * 2), bgStart.y + (overlayInfoText.size() * maxSize.y) + padding };
		pBgDrawList->AddRectFilled(bgStart, bgEnd, ImColor(11, 11, 11, 225));
		for (int i = 0; i < overlayInfoText.size(); i++) {
			pBgDrawList->AddText({ (float)startPosX, padding + (i * maxSize.y) }, overlayInfoText[i].second, overlayInfoText[i].first.c_str());
		}
		ImGui::PopFont();
	}
}
int main() {
	/* hide console % */
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	/* create script on seperate thread so we dont destroy out window fps :( % */
	std::thread(script::run).detach();
	GAPI::MakeWindow
	(
		encrypt("OBS Studio"), // window title
		encrypt("OBS Studio"), // window class
		WndProc,
		InitUI,
		RenderUI
	);
	return 0;
}

