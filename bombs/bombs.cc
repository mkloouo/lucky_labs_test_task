//
// Created by modnosum on 9/13/18.
//

#include <random>
#include <algorithm>
#include "bombs.h"

namespace bombs
{
	void fill_random_bombs(field_type& field, unsigned int bombs)
	{
		field_type available_positions;
		for (auto f: field)
		{
			if (f >= )
		}


		std::random_device random_device;
		std::default_random_engine engine(random_device());
		std::uniform_int_distribution<field_value_type>
				field_position_dist(0, FIELD_SIZE - 1);

		std::vector<int> random_bombs_positions(bombs);
		std::for_each(random_bombs_positions.begin(),
					  random_bombs_positions.end(),
					  [&](field_value_type& value)
					  {
						  value = field_position_dist(engine);
					  });


	}

	void calculate(field_type& field, unsigned int bombs)
	{
		if (field.size() != FIELD_SIZE)
		{
			throw invalid_field_size(field.size());
		}

		fill_random_bombs(field, bombs);

		for (size_t i = 0; i < field.size(); ++i)
		{
			if (field[i] >= 0 && field[i] <= 10)
			{
			}
			else
			{
				throw invalid_field_data(i / FIELD_ROWS, i % FIELD_COLS,
										 field[i]);
			}
		}
	}
}