#pragma once
#include "MyVector2.h"

class BackParticle
{
public:
    BackParticle();
    ~BackParticle();

    void Init(const Vector2& direction);
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
    int randNum_;
    int color_;

};

