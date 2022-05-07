#pragma once
#include "script.hpp"

void script::Smoothing(double delay, double control_time, int x, int y) {
	int x_ = 0, y_ = 0, t_ = 0;
	for (int i = 1; i <= (int)control_time; ++i) {
		int xI = i * x / (int)control_time;
		int yI = i * y / (int)control_time;
		int tI = i * (int)control_time / (int)control_time;
		mouse_event(1, (int)xI - (int)x_, (int)yI - (int)y_, 0, 0);
		sleep((int)tI - (int)t_);
		x_ = xI; y_ = yI; t_ = tI;
	}
	sleep((int)delay - (int)control_time);
}
int script::IsMuzzleBoost(float Delay) {
	if (script::active::weapon == script::states::barrel::boost) {
		float difference = Delay * 0.1f;
		Delay = Delay - difference;
		return (int)Delay + 2;
	}
	else
		return (int)Delay;
}
double script::Barrels() {
	if (script::active::barrel == script::states::barrel::silencer) {
		if (script::active::weapon == script::states::weapon::m249)
			Multiplyer::Barrel.Suppressor = 0.75;
		if (script::active::weapon == script::states::weapon::custom)
			Multiplyer::Barrel.Suppressor = 0.85;
		if (script::active::scope == script::states::scope::simple || script::active::scope == script::states::scope::holo)
			return 0.75;
		if (script::active::scope == script::states::scope::x8 == true && script::active::barrel == script::states::barrel::boost)
			return 1.46;
		else
			return Multiplyer::Barrel.Suppressor;
	}
	else if (script::active::barrel == script::states::barrel::boost) {
		return Multiplyer::Barrel.None;
	}
	else
		return Multiplyer::Barrel.None;
}
double script::Scopes() {
	if (script::active::scope == script::states::scope::x8) {
		if (script::active::weapon == script::states::weapon::custom || script::active::weapon == script::states::weapon::tommy) {
			if (script::active::scope == script::states::scope::x8)
				return Multiplyer::Scope.x8 + 0.75;
		}
		return Multiplyer::Scope.x8;
	}
	else if (script::active::scope == script::states::scope::x8) {
		if (script::active::scope == script::states::weapon::ak) {
			if (script::active::scope == script::states::scope::x8)
				return Multiplyer::Scope.x8 + 0.00279;
		}
		return Multiplyer::Scope.x8;
	}
	else if (script::active::scope == script::states::scope::simple) {
		if (script::active::weapon == script::states::weapon::custom || script::active::weapon == script::states::weapon::tommy) {
			if (script::active::scope == script::states::scope::simple)
				return Multiplyer::Scope.Simple + 0.1;
		}
		return Multiplyer::Scope.Simple;
	}
	else if (script::active::scope == script::states::scope::holo) {
		if (script::active::weapon == script::states::weapon::custom || script::active::weapon == script::states::weapon::tommy) {
			if (script::active::scope == script::states::scope::holo)
				return Multiplyer::Scope.Holo + 0.3;
		}
		return Multiplyer::Scope.Holo;
	}
	else if (script::active::scope == script::states::scope::simple) {
		if (script::active::scope == script::states::weapon::ak) {
			if (script::active::scope == script::states::scope::holo)
				return Multiplyer::Scope.Holo + 0.01395;
		}
		return Multiplyer::Scope.Holo;
	}
	else if (script::active::scope == script::states::scope::x16) {
		return Multiplyer::Scope.x16;
	}
	else
	return Multiplyer::Scope.None;
}
void script::sleep(int ms)
{
	LONGLONG timerResolution;
	LONGLONG wantedTime;
	LONGLONG currentTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
	timerResolution /= 1000;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	wantedTime = currentTime / timerResolution + ms;
	currentTime = 0;
	while (currentTime < wantedTime)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		currentTime /= timerResolution;
	}
}
namespace CurrentWeapon {
	 double x(int Bullet) 
	 {
		 if (vars::control_x != 0)
		 {
			 if (script::active::weapon == script::states::weapon::ak)
				 return (((Recoil_Ak47[Bullet].x * script::Scopes()) * script::Barrels()) / 4)/ vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::lr)
				 return (((Recoil_Lr300[Bullet].x * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::mp5)
				 return (((Recoil_Mp5a4[Bullet].x * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::tommy)
				 return (((Recoil_Thompson_g[Bullet].x * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::custom)
				 return (((Recoil_Custom_g[Bullet].x * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::m249)
				 return (((Recoil_M249[Bullet].x * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_x / 100);
			 else if (script::active::weapon == script::states::weapon::semi)
				 return (((Recoil_Semi_r[Bullet].x * script::Scopes()) * script::Barrels()) / 4) / vars::sensitivity * (vars::control_x / 100);
			 else
				 return 0;
		 }
	}
	double y(int Bullet) 
	{
		if (vars::control_y != 0)
		{
			if (script::active::weapon == script::states::weapon::ak)
				return (((Recoil_Ak47[Bullet].y * script::Scopes()) * script::Barrels()) / 4) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::lr)
				return (((Recoil_Lr300[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::mp5)
				return (((Recoil_Mp5a4[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::tommy)
				return (((Recoil_Thompson_g[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::custom)
				return (((Recoil_Custom_g[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::m249)
				return (((Recoil_M249[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else if (script::active::weapon == script::states::weapon::semi)
				return (((Recoil_Semi_r[Bullet].y * script::Scopes()) * script::Barrels()) / 2) / vars::sensitivity * (vars::control_y / 100);
			else
				return 0;
		}
	}
	double Delay() {
		if (script::active::weapon == script::states::weapon::ak)
			return WeaponData::AK47.Delay;
		else if (script::active::weapon == script::states::weapon::lr)
			return WeaponData::LR300.Delay;
		else if (script::active::weapon == script::states::weapon::mp5)
			return WeaponData::MP5.Delay;
		else if (script::active::weapon == script::states::weapon::tommy)
			return WeaponData::THOMPSON.Delay;
		else if (script::active::weapon == script::states::weapon::custom)
			return WeaponData::CUSTOM_SMG.Delay;
		else if (script::active::weapon == script::states::weapon::m249)
			return WeaponData::M249.Delay;
		else if (script::active::weapon == script::states::weapon::semi)
			return WeaponData::SEMI.Delay;
		else
			return 0;
	}
	double Control(int bullet) 
	{
		if (script::active::weapon == script::states::weapon::ak)
			return ControlTime_Ak47[bullet];
		else if (script::active::weapon == script::states::weapon::lr)
			return WeaponData::LR300.Delay;
		else if (script::active::weapon == script::states::weapon::mp5)
			return WeaponData::MP5.Delay;
		else if (script::active::weapon == script::states::weapon::tommy)
			return WeaponData::THOMPSON.Delay;
		else if (script::active::weapon == script::states::weapon::custom)
			return WeaponData::CUSTOM_SMG.Delay;
		else if (script::active::weapon == script::states::weapon::m249)
			return WeaponData::M249.Delay;
		else if (script::active::weapon == script::states::weapon::semi)
			return WeaponData::SEMI.Delay;
		else
			return 0;
	}
	int Bullet() {
		if (script::active::weapon == script::states::weapon::ak)
			return Recoil_Ak47.size() - 1;
		else if (script::active::weapon == script::states::weapon::lr)
			return Recoil_Lr300.size() - 1;
		else if (script::active::weapon == script::states::weapon::mp5)
			return Recoil_Mp5a4.size() - 1;
		else if (script::active::weapon == script::states::weapon::tommy)
			return Recoil_Thompson_g.size() - 1;
		else if (script::active::weapon == script::states::weapon::custom)
			return Recoil_Custom_g.size() - 1;
		else if (script::active::weapon == script::states::weapon::m249)
			return Recoil_M249.size() - 1;
		else if (script::active::weapon == script::states::weapon::semi)
			return Recoil_Semi_r.size() - 1;
		else
			return 0;
	}
	void RecoilBreak(int count) {
		if (script::active::weapon == script::states::weapon::semi) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		if (count == CurrentWeapon::Bullet()) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
};
// scuffed but eh 
void script::keybinds()
{
	if (GetAsyncKeyState(vars::keys::ak))
	{
		if (script::active::weapon == script::states::weapon::ak)
			script::active::weapon = script::states::weapon::weapon_none;
		else	
			script::active::weapon = script::states::weapon::ak;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::lr))
	{
		if (script::active::weapon == script::states::weapon::lr)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::lr;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::mp5))
	{
		if (script::active::weapon == script::states::weapon::mp5)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::mp5;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::tommy))
	{
		if (script::active::weapon == script::states::weapon::tommy)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::tommy;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::custom))
	{
		if (script::active::weapon == script::states::weapon::custom)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::custom;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::m249))
	{
		if (script::active::weapon == script::states::weapon::m249)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::m249;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::semi))
	{
		if (script::active::weapon == script::states::weapon::semi)
			script::active::weapon = script::states::weapon::weapon_none;
		else
			script::active::weapon = script::states::weapon::semi;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::holo))
	{
		if (script::active::scope == script::states::scope::holo)
			script::active::scope = script::states::scope::scope_none;
		else
			script::active::scope = script::states::scope::holo;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::x8))
	{
		if (script::active::scope == script::states::scope::x8)
			script::active::scope = script::states::scope::scope_none;
		else
			script::active::scope = script::states::scope::x8;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::x16))
	{
		if (script::active::scope == script::states::scope::x16)
			script::active::scope = script::states::scope::scope_none;
		else
			script::active::scope = script::states::scope::x16;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::simple))
	{
		if (script::active::scope == script::states::scope::simple)
			script::active::scope = script::states::scope::scope_none;
		else
			script::active::scope = script::states::scope::simple;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::silencer))
	{
		if (script::active::barrel == script::states::barrel::silencer)
			script::active::barrel = script::states::barrel::barrel_none;
		else
			script::active::barrel = script::states::barrel::silencer;
		Sleep(200);
	}
	if (GetAsyncKeyState(vars::keys::boost))
	{
		if (script::active::barrel == script::states::barrel::boost)
			script::active::barrel = script::states::barrel::barrel_none;
		else
			script::active::barrel = script::states::barrel::boost;
		Sleep(200);
	}
}
void script::run()
{
	while (true)
	{
		script::keybinds();
		if (script::active::weapon != 0 && vars::recoil) // insanity check :>
		{
			for (int i = 0; i <= CurrentWeapon::Bullet() && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000; i++)
			{
				Smoothing((int)IsMuzzleBoost((float)CurrentWeapon::Delay()), (int)IsMuzzleBoost(CurrentWeapon::Control(i)), (int)CurrentWeapon::x(i), (int)CurrentWeapon::y(i));
				CurrentWeapon::RecoilBreak(i);
			}
			
		}
		Sleep(1);
	}
}