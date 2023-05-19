#include "BulletObject.h"
#include <math.h>

void BulletObject::ChangePos(Vector2 newPos) {
	position = newPos;
}

float BulletObject::xPos() {
	return position.x;
}

float BulletObject::yPos() {
	return position.y;
}

float BulletObject::angle() {
	return Angle;
}

float BulletObject::time() {
	return Time;
}

void BulletObject::Draw() {
	DrawCircle(position.x, position.y, 1, RAYWHITE);
}

void BulletObject::Initialize(Vector2 pos, float angle, float time) {
	position = pos;
	Angle = angle;
	Time = time;
}

void BulletObject::SubTime(float time){
	Time -= time * GetFrameTime();
}

void BulletObject::Move() {
	position = { position.x + 500 * (float)cos(Angle - 1.5708) * GetFrameTime(),  position.y + 500 * (float)sin(Angle - 1.5708) * GetFrameTime() };
}
