#pragma once
#include <MyVector2.h>

class TitleParticle {
public:
    TitleParticle();
    ~TitleParticle();

    void Init(const Vector2& direction,bool isStart);
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
