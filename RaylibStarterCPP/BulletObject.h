#pragma once
#include "raylib.h" 


class BulletObject {
public:
	void ChangePos(Vector2 newPos);

	void Draw();

	float xPos();
	float yPos();
	float angle();
	float time();
	Vector2 momentum();

	void Initialize(Vector2 pos, float angle, float time, Vector2 mom);
	
	void Move();
	void SubTime(float time);


protected:
	Vector2 position;
	Vector2 Momentum;
	float Angle;
	float Time;
};