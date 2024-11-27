#pragma once
#include <Scene.h>
#include "FireFlowerManager.h"
#include "ClearName.h"

class ClearScene : public Scene
{
public:
    ClearScene() = default;
    ~ClearScene() = default;

    void onEnter() override;
    void onInput(char* keys, char* prekeys) override;
    void update() override;
    void draw(const Camera& camera) override;

private:
    FireFlowerManager fireFlower_;
    clearName clearName_;

    int fireFlowerTime_;
    int alpha_;
    bool tradition_;
    int bgmHandle;
    int bgmPlayHandle;
    int color_;
};
