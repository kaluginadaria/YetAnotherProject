#pragma once
#ifndef BOX_COLLISION_VISUALISER_HPP
#define BOX_COLLISION_VISUALISER_HPP

#include "../ComponentVisualiser.hpp"
#include "BoxColision.hpp"

class BoxColisionVisualiser : public ComponentVisualiser
{
	virtual void Visualize(ActorComponent* component, ComponentVisualiserHelper& helper) override
	{
		if (auto* box = dynamic_cast<BoxColision*>(component))
		{
			FVector    extends   = box->GetExtends();
			FTransform transform = box->GetComponentTransform();
			helper.DrawShape(FShape::MakeBox(extends), transform, FColor::Green);
		}
	}
};

#endif // !BOX_COLLISION_VISUALISER_HPP