#include "Gameplay/GameplayService.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
	}

	GameplayService::~GameplayService()
	{
		delete(gameplay_controller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller->initialize();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
	}
}