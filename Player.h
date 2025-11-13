#pragma once
#include "Engine\\GameObject.h"

class Fbx; // ‘O•ûéŒ¾

class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Fbx* pFbx_;
    float moveSpeed;
};

