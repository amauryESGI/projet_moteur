#include "GameObject.h"

GameObject::GameObject(std::string name)
{
	this->Name = name;
}

void GameObject::AddComponent(Component* comp)
{
	this->Components.push_back(comp);
	comp->AssignGameObject(this);
}

GameObject::~GameObject()
{
	for (Component* comp : this->Components)
	{
		delete comp;
	}
}
