#pragma once
#include <Windows.h>

class ModuleGet
{
public:
	DWORD getCLIENT_DLL();
	DWORD getLocalPlayer();
	int getplayerHealth();
	DWORD getEntityList();
	DWORD getGlowObjectManager();
	int getLocalTeam();
	int getCurrentEntityHealth(DWORD currentEntity);
	int getCurrentEntityDormant(DWORD currentEntity);
	int getplayerdormant();
};

