#ifndef IVIEWER_HPP
#define IVIEWER_HPP

#include "Types.hpp"

class World;
class CameraComponent;
class CameraManager;
class EventCollector;
class PlayerController;


struct IViewer
{
	IViewer(PlayerController* controller)
		: controller(controller)
	{}
	virtual ~IViewer() = default;

public:

	virtual void Render() = 0;
	virtual void DrawShape(FShape shape, Transform transform, Vector4f color) = 0;

	World*			 GetWorld();
	CameraComponent* GetActiveCamera();
	EventCollector*  GetEventCollector();
	CameraManager*   GetCameraManager();

protected:

	PlayerController* controller;
};


#endif // !IVIEWER_HPP
