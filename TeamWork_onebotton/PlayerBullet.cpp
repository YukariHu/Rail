#include "Novice.h"
#include "PlayerBullet.h"
#include <cmath>

PlayerBullet::PlayerBullet()
{
    for (int i = 0; i < 20; i++) {
        shot[i] = {
            { -100.0f,-100.0f },
            1.0f / 30.0f,
            5.0f,
            0.0f,
            false,
            -100,-100,
            { -100.0f,-100.0f }
        };
    }

    shotTimer = 0;
    coolTime = 5;
}

void PlayerBullet::Update(Vector2 player)
{
    if (shotTimer == 0) {
        if (Novice::IsPressMouse(0)) {
            for (int i = 0; i < 20; i++) {
                if (shot[i].isShot == false) {
                    shot[i].pos.x = player.x;
                    shot[i].pos.y = player.y;
                    shot[i].shotPos.x = player.x;
                    shot[i].shotPos.y = player.y;

                    Novice::GetMousePosition(&shot[i].targetPosX, &shot[i].targetPosY);

                    float dx = shot[i].targetPosX - shot[i].pos.x;
                    float dy = shot[i].targetPosY - shot[i].pos.y;

                    float length = std::sqrt(dx * dx + dy * dy);
                    if (length != 0.0f) {
                        dx /= length; 
                        dy /= length;
                    }

                    shot[i].direction = { dx * shot[i].speed, dy * shot[i].speed };

                    shot[i].isShot = true;
                    shotTimer = coolTime;
                    break;
                }
            }
        }
    } else {
        if (shotTimer > 0) {
            shotTimer--;
        }
    }

    for (int i = 0; i < 20; i++) {
        if (shot[i].isShot) {
            shot[i].pos.x += shot[i].direction.x;
            shot[i].pos.y += shot[i].direction.y;

            if (shot[i].pos.x < 0 || shot[i].pos.y < 0 ||
                shot[i].pos.x > 1280 || shot[i].pos.y > 720) {
                shot[i].pos.x = -100;
                shot[i].pos.y = -100;
                shot[i].direction = { 0.0f, 0.0f };
                shot[i].isShot = false;
            }
        }
    }
}

void PlayerBullet::Draw()
{
    for (int i = 0; i < 20; i++) {
        if (shot[i].isShot) {
            Novice::DrawEllipse(static_cast<int>(shot[i].pos.x), static_cast<int>(shot[i].pos.y),
                static_cast<int>(shot[i].radius), static_cast<int>(shot[i].radius), 0.0f, WHITE, kFillModeSolid);
        }
    }
}
