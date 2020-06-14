#pragma once
#ifndef TABLE_H
#define TABLE_H
#include "TableValue.h"
#include "Commands.h"

class Table {
public:
	Table();
	Table(string);
	
	int getRows()const;
	int getColumbs()const;
	TableValue* getCell(int, int);
	string getFileName();
	vector<vector<TableValue*>> getTable();

	void setRows(int);
	void setColumbs(int);
	void setFileName(string);

	void fillEmpty();
	void findDistance();
	void printSpaces(int);
	
	bool isRowEmpty(string);
	bool isFileEmpty();
	bool isFormula(string);
	bool isValidCell(int, int);
	bool isCell(string);
	bool isOnlyNumber(string);
	bool isCellValid(string);
	bool isOperator(char);
	bool devidedByZero(double, char);
	bool isDevidedByZero(vector<double>, vector<char>);

	void findAllCells(string, vector<string>&, vector<char>&);
	double toNumbers(string);
	void findAllNumbers(vector<double>&, vector<string>&);
	double arithmeticOperation(double, double, char);
	double readyOperations(vector<double>, vector<char>);
	
	void Print();
	void Edit(int, int, string);
	void Save();
	void SaveAs(string);
	void findCommand(string);

	friend ostream& operator<<(ostream&, Table& table);

private:
	vector<vector<TableValue*>> table;
	int rows;
	int columbs;
	vector<int> distance;
	string fileName;

};
#endif 
