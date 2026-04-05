#pragma once

#include <SFML/System/String.hpp>
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionController.h"

namespace Gameplay
{
	using namespace Collection;

	class GameplayController;
	enum class SearchType;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		StickCollectionController* collection_controlller;

		void initializeRandomSeed();

	public:
		GameplayService();
		~GameplayService();

		void initialize();

		void render();
		void update();

		void reset();
		void searchElement(Collection::SearchType search_type);

		Collection::SearchType getCurrentSearchType();

		int getNumberOfSticks();
		int getNumberOfComparison();
		int getNumberOfArrayAccess();
		int getDelayMilliseconds();
		sf::String getTimeComplexity();
	};
}
