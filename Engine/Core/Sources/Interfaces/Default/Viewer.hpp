#pragma once
#ifndef VIEWER_HPP
#define VIEWER_HPP

#include "../IViewer.hpp"


struct FViewer : public IViewer
{
public:
	FViewer(PlayerController* controller);

public:
	class  World*           GetWorld();
	class  CameraComponent* GetActiveCamera();
	struct EventCollector*  GetEventCollector();
	class  CameraManager*   GetCameraManager();
};


#endif //!VIEWER_HPP