#include "SFMLViewer.hpp"

#include "World.hpp"
#include "ActorComponent.hpp"
#include "ComponentVisualisers.hpp"
#include "Control/EventHandlers.hpp"
#include <iostream>


Viewer::Viewer(PlayerController* controller)
	: IViewer(controller),
	keyboardHandler(*GetEventCollector()),
	mouseHandler(*GetEventCollector())
{
	window.create(sf::VideoMode(1024, 768), "test");
}

void Viewer::Render()
{
	window.clear();

	sf::Event event;
	
	while(window.pollEvent(event))
	{

		keyboardHandler.handle(event);
		mouseHandler.handle(event);
	}

	World& world = *GetWorld();
	for (auto& component : world)
	{
		ComponentVisualisers::Visualise(&component, this);
		auto* tmp = dynamic_cast<Facade*>(component.GetFacade());
		if (tmp)
		{
			window.draw(tmp->sprite);
		}		
	}
	window.display();
}

void Viewer::DrawShape(FShape shape, FTransform transform, FColor color)
{
	assert(shape.type == EShapeType::eBox);
	const float pixinunit = 80;
	const float spritesize = 510;
	const float scalefactor = (float)pixinunit/spritesize;
	
	FVector extends = shape.extends;
	
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("C:/Users/dashu/Documents/cproj/YetAnotherProject/box.png");
	sprite.setTexture(texture);
	
	sprite.setTextureRect(sf::IntRect(0, 0, spritesize, spritesize));
	
	FVector origin = transform(-extends)*pixinunit;
	
	
	origin += FVector(255, 255, 0);
	sprite.setScale(scalefactor*extends.X*2, scalefactor*extends.Y * 2);
	sprite.setPosition(sf::Vector2f(origin.X, origin.Y));
	sprite.rotate(transform.Rotation.GetEulerAngles().Z);
	
	
	
	window.draw(sprite);
}

Facade* Viewer::GetRootFacade()
{
	auto* sceneRoot = GetWorld()->GetSceneRoot();
	auto* ifacade   = sceneRoot->GetFacade();
	return dynamic_cast<Facade*>(ifacade);
}
