#pragma once
#include "MyVector2.h"
#include "read_csv.h"
#include <Novice.h>

class clearName
{
public:
    clearName();
    ~clearName();

    void Init();
    void Update(); 
    void Draw();

private:
    ReadCSV csv;

    std::vector<std::vector<int>> map = csv.ReadMap("./clear.csv");

    int width_;

};
