/**
 * @brief Bombs implementation details.
 */

#include "bombs.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

#define __ANSI_RESET_COLOR__ "\033[0m"

#define __ANSI_RED_COLOR__ "\033[31m"
#define __ANSI_EXPLOSION_COLOR__ "\033[30;7m"
#define __ANSI_BLUE_COLOR__ "\033[34m"
#define __ANSI_CYAN_COLOR__ "\033[36m"

namespace bombs {
	namespace {
		unsigned getNumberLength(FieldSizeType number) {
			unsigned length = 0;
			for (; number; number /= 10, ++length);

			return length;
		}

		FieldValueType& getFieldData(FieldType& field, FieldSizeType row,
									 FieldSizeType column) {
			return field[row * kFieldCols + column];
		}

		/**
		 * @brief Explodes single bomb in horizontal and vertical directions.
		 *
		 * @param field Field where the bomb is placed on
		 * @param row Bomb row
		 * @param column Bomb column
		 */
		void explodeBomb(FieldType& field, FieldSizeType row,
						 FieldSizeType column) {
			getFieldData(field, row, column) = FieldDataType::kExploded;

			if (row > 0 &&
				getFieldData(field, row - 1, column) == FieldDataType::kEmpty) {
				getFieldData(field, row - 1, column) = FieldDataType::kExploded;
			}
			if (row < (kFieldRow - 1) &&
				getFieldData(field, row + 1, column) == FieldDataType::kEmpty) {
				getFieldData(field, row + 1, column) = FieldDataType::kExploded;
			}
			if (column > 0 &&
				getFieldData(field, row, column - 1) == FieldDataType::kEmpty) {
				getFieldData(field, row, column - 1) = FieldDataType::kExploded;
			}
			if (column < (kFieldCols - 1) &&
				getFieldData(field, row, column + 1) == FieldDataType::kEmpty) {
				getFieldData(field, row, column + 1) = FieldDataType::kExploded;
			}
		}

		/**
		 * @brief Explodes all bombs.
		 *
		 * @param field Field where all the bombs explode
		 * @throws InvalidFieldData Field contains something other than
		 * Bomb, Empty space, Exploded space.
		 */
		void explodeAllBombs(FieldType& field) {
			for (size_t i = 0; i < field.size(); ++i) {
				switch (field[i]) {
					case FieldDataType::kBomb:
						explodeBomb(field, i / kFieldCols, i % kFieldCols);
						break;
					case FieldDataType::kEmpty:
					case FieldDataType::kExploded: break;
					default:
						throw InvalidFieldData(i / kFieldCols, i % kFieldCols,
											   field[i]);
				}
			}
		}
	}

	void printField(FieldType& field) {
		int print_width = getNumberLength(kFieldRow) + 1;

		for (bombs::FieldSizeType i = 0; i < field.size(); ++i) {
			if (i > 0 && (i % kFieldCols) == 0) {
				std::cout << std::endl;
			}

			if (field[i] == FieldDataType::kEmpty) {
				std::cout << std::left << std::setw(print_width) << "n";
			} else if (field[i] == FieldDataType::kExploded) {
				std::cout << __ANSI_EXPLOSION_COLOR__;
				std::cout << std::left << std::setw(print_width) << "e";
			} else if (field[i] == FieldDataType::kBomb) {
				std::cout << __ANSI_RED_COLOR__;
				std::cout << std::left << std::setw(print_width) << "b";
			}
#ifdef OTHER
				else {
				  if (field[i] == 1)
					std::cout << __ANSI_CYAN_COLOR__;
				  else if (field[i] == 2)
					std::cout << __ANSI_CYAN_COLOR__;
				  else if (field[i] == 3)
					std::cout << __ANSI_BLUE_COLOR__;
				  else if (field[i] == 4)
					std::cout << __ANSI_BLUE_COLOR__;
				  std::cout << std::left << std::setw(print_width) << field[i];
				}
#else
			else {
				std::cout << __ANSI_CYAN_COLOR__ << std::left
						  << std::setw(print_width) << field[i];
			}
#endif
			std::cout << __ANSI_RESET_COLOR__;
		}
		std::cout << std::endl;
	}

	void fillWithRandomBombs(FieldType& field, unsigned int bombs_left) {
		static std::random_device random_device{};
		static std::default_random_engine engine(random_device());
		std::uniform_int_distribution<FieldValueType> field_position_dist(0,
																		  kFieldCols);

		for (FieldSizeType i = 0, bombs_count = 0; bombs_left > 0; ++i) {
			if (i == field.size() - 1) {
				if (bombs_count == field.size() && bombs_left > 0) {
					throw NoSpaceForRandomBombs(bombs_left);
				}

				i = 0;
				bombs_count = 0;
			}

			switch (field[i]) {
				case FieldDataType::kBomb: ++bombs_count;
					break;
				case FieldDataType::kEmpty:
					if (field_position_dist(engine) == 0) {
						field[i] = FieldDataType::kBomb;
						++bombs_count;
						--bombs_left;
					}
					break;
				default: throw InvalidFieldData(i / kFieldCols, i % kFieldCols,
												field[i]);
			}
		}
	}

	void fillEmptySpace(FieldType& field) {
		for (FieldSizeType col = 0, empty = 0; col < kFieldCols; ++col) {
			for (FieldSizeType row = 0; row < kFieldRow; ++row) {
				if (getFieldData(field, row, col) == FieldDataType::kEmpty) {
					++empty;
				}
				getFieldData(field, row, col) = FieldDataType::kExploded;
			}

			FieldSizeType to_fill_with_nums = kFieldRow - empty;
			for (FieldSizeType row = kFieldRow - 1; empty > 0; --row, --empty) {
				getFieldData(field, row, col) = FieldDataType::kEmpty;
			}

			for (FieldSizeType row = 0; row < to_fill_with_nums; ++row) {
#ifdef OTHER
				if (col > 0 && getFieldData(field, row, col - 1)
				  != FieldDataType::kEmpty) {
				  ++getFieldData(field, row, col - 1);
				  ++getFieldData(field, row, col);
				}
				if (row < (kFieldRow - 1)
				  && getFieldData(field, row + 1, col)
					!= FieldDataType::kEmpty) {
				  ++getFieldData(field, row + 1, col);
				  ++getFieldData(field, row, col);
				}
#else
				getFieldData(field, row, col) = static_cast<FieldValueType>(
					to_fill_with_nums - row);
#endif
			}
		}
	}

	void calculate(FieldType& field, unsigned int bombs) {
		if (field.size() != kFieldSize) {
			throw InvalidFieldSize(field.size());
		}

		fillWithRandomBombs(field, bombs);
#ifdef DEBUG
		std::cout << "Before explosion:" << std::endl;
		bombs::printField(field);
		std::cout << std::endl;
#endif
		explodeAllBombs(field);
#ifdef DEBUG
		std::cout << "After explosion:" << std::endl;
		bombs::printField(field);
		std::cout << std::endl;
#endif
		fillEmptySpace(field);
	}
}