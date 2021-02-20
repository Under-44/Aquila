#include "includes.h"

struct vector
{
	float x, y, z;
};

enum class Entity_flags : unsigned int {
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
}entflags;

struct SGlowStructEnemy
{
	float red = 0.f;
	float green = 0.f;
	float blue = 0.f;
	float alpha = 0.f;
	uint8_t padding1[8];
	float IDK = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnocclude = false;
	BYTE fullBloom = false;
}glowEnemyStrc;

struct SGlowStructLocal
{
	float red = 0.f;
	float green = 0.f;
	float blue = 0.f;
	float alpha = 0.f;
	uint8_t padding1[8];
	float IDK = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnocclude = false;
	BYTE fullBloom = false;
}glowLocalStrc;
