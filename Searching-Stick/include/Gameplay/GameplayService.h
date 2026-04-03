#pragma once

#include "Gameplay/GameplayController.h"
#include "Gameplay/GameplayView.h"

namespace Gameplay
{
	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

	public:
		GameplayService();
		~GameplayService();

		void initialize();

		void render();
		void update();

		void reset();
	};
}
