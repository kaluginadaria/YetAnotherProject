#ifndef SIMULATION_MODE_CONFIG_HPP
#define SIMULATION_MODE_CONFIG_HPP

#include "../Threading/Initialiser.hpp"

class PlayerController;
class SimulationMode;
class GameMode;

struct ISimulationModeConfig
{
	float simlationStep = 0;

	virtual UNIQUE(GameMode        ) GetDefaultGameMode        (Initialiser* init) = 0;
	virtual UNIQUE(PlayerController) GetDefaultPlayerController(Initialiser* init) = 0;
};


template<class _CT, class _GM>
struct TSimulationModeConfig : public ISimulationModeConfig
{
	TSimulationModeConfig()
	{
		simlationStep = 1/20.f;
	}

	virtual UNIQUE(GameMode) GetDefaultGameMode(Initialiser* init) override
	{ 
		return ObjectCreator::CreateGameMode<_GM>(init);
	}

	virtual UNIQUE(PlayerController) GetDefaultPlayerController(Initialiser* init) override 
	{ 
		return ObjectCreator::CreatePlayerController<_CT>(init);
	}
};

#endif // !SIMULATION_MODE_CONFIG_HPP
