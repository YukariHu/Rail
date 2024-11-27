#pragma once
#include <list>
#include "TitlePlayerParticle.h"

class TitlePlayerParticleManager
{
public:
    TitlePlayerParticleManager();
    ~TitlePlayerParticleManager();

    void Init();
    void Create(Vector2 playerPos);
    void Update();
    void Draw();

private:
    std::list<TitlePlayerParticle*> particles_;
};
