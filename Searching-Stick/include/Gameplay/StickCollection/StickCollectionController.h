#pragma once

#include <SFML/Graphics.hpp>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionView;
		class StickCollectionModel;
		struct Stick;
		enum class SearchType;

		class StickCollectionController
		{
		private:
			StickCollectionView* collection_view;
			StickCollectionModel* collection_medel;

			std::vector<Stick*> sticks;
			
			Collection::SearchType search_type;

			void initializeSticks();

			float calculateStickWidth();

			void updateStickPosition();

			void resetSticksColor();

			void initializeSticksArray();
			float calculateStickHieght(int array_pos);

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void render();
			void update();

			void reset();

			SearchType getSearchType();

			int getNumberOfSticks();
		};
	}
}