#include "Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
		collection_controlller = new StickCollectionController();
	}

	GameplayService::~GameplayService()
	{
		delete(gameplay_controller);
		delete(collection_controlller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller->initialize();
		collection_controlller->initialize();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
		collection_controlller->render();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
		collection_controlller->update();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
		collection_controlller->reset();
	}
}