/**
 * Execution start point.
 *
 * @date 09/13/2018
 * @author Mykola Odnosumov
 */

#include <iostream>

#include "bombs.h"

int main()
{
	bombs::field_type test_field(bombs::FIELD_SIZE,
			bombs::FieldDataType::Nothing);
	bombs::fill_with_random_bombs(test_field, bombs::DEFAULT_INITIAL_BOMBS);

	try
	{
		bombs::calculate(test_field, 1);

		std::cout << "After calculation:" << std::endl;
		bombs::print_field(test_field);
		std::cout << std::endl;
	}
	catch (bombs::invalid_field_size& ex)
	{
		std::cout << ex.what() << " given size:" << ex.size << std::endl;
	}
	catch (bombs::invalid_field_data& ex)
	{
		std::cout << ex.what() << ": " << ex.value << " at (" << ex.column
				  << ", " << ex.row << ")"
				  << std::endl;
	}
	catch (bombs::no_place_for_random_bombs& ex)
	{
		std::cout << ex.what() << " bombs left: " << ex.left << std::endl;
	}
	return 0;
}