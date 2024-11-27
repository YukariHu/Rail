#pragma once
#include "MyVector2.h"
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
    void Create();

private:
    std::list<FireFlower*> fireFlower_;
    float PI = 3.14f;
};


