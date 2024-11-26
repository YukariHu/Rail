#include "FireParticle.h"

#include "FireParticle.h"
#include "Novice.h"
FireParticle::FireParticle(Vector2 _pos, Vector2 _size, int _lifetime)
{
	this->pos = _pos;
	this->size = _size;
	this->lifeTime = _lifetime;

	//在（2-4之间）随机获取火焰粒子升起的速度
	velocity = Vector2(0, -1) * (rand() % 200 / 100.0f + 2.0f);
	////在（0.5-1.5之间）随机获取火焰粒子的大小
	//size = Vector2(1, 1) * (rand() % 100 / 100.0f + 0.5f);


	alpha = 255;
	color = GetColor(0, 139, 139, alpha);

	/*lifeTimer.set_wait_time(lifeTime);
	lifeTimer.set_one_shot(true);
	lifeTimer.set_on_timeout([this]() {
		isOver = true;
		});*/

}

void FireParticle::Update()
{
	passedTime++;

	float progress = static_cast<float>(passedTime) / static_cast<float>(lifeTime);
	alpha = int(255 * (1 - progress));
	color = GetColor(0, 139, 139, 255);
	//size逐渐变小
	size = size * 0.96f;
	pos += velocity;

	//是否结束
	if (passedTime >= lifeTime)
	{
		isOver = true;
	}


}

void FireParticle::Draw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y), 0.0f, color, kFillModeSolid);
}

int FireParticle::GetColor(unsigned int red, unsigned int green, unsigned int blue, int _alpha)
{
	//unsigned char top = 0x;
	return color = (red << 24) | (green << 16) | (blue << 8) | _alpha;
}
