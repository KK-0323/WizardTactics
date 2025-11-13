#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\Fbx.h"
#include <vector>
#include <fstream>

class Stage :
    public GameObject
{
public:
    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Fbx* pFbx_;
    Fbx* blockFbx_;

    static const int STAGE_WIDTH = 10;
    static const int STAGE_HEIGHT = 5;

    int mapData_[STAGE_HEIGHT][STAGE_WIDTH];

    void LoadMapData(const std::string& filename);    
};

