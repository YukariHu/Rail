#pragma once
#include "Charactor.h"

class BossA : public Charactor
{
public:
	BossA();
	~BossA() = default;

	void onUpdate() override;
	void onDraw() override;

	

private:
	

	
};
