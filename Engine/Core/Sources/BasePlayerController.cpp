#include "BasePlayerController.hpp"
#include "Threading/ThreadContext.hpp"

BasePlayerController::BasePlayerController()
	: world (ThreadContext::TopInitialiser()->world)
	, target(nullptr)
{}

void BasePlayerController::OnBeginPlay()
{}

void BasePlayerController::OnEndPlay()
{}

void BasePlayerController::Tick(float DeltaTime, ETickType type)
{}
