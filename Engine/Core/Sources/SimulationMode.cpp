#include "SimulationMode.hpp"
#include "PlayerController.hpp"
#include "GameMode.hpp"


SimulationMode::SimulationMode(ISimulationModeConfig* config)
	: bStop		 (0)
	, lastTime	 (0)
	, currentTime(0)
	, config(config)
{
	if (config)
	{
		auto init = Initialiser::Get();
		init->world = new World();
		init->simulation = this;

		controller = std::move(config->GetDefaultPlayerController(init.get()) );
		init->controller = controller.get();

		gameMode = std::move(config->GetDefaultGameMode(init.get()) );
		if (gameMode) 
		{
			gameMode->OnConstructed();
		}
	}
}

SimulationMode::~SimulationMode()
{
	if (gameMode)
	{
		gameMode->OnStartDestroy();
	}
}

UNIQUE(SimulationMode) SimulationMode::Get(ISimulationModeConfig* config)
{
	return std::make_unique<SimulationMode>(config);
}

void SimulationMode::OnSimulationBegin()
{
	if (gameMode)
	{
		gameMode->OnBeginPlay();
	}
	if (controller) 
	{
		controller->OnBeginPlay();
	}
}

void SimulationMode::OnSimulationEnd()
{
	if (gameMode)
	{
		gameMode->OnEndPlay();
	}
	if (controller)
	{
		controller->OnEndPlay();
	}
}

void SimulationMode::DoTick(float deltaTime, ETickType type)
{
	gameMode->Tick(deltaTime, type);

	if (type == ETickType::ePostPhysics)
	{
		controller->Tick(deltaTime, type);
	}
	if (type == ETickType::eRender)
	{
		controller->Render();
	}
}

void SimulationMode::StopSimulation()
{
	// TODO::
	bStop = true;
}

bool SimulationMode::TickRequired() const
{
	return !bStop;
}

float SimulationMode::GetSimulationStep() 
{ 
	if (config)
	{
		return config->simlationStep;
	}
	return 1/30;
}

void SimulationMode::SetDeltaTime(float delta)
{
	lastTime = currentTime;
	currentTime += delta;
}
