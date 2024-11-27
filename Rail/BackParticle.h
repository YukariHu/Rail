#pragma once
#include "MyVector2.h"
#include "Camera.h"

class BackParticle
{
public:
    BackParticle();
    ~BackParticle();

    void Init(const Vector2& direction);
    void Update();
    void Draw(const Camera& camera);
    bool IsAlive() const;

    void SetIsStart(bool isStart) { isStart_ = isStart; };
    bool GetIsStart() const { return isStart_; };

private:
    Vector2 pos_;
    Vector2 direction_;
    float rad_;
    float velocity_;
    float oscillation_;
    bool alive_;
    int randNum_;
    int color_;
    bool isStart_;
};

