#pragma once
#include "raylib.h" 


class BulletObject {
public:
	void ChangePos(Vector2 newPos);

	void Draw();

	float xPos();
	float yPos();

	void Initialize(Vector2 pos, float angle, float time);
	
	void Move();


protected:
	Vector2 position;
	float Angle;
	float Time;
};