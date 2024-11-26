#include "ClearScene.h"
#include <SceneManager.h>
#include <Novice.h>

extern SceneManager sceneManager;

void ClearScene::onEnter()
{
    fireFlower_.Init();
    fireFlowerTime_ = 180;
}

void ClearScene::onInput(char* keys, char* prekeys)
{
    if (keys[DIK_SPACE] && !prekeys[DIK_SPACE])
    {
        sceneManager.switchScene(SceneManager::SceneType::Game);
    }
}

void ClearScene::update()
{
    fireFlower_.Update();
    fireFlowerTime_--;

    if (fireFlowerTime_ <= 0) {
        fireFlower_.Create();
        fireFlowerTime_ = 180;
    }
}

void ClearScene::draw(const Camera& camera)
{
    Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x333333FF, kFillModeSolid);
    fireFlower_.Draw();

    Novice::DrawLine(0, 720 / 2, 1280, 720 / 2, 0x4A505FFF);
    Novice::DrawEllipse(1280 / 2 + (int)camera.GetPos().x, 720 / 2, 20, 20, 0.0f, 0x4A505FFF, kFillModeSolid);
}
