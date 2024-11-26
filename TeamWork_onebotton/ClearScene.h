#pragma once
#include <Scene.h>
#include "FireFlowerManager.h"

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
    int fireFlowerTime_;
    int alpha_;
    bool tradition_;
};
