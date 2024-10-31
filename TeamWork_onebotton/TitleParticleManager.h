#pragma once
#include <Vector2.h>
#include <list>
#include "TitleParticle.h"

class TitleParticle;

class TitleParticleManager
{
public:
	TitleParticleManager();
	~TitleParticleManager();

	void Init();
	void Update();
	void Draw();

	void Finalize();
	void Create();

private:
	void DeleteParticle();

private:
	std::list<TitleParticle*>mpParticle_;

};

