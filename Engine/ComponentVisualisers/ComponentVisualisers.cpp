#include "ComponentVisualisers.hpp"
#include "ComponentVisualisers.hpp"

#include "ActorComponent.hpp"
#include "ComponentVisualiser.hpp"

#include "Visualisers/BoxColisionVisualiser.hpp"


//TODO:: memory lick
ComponentVisualisers::Visualisers ComponentVisualisers::visualisers = {
	{"BoxColision", new BoxColisionVisualiser},
	};

void ComponentVisualisers::Visualise(ActorComponent* component, IViewer* viewer)
{
	if (!component || !viewer) return;

	std::string className = component->__GetClassName();
	auto itr = visualisers.find(className);
	auto end = visualisers.end();
	if (itr != end)
	{
		auto helper = ComponentVisualiserHelper(viewer);
		itr->second->Visualize(component, helper);
	}
}

void ComponentVisualisers::AddVisualiser(const std::string & className, ComponentVisualiser* visualiser)
{
}
