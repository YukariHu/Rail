#pragma once
#include <Scene.h>
#include "TitleLine.h"
#include "TitlePlayer.h"
#include "TitlePlayerParticleManager.h"
#include "TitleParticleManager.h"
#include "titleName.h"

class TitleScene : public Scene
{
public:
    TitleScene() = default;
    ~TitleScene() = default;

    void onEnter() override;
    void onInput(char* keys, char* prekeys) override;
    void update() override;
    void draw(const Camera& camera) override;

private:
    TitleLine titleLine_;                        
    TitlePlayer player_;                             
    TitleParticleManager titleParticle_;
    titleName titleName_;

    int titleSceneParticleTime_;
    int titleScenePlayerParticleTime_;
    int lineLength_;
    int h_;
    int hF_;
    bool isStart = false;
    int bgmHandle;
    int bgmPlayHandle;
};
