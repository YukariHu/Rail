#include "PlayerBu.h"
extern int windowHeight;
extern int windowWidth;
PlayerBu::PlayerBu(Vector2 _firePos, Vector2 _targetPos)
{
    pos = _firePos;
    firePos = _firePos;
    targetPos = _targetPos;

    Vector2 direction = { targetPos.x - firePos.x, targetPos.y - firePos.y };

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    dir = { direction.x / length, direction.y / length };  

    targetID = 1;
    speed = 18.0f; 
    size = { 5.0f, 5.0f }; 
    damage = 1; 
    t = 0.0f;
}

void PlayerBu::onUpdate()
{

    pos.x += dir.x * speed;
    pos.y += dir.y * speed;

    if (pos.x > windowWidth || pos.x < 0.0f || pos.y > windowHeight || pos.y < 0.0f)
    {
        isCanRemove = true;
    }
}
