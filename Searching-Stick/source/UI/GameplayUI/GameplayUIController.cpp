#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Main/GameService.h"

namespace UI
{
	using namespace UIElement;
	using namespace Global;
	using namespace Sound;
	using namespace Main;
	using namespace Gameplay;
	using namespace Collection;

	namespace GameplayUI
	{
		GameplayUIController::GameplayUIController()
		{
			createButton();
			createTexts();
		}

		GameplayUIController::~GameplayUIController()
		{
			destroy();
		}

		void GameplayUIController::createButton()
		{
			menu_button = new ButtonView();
		}

		void GameplayUIController::createTexts()
		{
			search_type_text = new TextView;
			number_of_comparisons_text = new TextView;
			number_of_array_access_text = new TextView;
			num_sticks_text = new TextView;
			delay_text = new TextView;
			time_complexity_text = new TextView;
		}

		void GameplayUIController::initialize()
		{
			initializeButton();
			initializeTexts();
		}

		void GameplayUIController::update()
		{
			menu_button->update();
			updateArrayAccessText();
			updateComparisonsText();
			updateDelayText();
			updateNumberOfSticksText();
			updateSearchTypeText();
			updateTimeComplexityText();
		}

		void GameplayUIController::render()
		{
			menu_button->render();
			search_type_text->render();
			number_of_comparisons_text->render();
			number_of_array_access_text->render();
			num_sticks_text->render();
			delay_text->render();
			time_complexity_text->render();
		}

		void GameplayUIController::show()
		{
			menu_button->show();
			search_type_text->show();
			number_of_comparisons_text->show();
			number_of_array_access_text->show();
			num_sticks_text->show();
			delay_text->show();
			time_complexity_text->show();
		}

		void GameplayUIController::menuButtonCallback()
		{
			ServiceLocator::getInstance()->getGameplayService()->reset();
			ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
			GameService::setGameState(GameState::MAIN_MENU);
		}

		void GameplayUIController::registerButtonCallback()
		{
			menu_button->registerCallbackFuntion(std::bind(& GameplayUIController::menuButtonCallback, this));
		}

		void GameplayUIController::initializeButton()
		{
			menu_button->initialize("Menu Button", Config::menu_button_texture_path, menu_button_width, menu_button_height, sf::Vector2f(menu_button_x_position, menu_button_y_position));
			registerButtonCallback();
		}

		void GameplayUIController::initializeTexts()
		{
			search_type_text->initialize("Search Type : Linear Search", sf::Vector2f(searchType_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			number_of_comparisons_text->initialize("Comparisons : 0", sf::Vector2f(number_of_comparisons_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			number_of_array_access_text->initialize("Array access : 0", sf::Vector2f(number_of_array_access_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			num_sticks_text->initialize("Number of sticks : 0", sf::Vector2f(num_sticks_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			delay_text->initialize("Delay (ms) : 0", sf::Vector2f(delay_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			time_complexity_text->initialize("Time complexity : O(n)", sf::Vector2f(time_complexity_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
		}

		void GameplayUIController::updateArrayAccessText()
		{
			int number_of_array_access = ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess();

			sf::String array_access_sticks = "Array access : " + std::to_string(number_of_array_access);

			number_of_array_access_text->setText(array_access_sticks);
			number_of_array_access_text->update();
		}

		void GameplayUIController::updateComparisonsText()
		{
			int number_of_comparisons = ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparison();

			sf::String comparison_string = "Comparisons : " + std::to_string(number_of_comparisons);
			
			number_of_comparisons_text->setText(comparison_string);
			number_of_comparisons_text->update();
		}

		void GameplayUIController::updateDelayText()
		{
			int delay = ServiceLocator::getInstance()->getGameplayService()->getDelayMilliseconds();

			sf::String delay_string = "Delay (ms) : " + std::to_string(delay);

			delay_text->setText(delay_string);
			delay_text->update();
		}

		void GameplayUIController::updateNumberOfSticksText()
		{
			int number_of_sticks = ServiceLocator::getInstance()->getGameplayService()->getNumberOfSticks();

			sf::String number_of_sticks_string = "Number of sticks : " + std::to_string(number_of_sticks);

			num_sticks_text->setText(number_of_sticks_string);
			num_sticks_text->update();
		}

		void GameplayUIController::updateSearchTypeText()
		{
			Gameplay::Collection::SearchType new_search_type = ServiceLocator::getInstance()->getGameplayService()->getCurrentSearchType();

			switch (new_search_type)
			{
			case Gameplay::Collection::SearchType::LINEAR_SEARCH:
				search_type_text->setText("Linear Search");
				break;

			case Gameplay::Collection::SearchType::BINARY_SEARCH:
				break;
			}

			search_type_text->update();
		}

		void GameplayUIController::updateTimeComplexityText()
		{
			sf::String time_complexity = ServiceLocator::getInstance()->getGameplayService()->getTimeComplexity();

			sf::String time_complexity_string = "Time complexity : " + time_complexity;

			time_complexity_text->setText(time_complexity_string);
			time_complexity_text->update();
		}

		void GameplayUIController::destroy()
		{
			delete(search_type_text);
			delete(number_of_array_access_text);
			delete(number_of_comparisons_text);
			delete(num_sticks_text);
			delete(delay_text);
			delete(time_complexity_text);
			delete(menu_button);
		} 
	}
}