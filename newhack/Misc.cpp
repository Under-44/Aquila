#include <cmath>
#include "Misc.h"
#include "OffSets.h"
#include "ModuleGet.h"
#include "structandstuff.h"

ModuleGet modget;
#define CLIENT_DLL modget.getCLIENT_DLL()
#define localPlayer modget.getLocalPlayer()

//global verbals
DWORD currentEntity;
float flSpeed;
bool once = true;


Misc::Misc()
{
	//init
}

void Misc::radar(bool radarHax)
{
	if (radarHax)
	{
		for (int i = 1; i < 32; i++)
		{
			currentEntity = *(DWORD*)(CLIENT_DLL + dwEntityList + (i * 0x10));
			if (currentEntity > 0)
			{
				*(int*)(currentEntity + m_bSpotted) = 1;
			}
		}
	}
}

void Misc::bhop(bool bhop)
{
	if (bhop && GetAsyncKeyState(VK_SPACE))
	{
		DWORD flag = *(BYTE*)(localPlayer + m_fFlags);
		if (modget.getplayerHealth() > 0 && flag & (1 << 0))
		{
			*(DWORD*)(CLIENT_DLL + dwForceJump) = 6;
		}
	}
}

int Misc::playercheck(int playercheck)
{
	playercheck = localPlayer;
	return playercheck;
}

float Misc::velocity()
{
	vector playerVel = *(vector*)(localPlayer + 0x110); // 0x110 is = velocity.
	flSpeed = sqrt(pow(playerVel.y, 2) + pow(playerVel.z, 2)) + 0.00009;
	return flSpeed;
}

void Misc::noflash(float flash)
{
		*(float*)(localPlayer + m_flFlashMaxAlpha) = (flash * 2.55);
}

void Misc::Glow(bool glow)
{
	if (glow)
	{
		int localTeam = *(int*)(modget.getLocalPlayer() + m_iTeamNum);
		for (int i = 1; i < 32; i++)
		{
			currentEntity = *(DWORD*)(CLIENT_DLL + dwEntityList + (i * 0x10));
			if (currentEntity == 0) continue;

			int glowindex = *(int*)(currentEntity + m_iGlowIndex);
			int entityTeam = *(int*)(currentEntity + m_iTeamNum);

			if (entityTeam == localTeam)
			{
				//Local Team
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = 0.f; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = 1.f; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = 0.f; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = 1.7f; //a
			}
			else
			{
				//Enemy Team
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = 1.f; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = 0.f; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = 0.f; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = 1.7f; //a
			}
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x24)) = true;
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x25)) = false;
		}
	}
}

