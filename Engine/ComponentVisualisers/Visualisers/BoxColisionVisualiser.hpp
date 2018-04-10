#pragma once

#include "../ComponentVisualiser.hpp"
#include "BoxColision.hpp"

class BoxColisionVisualiser : public ComponentVisualiser
{
	virtual void Visualize(ActorComponent* component, ComponentVisualiserHelper& helper) override
	{
		if (auto* box = static_cast<BoxColision*>(component))
		{
			Vector3f  extends   = box->GetExtends();
			Transform transform = box->GetComponentTransform();
			helper.DrawShape(FShape::MakeBox(extends), transform, Vector4f(0, 1, 0, 1));
		}
	}
};