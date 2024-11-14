#include "FireFlowerManager.h"

FireFlowerManager::FireFlowerManager() : fireFlower_() {}

FireFlowerManager::~FireFlowerManager() {
    Finalize();
}

void FireFlowerManager::Init() {
}

void FireFlowerManager::Update() {
    for (auto itr = fireFlower_.begin(); itr != fireFlower_.end();) {
        if ((*itr) != nullptr) {
            (*itr)->Update();
            if (!(*itr)->IsAlive()) {
                delete (*itr);
                itr = fireFlower_.erase(itr);
            } else {
                ++itr;
            }
        } else {
            ++itr;
        }
    }
}

void FireFlowerManager::Draw() {
    for (auto& particle : fireFlower_) {
        if (particle != nullptr) {
            particle->Draw();
        }
    }
}

void FireFlowerManager::Create(const Vector2& direction) {
    FireFlower* newParticle = new FireFlower();
    newParticle->Init(direction);
    fireFlower_.push_back(newParticle);
}

void FireFlowerManager::Finalize() {
    for (auto& particle : fireFlower_) {
        delete particle;
    }
    fireFlower_.clear();
}
