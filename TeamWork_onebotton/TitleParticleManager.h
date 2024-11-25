#pragma once
#include <MyVector2.h>
#include <list>
#include "TitleParticle.h"

class TitleParticleManager {
public:
    TitleParticleManager();
    ~TitleParticleManager();

    void Init();
    void Update();
    void Draw();
    void Finalize();
    void Create(const Vector2& direction, bool isStart);

private:
    void DeleteParticle();
    std::list<TitleParticle*> mpParticle_;
};
