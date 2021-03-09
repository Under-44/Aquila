#include <Windows.h>
#include "structandstuff.h"
class Misc
{
public:
	Misc();
	void bhop(bool bhop);
	float velocity();
	void noflash(float flash);
	void PlayerDeathSound();
	int idcrosshair(bool crossidbool);
	uintptr_t EntityPlayerListCheck(int i);
	void radar(bool radarHax);
	void Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy, bool velocityglow_local, bool velocityglow_enemy);
private:
};

