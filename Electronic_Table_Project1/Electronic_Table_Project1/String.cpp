#include "String.h"

String::String(string newValue) {
	if (newValue[0] != '\0')
		this->setString(newValue);
}

string String::getString()const {
	return this->value;
}

void String::setString(string newValue) {
	this->value = newValue;
}

void String::setCell(double& result) {
	result = (TableValue::toNumber(this->value));
}

void String::print() {
	cout << this->value << " | ";
}

int String::size() {
	return this->value.size();
}

void String::writeValue(ostream& writeInFile) {
	if (this->value == " ")
		writeInFile << " , ";
	else
		writeInFile << "\"" << this->value << "\", ";
}
