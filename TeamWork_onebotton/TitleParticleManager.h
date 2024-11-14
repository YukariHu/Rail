#pragma once
#include <Vector2.h>
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
    void Create(const Vector2& direction);  

private:
    std::list<TitleParticle*> mpParticle_;
};
