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

			Stick* stick_to_search;
			
			Collection::SearchType search_type;
			std::thread search_thread;

			int number_of_comparisons;
			int number_of_array_access;
			int current_operation_delay;
			int delay_in_ms;

			sf::String time_complexity;

			void initializeSticks();

			float calculateStickWidth();
			void updateSticksPosition();

			void resetSticksColor();
			void resetVariables();
			void resetSearchStick();

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void joinThread();

			void sortElements();

			void shuffleSticks();

			void processLinearSearch();
			void processBinarySearch();
			void processSearchThreadState();

			bool compareElementsByData(const Stick* a, const Stick* b) const;

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

			int getDelayMilliseconds();

			sf::String getTimeComplexity();
		};
	}
}