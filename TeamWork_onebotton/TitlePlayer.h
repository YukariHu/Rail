#pragma once
#include <Vector2.h>

class TitlePlayer
{
public:
    TitlePlayer();
    ~TitlePlayer();

    void Init();
    void Update();
    void Draw();

    Vector2 GetPos() const { return pos_; }

    bool SetTran(bool trans) { this->isTransition_ = trans; return isTransition_; }

private:
    Vector2 pos_;         
    Vector2 startPos_;    
    Vector2 targetPos_;    
    float easingFactor_;  
    float elapsedTime_;    
    float totalTime_;     
    bool isTransition_;
};
