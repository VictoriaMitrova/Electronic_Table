#pragma once
#ifndef TABLEVALUE_H
#define TABLEVALUE_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>


using namespace std;

class TableValue {
public:
	static TableValue* createValue(string, int, int);

	virtual void print() = 0;
	virtual void writeValue(ostream&) = 0;
	virtual int size() = 0;
	virtual void setCell(double&) = 0;

	static int toInteger(string, int&);
	static double toDouble(string, int&);
	static string toString(string);
	
	static int fromCharToNumber(char);
	static char fromNumberToChar(int);
	
	static bool isNumber(string, int&);
	static double toNumber(string);

	static bool isInteger(string, int&);
	static bool isDouble(string, int&);
	static bool isString(string);

	//		-1-
	// По идея от кодът, писан по време на лекции
	friend ostream& operator<<(ostream&, vector<TableValue*>);

};

#endif