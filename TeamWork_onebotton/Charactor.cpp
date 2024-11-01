#include "Charactor.h"


void Charactor::onUpdate()
{
    
    if (hp <= 0)
    {
        isDead = true;
    }
}

void Charactor::onDraw()
{
    Novice::DrawEllipse(static_cast<int>(pos.x),static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x),0.0f,WHITE,kFillModeSolid);
}

void Charactor::onHurt(int damage)
{
	hp -= damage;
}

int Charactor::GetHp()
{
    return hp;
}

void Charactor::Setposition(const Vector2& _pos)
{
    this->pos = _pos;
}

const Vector2& Charactor::Getposition()
{
    return pos;
}

void Charactor::SetSize(const Vector2& _size)
{
	this->size = _size;
}

const Vector2& Charactor::GetSize()
{
    return size;
}
