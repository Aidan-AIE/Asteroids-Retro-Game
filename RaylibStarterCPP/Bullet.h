#pragma once
#include "GameObject.h"

class Bullet : protected GameObject {
public:
	void Draw() override;
	void Initialize(Vector2 pos, float angle, float time);
	void Move();
protected:
	float Angle;
	float Time;

};