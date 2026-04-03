#pragma once

#include <SFML/Graphics.hpp>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionView
		{
		public:
			StickCollectionView();
			~StickCollectionView();

			void initialize();
			void update();
			void render();
		};
	}
}