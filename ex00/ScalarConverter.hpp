#ifndef GENERIC_H
#define GENERIC_H

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

#define NUMBER_OF_TYPES 4

class ScalarConverter {
public:
    static void convert(std::string literal);
private:
	static std::string types[NUMBER_OF_TYPES];
	static std::string literal;
	static std::string type;
	static void init();
	static bool (*typeDeterminants[NUMBER_OF_TYPES])(std::string literal);
	static void (*conversionPrinters[NUMBER_OF_TYPES])();
	static void determineType(std::string literal);
    static void printConversions();

    // determiners
	static bool isFloat(std::string literal);
	static bool isInt(std::string literal);
	static bool isChar(std::string literal);
	static bool isDouble(std::string literal);

    // printers
	static void printConversionFromChar();
	static void printConversionFromInt();
	static void printConversionFromFloat();
	static void printConversionFromDouble();
};

#endif