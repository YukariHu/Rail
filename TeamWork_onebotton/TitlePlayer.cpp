#include "TitlePlayer.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>

TitlePlayer::TitlePlayer()
    : pos_({ 0, 600 }), startPos_({ -20, 600 }), targetPos_({ 640, 600 }), easingFactor_(0.02f), elapsedTime_(0.0f), totalTime_(200.0f)
{
}

TitlePlayer::~TitlePlayer() {}

void TitlePlayer::Init()
{
    pos_ = startPos_;
    elapsedTime_ = 0.0f;
}

void TitlePlayer::Update()
{
    elapsedTime_ += easingFactor_;
    if (elapsedTime_ > 1.0f) {
        elapsedTime_ = 1.0f;  
    }

    float ease = -(cosf((float)M_PI * elapsedTime_) - 1.0f) / 2.0f;
    pos_.x = startPos_.x + (targetPos_.x - startPos_.x) * ease;

    if (elapsedTime_ >= 1.0f) {
        pos_.x = targetPos_.x;
    }
}

void TitlePlayer::Draw()
{
    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, 15,15,0.0f, WHITE, kFillModeSolid);
}
