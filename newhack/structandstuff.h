#pragma once

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
};
