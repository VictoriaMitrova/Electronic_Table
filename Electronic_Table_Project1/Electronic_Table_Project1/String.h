#pragma once
#ifndef STRING_H
#define STRING_H
#include "TableValue.h"

class String : public TableValue{
public:
	String(string);

	string getString()const;
	void setString(string);

	void print() override;
	void setCell(double&) override;

	int size() override;

	void writeValue(ostream&) override;

private:
	string value;
};

#endif 
