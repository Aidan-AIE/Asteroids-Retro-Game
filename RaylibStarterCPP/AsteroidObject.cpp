#include "AsteroidObject.h"

void AsteroidObject::Draw() {
	switch (Size) {
	case 0:
		DrawPolyLines( position, 8, 10, 0, RAYWHITE);
		break;
	case 1:
		DrawPolyLines(position, 8, 20, 0, RAYWHITE);
		break;
	case 2:
		DrawPolyLines(position, 10, 35, 0, RAYWHITE);
		break;
	}
}

void AsteroidObject::Break() {

}

void AsteroidObject::ChangePos(Vector2 newPos) {
	position = newPos;
}

float AsteroidObject::xPos() {
	return position.x;
}

float AsteroidObject::yPos() {
	return position.y;
}

float AsteroidObject::speed() {
	return Speed;
}

float AsteroidObject::angle() {
	return Angle;
}

int AsteroidObject::size() {
	switch (Size) {
	case 0:
		return 10;
		break;
	case 1:
		return 20;
		break;
	case 2:
		return 35;
		break;
	}
}


void AsteroidObject::Initialize(Vector2 pos, float angle, float speed, int size) {
	position = pos;
	Angle = angle;
	Speed = speed;
	Size = size;
}