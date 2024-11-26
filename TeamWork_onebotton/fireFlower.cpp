#include "FireFlower.h"
#include <cmath>
#include <cstdlib>
#include <Novice.h>

FireFlower::FireFlower() :
    pos_({ 0, 0 }), direction_({ 0.0f, 0.0f }), rad_(10.0f), velocity_(2.0f), time_(120), alive_(true), expandRate_(0.0f)
{
}

FireFlower::~FireFlower()
{
}

void FireFlower::Init(Vector2 direction, float xPosition, float yPosition)
{
    pos_ = { xPosition, yPosition };
    time_ = 120;
    alive_ = true;
    rad_ = 10.0f;

    direction_ = { direction.x, direction.y };
    expandRate_ = 0.0f;
}

void FireFlower::Update()
{
    float progress = static_cast<float>(time_) / 30.0f;
    expandRate_ = 1.0f - (1.0f - progress) * (1.0f - progress);

    pos_.x += direction_.x * velocity_ * expandRate_;
    pos_.y += direction_.y * velocity_ * expandRate_;

    rad_ -= 0.1f;
    if (rad_ < 0) rad_ = 0;

    time_--;
    if (time_ <= 0) {
        alive_ = false;
    }
}

void FireFlower::Draw()
{
    if (alive_) {
        Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, 0xB6BBC4FF, kFillModeSolid);
    }
}

bool FireFlower::IsAlive() const
{
    return alive_;
}
