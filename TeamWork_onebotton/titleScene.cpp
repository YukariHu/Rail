﻿#include "TitleScene.h"
#include <Novice.h>
#include "SceneManager.h"

extern SceneManager sceneManager;

float tLerp(float start, float end, float t)
{
    return start + t * (end - start);
}


void TitleScene::onEnter()
{
    titleLine_.Init();
    player_.Init();
    titleName_.Init();
    titleSceneParticleTime_ = 100;
    titleScenePlayerParticleTime_ = 100;
    lineLength_ = 0;
    h_ = 0;
    hF_ = false;
}

void TitleScene::onInput(char* keys, char* prekeys)
{
    if (keys[DIK_SPACE] && !prekeys[DIK_SPACE] /*||*/
       /* Novice::IsTriggerMouse(0)*/) {
        hF_ = true;
        player_.SetTran(hF_);
    }

    if (h_ >= 1400) {
        sceneManager.switchScene(SceneManager::SceneType::StageSelect);
    }
}

void TitleScene::update()
{
    titleParticle_.Update();
    titleSceneParticleTime_--;

    if (titleSceneParticleTime_ <= 0) {
        titleParticle_.Create({ -1.0f, 1.0f }); 
        titleSceneParticleTime_ = 5; 
    }

    lineLength_ += 50;
    if (lineLength_ >= 1280) {
        lineLength_ = 1280;
    }

    titleLine_.Update(lineLength_);

    player_.Update();

    titleName_.Update();

    /*if (hF_) {

        h_ += 1;
        if (h_ >= 600) {
            h_ = 600;
        }
    }*/

    if (player_.GetPos().x >= 1280.0f) {
        h_ = (int)tLerp((float)h_, 1500.0f, 0.05f);
    }
}

void TitleScene::draw()
{

    Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x161A30FF, kFillModeSolid);

    titleParticle_.Draw();

    titleName_.Draw();

    Novice::DrawEllipse(1280, 720 / 2, h_, h_, 0.0f, WHITE, kFillModeSolid);

    titleLine_.Draw();

    player_.Draw();

}
