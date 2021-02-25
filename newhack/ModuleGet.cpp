#include "ModuleGet.h"
#include "OffSets.h"
#include <Windows.h>
#include "Misc.h"


DWORD ModuleGet::getCLIENT_DLL()
{
	return (DWORD)GetModuleHandle("client.dll");
}

DWORD ModuleGet::getLocalPlayer()
{
	return *(DWORD*)(getCLIENT_DLL() + dwLocalPlayer);
}

int ModuleGet::getplayerHealth()
{
	return *(int*)(getLocalPlayer() + m_iHealth);
}
DWORD ModuleGet::getGlowObjectManager()
{
	return *(DWORD*)(getCLIENT_DLL() + dwGlowObjectManager);
}

DWORD ModuleGet::getEntityList()
{
	return *(DWORD*)(getCLIENT_DLL() + dwEntityList);
}

int ModuleGet::getLocalTeam()
{
	return *(int*)(getLocalPlayer() + m_iTeamNum);
}

int ModuleGet::getCurrentEntityHealth(DWORD currentEntity)
{
	return *(int*)(currentEntity + m_iHealth);
}

int ModuleGet::getCurrentEntityDormant(DWORD currentEntity)
{
	return *(int*)(currentEntity + m_bDormant);
}
int ModuleGet::getplayerdormant()
{
	return *(int*)(getLocalPlayer() + m_bDormant);
}