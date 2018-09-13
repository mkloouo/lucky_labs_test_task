//
// Created by modnosum on 9/13/18.
//

#include "bombs.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

#define __ANSI_RESET_COLOR__ "\033[0m"

#define __ANSI_RED_COLOR__ "\033[31m"
#define __ANSI_EXPLOSION_COLOR__ "\033[30;7m"
#define __ANSI_BLUE_COLOR__ "\033[34m"
#define __ANSI_CYAN_COLOR__ "\033[36m"

namespace bombs
{
	namespace
	{
		field_value_type& get_field_data(field_type& field, field_size_type row,
				field_size_type column)
		{
			return field[row * FIELD_ROWS + column];
		}
	}

	void print_field(field_type& field)
	{
		for (bombs::field_size_type i = 0;
			 i < field.size(); ++i)
		{
			if (i > 0 && (i % FIELD_COLS) == 0)
				std::cout << std::endl;
			if (field[i] == FieldDataType::Nothing)
				std::cout << "n ";
			else if (field[i] == FieldDataType::Explosion)
				std::cout << __ANSI_EXPLOSION_COLOR__ "e " __ANSI_RESET_COLOR__;
			else if (field[i] == FieldDataType::Bomb)
				std::cout << __ANSI_RED_COLOR__ "b " __ANSI_RESET_COLOR__;
			else if (field[i] == 1)
				std::cout << __ANSI_CYAN_COLOR__ "1 " __ANSI_RESET_COLOR__;
			else if (field[i] == 2)
				std::cout << __ANSI_CYAN_COLOR__ "2 " __ANSI_RESET_COLOR__;
			else if (field[i] == 3)
				std::cout << __ANSI_BLUE_COLOR__ "3 " __ANSI_RESET_COLOR__;
			else if (field[i] == 4)
				std::cout << __ANSI_BLUE_COLOR__ "4 " __ANSI_RESET_COLOR__;
		}
		std::cout << std::endl;
	}

	void fill_with_random_bombs(field_type& field, unsigned int bombs)
	{
		static std::random_device random_device {};
		static std::default_random_engine engine(random_device());
		std::uniform_int_distribution<field_value_type>
				field_position_dist(0, FIELD_COLS);

		for (field_size_type i = 0; bombs > 0; ++i)
		{
			if (i == field.size() - 1)
			{
				i = 0;
			}

			switch (field[i])
			{
				case FieldDataType::Bomb:
					break;
				case FieldDataType::Nothing:
					if (field_position_dist(engine) == 0)
					{
						field[i] = FieldDataType::Bomb;
						--bombs;
					}
					break;
				default:
					throw invalid_field_data(i / FIELD_ROWS, i % FIELD_COLS,
							field[i]);
			}
		}
	}

	void
	explode_bomb(field_type& field, field_size_type row, field_size_type column)
	{
		get_field_data(field, row, column) = FieldDataType::Explosion;

		if (row > 0 && get_field_data(field, row - 1, column)
				!= FieldDataType::Explosion)
		{
			get_field_data(field, row - 1, column) = FieldDataType::Explosion;
		}
		if (row < (FIELD_ROWS - 1) && get_field_data(field, row + 1, column)
				!= FieldDataType::Explosion)
		{
			get_field_data(field, row + 1, column) = FieldDataType::Explosion;
		}
		if (column > 0 && get_field_data(field, row, column - 1)
				!= FieldDataType::Explosion)
		{
			get_field_data(field, row, column - 1) = FieldDataType::Explosion;
		}
		if (column < (FIELD_COLS - 1) && get_field_data(field, row, column + 1)
				!= FieldDataType::Explosion)
		{
			get_field_data(field, row, column + 1) = FieldDataType::Explosion;
		}
	}

	void explode_all_bombs(field_type& field)
	{
		for (size_t i = 0; i < field.size(); ++i)
		{
			switch (field[i])
			{
				case FieldDataType::Bomb:
					explode_bomb(field, i / FIELD_ROWS, i % FIELD_COLS);
					break;
				case FieldDataType::Nothing:
				case FieldDataType::Explosion:
					break;
				default:
					throw invalid_field_data(i / FIELD_ROWS, i % FIELD_COLS,
							field[i]);
			}
		}
	}

	void fill_empty_space(field_type& field)
	{
		for (field_size_type col = 0, empty = 0; col < FIELD_COLS; ++col)
		{
			for (field_size_type row = 0; row < FIELD_ROWS; ++row)
			{
				if (get_field_data(field, row, col) == FieldDataType::Nothing)
				{ ++empty; }
				get_field_data(field, row, col) = FieldDataType::Explosion;
			}

			field_size_type to_fill_with_nums = FIELD_ROWS - empty;
			for (field_size_type row = FIELD_ROWS - 1; empty > 0;
				 --row, --empty)
			{
				get_field_data(field, row, col) = FieldDataType::Nothing;
			}

			for (field_size_type row = 0; row < to_fill_with_nums; ++row)
			{
				if (col > 0 && get_field_data(field, row, col - 1)
						>= FieldDataType::Explosion
						&& get_field_data(field, row, col - 1)
								< FieldDataType::Nothing)
				{
					++get_field_data(field, row, col - 1);
					++get_field_data(field, row, col);
				}
				if (row < (FIELD_ROWS - 1)
						&& get_field_data(field, row + 1, col)
								>= FieldDataType::Explosion
						&& get_field_data(field, row + 1, col)
								< FieldDataType::Nothing)
				{
					++get_field_data(field, row + 1, col);
					++get_field_data(field, row, col);
				}
			}
		}
	}

	void calculate(field_type& field, unsigned int bombs)
	{
		if (field.size() != FIELD_SIZE)
		{ throw invalid_field_size(field.size()); }

		fill_with_random_bombs(field, bombs);
#ifdef DEBUG
		std::cout << "Before explosion:" << std::endl;
		bombs::print_field(field);
		std::cout << std::endl;
#endif
		explode_all_bombs(field);
#ifdef DEBUG
		std::cout << "After explosion:" << std::endl;
		bombs::print_field(field);
		std::cout << std::endl;
#endif
		fill_empty_space(field);
	}
}