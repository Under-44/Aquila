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
	DWORD EntityPlayerListCheck(int i);
	void radar(bool radarHax);
	void Glow(bool glow, AquilaColor EnemyGlow, AquilaColor TeamGlow, bool fullbloomlocal, bool fullbloomenemy); // idk how to declare this
private:
};

