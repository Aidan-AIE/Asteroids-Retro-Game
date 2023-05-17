#include "Bullet.h"
#include <math.h>

void Bullet::Draw() {
	DrawCircle(position.x, position.y, 1, RAYWHITE);
}

void Bullet::Initialize(Vector2 pos, float angle, float time) {
	position = pos;
	Angle = angle;
	Time = time;
}

void Bullet::Move() {
	position = { position.x + 500 * (float)cos(Angle - 1.5708) * GetFrameTime(),  position.y + 500 * (float)sin(Angle - 1.5708) * GetFrameTime() };
}