#pragma once
#include "Engine\\GameObject.h"
#include <vector>

class StageManager :
    public GameObject
{
public:
    StageManager(GameObject* parent);
    ~StageManager();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    const std::vector<GameObject*>& GetStageList() const { return stageList_; }
private:
    std::vector<GameObject*> stageList_;
};

