#pragma once
#include <string>

class GameObject;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(GameObject* pActor, GameObject* pTarget) = 0;
	
	virtual std::string GetCommandName() const = 0;
	virtual int GetMpCost() const { return 0; }
};

