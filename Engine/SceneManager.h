#pragma once
#include "GameObject.h"

enum SCENE_ID
{
    SCENE_ID_TITLE,
    SCENE_ID_PLAY,
    SCENE_ID_BATTLE,
    SCENE_ID_CLEAR,
    SCENE_ID_GAMEOVER,
    SCENE_ID_MAX
};
class SceneManager :
    public GameObject
{
public:
    SceneManager(GameObject* parent);
    ~SceneManager();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ChangeScene(SCENE_ID nextScene);
    
    SCENE_ID GetCurrentSceneID() const { return currentSceneID_; }
private:
    SCENE_ID currentSceneID_;
    SCENE_ID nextSceneID_;
};

