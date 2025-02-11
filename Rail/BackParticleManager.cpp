#include "BackParticleManager.h"

BackParticleManager::BackParticleManager() : mpParticle_() {}

BackParticleManager::~BackParticleManager() {
    Finalize();
}

void BackParticleManager::Init() {
}

void BackParticleManager::Update() {
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

void BackParticleManager::Draw(const Camera& camera) {
    for (auto& particle : mpParticle_) {
        if (particle != nullptr) {
            particle->Draw(camera);
        }
    }
}

void BackParticleManager::Create(const Vector2& direction, bool isStart) {
    BackParticle* newParticle = new BackParticle();
    newParticle->SetIsStart(isStart);
    newParticle->Init(direction);
    mpParticle_.push_back(newParticle);
}


void BackParticleManager::Finalize() {
    for (auto& particle : mpParticle_) {
        delete particle;
    }
    mpParticle_.clear();
}