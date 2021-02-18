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
		for (int i = 1; i < 64; i++)
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


