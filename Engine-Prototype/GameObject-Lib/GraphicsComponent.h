#pragma once
#include "Component.h"

#include "Helper.h"

class GraphicsComponent : public Component
{
public:
	~GraphicsComponent() { }
	virtual void Draw(const RenderDataBinder& render) const = 0;
	const int getType() final { return ComponentType::GraphicalComponent; };
};