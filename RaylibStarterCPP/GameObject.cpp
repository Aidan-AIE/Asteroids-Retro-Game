#include "GameObject.h"

void GameObject::ChangePos(Vector2 newPos) {
	position = newPos;
}

float GameObject::xPos() {
	return position.x;
}

float GameObject::yPos() {
	return position.y;
}

void GameObject::AddChild(GameObject child) {
	children.push_back(child);
}

void GameObject::Draw() {
	//wow nothing!!!!
}