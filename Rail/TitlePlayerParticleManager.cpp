#include "TitlePlayerParticleManager.h"
#include "TitlePlayerParticle.h"

TitlePlayerParticleManager::TitlePlayerParticleManager() {}

TitlePlayerParticleManager::~TitlePlayerParticleManager()
{
    for (auto particle : particles_) {
        delete particle;
    }
}

void TitlePlayerParticleManager::Init() {}

void TitlePlayerParticleManager::Create(Vector2 playerPos)
{
    TitlePlayerParticle* newParticle = new TitlePlayerParticle();
    newParticle->Init(playerPos);
    particles_.push_back(newParticle);
}

void TitlePlayerParticleManager::Update()
{
    for (auto particle : particles_) {
        particle->Update();
    }

    particles_.remove_if([](TitlePlayerParticle* p) { return !p->IsAlive(); });
}

void TitlePlayerParticleManager::Draw()
{
    for (auto particle : particles_) {
        particle->Draw();
    }
}
