#include "Engine.hpp"
#include "B2Config.hpp"
#include "OSGConfig.hpp"
#include "Modules/ModuleManager.hpp"

#include "PDGameMode.hpp"
#include "PDPlayerController.hpp"
#include "Pendulum.hpp"

using PDSimulationConfig = TSimulationModeConfig<PDPlayerController, PDGameMode>;



int main()
{
	ModuleManager::SetFrontendConfig(new OSGConfig());
	ModuleManager::SetPhysicsConfig (new B2Config() );

	auto* config = new PDSimulationConfig();
	auto mode = SimulationMode::Get(config);
	
	Engine engine;
	engine.SetSimulationMode(std::move(mode));
	return engine.MainCycle();
}