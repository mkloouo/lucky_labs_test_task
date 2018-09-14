/**
 * @brief Explosions and fields.
 *
 * @date 09/13/2018
 * @author Mykola Odnosumov
 */

#ifndef LUCKY_LABS_TEST_TASK_BOMBS_H
#define LUCKY_LABS_TEST_TASK_BOMBS_H

#include <stdexcept>
#include <vector>

namespace bombs {
	using FieldType = std::vector<int>;
	using FieldValueType = FieldType::value_type;
	using FieldSizeType = FieldType::size_type;

	constexpr FieldSizeType kDefaultInitialBombs = 10;
	constexpr FieldSizeType kFieldRow = 13;
	constexpr FieldSizeType kFieldCols = 10;
	constexpr FieldSizeType kFieldSize = kFieldRow * kFieldCols;

	/**
	 * @brief Defines set of possible values of field data.
	 */
	enum FieldDataType : FieldValueType {
		kBomb = -2, kEmpty = -1, kExploded = 0
	};

	struct InvalidFieldSize : std::runtime_error {
		explicit InvalidFieldSize(FieldSizeType size)
			:runtime_error("invalid field size"),
			 size(size) {}

		FieldSizeType size;
	};

	struct InvalidFieldData : std::runtime_error {
		InvalidFieldData(FieldSizeType column, FieldSizeType row,
						 FieldValueType value)
			:runtime_error("invalid field data"),
			 column(column),
			 row(row),
			 value(value) {}

		FieldSizeType column;
		FieldSizeType row;
		FieldValueType value;
	};

	struct NoSpaceForRandomBombs : std::runtime_error {
		explicit NoSpaceForRandomBombs(FieldSizeType left)
			:runtime_error("no space left to place random bombs"),
			 left(left) {}

		FieldSizeType left;
	};

	/**
	 * @brief Prints out field to std::cout.
	 *
	 * @param field Field of bombs, empty places, exploded places and numbers.
	 */
	void printField(FieldType& field);

	/**
	 * @brief Fills field randomly placing bombs_left number of bombs.
	 *
	 * @param field Field to fill with bombs
	 * @param bombs_left Number of bombs to randomly place on the field
	 * @throws InvalidFieldData When field cell contains something other than
	 * predefined in FieldDataType
	 * @throws NoSpaceForRandomBombs When there's no more space to
	 * place a random bomb
	 */
	void fillWithRandomBombs(FieldType& field, unsigned int bombs_left);

	/**
	 * @brief Calculates numbering on the map, after placing random
	 * number of bombs and exploding them.
	 *
	 * @param field Field, possibly filled with bombs
	 * @param bombs Number of bombs to be randomly placed
	 * @throws InvalidFieldSize When field size does not match predefined one.
	 * @throws InvalidFieldData When field cell contains something other than
	 * predefined in FieldDataType or a number
	 * @throws NoSpaceForRandomBombs When there's no more space to
	 * place a random bomb
	 */
	void calculate(FieldType& field, unsigned int bombs);
}

#endif //LUCKY_LABS_TEST_TASK_BOMBS_H
