#pragma once
#include "Engine\\Command.h"
class AtkCmd :
    public Command
{
public:
    void Execute(GameObject* pActor, GameObject* pTarget) override;
    std::string GetCommandName() const override { return "Attack"; }
};

