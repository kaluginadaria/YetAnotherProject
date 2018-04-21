#ifndef SIMULATION_MODE_HPP
#define SIMULATION_MODE_HPP
#pragma once

#include "Common.hpp"
#include "Configs/SimulationModeConfig.hpp"

class GameMode;
class PlayerController;


/** A class handling a symualtion
 *	Tasks:
 *	. world initialisation
 *	. 
 */
class SimulationMode
{
public:

	SimulationMode(ISimulationModeConfig* config);
	virtual ~SimulationMode();

	static UNIQUE(SimulationMode) Get(ISimulationModeConfig* config);

public: //~~~~~~~~~~~~~~| API for an @Engine

	virtual void OnSimulationBegin();
	virtual void OnSimulationEnd();

	virtual void DoTick(float deltaTime, ETickType type);
	
	virtual void StopSimulation();

	virtual bool TickRequired() const;

public:

	float GetSimulationStep();

	void SetDeltaTime(float delta);

protected:

	/// >> tick
	bool bStop;
	/// << 

	/// >> time (seconds)
	float currentTime;
	float lastTime;
	/// <<

	/// >>
	UNIQUE(ISimulationModeConfig) config;
	UNIQUE(PlayerController) controller;
	UNIQUE(GameMode) gameMode;
	/// <<
};

#endif // SIMULATION_MODE_HPP