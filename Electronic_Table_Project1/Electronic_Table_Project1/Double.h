#pragma once
#ifndef DOUBLE_H
#define DOUBLE_H
#include <iostream>
#include <iomanip>
#include "TableValue.h"
class Double : public TableValue{
public:
	Double(double, int);

	double getValue()const;
	int getValueSize()const;


	void setValue(double);
	void setValueSize(int);

	void print() override;
	void setCell(double&) override;

	int size() override;

	void writeValue(ostream&) override;

protected:
	double value;
	int valueSize;

};

#endif 
