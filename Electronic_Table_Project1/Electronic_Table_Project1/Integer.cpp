#include "Integer.h"
#include <iostream>


Integer::Integer(int value, int valueSize) {
	setValue(value);
	this->valueSize = valueSize;
}

int Integer::getValue()const {
	return this->value;
}

void Integer::setValue(int newValue) {
	this->value = newValue;
}

void Integer::setCell(double& result) {
	result = this->value;
}

void Integer::print() {
		cout << this->value << " | ";
}

int Integer::size() {
	string inInteger = to_string(this->value);
	
	return inInteger.size();
}

void Integer::writeValue(ostream& writeInFile) {
	writeInFile << this->value << ", ";
}
