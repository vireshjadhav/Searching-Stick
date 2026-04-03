#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"


namespace Gameplay
{
	namespace Collection
	{
		using namespace UI::UIElement;
		using namespace Global;
		using namespace Graphics;

		StickCollectionController::StickCollectionController()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}

		void StickCollectionController::initialize()
		{
			initializeSticks();
			reset();
		}

		void StickCollectionController::update()
		{
			for (int i = 0; i < sticks.size(); ++i)
			{
				sticks[i]->stick_view->update();
			}
		}

		void StickCollectionController::render()
		{
			for (int i = 0; i < sticks.size(); ++i)
			{
				sticks[i]->stick_view->render();
			}
		}

		void StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();					// calculate width

			// loop over the vector of sticks
			for (int i = 0; i < collection_model->number_of_elements; ++i)
			{
				// calculate height ( assigning the returned value from the calculateStickHeight() method to the variable rectangle_height) 
				float rectangle_height = calculateStickHeight(i);

				// create a 2D vector 'rectangle_size' to store width and height of rectangle
				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				// Initialize each stick at 0,0 with the default color 
				// You will update the position of sticks later
				// You will change the color of the sticks later to visually show the search algorithm taking place.
				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float StickCollectionController::calculateStickWidth()
		{
			// to get the width of the game window
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			// Calculate total spacing as 10% of the total space
			float total_spacing = collection_model->space_percentage * total_space;

			// Calculate the space between each stick
			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			// Calculate the remaining space for the rectangles
			float remaining_space = total_space - total_spacing;

			// Calculate the width of each rectangle
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		float StickCollectionController::calculateStickHeight(int array_pos)		// calculate the stick height based on its position in the array
		{
			// scaling its position to a range of 0.0 to 1.0 and multiplying by the maximum element height.
			return (static_cast<float>(array_pos +1) /collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void StickCollectionController::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); ++i)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);

				float y_position = collection_model->element_y_poition - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void StickCollectionController::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; ++i)
			{
				sticks.push_back(new Stick(i));
			}
		}

		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); ++i)
			{
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
			}
		}

		void StickCollectionController::searchElement(SearchType search_type)
		{

		}

		void StickCollectionController::reset()
		{
			updateSticksPosition();
			resetSticksColor();
		}

		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}

		int StickCollectionController::getNumberOfSticks()
		{
			return collection_model->number_of_elements;
		}

		void StickCollectionController::destroy()
		{
			for (int i = 0; i < sticks.size(); ++i)
				delete(sticks[i]);

			delete(collection_view);
			delete(collection_model);
		}
	}
}