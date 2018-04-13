#include "PlayerController.hpp"

#include <assert.h>
#include <thread>

#include "World.hpp"
#include "Avatar.hpp"

#include "Modules/ModuleManager.hpp"


const unsigned int MASK_2D = 0xF0000000;
const unsigned int MASK_3D = 0x0F000000;



PlayerController::PlayerController()
	: cameraManager()
	, viewer(ModuleManager::MakeViewer(this))
{}

PlayerController::~PlayerController()
{}

void PlayerController::OnBeginPlay()
{
	Super::OnBeginPlay();
	if (target)
	{
		EventBinder binder;

		target->SetupInput(&binder);

		eventManager.ProcessEventBinder(binder);
	}
}

void PlayerController::Tick(float DeltaTime, ETickType type)
{
	processInput();
}

void PlayerController::Render()
{
	if (viewer)
	{
		viewer->Render();
	}
}

void PlayerController::UnregisterCamera(CameraComponent* camera)
{
	cameraManager.UnregisterCamera(camera);
}

void PlayerController::RegisterCamera(CameraComponent* camera, bool bActivate)
{
	cameraManager.RegisterCamera(camera, bActivate);
}

void PlayerController::SetCameraActive(CameraComponent* camera, bool newState)
{
	cameraManager.SetCameraActive(camera, newState);
}

CameraComponent* PlayerController::GetActiveCamera()
{
	return cameraManager.GetCurrentCamera();
}

CameraManager& PlayerController::GetCameraManager()
{
	return cameraManager;
}

EventCollector& PlayerController::GetEventCollector()
{
	return eventCollector;
}

void PlayerController::processInput()
{
	auto& events  = eventCollector.GetEvents();
	float mouse_X = eventCollector.GetMouseX();
	float mouse_Y = eventCollector.GetMouseY();

	eventManager.ProcessKeys(events);
	eventManager.UpdateMouseLocation(mouse_X, mouse_Y);

	eventCollector.Flush();
}
