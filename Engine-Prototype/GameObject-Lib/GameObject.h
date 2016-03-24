#pragma once
#include <string>
#include <vector>

#include "Component.h"
#include "Transform.h"
#include "Helper.h"

class Component;

class GameObject
{
public:
	GameObject(std::string name);

	std::string	getName() const		{ return this->Name; }
	Vec3		getPosition() const	{ return this->transform.Position; }

	void GameObject::AddComponent(Component* comp);

	~GameObject();
private:
	std::string Name;
	Transform transform;
	std::vector<Component*> Components;

};

