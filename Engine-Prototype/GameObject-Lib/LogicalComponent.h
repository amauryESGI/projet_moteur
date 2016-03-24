#pragma once
#include "Component.h"

#include "Helper.h"

class LogicalComponent : public Component
{
public:
	~LogicalComponent() { delete this->gameObject; }
	virtual void Update(void) = 0;
	const int getType() final { return ComponentType::LogicComponent; };
};