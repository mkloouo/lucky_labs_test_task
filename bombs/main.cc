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
	bombs::field_type test_field(bombs::FIELD_SIZE, 10);

	try
	{
		bombs::calculate(test_field, 12);
	} catch (bombs::invalid_field_size& ex)
	{
		std::cout << ex.what() << " given size:" << ex.size << std::endl;
	} catch (bombs::invalid_field_data& ex)
	{
		std::cout << ex.what() << ": " << ex.value << " at (" << ex.column
				  << ", " << ex.row << ")"
				  << std::endl;
	} catch (bombs::no_place_for_random_bombs& ex)
	{
		std::cout << ex.what() << " bombs left: " << ex.left << std::endl;
	}

	for (bombs::field_size_type i = 0; i < test_field.size(); ++i)
	{
		if ((i % bombs::FIELD_COLS) == 0)
		{

		}
	}

	return 0;
}