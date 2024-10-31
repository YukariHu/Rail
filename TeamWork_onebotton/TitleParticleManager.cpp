#include "TitleParticleManager.h"

TitleParticleManager::TitleParticleManager():mpParticle_()
{
}

TitleParticleManager::~TitleParticleManager()
{
}

void TitleParticleManager::Init()
{
}

void TitleParticleManager::Update()
{
	for (std::list<TitleParticle*>::iterator itr = mpParticle_.begin(); itr != mpParticle_.end(); itr++) {
		if ((*itr) != nullptr)
		{
			(*itr)->Update();
		}
	}
}

void TitleParticleManager::Draw()
{
	for (std::list<TitleParticle*>::iterator itr = mpParticle_.begin(); itr != mpParticle_.end(); itr++) {
		if ((*itr) != nullptr)
		{
			(*itr)->Draw();
		}
	}
}

void TitleParticleManager::Finalize()
{
	for (std::list<TitleParticle*>::iterator itr = mpParticle_.begin(); itr != mpParticle_.end(); itr++) {
		if ((*itr) != nullptr)
		{
			continue;
		}

		(*itr)->Finalize();
		delete (*itr);
	}

	mpParticle_.clear();
}

void TitleParticleManager::Create()
{
	mpParticle_.push_back(new TitleParticle());
	std::list<TitleParticle*>::iterator itr = mpParticle_.end();
	itr--;
	(*itr)->Init();
}

void TitleParticleManager::DeleteParticle()
{
	for (std::list<TitleParticle*>::iterator itr = mpParticle_.begin(); itr != mpParticle_.end(); itr++) {
		if ((*itr) != nullptr)
		{
			itr++;
			continue;
		}

		if ((*itr)->GetPos().y <= 0.0f) {
			(*itr)->Finalize();
			delete (*itr);
			(*itr) = nullptr;
			itr = mpParticle_.erase(itr);
			continue;
		}
		itr++;
	}
}
