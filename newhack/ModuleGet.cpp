#include "ModuleGet.h"
#include "OffSets.h"
#include <Windows.h>
#include "Misc.h"


uintptr_t ModuleGet::getCLIENT_DLL()
{
	return reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
}

uintptr_t ModuleGet::getLocalPlayer()
{
	return *reinterpret_cast<uintptr_t*>(getCLIENT_DLL() + dwLocalPlayer);
}

int ModuleGet::getplayerHealth()
{
	return *reinterpret_cast<int*>(getLocalPlayer() + m_iHealth);
}
uintptr_t ModuleGet::getGlowObjectManager()
{
	return *reinterpret_cast<uintptr_t*>(getCLIENT_DLL() + dwGlowObjectManager);
}

uintptr_t ModuleGet::getEntityList()
{
	return *reinterpret_cast<uintptr_t*>(getCLIENT_DLL() + dwEntityList);
}

int ModuleGet::getLocalTeam()
{
	return *reinterpret_cast<int*>(getLocalPlayer() + m_iTeamNum);
}

int ModuleGet::getCurrentEntityHealth(DWORD currentEntity)
{
	return *reinterpret_cast<int*>(currentEntity + m_iHealth);
}

int ModuleGet::getCurrentEntityDormant(DWORD currentEntity)
{
	return *reinterpret_cast<int*>(currentEntity + m_bDormant);
}
int ModuleGet::getplayerdormant()
{
	return *reinterpret_cast<int*>(getLocalPlayer() + m_bDormant);
}

int ModuleGet::getCH()
{
	return *reinterpret_cast<int*>(getLocalPlayer() + m_iCrosshairId);
}

int ModuleGet::getMovmentType()
{
	return *reinterpret_cast<int*>(getLocalPlayer() + m_MoveType);
}