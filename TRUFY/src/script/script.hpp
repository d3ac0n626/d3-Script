#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <string>
#include <fcntl.h> 
#include <io.h>
#include <fcntl.h> 
#include <cstdio>
#include <conio.h>

//tables
#include "others/recoilTables.h"
#include "vars.hpp"
namespace script
{
	void Smoothing(double delay, double control_time, int x, int y);
	int IsMuzzleBoost(float Delay);
	double Scopes();
    double Barrels();
    void sleep(int ms);
    void run();
	void keybinds();
	// text storage 
	inline const char* weaponStr[] = { ("none"), ("assault rifle"), ("lr-300"), ("mp5"), ("thompson"), ("custom"), ("m249"), ("semi-rifle") };
	inline const char* scopesStr[] = { ("none"),("holo"), ("8x"), ("16x") };
	inline const char* barrelStr[] = { ("none"),("silencer"), ("boost") };
	// weapon storage 
	namespace states
	{
		enum weapon : int {
			weapon_none = 0,
			ak,
			lr,
			mp5,
			tommy,
			custom,
			m249,
			semi
		};
		enum scope : int {
			scope_none = 0,
			holo,
			x8,
			x16,
			simple
		};
		enum barrel : int {
			barrel_none = 0,
			silencer,
			boost
		};
	}
	namespace active
	{
		// current active
		 inline int weapon = states::weapon::weapon_none;
		 inline int scope = states::scope::scope_none;
		 inline int barrel = states::barrel::barrel_none;
	}
	
}