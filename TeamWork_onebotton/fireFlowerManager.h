#pragma once
#include <Vector2.h>
#include <list>
#include "FireFlower.h"

class FireFlowerManager {
public:
    FireFlowerManager();
    ~FireFlowerManager();

    void Init();
    void Update();
    void Draw();
    void Finalize();
    void Create(const Vector2& direction);

private:
    std::list<FireFlower*> fireFlower_;
};


