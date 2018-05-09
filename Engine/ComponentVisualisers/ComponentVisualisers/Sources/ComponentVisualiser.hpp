#ifndef COMPONENT_VISUALISER_HPP
#define COMPONENT_VISUALISER_HPP
#pragma once

#include "ComponentVisualiserHelper.hpp"
#include "ActorComponent.hpp"


class ComponentVisualiser
{
public:

	virtual void Visualize(ActorComponent* component, ComponentVisualiserHelper& helper) = 0;
};


#endif // !COMPONENT_VISUALISER_HPP
