#include "GameMode.hpp"
#include "Threading/ThreadContext.hpp"
#include "Threading/Initialiser.hpp"
#include "PlayerController.hpp"

GameMode::GameMode()
	: simulationMode(ThreadContext::TopInitialiser()->simulation)
	, world			(ThreadContext::TopInitialiser()->world     )
{
	playerController = static_cast<PlayerController*>(ThreadContext::TopInitialiser()->controller);
}

void GameMode::Tick(float DeltaTime, ETickType type)
{
	if (world)
	{
		world->DoTick(DeltaTime, type);
	}
}
