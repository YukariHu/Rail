#pragma once
#include <Vector2.h>
#include <list>
#include "TitleParticleManager.h"

class TitleParticle
{
private:
	
	TitleParticleManager *tileParticleManager_;

public:
	TitleParticle();
	~TitleParticle();

	void Init();
	void Update();
	void Draw();

	void Finalize();

	Vector2 GetPos() { return pos_; }

public:
	Vector2 pos_;
	float rad_;
	float theta_;
	float velocity_;
	int time_;
};

