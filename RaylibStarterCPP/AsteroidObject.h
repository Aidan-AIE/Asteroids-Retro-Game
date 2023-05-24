#pragma once
#include "raylib.h" 

class AsteroidObject {
public:	
	void ChangePos(Vector2 newPos);
	
	void Draw();
	void Break();
	void Initialize( Vector2 pos, float angle, float speed, int size);

	float xPos();
	float yPos();
	float speed();
	float angle();
	float generateSpeed();
	int size();//returns pixel size
	int sizeI();//returns the regular int

protected:
	Vector2 position;
	int Size;
	float Speed;
	float Angle;

};
