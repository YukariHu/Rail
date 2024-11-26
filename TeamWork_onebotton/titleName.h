#pragma once
#include "MyVector2.h"
#include "read_csv.h"
#include <Novice.h>

class titleName
{
public:
    titleName();
    ~titleName();

    void Init();
    void Update();
    void Draw();

private:
    ReadCSV csv;

    std::vector<std::vector<int>> map = csv.ReadMap("./title.csv");

    int width_;

};
