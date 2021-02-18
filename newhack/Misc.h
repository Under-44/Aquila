#pragma once
#include <Windows.h>
class Misc
{
public:
	Misc();
	void radar(bool radarHax, bool glow);
	void bhop(bool bhop);
	int playercheck(int playercheck);
	float velocity();
	void noflash(float flash);
	void Glow(bool glow, float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2);
};

