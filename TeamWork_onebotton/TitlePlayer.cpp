#include "TitlePlayer.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#define M_PI       3.14159265358979323846   // pi
#include <cmath>

float lerp(float start, float end, float t)
{
    return start + t * (end - start);
}

TitlePlayer::TitlePlayer()
    :
    pos_({ 0, 600 }),
    startPos_({ -20, 600 }),
    targetPos_({ 640, 600 }),
    easingFactor_(0.02f), 
    elapsedTime_(0.0f), 
    totalTime_(200.0f)
{
}

TitlePlayer::~TitlePlayer() {}

void TitlePlayer::Init()
{
    pos_ = startPos_;
    elapsedTime_ = 0.0f;
    isTransition_ = false;
}

void TitlePlayer::Update()
{
    
    if (isTransition_) {
        pos_.x = lerp(pos_.x, 1400.0f, 0.06f);
    } else {
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

}

void TitlePlayer::Draw()
{
    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, 20, 20, 0.0f, 0xB6BBC4FF, kFillModeSolid);
}
