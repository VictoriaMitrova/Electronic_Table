#pragma once
#ifndef INTEGER_H
#define INTEGER_H

#include "TableValue.h"

using namespace std;

class Integer : public TableValue {
public:
	Integer(int value, int valueSize);
	
	int getValue()const;
	void setValue(int);

	void print() override;
	void setCell(double&) override;

	int size() override;

	void writeValue(ostream&) override;

protected:
	int value;
	int valueSize;

};

#endif 

