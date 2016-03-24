#pragma once

#include "GameObject.h"

class GameObject;

enum ComponentType { LogicComponent, PhysicComponent, GraphicalComponent, LightComponent };

class Component
{
public:
	virtual ~Component() {}
	virtual const int getType() = 0;
	void AssignGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
protected:
	GameObject* gameObject;
};