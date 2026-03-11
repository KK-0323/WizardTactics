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
};