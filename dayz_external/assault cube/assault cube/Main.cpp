#include <iostream>
#include <Windows.h>
//yeyeyeye
#include "GameEngine.h"
#include "offsets.h"
#include "Memory.h"
#include "ConsoleMenu.h"

using namespace offsets;

MenuFeatureBool Brightness;
MenuFeatureFloat BrightnessLevel;


using std::cout;
using std::endl;



void SetUpFt() {
	Brightness.title = "Brightness";
	Brightness.value = false;

	BrightnessLevel.title = "Brightness Level";
	BrightnessLevel.value = 10.0f;
}

int main() {
	SetUpFt();

	ConsoleMenu menu;
	menu.addFeature(&Brightness);
	menu.addFeature(&BrightnessLevel);

	CDispatcher* mem = CDispatcher::Get();
	mem->Attach("DayZ_x64.exe");
	uint64_t base = mem->GetModuleBase("DayZ_x64.exe");
	uint64_t worldPtr = mem->ReadMemory<uint64_t>(base + xWorld);
	World world = mem->ReadMemory<World>(worldPtr);
	
	SetConsoleTitle("z3n1th");

	menu.printMenu();

	while (!GetAsyncKeyState(VK_NUMPAD0)) { 
		if (Brightness.value) {
			mem->WriteMemory<float>(worldPtr + offsetof(World, EyeAccom), BrightnessLevel.value);
		}
		else {
			mem->WriteMemory<float>(worldPtr + offsetof(World, EyeAccom), 1.0f);
		}
		
		Sleep(100);
		menu.update();
	}


	return 0;
}

