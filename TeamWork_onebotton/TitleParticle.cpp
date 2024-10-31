#include "TitleParticle.h"
#include <Novice.h>

TitleParticle::TitleParticle()
{
}

TitleParticle::~TitleParticle()
{
}

void TitleParticle::Init()
{
	pos_ = { float(rand() % 1280),720.0f };
	rad_ = rand() % 10;
	velocity_ = 5.0f;
	time_ = 20;
}

void TitleParticle::Update()
{
	pos_.y -= velocity_;

	time_--;

	if (time_ <= 0)
	{
		tileParticleManager_->Create();
		time_ = 20;
	}
}

void TitleParticle::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, rad_, rad_, 0.0f, 0xFFFFFFEE, kFillModeSolid);
}

void TitleParticle::Finalize()
{

}
