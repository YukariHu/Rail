#include "TitleParticle.h"
#include <Novice.h>
#include <cstdlib>
#include <cmath>

TitleParticle::TitleParticle()
    : pos_({ 0, 0 }), direction_({ -1.0f, 0.3f }), rad_(4.0f), velocity_(7.0f), oscillation_(0.0f), alive_(true) {}

TitleParticle::~TitleParticle() {}

void TitleParticle::Init(const Vector2& direction, bool isStart) {
    if (!isStart) {
        pos_ = { float(rand() % 1280), float(rand() % 720) }; 
    } else {
        pos_ = { 1300.0f, float(rand() % 720) }; 
    }

    direction_ = direction;
    rad_ = 4.0f;
    velocity_ = 6.0f + float(rand() % 3);
    oscillation_ = float(rand() % 360);
    alive_ = true;
}

void TitleParticle::Update() {
    pos_.x += direction_.x * velocity_ + sinf(oscillation_) * 1.5f;  
    pos_.y += sinf(oscillation_ * 0.5f) * 1.0f;  

    oscillation_ += 0.3f;
 
    if (pos_.x < -rad_) {  
        alive_ = false;
    }
}

void TitleParticle::Draw() {
    if (alive_) {
        Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, 0x6962ADAA, kFillModeSolid);
    }
}

bool TitleParticle::IsAlive() const {
    return alive_;
}
