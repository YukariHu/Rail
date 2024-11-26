#pragma once
#include <Vector2.h>

class FireFlower {
public:
    FireFlower();
    ~FireFlower();

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
};
