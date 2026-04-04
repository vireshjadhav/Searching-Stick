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
		initializeRandomSeed();
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

	void GameplayService::initializeRandomSeed()		// Helper function for initializing the random seed
	{
		// Seed the random number generator with the current time
		// This ensures that the sequence of random numbers will be different each time the program is run
		// The `std::time(nullptr)` function returns the current time as the number of seconds since the Unix epoch (January 1, 1970)
		// The `static_cast<unsigned int>` is used to cast the `std::time_t` value to an `unsigned int`, which is required by `std::srand`
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}

	void GameplayService::searchElement(Collection::SearchType search_type)
	{
		collection_controlller->searchElement(search_type);
	}
}