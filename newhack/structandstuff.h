#include <iostream>
#include <Windows.h>


struct vec2
{
	float x, y;
};

struct vec3
{
	float x, y, z;
};

struct vec4
{
	float x, y, z, w;
};

struct AquilaColor
{
	float a, r, g, b;
	// alpha, red, green, blue.
};

enum class Entity_flagsCS : unsigned int {
	on_ground = (1 << 0),
	ducking = (1 << 1),
	water_jump = (1 << 2),
	on_train = (1 << 3),
	in_rain = (1 << 4),
	frozen = (1 << 5),
	at_controls = (1 << 6),
	client = (1 << 7),
	fake_client = (1 << 8),
	in_water = (1 << 9)
};

struct SGlowStructEnemy
{
	float red = 1.f;
	float green = 0.f;
	float blue = 0.f;
	float alpha = 1.f;
	char padding1[8];
	float IDK = 1.f;
	char padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnocclude = false;
	BYTE fullBloom = false;
};

struct SGlowStructLocal
{
	float red = 0.f;
	float green = 1.f;
	float blue = 0.f;
	float alpha = 1.f;
	char padding1[8];
	float IDK = 1.f;
	char padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnocclude = false;
	BYTE fullBloom = false;
};
