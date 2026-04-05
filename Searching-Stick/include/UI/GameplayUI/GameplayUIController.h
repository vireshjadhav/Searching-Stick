#pragma once

#include "UI/Interface/IUIController.h"
#include "UI/UIElement/TextView.h"
#include "UI/UIElement/ButtonView.h"
#include "UI/UIElement/ImageView.h"
#include "Gameplay/GameplayService.h"

namespace UI
{
	namespace GameplayUI
	{
		class GameplayUIController: public Interface::IUIController
		{
		private:
			const float text_y_position = 36.0f;
			const float text_y_position_2 = 76.0f;

			const float font_size = 40.0f;

			const float searchType_x_position = 60.0f;
			const float number_of_comparisons_x_position = 687.0f;
			const float number_of_array_access_x_position = 1250.0f;
			const float num_sticks_x_position = 60.0f;
			const float delay_x_position = 687.f;
			const float time_complexity_x_position = 1250.0f;

			const float menu_button_x_position = 1770.0f;
			const float menu_button_y_position = 33.0f;

			const float menu_button_width = 100.0f;
			const float menu_button_height = 50.0f;

			UIElement::TextView* search_type_text;
			UIElement::TextView* number_of_comparisons_text;
			UIElement::TextView* number_of_array_access_text;
			UIElement::TextView* num_sticks_text;
			UIElement::TextView* delay_text;
			UIElement::TextView* time_complexity_text;

			UIElement::ButtonView* menu_button;

			void createButton();
			void createTexts();

			void initializeButton();
			void initializeTexts();

			void updateSearchTypeText();
			void updateComparisonsText();
			void updateArrayAccessText();
			void updateNumberOfSticksText();
			void updateDelayText();
			void updateTimeComplexityText();

			void registerButtonCallback();
			void menuButtonCallback();

			void destroy();

		public:
			GameplayUIController();
			~GameplayUIController();

			void initialize() override;

			void update() override;
			void render() override;

			void show() override;
		};
	}
}