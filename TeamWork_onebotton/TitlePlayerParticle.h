#pragma once
#include <Vector2.h>

class TitlePlayerParticle
{
public:
    TitlePlayerParticle();
    ~TitlePlayerParticle();

    void Init(Vector2 playerPos);
    void Update();
    void Draw();
    bool IsAlive() const;

private:
    Vector2 pos_;
    Vector2 direction_;
    float rad_;
    float velocity_;
    float oscillation_;
    bool alive_;
};
