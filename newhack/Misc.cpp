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
bool soundbool = true;
SGlowStructEnemy glowenemy;
SGlowStructLocal glowlocal;

Misc::Misc()
{
	//init
}

void Misc::bhop(bool bhop) // create new bhop thing also make a crouch bhop.
						   // bhop fixed now just need to not move when velocity is 0,
						   // also need to add when on a ladder it disables it.
{
		if (bhop && GetAsyncKeyState(VK_SPACE) && 0x8000)
		{
			DWORD flag = *(BYTE*)(localPlayer + m_fFlags);
			if (modget.getMovmentType() != MoveType::LADDER && modget.getplayerHealth() > 0 && flag & (1 << 0))
			{
				*(DWORD*)(CLIENT_DLL + dwForceJump) = 6;
			}
			else if(modget.getMovmentType() == MoveType::LADDER)
			{
				*(DWORD*)(CLIENT_DLL + dwForceJump) = 6;
			}
			else
			{
				*(DWORD*)(CLIENT_DLL + dwForceJump) = 4;
			}
		}
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

void Misc::Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy, bool velocityglow_local, bool velocityglow_enemy) // optimise this. // make a entity class for this // fix red square bug health thing
{
	if (glow)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD currentEntity = EntityPlayerListCheck(i);

			if (currentEntity == 0) continue;
			if (modget.getCurrentEntityHealth(currentEntity) < 1 ||
				modget.getCurrentEntityHealth(currentEntity) > 100) continue;

			//
			vec3 playerVel = *(vec3*)(EntityPlayerListCheck(i) + 0x110); // 0x110 is = velocity.
			float eplSpeed = static_cast<float>(sqrt(pow(playerVel.y, 2) + pow(playerVel.z, 2)) + 0 /*this is for glow when standing still*/ );
			//
			int glowindex = *(int*)(currentEntity + m_iGlowIndex);
			int entityTeam = *(int*)(currentEntity + m_iTeamNum);


			if (entityTeam == modget.getLocalTeam())
			{
				//Local Team
				glowlocal.fullBloom = fullbloomlocal;
				glowlocal.red = TeamGlow.r;
				glowlocal.green = TeamGlow.g;
				glowlocal.blue = TeamGlow.b;
				if (velocityglow_local)
				{
					glowlocal.alpha = (eplSpeed / 500); // make the value a slider or use the alpha and just times it // do this
				}

				else
					glowlocal.alpha = TeamGlow.a / static_cast<float>(95.2);
				*(SGlowStructLocal*)(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowlocal;
			}
			else if(entityTeam != modget.getLocalTeam())
			{
				//Enemy Team
				glowenemy.fullBloom = fullbloomenemy;
				
				glowenemy.red = EnemyGlow.r;
				glowenemy.green = EnemyGlow.g;
				glowenemy.blue = EnemyGlow.b;
				if (velocityglow_enemy)
				{
					glowenemy.alpha = (eplSpeed / 500); // make the value a slider or use the alpha and just times it // do this
				}
				else
					glowenemy.alpha = EnemyGlow.a / static_cast<float>(95.2);
				*(SGlowStructEnemy*)(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowenemy;
			}
		}b
	}
}

// ..Create trigger bot

// ..Create a player resourse thing to get all the players names. and store it somehow
// then i could add on more to this feature, example is flowhooks player list.
// ??idea on how to do it is create a function the requires a index number, then return the struct with the data, then show that info
// depending on what wiget you're focused on at that time.

void Misc::PlayerDeathSound()
{
	if (modget.getplayerHealth() == 0 && soundbool == true)
	{
		//i have to find a way to put the wav file into the dll.
		// have to put the sound into the csgo file then call it from the ingame console.
		soundbool = false;
	}
	else
	{
		if (modget.getplayerHealth() > 0 && soundbool == false)
		{
			soundbool = true;
		}
	}
}

DWORD Misc::EntityPlayerListCheck(int i)
{
	return *(DWORD*)(CLIENT_DLL + dwEntityList + (i * 0x10));
}

