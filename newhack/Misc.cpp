#include <cmath>
#include "Misc.h"
#include "OffSets.h"
#include "ModuleGet.h"



ModuleGet modget;
#define CLIENT_DLL modget.getCLIENT_DLL()
#define localPlayer modget.getLocalPlayer()

//global verbals
float flSpeed;
bool once = true;
SGlowStructEnemy glowenemy;
SGlowStructLocal glowlocal;

Misc::Misc()
{
	//init
}

void Misc::bhop(bool bhop) // create new bhop thing also make a crouch bhop.
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

void Misc::Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy, bool velocityglow_local, bool velocityglow_enemy) // optimise this. // make a entity class for this
{
	if (glow)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD currentEntity = EntityPlayerListCheck(i);

			if (currentEntity == 0) continue;
			if (modget.getCurrentEntityHealth(currentEntity) < 1 ||
				modget.getCurrentEntityHealth(currentEntity) > 100) continue;

			int glowindex = *(int*)(currentEntity + m_iGlowIndex);
			int entityTeam = *(int*)(currentEntity + m_iTeamNum);

			if (entityTeam == modget.getLocalTeam())
			{
				//Local Team // change to struct
				
				glowlocal.fullBloom = fullbloomlocal;
				glowlocal.red = TeamGlow.r;
				glowlocal.green = TeamGlow.g;
				glowlocal.blue = TeamGlow.b;
				if (velocityglow_local)
				{
					glowlocal.alpha = (velocity() / 500);
				}
				else
					glowlocal.alpha = TeamGlow.a / static_cast<float>(95.2);
				*(SGlowStructLocal*)(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowlocal;
			}
			else if(entityTeam != modget.getLocalTeam())
			{
				//Enemy Team // change to struct
				glowenemy.fullBloom = fullbloomenemy;
				glowenemy.red = EnemyGlow.r;
				glowenemy.green = EnemyGlow.g;
				glowenemy.blue = EnemyGlow.b;
				if (velocityglow_enemy)
				{
					glowenemy.alpha = (velocity() / 500);
				}
				else
					glowenemy.alpha = EnemyGlow.a / static_cast<float>(95.2);
				*(SGlowStructEnemy*)(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowenemy;
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

