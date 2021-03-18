#include <Windows.h>
#include "structandstuff.h"
class Misc
{
public:
	Misc();
	void bhop(bool bhop);
	float velocity();
	float Entityvelocity(int index);
	void noflash(float flash);
	void PlayerDeathSound();
	int idcrosshair(bool crossidbool);
	void radar(bool radarHax);
	void Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy, bool velocityglow_local, bool velocityglow_enemy);
	vec3 EntityPos(int index);
	vec3 PlayerPos();
	float EntityDistanceFromPlayer(bool crossidbool, int index);


	//random
	void jebaited();
private:
};

