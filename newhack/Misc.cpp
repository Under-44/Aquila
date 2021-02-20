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

void Misc::radar(bool radarHax, bool glow)
{
	if (radarHax && glow == false)
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
		if (bhop && GetAsyncKeyState(VK_SPACE) && 0x8000)
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

void Misc::Glow(bool glow, float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2)
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
				//Local Team // change to struct
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = r1; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = g1; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = b1; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = a1; //a
			}
			else
			{
				//Enemy Team // change to struct
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = r2; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = g2; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = b2; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = a2; //a
			}
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x24)) = true;
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x25)) = false;
		}
	}
}

