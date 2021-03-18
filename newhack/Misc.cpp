#include <cmath>
#include "Misc.h"
#include "OffSets.h"
#include "ModuleGet.h"

//..
// also learn a bit more about the "this" key-word.
//..

ModuleGet modget; // object for modget's.

//global verbals
float flSpeed;
float eplSpeed;

float glow_eplSpeed;

bool once = true;
bool soundbool = true;
int entityid;

vec3 playerVel;
vec3 EVel;
vec3 FinalPostion;

SGlowStructEnemy glowenemy;
SGlowStructLocal glowlocal;

Misc::Misc()
{
	//init
}

void Misc::bhop(bool bhop) // create new bhop thing also make a crouch bhop.
						   // bhop fixed now just need to not move when velocity is 0,
						   // also need to add when on a ladder it disables it.
							
						   // ??idea, add a chance of hitting a bhop slider.
						   // also fix it jumping when out of program or in console or talking.
{
	if (bhop && GetAsyncKeyState(VK_SPACE))
	{
		uintptr_t flag = *reinterpret_cast<BYTE*>(modget.getLocalPlayer() + m_fFlags);
		if (GetAsyncKeyState(VK_SPACE) && modget.getMovmentType() != MoveType::LADDER && modget.getplayerHealth() > 0 && flag & Entity_flagsCS::on_ground)
		{
			*reinterpret_cast<uintptr_t*>(modget.getCLIENT_DLL() + dwForceJump) = 6;
		}
		else if (modget.getMovmentType() == MoveType::LADDER)
		{
			*reinterpret_cast<uintptr_t*>(modget.getCLIENT_DLL() + dwForceJump) = 6;
		}
		else
		{
			*reinterpret_cast<uintptr_t*>(modget.getCLIENT_DLL() + dwForceJump) = 4;
		}

	}
}



float Misc::velocity()
{
	playerVel = *reinterpret_cast<vec3*>(modget.getLocalPlayer() + 0x110); // 0x110 is = velocity.
	flSpeed = static_cast<float>(sqrt(pow(playerVel.y, 2) + pow(playerVel.z, 2)) + 0.00009);
	return flSpeed;
}

float Misc::Entityvelocity(int index) 
{
	EVel = *reinterpret_cast<vec3*>(modget.getEntityPlayerListCheck(index) + 0x110); // 0x110 is = velocity.
	eplSpeed = static_cast<float>(sqrt(pow(EVel.y, 2) + pow(EVel.z, 2)) + 0.00009);
	return eplSpeed;
}

void Misc::noflash(float flash)
{
		*reinterpret_cast<float*>(modget.getLocalPlayer() + m_flFlashMaxAlpha) = (flash * static_cast<float>(2.55));
}


void Misc::radar(bool radarHax)
{
	if (radarHax)
	{
		for (int i = 0; i < 32; i++)
		{
			uintptr_t currentEntity = modget.getEntityPlayerListCheck(i);
			if (currentEntity == 0) continue;
			*reinterpret_cast<int*>(currentEntity + m_bSpotted) = 1;
		}
	}
}

void Misc::Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy, bool velocityglow_local, bool velocityglow_enemy)
// make a global colour and fullbloom and stuff.
{
	if (glow)
	{
		for (int i = 0; i < 32; i++)
		{
			uintptr_t currentEntity = modget.getEntityPlayerListCheck(i);

			if (currentEntity == 0) continue;
			if (modget.getCurrentEntityHealth(currentEntity) < 1 ||
				modget.getCurrentEntityHealth(currentEntity) > 100) continue;

			// velocity glow
			glow_eplSpeed = Entityvelocity(i);
			//

			int glowindex = *reinterpret_cast<int*>(currentEntity + m_iGlowIndex);
			int entityTeam = *reinterpret_cast<int*>(currentEntity + m_iTeamNum);


			if (entityTeam == modget.getLocalTeam())
			{
				//Local Team
				glowlocal.fullBloom = fullbloomlocal; // you need to toggle this everytime a player joins a game.
				glowlocal.red = TeamGlow.r;
				glowlocal.green = TeamGlow.g;
				glowlocal.blue = TeamGlow.b;
				if (velocityglow_local)
				{
					glowlocal.alpha = (glow_eplSpeed / 500); // make the value a slider or use the alpha and just times it // do this
				}

				else
					glowlocal.alpha = TeamGlow.a / static_cast<float>(95.2);
				*reinterpret_cast<SGlowStructLocal*>(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowlocal;
			}
			else if(entityTeam != modget.getLocalTeam())
			{
				//Enemy Team
				glowenemy.fullBloom = fullbloomenemy; // you need to toggle this everytime a player joins a game.
				
				glowenemy.red = EnemyGlow.r;
				glowenemy.green = EnemyGlow.g;
				glowenemy.blue = EnemyGlow.b;
				if (velocityglow_enemy)
				{
					glowenemy.alpha = (glow_eplSpeed / 500); // make the value a slider or use the alpha and just times it // do this
				}
				else
					glowenemy.alpha = EnemyGlow.a / static_cast<float>(95.2);
				*reinterpret_cast<SGlowStructEnemy*>(modget.getGlowObjectManager() + (glowindex * 0x38) + 0x4) = glowenemy;
			}
		}
	}
}

// ..Create trigger bot

// ..Create a player resourse thing to get all the players names. and store it somehow
// then i could add on more to this feature, example is flowhooks player list.
// ??idea on how to do it is create a function the requires a index number, then return the struct with the data, then show that info
// depending on what wiget you're focused on at that time.

//??idea create a translate text chat command.

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

int Misc::idcrosshair(bool crossidbool)
{
	if (crossidbool)
	{
		entityid = modget.getCH();
		return entityid;
	}
	return FALSE;
}

vec3 Misc::EntityPos(int index) // bug here fix it, id 10 crashs the game
{
	return *reinterpret_cast<vec3*>(modget.getEntityPlayerListCheck(index) + m_vecOrigin);
}

vec3 Misc::PlayerPos()
{
	return *reinterpret_cast<vec3*>(modget.getLocalPlayer() + m_vecOrigin);
}

float Misc::EntityDistanceFromPlayer(bool crossidbool, int index)
{
	if (crossidbool)
	{
		if (modget.getEntityHealth(index) != 0)
		{
			FinalPostion.x = PlayerPos().x - EntityPos(index - 1).x;
			FinalPostion.y = PlayerPos().y - EntityPos(index - 1).y;

			return static_cast<float>(sqrt(pow(FinalPostion.x, 2) + pow(FinalPostion.y, 2)));
		}
	}
	return FALSE;
}

void Misc::jebaited()
{
	ShellExecute(NULL, NULL,
		"https://www.youtube.com/watch?v=iIYK1LsBZbo",
		NULL, NULL,
		SW_SHOWNORMAL);
}


