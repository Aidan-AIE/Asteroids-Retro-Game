#pragma once
#include "Raylib.h"
#include <vector>

class GameObject {
public:
	void ChangePos(Vector2 newPos);
	void AddChild(GameObject object);
	
	std::vector<GameObject> children;

	virtual void Draw();
	
	float xPos();
	float yPos();


protected:
	
	Vector2 position;
	
};