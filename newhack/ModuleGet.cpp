#include "ModuleGet.h"
#include "OffSets.h"
#include <Windows.h>

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