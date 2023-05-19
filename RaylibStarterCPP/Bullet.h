#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	void Draw();
	void Initialize(Vector2 pos, float angle, float time);
	void Move();
protected:
	float Angle;
	float Time;

};