#include "TitleParticleManager.h"

TitleParticleManager::TitleParticleManager() : mpParticle_() {}

TitleParticleManager::~TitleParticleManager() {
    Finalize();
}

void TitleParticleManager::Init() {
}

void TitleParticleManager::Update() {
    for (auto itr = mpParticle_.begin(); itr != mpParticle_.end();) {
        if ((*itr) != nullptr) {
            (*itr)->Update();
            if (!(*itr)->IsAlive()) {
                delete (*itr);
                itr = mpParticle_.erase(itr);
            } else {
                ++itr;
            }
        } else {
            ++itr;
        }
    }
}


void TitleParticleManager::Draw() {
    for (auto& particle : mpParticle_) {
        if (particle != nullptr) {
            particle->Draw();
        }
    }
}

void TitleParticleManager::Create(const Vector2& direction, bool isStart) {
    TitleParticle* newParticle = new TitleParticle();
    newParticle->Init(direction, isStart);
    mpParticle_.push_back(newParticle);
}

void TitleParticleManager::Finalize() {
    for (auto& particle : mpParticle_) {
        delete particle;
    }
    mpParticle_.clear();
}
