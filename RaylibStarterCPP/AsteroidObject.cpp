#include "AsteroidObject.h"

void AsteroidObject::Draw() {
	switch (Size) {
	case 0: //small
		DrawPolyLines( position, 8, 10, 0, RAYWHITE);
		break;
	case 1: //medium
		DrawPolyLines(position, 8, 20, 0, RAYWHITE);
		break;
	case 2: //big
		DrawPolyLines(position, 10, 35, 0, RAYWHITE);
		break;
	default:
		break;
	}
}

void AsteroidObject::Break() {
	Size -= 1;
}

void AsteroidObject::ChangePos(Vector2 newPos) {
	position = newPos;
}

void AsteroidObject::Initialize(Vector2 pos, float angle, float speed, int size) {
	position = pos;
	Angle = angle;
	Speed = speed;
	Size = size;
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

float AsteroidObject::generateSpeed() {
	switch (Size) {
	case 0:
		return GetRandomValue(70, 250);
		break;
	case 1:
		return GetRandomValue(50, 100);
		break;
	case 2:
		return GetRandomValue(30, 50);
		break;
	default:
		return 0;
	}
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
	default:
		return 0;
	}
}

int AsteroidObject::sizeI() {
	return Size;
}


