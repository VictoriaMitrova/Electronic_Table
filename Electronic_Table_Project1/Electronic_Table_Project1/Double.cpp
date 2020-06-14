#include "Double.h"

//		-1-
// Идеята е, тъй като при промяна на стойността на клетката работя с тип double, 
// а понякога реалното число е от тип int (12.0)
//		-2-
// Затова разделям целочислената част, която вадя от дробното число, за да разбера
// дали то реално е дробно (както 12.0 всъщност е int)

Double::Double(double newValue, int newValueSize) {
	this->setValue(newValue);
	int par1 = this->value;
	if ((double)(this->value - par1) == 0)
		this->setValueSize(newValueSize - 1);
	else
		this->setValueSize(newValueSize);
}

double Double::getValue()const {
	return this->value;
}

int Double::getValueSize()const {
	return this->valueSize;
}

void Double::setValue(double newValue) {
	this->value = newValue;
}

void Double::setCell(double& result) {
	result = this->value;
}

void Double::setValueSize(int newValueSize) {
	this->valueSize = newValueSize;
}

void Double::print() {
	cout << this->value << " | ";
}

int Double::size() {
	return this->valueSize;
}

void Double::writeValue(ostream& writeInFile) {
	writeInFile << this->value << ", ";
}