#pragma once
#include "MyVector2.h"

class FireFlower {
public:
    FireFlower();
    ~FireFlower();

    void Init(Vector2 direction, float xPosition, float yPosition);
    void Update();
    void Draw();
    bool IsAlive() const;

private:
    Vector2 pos_;
    Vector2 direction_;
    float rad_;
    float velocity_;
    float expandRate_;
    int time_;
    bool alive_;
};
