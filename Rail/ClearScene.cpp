#include "ClearScene.h"
#include <SceneManager.h>
#include <Novice.h>
#include "Blend.h"

extern SceneManager sceneManager;

void ClearScene::onEnter()
{
    fireFlower_.Init();
    clearName_.Init();
    fireFlowerTime_ = 30;

    alpha_ = 255;
    tradition_ = false;
    bgmHandle = Novice::LoadAudio("./bgm/clear.mp3");
    bgmPlayHandle = -1;
    color_ = 255;
}

void ClearScene::onInput(char* keys, char* prekeys)
{
    if (keys[DIK_SPACE] && !prekeys[DIK_SPACE] ||
        Novice::IsTriggerMouse(0))
    {
        tradition_ = true;
    }
}

void ClearScene::update()
{
    if (Novice::IsPlayingAudio(bgmPlayHandle) == 0 || bgmPlayHandle == -1)
    {
        bgmPlayHandle = Novice::PlayAudio(bgmHandle, 1, 0.5f);
    }

    fireFlower_.Update();
    fireFlowerTime_--;

    if (fireFlowerTime_ <= 0) {
        fireFlower_.Create();
        fireFlowerTime_ = 100;
    }

    if (!tradition_) {
        alpha_-= 5;

        if(alpha_ <= 0){
            alpha_ = 0;
        }
        color_ = 255;
    } else {
        alpha_ += 5;
        color_ = 0;
        if (alpha_ >= 255) {
            alpha_ = 255;
            sceneManager.switchScene(SceneManager::SceneType::Title);
            Novice::StopAudio(bgmPlayHandle);
        }
    }
    clearName_.Update();
}

void ClearScene::draw(const Camera& camera)
{
    Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x707147FF, kFillModeSolid);

    Novice::DrawLine(0, 720 / 2 + 200, 1280, 720 / 2 + 200, WHITE);
    
    fireFlower_.Draw();

    clearName_.Draw();

    Novice::DrawEllipse(1280 / 2 + (int)camera.GetPos().x, 720 / 2 + 200, 20, 20, 0.0f, WHITE, kFillModeSolid);

    Novice::DrawBox(0, 0, 1280, 720, 0.0f, GetColor(color_, color_, color_, alpha_), kFillModeSolid);
}
