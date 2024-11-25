#define _USE_MATH_DEFINES

#include <math.h>
#include "Novice.h"
#include "PlayerParticles.h"

PlayerParticles::PlayerParticles()
{
	for (int i = 0; i < 100; i++) {
		moveParticl[i] = {
			{ 0.0f,0.0f },
			10,
			5,
			false,
		};
		if (i < 5) {
			changeParticl[i] = {
				{ 0.0f ,0.0f },
				{ 0.0f ,0.0f },
				5,
				4,
				0.0f,
				false,
			};
		}
	}
}


void PlayerParticles::CreateChangeParticl(Vector2 pos)
{
	changeParticl[0].radian = float(M_PI) / 2;
	changeParticl[0].direction = { 0.0f,-1.0f };

	changeParticl[1].radian = float(M_PI) / 4;
	changeParticl[1].direction = { 1.0f,-1.0f };

	changeParticl[2].radian = float(M_PI) / 4;
	changeParticl[2].direction = { 1.0f,1.0f };

	changeParticl[3].radian = float(M_PI) / 4;
	changeParticl[3].direction = { -1.0f,1.0f };

	changeParticl[4].radian = float(M_PI) / 4;
	changeParticl[4].direction = { -1.0f,-1.0f };

	for (int i = 0; i < 5; i++) {
		changeParticl[i].pos = { static_cast<float>(pos.x),static_cast<float>(pos.y) };
		changeParticl[i].isAlive = true;
		changeParticl[i].radius = 10;
	}
}


void PlayerParticles::Update(Vector2 pos, Vector2 startLine)
{
	for (int i = 0; i < 100; i++) {
		if (moveParticl[i].isAlive == false) {
			moveParticl[i].isAlive = true;
			moveParticl[i].pos.x = pos.x + rand() % 25 - 12;
			moveParticl[i].pos.y = pos.y + rand() % 25 - 12;
			moveParticl[i].radius = 6;
			break;
		}
	}

	for (int i = 0; i < 100; i++) {
		if (moveParticl[i].isAlive) {
			if (startLine.x == 0.0f) {
				moveParticl[i].pos.x -= moveParticl[i].speed;
			} else {
				moveParticl[i].pos.y -= moveParticl[i].speed;
			}
			moveParticl[i].radius--;
			if (moveParticl[i].radius < 1) {
				moveParticl[i].isAlive = false;
			}
		}
	}


	for (int i = 0; i < 5; i++) {
		if (changeParticl[i].isAlive) {
			changeParticl[i].pos.x += changeParticl[i].speed * cosf(changeParticl[i].radian) * changeParticl[i].direction.x;
			changeParticl[i].pos.y += changeParticl[i].speed * sinf(changeParticl[i].radian) * changeParticl[i].direction.y;
			changeParticl[i].radius--;
			if (changeParticl[i].radius <= 0) {
				changeParticl[i].isAlive = false;
			}
		}
	}

}

void PlayerParticles::Draw()
{
	for (int i = 0; i < 100; i++) {
		if (moveParticl[i].isAlive) {
			Novice::DrawEllipse(static_cast<int>(moveParticl[i].pos.x), static_cast<int>(moveParticl[i].pos.y),
				moveParticl[i].radius, moveParticl[i].radius, 0.0f, WHITE, kFillModeSolid);
		}
	}

	for (int i = 0; i < 5; i++) {
		if (changeParticl[i].isAlive) {
			Novice::DrawEllipse(static_cast<int>(changeParticl[i].pos.x), static_cast<int>(changeParticl[i].pos.y),
				changeParticl[i].radius, changeParticl[i].radius, 0.0f, WHITE, kFillModeSolid);
		}
	}
}
