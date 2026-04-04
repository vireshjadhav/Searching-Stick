#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

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

			Stick* stick_to_search;
			
			Collection::SearchType search_type;

			int number_of_comparisons;
			int number_of_array_access;

			void initializeSticks();

			float calculateStickWidth();
			void updateSticksPosition();

			void resetSticksColor();
			void resetSearchStick();

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void shuffleSticks();
			void processLinearSeach();
			void resetVariables();

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void render();
			void update();

			void reset();
			void searchElement(SearchType search_type);

			int getNumberOfSticks();

			SearchType getSearchType();

			int getNumberOfComparisons();
			int getNumberOfArrayAccess();
		};
	}
}