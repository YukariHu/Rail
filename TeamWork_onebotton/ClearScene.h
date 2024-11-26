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
    void draw() override;

private:
    FireFlowerManager fireFlower_;
    int fireFlowerTime_;
};
