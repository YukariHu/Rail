#pragma once
#include <Novice.h>

class TitleLine
{
public:
    TitleLine() : lineLength_(0) {}
    ~TitleLine() {}

    void Init();
    void Update(int time);
    void Draw();

private:
    int lineLength_; 
};

