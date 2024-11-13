#include "TitlePlayerParticle.h"
#include <Novice.h>
#include <cstdlib>
#include <cmath>

TitlePlayerParticle::TitlePlayerParticle()
    : pos_({ 0, 0 }), direction_({ -1.0f, 0.1f }), rad_(4.0f), velocity_(7.0f), oscillation_(0.0f), alive_(true) {}

TitlePlayerParticle::~TitlePlayerParticle() {}

void TitlePlayerParticle::Init(Vector2 playerPos)
{
    pos_ = { playerPos.x - 50, playerPos.y };
    direction_ = { -1.0f, 0.1f };
    rad_ = 4.0f;
    velocity_ = 6.0f + float(rand() % 3);
    oscillation_ = float(rand() % 360);
    alive_ = true;
}

void TitlePlayerParticle::Update()
{
    pos_.x += direction_.x * velocity_ + sinf(oscillation_) * 1.5f;
    pos_.y += direction_.y * velocity_;
    oscillation_ += 0.3f;

    if (pos_.x < -rad_) {
        alive_ = false;
    }
}

void TitlePlayerParticle::Draw()
{
    if (alive_) {
        Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)rad_, (int)rad_, 0.0f, 0xFFFFFFAA, kFillModeSolid);
    }
}

bool TitlePlayerParticle::IsAlive() const
{
    return alive_;
}
