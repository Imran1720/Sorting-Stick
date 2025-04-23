#include "Gameplay/Collection/StickCollectionController.h"
#include "Gameplay/Collection/StickCollectionView.h"
#include "Gameplay/Collection/StickCollectionModel.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include "Gameplay/Collection/Stick.h"
#include <random>
#include <iostream>

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

			for (int i = 0; i < collection_model->number_of_elements; i++) sticks.push_back(new Stick(i));
		}

		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}

		void StickCollectionController::initialize()
		{
			sort_state = SortState::NOT_SORTING;
			collection_view->initialize(this);
			initializeSticks();
			reset();
		}

		void StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();


			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i); //calc height

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		void StickCollectionController::update()
		{
			processSortThreadState();
			collection_view->update();
			for (int i = 0; i < sticks.size(); i++) sticks[i]->stick_view->update();
		}

		void StickCollectionController::render()
		{
			collection_view->render();
			for (int i = 0; i < sticks.size(); i++) sticks[i]->stick_view->render();
		}

		float StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			// Calculate total spacing as 10% of the total space
			float total_spacing = collection_model->space_percentage * total_space;

			// Calculate the space between each stick
			float space_between = total_spacing / (collection_model->number_of_elements);
			collection_model->setElementSpacing(space_between);

			// Calculate the remaining space for the rectangles
			float remaining_space = total_space - total_spacing;

			// Calculate the width of each rectangle
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		float StickCollectionController::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void StickCollectionController::updateStickPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);
				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void StickCollectionController::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
			updateStickPosition();
		}

		bool StickCollectionController::compareSticksByData(const Stick* a, const Stick* b) const
		{
			return a->data < b->data;
		}

		void StickCollectionController::processSortThreadState()
		{
			if (sort_thread.joinable() && isCollectionSorted())
			{
				sort_thread.join();
				sort_state = SortState::SORTING;
				std::cout << "Not Sorting" << std::endl;
			}
		}

		void StickCollectionController::processBubbleSort()
		{
			Sound::SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();
			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
					if (sort_state == SortState::NOT_SORTING)
					{
						break;
					}
				bool swapped = false;

				for (int j = 0; j < collection_model->number_of_elements - i - 1; j++)
				{
					if (sort_state == SortState::NOT_SORTING)
					{
						break;
					}

					number_of_array_access+=2;
					number_of_comparisons++;
					
					sound_service->playSound(Sound::SoundType::COMPARE_SFX);
					
					sticks[j]->stick_view->setFillColor(collection_model->processing_element_color);
					sticks[j+1]->stick_view->setFillColor(collection_model->processing_element_color);
					

					if (sticks[j]->data > sticks[j + 1]->data)
					{
						Stick* temp_stick = sticks[j];
						sticks[j] = sticks[j + 1];
						sticks[j + 1] = temp_stick;
						swapped = true;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

					if (swapped)
					{
						sticks[j + 1]->stick_view->setFillColor(collection_model->placement_position_element_color);
					}
					else
					{
						sticks[j + 1]->stick_view->setFillColor(collection_model->element_color);
					}
					sticks[j]->stick_view->setFillColor(collection_model->element_color);

					updateStickPosition();
				}
				if (!swapped)
				{
					break;
				}
			}

			setCompletedColor();
		}

		void StickCollectionController::processInsertionSort()
		{
			Sound::SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();
			for (int i = 1; i < collection_model->number_of_elements; i++)
			{
				if (sort_state == SortState::NOT_SORTING)
				{
					break;
				}

				Stick* key = sticks[i];
				int j;

						sound_service->playSound(Sound::SoundType::COMPARE_SFX);
				key->stick_view->setFillColor(collection_model->processing_element_color);
				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

				for (j = i - 1; j >= 0; j--)
				{
					if (sort_state == SortState::NOT_SORTING)
					{
						break;
					}

					number_of_array_access+=2;
					number_of_comparisons++;

					if (sticks[j]->data > key->data)
					{

						sound_service->playSound(Sound::SoundType::COMPARE_SFX);
						sticks[j+1] = sticks[j];
						sticks[j]->stick_view->setFillColor(collection_model->processing_element_color);
						updateStickPosition();
						sticks[j +1]->stick_view->setFillColor(collection_model->processing_element_color);
						std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

						sticks[j]->stick_view->setFillColor(collection_model->selected_element_color);
						sticks[j +1]->stick_view->setFillColor(collection_model->selected_element_color);

					}
					else
					{

						break;
					}
				}
				sticks[j + 1] = key;
				updateStickPosition();
				sticks[j + 1]->stick_view->setFillColor(collection_model->temporary_processing_color);
				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
				sticks[j + 1]->stick_view->setFillColor(collection_model->selected_element_color);

			}
				setCompletedColor();
		}

		void StickCollectionController::processSelectionSort()
		{
			int min_index;
			int max_range = collection_model->number_of_elements;
			Stick* temporary_stick = nullptr;
			Sound::SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();

			for (int i = 0; i < max_range; i++)
			{
				if (sort_state == SortState::NOT_SORTING)
				{
					break;
				}
				min_index = i;
				sticks[i]->stick_view->setFillColor(collection_model->selected_element_color);

				for (int j = i + 1; j < max_range; j++)
				{
					if (sort_state == SortState::NOT_SORTING)
					{
						break;
					}
					sound_service->playSound(Sound::SoundType::COMPARE_SFX);
				
					number_of_array_access += 2;
					number_of_comparisons++;
					
					if (sticks[min_index]->data > sticks[j]->data)
					{
						if (min_index != i) 
							sticks[min_index]->stick_view->setFillColor(collection_model->element_color);
						min_index = j;
						sticks[min_index]->stick_view->setFillColor(collection_model->temporary_processing_color);
						continue;
					}
					sticks[j]->stick_view->setFillColor(collection_model->processing_element_color);
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
					sticks[j]->stick_view->setFillColor(collection_model->element_color);
				}

				if (min_index != i)
				{

					temporary_stick = sticks[i];
					sticks[i] = sticks[min_index];
					sticks[min_index] = temporary_stick;
					updateStickPosition();
				}
				sticks[i]->stick_view->setFillColor(collection_model->placement_position_element_color);

			}
		}

		void StickCollectionController::processInPlaceMergeSort()
		{
			int size = getNumberOfSticks() - 1;
			if (size > 1)
			{
				inPlaceMergeSort(0, size);
				inPlaceMerge(0, size / 2, size);
				setCompletedColor();
			}
		}

		void StickCollectionController::inPlaceMergeSort(int left, int right)
		{
			if (left >= right)
			{
				return;
			}

			int mid = left + (right - left) / 2;
			inPlaceMergeSort(left, mid);
			inPlaceMerge(left, (left + (mid-left) / 2), mid);

			inPlaceMergeSort(mid+1,right);
			inPlaceMerge(mid + 1, (mid + 1) + (right - (mid + 1)) / 2, right);
		}

		void StickCollectionController::inPlaceMerge(int left, int mid, int right)
		{
			Sound::SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();
			int start2 = mid + 1;
			
			if (mid < 0 || mid >= sticks.size() || start2 < 0 || start2 >= sticks.size()) {
				return;
			}

			if (sticks[mid]->data <= sticks[start2]->data )
			{
				number_of_array_access += 2;
				number_of_comparisons++;
				return;
			}

			while (left <= mid && start2 <= right)
			{
				sound_service->playSound(Sound::SoundType::COMPARE_SFX);
				if (sticks[left]->data <= sticks[start2]->data)
				{
					left++;
					number_of_comparisons++;
				}
				else
				{
					Stick* temp_stick = sticks[start2];

					for (int i = start2; i > left; i--)
					{
						sound_service->playSound(Sound::SoundType::COMPARE_SFX);
						sticks[i] = sticks[i - 1];
						number_of_array_access+=2;

						sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);
						sticks[i-1]->stick_view->setFillColor(collection_model->processing_element_color);

						std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

						sticks[i]->stick_view->setFillColor(collection_model->element_color);
						sticks[i - 1]->stick_view->setFillColor(collection_model->element_color);
					}

					sticks[left] = temp_stick;
					left++;
					start2++;
					mid++;
					updateStickPosition();

				}
			}
		}

		void StickCollectionController::setCompletedColor()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				sticks[i]->stick_view->setFillColor(collection_model->element_color);

			}
			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				if (sort_state == SortState::NOT_SORTING)
				{
					break;
				}
				
				
				std::this_thread::sleep_for(std::chrono::milliseconds(color_delay));

				ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::COMPARE_SFX);
				sticks[i]->stick_view->setFillColor(collection_model->placement_position_element_color);
			}

			/*if (sort_state == SortState::SORTING)
			{
				ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::);
			}*/
		}


		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++) sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void StickCollectionController::resetVariables()
		{
			current_operation_delay = 0;
			color_delay = 0;

			number_of_comparisons = 0;
			number_of_array_access = 0;
		}

		void StickCollectionController::reset()
		{
			sort_state = SortState::NOT_SORTING;
			
			if (sort_thread.joinable()) sort_thread.join();

			shuffleSticks();
			resetSticksColor();
			resetVariables();
		}

		void StickCollectionController::sortElements(SortType sort_type)
		{
			current_operation_delay = collection_model->operation_delay;
			this->sort_type = sort_type;
			sort_state = SortState::SORTING;


			switch (sort_type)
			{
			case Gameplay::Collection::SortType::BUBBLE_SORT:
				color_delay = collection_model->initial_color_delay;
				current_operation_delay = collection_model->operation_delay;
				time_complexity = "O(n^2)";
				sort_thread = std::thread(&StickCollectionController::processBubbleSort, this);
				break;

			case Gameplay::Collection::SortType::INSERTION_SORT:
				color_delay = collection_model->initial_color_delay;
				current_operation_delay = collection_model->operation_delay;
				time_complexity = "O(n^2)";

				sort_thread = std::thread(&StickCollectionController::processInsertionSort, this);
				break;

			case Gameplay::Collection::SortType::SELECTION_SORT:
				color_delay = collection_model->initial_color_delay;
				current_operation_delay = collection_model->operation_delay;
				time_complexity = "O(n^2)";

				sort_thread = std::thread(&StickCollectionController::processSelectionSort, this);
				break;

			case Gameplay::Collection::SortType::MERGE_SORT:
				color_delay = collection_model->initial_color_delay;
				current_operation_delay = collection_model->operation_delay;
				time_complexity = "O(log n)";

				sort_thread = std::thread(&StickCollectionController::processInPlaceMergeSort, this);
				break;
			}
		}

		bool StickCollectionController::isCollectionSorted()
		{
			for (int i = 1; i < sticks.size(); i++) if (sticks[i] < sticks[i - 1]) return false;
			return true;
		}

		void StickCollectionController::destroy()
		{
			current_operation_delay = 0;
			if (sort_thread.joinable()) sort_thread.join();

			for (int i = 0; i < sticks.size(); i++) delete(sticks[i]);
			sticks.clear();

			delete (collection_view);
			delete (collection_model);
		}

		SortType StickCollectionController::getSortType() { return sort_type; }

		int StickCollectionController::getNumberOfComparisons() { return number_of_comparisons; }

		int StickCollectionController::getNumberOfArrayAccess() { return number_of_array_access; }

		int StickCollectionController::getNumberOfSticks() { return collection_model->number_of_elements; }

		int StickCollectionController::getDelayMilliseconds() { return current_operation_delay; }

		sf::String StickCollectionController::getTimeComplexity() { return time_complexity; }
	}
}


