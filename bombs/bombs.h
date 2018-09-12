//
// Created by modnosum on 9/13/18.
//

#ifndef LUCKY_LABS_TEST_TASK_BOMBS_H
#define LUCKY_LABS_TEST_TASK_BOMBS_H

#include <stdexcept>
#include <vector>

namespace bombs
{
	using field_type = std::vector<int>;
	using field_value_type = field_type::value_type;
	using field_size_type = field_type::size_type;

	constexpr field_value_type EMPTY_FIELD_DATA = 10;
	constexpr field_value_type BOMB_FIELD_DATA = 0;

	constexpr int FIELD_ROWS = 10;
	constexpr int FIELD_COLS = 10;
	constexpr int FIELD_SIZE = FIELD_ROWS * FIELD_COLS;

	constexpr bool is_valid_field_data(const int data)
	{
		return data >= 0 && data <= 10;
	}

	struct invalid_field_size : std::runtime_error
	{
		explicit invalid_field_size(field_size_type size)
				: runtime_error("invalid field size"),
				  size(size) {}

		field_size_type size;
	};

	struct invalid_field_data : std::runtime_error
	{
		invalid_field_data(field_size_type column, field_size_type row,
						   field_value_type value)
				: runtime_error("invalid field data"),
				  column(column), row(row), value(value) {}

		field_size_type column;
		field_size_type row;
		field_value_type value;
	};

	struct no_place_for_random_bombs : std::runtime_error
	{
		explicit no_place_for_random_bombs(field_size_type left)
				: runtime_error("no space left to place random bombs"),
				  left(left) {}

		field_size_type left;
	};

	struct bomb_exploded_

	void fill_random_bombs(field_type& field, unsigned int bombs);

	void calculate(field_type& field, unsigned int bombs);
}

#endif //LUCKY_LABS_TEST_TASK_BOMBS_H
