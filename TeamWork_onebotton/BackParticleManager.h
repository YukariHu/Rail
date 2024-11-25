#pragma once
#include "BackParticle.h"
#include "MyVector2.h"
#include <list>

class BackParticleManager
{
public:
    BackParticleManager();
    ~BackParticleManager();

    void Init();
    void Update();
    void Draw();
    void Finalize();
    void Create(const Vector2& direction, bool isStart);

private:
    void DeleteParticle();
    std::list<BackParticle*> mpParticle_;
};

