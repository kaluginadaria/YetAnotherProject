#include "SFMLViewer.hpp"

#include "World.hpp"
#include "ActorComponent.hpp"
#include "ComponentVisualisers.hpp"

#include <iostream>


Viewer::Viewer(PlayerController* controller)
	: IViewer(controller)
{
	window.create(sf::VideoMode(1024, 768), "test");
}

void Viewer::Render()
{
	window.clear();

	sf::Event event;
	while(window.pollEvent(event)) // the sheet doesn't works without the stuff
	{
		if(event.type == sf::Event::Closed)
			window.close();
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
	std::cout << scalefactor << std::endl;
	FVector extends = shape.extends;
	sf::Sprite sprite2;
	sf::Texture texture2;
	texture2.loadFromFile("C:/Users/makde/Desktop/YetAnotherProject/box2.png");
	sprite2.setTexture(texture2);
	sprite2.setPosition(sf::Vector2f(255, 255));
	
	sprite2.setTextureRect(sf::IntRect(0, 0, 5, 5));
	
	window.draw(sprite2);
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("C:/Users/makde/Desktop/YetAnotherProject/box.png");
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
