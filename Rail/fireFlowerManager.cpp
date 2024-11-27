#include "FireFlowerManager.h"
#include <cstdlib>
#include <cmath>

FireFlowerManager::FireFlowerManager() : fireFlower_() {}

FireFlowerManager::~FireFlowerManager() {
    Finalize();
}

void FireFlowerManager::Init() {}

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

void FireFlowerManager::Create()
{
    int numParticles = 15;
    for (int i = 0; i < numParticles; i++) {
        float angle = i * 360.0f / numParticles;
        Vector2 direction = { cosf(angle * PI / 180.0f), sinf(angle * PI / 180.0f) };

        float randomX = 1280.0f / 2.0f;
        float randomY = 360.0f;

        FireFlower* fireFlower = new FireFlower();
        fireFlower->Init(direction, randomX, randomY);
        fireFlower_.push_back(fireFlower);
    }
}

void FireFlowerManager::Finalize() {
    for (auto& particle : fireFlower_) {
        delete particle;
    }
    fireFlower_.clear();
}
