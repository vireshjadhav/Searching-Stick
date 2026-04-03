#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionView;
		class StickCollectionModel;
		enum class SearchType;
		struct Stick;

		class StickCollectionController
		{
		private:
			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;

			std::vector<Stick*> sticks;
			
			Collection::SearchType search_type;

			void initializeSticks();

			float calculateStickWidth();

			void updateSticksPosition();

			void resetSticksColor();

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void render();
			void update();

			void reset();
			void searchElement(SearchType search_type);

			SearchType getSearchType();

			int getNumberOfSticks();
		};
	}
}