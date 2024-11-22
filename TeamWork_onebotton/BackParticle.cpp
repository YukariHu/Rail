#include "BackParticle.h"
#include <Novice.h>
#include <cstdlib>
#include <cmath>

BackParticle::BackParticle()
    : pos_({ 0, 0 }), direction_({ -1.0f, 0.3f }), rad_(5.0f), velocity_(7.0f), oscillation_(0.0f), alive_(true), randNum_(rand() % 3 + 1),color_(){}

BackParticle::~BackParticle() {}

void BackParticle::Init(const Vector2& direction) {
    pos_ = { float (rand() % 1280), float(rand() % 720)};
    direction_ = direction;
    rad_ = 5.0f * randNum_;
    velocity_ = 1.0f * randNum_ + 3.0f;
    oscillation_ = float(rand() % 360);
    alive_ = true;
    color_ = 0x303030FF;

}

void BackParticle::Update() {
    pos_.x += direction_.x * velocity_;
  
    oscillation_ += 0.3f;

    if (pos_.x < -rad_) {
        alive_ = false;
    }
}

void BackParticle::Draw() {
    if (alive_) {
        Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, color_, kFillModeSolid);
    }
}

bool BackParticle::IsAlive() const {
    return alive_;
}