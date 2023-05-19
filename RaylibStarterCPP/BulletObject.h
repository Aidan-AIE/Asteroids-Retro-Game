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

	void Initialize(Vector2 pos, float angle, float time);
	
	void Move();
	void SubTime(float time);


protected:
	Vector2 position;
	float Angle;
	float Time;
};