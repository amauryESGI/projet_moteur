#pragma once
#include "Component.h"

#include "Helper.h"

class PhysicsComponent : public Component
{
public:
	~PhysicsComponent() { delete this->gameObject; }
	virtual void Update(void) = 0;
	const int getType() final { return ComponentType::PhysicComponent; };
};