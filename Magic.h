#pragma once
#include "Engine\\GameObject.h"

class Fbx;

enum MAGIC_ID
{
    MAGIC_FIRE,
    MAGIC_WATER,
    MAGIC_THUNDER,
    MAGIC_MAX
};

class Magic :
    public GameObject
{
public:
    Magic(GameObject* parent);
    Magic(GameObject* parent, MAGIC_ID id);
    ~Magic();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
    float magicSpeed_;
    MAGIC_ID magicID_;
};

