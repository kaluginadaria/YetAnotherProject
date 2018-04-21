#ifndef COMPONENT_VISUALISERS_HPP
#define COMPONENT_VISUALISERS_HPP
#pragma once

#include <string>
#include <unordered_map>
#include "Interfaces/IViewer.hpp"

class ComponentVisualiser;
class ActorComponent;


class ComponentVisualisers
{
public:
	using Visualisers = std::unordered_map<std::string, ComponentVisualiser*>;

public:
	// request a visualisation for the component
	static void Visualise(ActorComponent* component, IViewer* viewer);

	static void AddVisualiser(const std::string& className, ComponentVisualiser* visualiser);
	
private:
	static Visualisers visualisers;
};



#endif // !COMPONENT_VISUALISERS_HPP
