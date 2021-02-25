#include <cmath>
#include "Misc.h"
#include "OffSets.h"
#include "ModuleGet.h"



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
	vec3 playerVel = *(vec3*)(localPlayer + 0x110); // 0x110 is = velocity.
	flSpeed = static_cast<float>(sqrt(pow(playerVel.y, 2) + pow(playerVel.z, 2)) + 0.00009);
	return flSpeed;
}

void Misc::noflash(float flash)
{
		*(float*)(localPlayer + m_flFlashMaxAlpha) = (flash * static_cast<float>(2.55));
}


void Misc::radar(bool radarHax)
{
	if (radarHax)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD currentEntity = EntityPlayerListCheck(i);
			if (currentEntity == 0) continue;
			*(int*)(currentEntity + m_bSpotted) = 1;
		}
	}
}

void Misc::Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow) // optimise this. // make a entity class for this
{
	if (glow)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD currentEntity = EntityPlayerListCheck(i);

			if (currentEntity == 0) continue;

			int glowindex = *(int*)(currentEntity + m_iGlowIndex);
			int entityTeam = *(int*)(currentEntity + m_iTeamNum);

			if (entityTeam == modget.GetLocalTeam())
			{
				//Local Team // change to struct
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = TeamGlow.r; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = TeamGlow.g; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = TeamGlow.b; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = TeamGlow.a; //a
			}
			else
			{
				//Enemy Team // change to struct
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x4)) = EnemyGlow.r; //r
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x8)) = EnemyGlow.g; //g
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0xC)) = EnemyGlow.b; //b
				*(float*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x10)) = EnemyGlow.a; //a
			}
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x24)) = true;
			*(bool*)((modget.getGlowObjectManager() + glowindex * 0x38 + 0x25)) = false;
		}
	}
}

DWORD Misc::EntityPlayerListCheck(int i)
{
	return *(DWORD*)(CLIENT_DLL + dwEntityList + (i * 0x10));
}
