#include "TableValue.h"
#include "Integer.h"
#include "Double.h"
#include "String.h"

ostream& operator<<(ostream& write, vector<TableValue*> value) {
	for (int i = 0; i < value.size(); ++i) {
		value.at(i)->writeValue(write);
	}
	return write;
}

TableValue* TableValue::createValue(string buffer, int currentRow, int currentColumb) {
	int dots = 0;
	
	isNumber(buffer, dots);

	if (isInteger(buffer, dots) == true && isNumber(buffer, dots) == true) {
		buffer.erase(buffer.find_last_not_of('0') + 1, std::string::npos);
		return new Integer(toInteger(buffer, dots), buffer.size());
	}
	else if (isDouble(buffer, dots) == true) {
		// Премахва излишните нули, които to_string е прибавила
		buffer.erase(buffer.find_last_not_of('0') + 1, std::string::npos);
		return new Double(toDouble(buffer, dots), (buffer.at(0) == '+' ? buffer.size() - 1 : buffer.size()));
	}
	else if (isString(buffer) == true && isNumber(buffer, dots) == false)
		return new String(toString(buffer));
	else {
		cerr << "ERROR: row " << currentRow + 1 << ", columb " << currentColumb + 1 << " " <<
			buffer << " is unknown data type.";
		exit(1);
	}
}

int TableValue::toInteger(string str, int& dotsCounter) {

	int result = 0;
	if (isNumber(str, dotsCounter) && isInteger(str, dotsCounter)) {

		if (str[0] == '+' || str[0] == '-') {
			for (int index = 1; str[index] != '\0'; ++index)
				result = result * 10 + fromCharToNumber(str[index]);
			if (str[0] == '-')
				result = -result;
		}
		else {
			for (int index = 0; str[index] != '\0'; ++index)
				result = result * 10 + fromCharToNumber(str[index]);
		}
	}
	return result;
}

//		-1-
// Разделяме числото на целочистлена и дробна част
//		-2-
// Чрез натрупване образуваме двете части
//		-3-
// Накрая събираме двата ресултата и определяме знака на полученото число

double TableValue::toDouble(string str, int& dots) {
	int decimalPart = 0;
	double fractionalPart = 0.0;
	int counter = 1;
		if (str[0] == '+' || str[0] == '-') {
			for (int index = 1; str[index] != '.'; ++index) {
				decimalPart = decimalPart * 10 + fromCharToNumber(str[index]);
				if (str[index + 1] == '.')
					for (int j = index + 2; str[j] != '\0'; ++j, ++counter)
						fractionalPart += (double)((fromCharToNumber(str[j]) / pow(10, counter)));
			}
		}
		else {
			for (int index = 0; str[index] != '.'; ++index) {
				decimalPart = decimalPart * 10 + fromCharToNumber(str[index]);
				if (str[index + 1] == '.')
					for (int j = index + 2; str[j] != '\0'; ++j, ++counter)
						fractionalPart += (double)((fromCharToNumber(str[j]) / pow(10, counter)));
			}
		}
	double result = (decimalPart + fractionalPart);
	if (str[0] == '-') 
		result = -result;
	return result;
}

string TableValue::toString(string str) {
	string temp;
	if (isString(str) == true)
		for (int i = 1; i < str.length() - 1; ++i)
			temp.push_back(str[i]);
	if (temp[0] == '\0')
		temp = "Unknown data type!";
	return temp;
}

int TableValue::fromCharToNumber(char element) {
	switch (element)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return -1;
	}
}

char TableValue::fromNumberToChar(int number) {
	switch (number)
	{
	case 0:return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default:
		return 'a';
	}
}

bool TableValue::isNumber(string str, int& dotsCounter) {

	for (int index = 0; str[index] != '\0'; ++index) {
		if (str[index] == '.')
			++dotsCounter;
		if ((str[index] == '+' || str[index] == '-') && index != 0)
			return false;
		else if (((str[index]) < '0' || (str[index]) > '9') && str[index] != '.' && str[index] != '-' && str[index] != '+')
			return false;
	}
	return (dotsCounter > 1 ? false : true);
}

double TableValue::toNumber(string str) {
	int dotsCounter = 0;
	if (isNumber(str, dotsCounter) == false)
		return 0;
	else if (isInteger(str, dotsCounter) == true)
		return (toInteger(str, dotsCounter));
	else if (isDouble(str, dotsCounter) == true)
		return (toDouble(str, dotsCounter));
	else
		return 0;
}

bool TableValue::isDouble(string str, int& dotsCounter) {
	return dotsCounter != 1 ? false : true;
}

bool TableValue::isInteger(string str, int& dotsCounter) {
	return dotsCounter == 0 ? true : false;
}

bool TableValue::isString(string str) {
	if(str[0] == '\"' && str[str.length() - 1] == '\"')
		return true;
	return false;
}
