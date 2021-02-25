#include <Windows.h>
#include "structandstuff.h"
class Misc
{
public:
	Misc();
	void bhop(bool bhop);
	int playercheck(int playercheck);
	float velocity();
	void noflash(float flash);
	void EntityCheckHacks(bool radarHax, bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow);
	void radar(bool radarHax, DWORD currentEntity);
	void Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, DWORD currentEntity); // idk how to declare this
private:
};

