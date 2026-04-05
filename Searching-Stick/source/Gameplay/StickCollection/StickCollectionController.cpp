#include <random>
#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include "Sound/SoundService.h"


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
			collection_model->initialize();
			initializeSticks();
			reset();

			time_complexity = "XYZ";
		}

		void StickCollectionController::update()
		{
			processSearchThreadState();
			collection_view->update();

			for (int i = 0; i < sticks.size(); ++i)
			{
				sticks[i]->stick_view->update();
			}
		}

		void StickCollectionController::render()
		{
			collection_view->render();

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
			// stores the search type that is chosen
			this->search_type = search_type;

			switch (search_type)			// checks the value of search_type
			{
			case SearchType::LINEAR_SEARCH:			// checks if the search type is LINEAR SEARCH
			
				time_complexity = "O(n)";

				// obtains delay for linear search
				current_operation_delay = collection_model->linear_search_delay;

				// a new thread, 'search_thread' is created to execute the 'processLinearSearch'
				// 'this' keyword is passed to provide the context of the current 'StickCollectionContoller' object, allowing 'processLinearSearch' to access its data
				search_thread = std::thread(&StickCollectionController::processLinearSearch, this);
				break;

			case SearchType::BINARY_SEARCH:
				time_complexity = "O(log n)";
				// sort the collection before the binary search performs
				sortElements();

				// sets delay for binary search
				current_operation_delay = collection_model->binary_search_delay;

				// separate thread for executing 'processBinarySearch'
				search_thread = std::thread(&StickCollectionController::processBinarySearch, this);
				break;
			}
		}

		void StickCollectionController::reset()
		{
			current_operation_delay = 0;

			if (search_thread.joinable()) search_thread.join();

			shuffleSticks();
			updateSticksPosition();
			resetSticksColor();
			resetSearchStick();
			resetVariables();
		}

		void StickCollectionController::shuffleSticks()
		{
			// declare a variable 'device' of type std::random_device
			// 'std::random_device is a random number generator that produces non-deterministic random numbers.
			std::random_device device;
			std::mt19937 randome_engine(device());

			// shuffle the elements in the sticks collection using the random engine
			std::shuffle(sticks.begin(), sticks.end(), randome_engine);
		}

		void StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}

		void StickCollectionController::processLinearSearch()
		{
			Sound::SoundService* sound_service = Global::ServiceLocator::getInstance()->getSoundService();

			for (int i = 0; i < sticks.size(); ++i)
			{
				number_of_array_access += 1;		// keeps track of the number of sticks array is accessed
				number_of_comparisons++;			// keeps track of the number of comparisons made between target stick and another stick
					
				sound_service->playSound(Sound::SoundType::COMPARE_SFX);		// play the comparision sound

				if (sticks[i] == stick_to_search)		// condition to check if the current stick is the target stick
				{
					// if the target stick is found, this line of code sets the fill colour of the target's stick view
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;		// sets the pointer to null; meaning the search is completed.
					return;
				}
				else
				{
					// sets the fill color of the current stick's view to the processing_element_color; meaning the stick is still being checked
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);
					
					//pauses the thread for a small duration to show the searching operation
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

					// sets the fill color of the current stick's view back to the default element_color after the pause.
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}

			}
		}

		void StickCollectionController::processBinarySearch()
		{
			// initialize left index to the start of the collection
			int left = 0;

			// initialize right index to the size of the collection which is the end
			int right = sticks.size();

			Sound::SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();

			// loop for binary search
			while (left < right)
			{
				// calculate the middle index
				int mid = left + (right - left) / 2;
				number_of_array_access += 2;			//keeps track of the number of sticks array is accessed
				number_of_comparisons++;				// keeps track of the number of comparisons made between target stick and another stick

				sound_service->playSound(Sound::SoundType::COMPARE_SFX);			// play comparison sound effect

				// check if target element is found at the middle index
				if (sticks[mid] == stick_to_search)
				{
					// if the target element is found, set color for found element
					sticks[mid]->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;			//ets the pointer to null; meaning the search is completed
					return;
				}
				
				sticks[mid]->stick_view->setFillColor(collection_model->processing_element_color);			// if mid is not the target element, set the stick color to processing element color

				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));			// //pauses the thread for a small duration to show the searching operation

				sticks[mid]->stick_view->setFillColor(collection_model->element_color);						// sets the fill color of the mid stick's view back to the default element_color after the pause.

				number_of_array_access++;			// increment counter for array access for mid element access

				// target can be in the right half or middle element itself
				if (sticks[mid]->data <= stick_to_search->data) left = mid;			// target must be in the right half, mid element included beacuse '<='
				else right = mid;				// target must be in the left half
			}

		}

		void StickCollectionController::processSearchThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThread();
			}
		}

		void StickCollectionController::joinThread()
		{
			search_thread.join();
		}

		void StickCollectionController::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
		}

		void StickCollectionController::sortElements()
		{
			// sort the sticks collection based on a custom comparison function
			std::sort(sticks.begin(), sticks.end(), [this](const Stick* a, const Stick* b) {return compareElementsByData(a, b); });			// 'compareElementsByData' function to determine order
			
			// after sorting, update the positions of the sticks in the view.
			updateSticksPosition();
		}


		// this function compares two Stick objects based on their data member. 
		// it takes two pointers to Stick objects, 'a' and 'b', as arguments.
		bool StickCollectionController::compareElementsByData(const Stick* a, const Stick* b) const
		{
			// if 'a->data' is less than 'b->data', the expression evaluates to true which indicates that 'a' should precede 'b' in the sorted order.
			return a->data < b->data;
		}

		int StickCollectionController::getNumberOfArrayAccess() { return number_of_array_access; }

		int StickCollectionController::getNumberOfComparisons() { return number_of_comparisons; }
	
		int StickCollectionController::getNumberOfSticks() { return collection_model->number_of_elements; }
		
		int StickCollectionController::getDelayMilliseconds() { return current_operation_delay; }

		SearchType StickCollectionController::getSearchType() { return search_type; }

		sf::String StickCollectionController::getTimeComplexity() { return time_complexity; }

		void StickCollectionController::destroy()
		{
			if (search_thread.joinable()) search_thread.join();


			for (int i = 0; i < sticks.size(); ++i)
				delete (sticks[i]);

			sticks.clear();

			delete(collection_view);
			delete(collection_model);
		}
	}
}