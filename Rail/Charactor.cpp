#include "Charactor.h"
#include "Bullet.h"
extern std::vector<Bullet*> bulletList;
extern Camera mainCamera;

extern int damageSound;
void Charactor::onUpdate()
{
    Collision();

}

void Charactor::onDraw(const Camera& camera)
{
    (void)camera;
    const Vector2& cameraPos = camera.GetPos();
    Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x),static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x),0.0f,WHITE,kFillModeSolid);
}

void Charactor::Collision()
{
    if (!isEnableCollision)
    {
		return;
	}
    for (auto& bullet : bulletList)
    {
        if (id!= bullet->targetID)
        {
            continue;
        }
        if (bullet->checkCollision(pos, size))
        {
		    onHurt(bullet->getDamage());
		}
	}
}

void Charactor::onHurt(int damage)
{
    if (!Novice::IsPlayingAudio(damageSound))
    {
        Novice::PlayAudio(damageSound, false, 0.5f);
    }
    
	hp -= damage;
    mainCamera.Shack(10.0f,0.3f);
    if (hp <= 0)
    {
        isDead = true;
    }
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

void Charactor::SetIsEnableCollision(bool _isEnableCollision)
{
	this->isEnableCollision = _isEnableCollision;
}

void Charactor::SetIsDead(bool _isDead)
{
	this->isDead = _isDead;
}

void Charactor::SetTarget(Charactor* _target)
{
	this->target = _target;
}

void Charactor::SwitchState(const std::string& _id)
{
    stateMachine.SwitchTo(_id);
}
