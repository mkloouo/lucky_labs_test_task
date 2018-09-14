/**
 * Execution start point.
 *
 * @date 09/13/2018
 * @author Mykola Odnosumov
 */

#include <iostream>

#include "bombs.h"

int main() {
	bombs::FieldType test_field(bombs::kFieldSize,
								bombs::FieldDataType::kEmpty);
	bombs::fillWithRandomBombs(test_field, bombs::kDefaultInitialBombs);

	try {
		bombs::calculate(test_field, 11);

		std::cout << "After calculation:" << std::endl;
		bombs::printField(test_field);
		std::cout << std::endl;
	} catch (bombs::InvalidFieldSize& ex) {
		std::cout << ex.what() << " given size:" << ex.size << std::endl;
	} catch (bombs::InvalidFieldData& ex) {
		std::cout << ex.what() << ": " << ex.value << " at (" << ex.column
				  << ", " << ex.row << ")" << std::endl;
	} catch (bombs::NoSpaceForRandomBombs& ex) {
		std::cout << ex.what() << " bombs left: " << ex.left << std::endl;
	}
	return 0;
}
