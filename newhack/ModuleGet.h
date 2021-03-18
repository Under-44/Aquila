#pragma once
#include <Windows.h>

class ModuleGet
{
public:
	uintptr_t getCLIENT_DLL();
	uintptr_t getLocalPlayer();
	int getplayerHealth();
	uintptr_t getEntityList();
	uintptr_t getGlowObjectManager();
	uintptr_t getEntityPlayerListCheck(int i);
	int getEntityHealth(int index);
	int getLocalTeam();
	int getCurrentEntityHealth(DWORD currentEntity);
	int getCurrentEntityDormant(DWORD currentEntity);
	int getplayerdormant();
	int getMovmentType();
	int getCH();
};

