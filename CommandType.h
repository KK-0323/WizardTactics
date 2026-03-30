#pragma once

enum class CommandType
{
	NONE,
	ATTACK,
	DEFENSE,
	SKILL,
	MAX
};

struct OrderData
{
	CommandType type_ = CommandType::NONE;
	float power_ = 0.0f;
	int targetId_ = -1;
};