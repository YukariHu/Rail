#include "Novice.h"
#include "PlayerParticles.h"

PlayerParticles::PlayerParticles()
{
	for (int i = 0; i < 100; i++) {
		particl[i] = {
			{ 0.0f,0.0f },
			10,
			5,
			false,
		};
	}
}

void PlayerParticles::Update(Vector2 pos, Vector2 startLine)
{
	for (int i = 0; i < 100; i++) {
		if (particl[i].isAlive == false) {
			particl[i].isAlive = true;
			particl[i].pos.x = pos.x + rand() % 25 - 12;
			particl[i].pos.y = pos.y + rand() % 25 - 12;
			particl[i].radius = 6;
			break;
		}
	}

	for (int i = 0; i < 100; i++) {
		if (particl[i].isAlive) {
			if (startLine.x == 0.0f) {
				particl[i].pos.x -= particl[i].speed;
			} else {
				particl[i].pos.y -= particl[i].speed;
			}
			particl[i].radius--;
			if (particl[i].radius < 1) {
				particl[i].isAlive = false;
			}
		}
	}

}

void PlayerParticles::Draw()
{
	for (int i = 0; i < 100; i++) {
		if (particl[i].isAlive) {
			Novice::DrawEllipse(static_cast<int>(particl[i].pos.x), static_cast<int>(particl[i].pos.y),
				particl[i].radius, particl[i].radius, 0.0f, WHITE, kFillModeSolid);
		}
	}
}
