#include "ScalarConverter.hpp"

void ScalarConverter::convert(std::string literal) {
	init();
	determineType(literal);
    printConversions();
}

void ScalarConverter::printConversions() {
	for (int i = 0; i < NUMBER_OF_TYPES; i++) {
		if (type == types[i]) {
			(conversionPrinters[i])();
			return ;
		}
	}
	std::cout << "Undefined Type" << std::endl;
}

void ScalarConverter::init() {
	types[0] = "char";
	types[1] = "int";
	types[2] = "float";
	types[3] = "double";
	typeDeterminants[0] = &isChar;
	typeDeterminants[1] = &isInt;
	typeDeterminants[2] = &isFloat;
	typeDeterminants[3] = &isDouble;
	conversionPrinters[0] = &printConversionFromChar;
	conversionPrinters[1] = &printConversionFromInt;
	conversionPrinters[2] = &printConversionFromFloat;
	conversionPrinters[3] = &printConversionFromDouble;
}

void ScalarConverter::determineType(std::string literal) {
	for (int i = 0; i < NUMBER_OF_TYPES; i++) {
		if ((*typeDeterminants[i])(literal)) {
			type = types[i];
			return ;
		}
	}
	type = "undefined";
}

bool ScalarConverter::isChar(std::string literal) {
    if (literal.length() != 1 || std::isprint(literal[0])) {
        return false;
    }

    return true;
}

bool ScalarConverter::isInt(std::string literal) {
	int length = literal.length();

	if (!std::isdigit(literal[0]) && literal[0] != '+' && literal[0] != '-') {
		return false;
	}

	for (int i = 0; i < length; i++) {
		if (!std::isdigit(literal[i])) {
			return false;
		}
	}

	long temp = std::strtol(literal.c_str(), NULL, 10);
	if (temp > INT_MAX || temp < INT_MIN) {
		return false;
	}

	return true;
}

bool ScalarConverter::isFloat(std::string literal) {
	int length = literal.length();
	int pointCount = 0;

	if (literal == "-inff" || literal == "+inff" || literal == "nanf") {
		return true;
	}

	if (!std::isdigit(literal[0]) && literal[0] != '+' && literal[0] != '-') {
		return false;
	}

	for (int i = 1; i < length - 1; i++) {
		if (literal[i] == '.') {
			pointCount++;
		}
		if (!std::isdigit(literal[i]) && pointCount != 1) {
			return false;
		}
	}

	if (literal[length - 1] != 'f') {
		return false;
	}

	float temp = std::strtof(literal.c_str(), NULL);
	if (!std::isfinite(temp)) {
		return false;
	}

	return true;
}

bool ScalarConverter::isDouble(std::string literal) {
	int length = literal.length();
	int pointCount = 0;

	if (literal == "-inf" || literal == "+inf" || literal == "nan") {
		return true;
	}

	if (!std::isdigit(literal[0]) && literal[0] != '+' && literal[0] != '-') {
		return false;
	}

	for (int i = 1; i < length; i++) {
		if (literal[i] == '.') {
			pointCount++;
		}
		if (!std::isdigit(literal[i]) && pointCount != 1) {
			return false;
		}
	}

	double temp = std::strtod(literal.c_str(), NULL);
	if (!std::isfinite(temp)) {
		return false;
	}

	return true;
}

void ScalarConverter::printConversionFromChar() {
	char value = literal[0];

	std::cout << "char: ";
	if (!std::isprint(value)) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << value << std::endl;
	}
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::printConversionFromInt() {
	int value = std::strtol(literal.c_str(), NULL, 10);

	std::cout << "char: ";
	if (value > CHAR_MAX || value < CHAR_MIN) {
		std::cout << "impossible" << std::endl;
	} else if (!std::isprint(value)) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << static_cast<char>(value) << std::endl;
	}
	std::cout << "int: " << value << std::endl;
	std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::printConversionFromFloat() {
	float value = std::strtof(literal.c_str(), NULL);
	int intValue = static_cast<int>(value);

	std::cout << "char: ";
	if (intValue > CHAR_MAX || intValue < CHAR_MIN) {
		std::cout << "impossible" << std::endl;
	} else if (!std::isprint(intValue)) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << static_cast<char>(value) << std::endl;
	}
	std::cout << "int: ";
	if (!std::isfinite(value) || value > INT_MAX || value < INT_MIN) {
		std::cout << "impossible" << std::endl;
	} else {
		std::cout << intValue << std::endl;
	}
	if (value - static_cast<int>(value) == 0.0f) {
		std::cout << std::fixed << std::setprecision(1);
	}
	std::cout << "float: " << value << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << std::endl;
}

void ScalarConverter::printConversionFromDouble() {
	double value = std::strtod(literal.c_str(), NULL);
	int intValue = static_cast<int>(value);

	std::cout << "char: ";
	if (intValue > CHAR_MAX || intValue < CHAR_MIN) {
		std::cout << "impossible" << std::endl;
	} else if (!std::isprint(intValue)) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << static_cast<char>(value) << std::endl;
	}
	std::cout << "int: ";
	if (!std::isfinite(value) || value > INT_MAX || value < INT_MIN) {
		std::cout << "impossible" << std::endl;
	} else {
		std::cout << intValue << std::endl;
	}
	if (static_cast<float>(value) - static_cast<int>(value) == 0.0f) {
		std::cout << std::fixed << std::setprecision(1);
	}
	std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << value << std::endl;
}