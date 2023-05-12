#pragma once
#include "Raylib.h"

class GameObject {
public:
	virtual void Draw();

protected:
	float posX;
	float posY;

};