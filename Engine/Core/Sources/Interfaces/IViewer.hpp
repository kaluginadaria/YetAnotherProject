#ifndef IVIEWER_HPP
#define IVIEWER_HPP

#include "Types.hpp"

class World;
class CameraComponent;
class CameraManager;
class PlayerController;
struct EventCollector;


struct IViewer
{
	IViewer(PlayerController* controller)
		: controller(controller)
	{}
	virtual ~IViewer() = default;

public:

	virtual void Render() = 0;
	virtual void DrawShape(FShape shape, FTransform transform, FColor color) = 0;

	World*			 GetWorld();
	CameraComponent* GetActiveCamera();
	EventCollector*  GetEventCollector();
	CameraManager*   GetCameraManager();

protected:

	PlayerController* controller;
};


#endif // !IVIEWER_HPP
