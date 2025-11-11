#pragma once
#include "Engine\\GameObject.h"

class Fbx; // ‘O•ûéŒ¾

class Player :
    public GameObject
{
    Fbx* pFbx_;
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

