#include "Table.h"

Table::Table() {
	this->rows = 0;
	this->columbs = 0;
	this->fileName = "TestingTable.txt";

	fstream inFile;

	inFile.open(this->fileName);
	
	if (this->isFileEmpty() == true)
		return;

	while (!inFile.eof()) {
		string buffer;
		getline(inFile, buffer);
		string result[100];
		int resultIndex = 0;

		if (inFile.eof() && buffer.size() == 0)
			break;
		
		if (this->isRowEmpty(buffer) == false) {
			for (int i = 0; i < buffer.length(); ++i) {
				if (buffer[i] == '\"') {
					string element;
					element.push_back(buffer[i]);
					++i;
					for (int j = 0; (buffer[i] != '\"' && buffer[i] != ',') && buffer[i] != '\0'; ++j, ++i)
						if (buffer[i] != '\\')
							element.push_back(buffer[i]);

					if (buffer[i] == '\"')
						element.push_back(buffer[i]);
					result[resultIndex] = element;
					++resultIndex;

				}
				else if (buffer[i] != ' ' && buffer[i] != ',') {
					string element;
					for (int j = 0; buffer[i] != ' ' && buffer[i] != ',' && buffer[i] != '\0'; ++j, ++i)
						element.push_back(buffer[i]);
					result[resultIndex] = element;
					++resultIndex;
				}
			}
		}
		
		if (resultIndex > this->columbs)
			this->setColumbs(resultIndex);

		vector<TableValue*> row;
		for (int i = 0; i < resultIndex; ++i) {
			row.push_back(TableValue::createValue(result[i], this->rows, i));
		}
		table.push_back(row);
		++this->rows;
	}
	
	this->fillEmpty();

	Commands::Close(inFile, "TestingTable.txt");
}

Table::Table(string fileName) {
	this->rows = 0;
	this->columbs = 0;
	this->fileName = fileName;
	
	fstream myFile;

	myFile.open(fileName);

	if (this->isFileEmpty() == true)
		return;

	while (!myFile.eof()) {
		string buffer;
		getline(myFile, buffer);
		string result[100];
		int resultIndex = 0;

		if (this->isRowEmpty(buffer) == false) {
			for (int i = 0; i < buffer.length(); ++i) {
				if (buffer[i] == '\"') {
					string element;
					element.push_back(buffer[i]);
					++i;
					for (int j = 0; (buffer[i] != '\"' && buffer[i] != ',') && buffer[i] != '\0'; ++j, ++i)
						if (buffer[i] != '\\')
							element.push_back(buffer[i]);

					if (buffer[i] == '\"')
						element.push_back(buffer[i]);
					result[resultIndex] = element;
					++resultIndex;

				}
				else if (buffer[i] != ' ' && buffer[i] != ',') {
					string element;
					for (int j = 0; buffer[i] != ' ' && buffer[i] != ',' && buffer[i] != '\0'; ++j, ++i)
						element.push_back(buffer[i]);
					result[resultIndex] = element;
					++resultIndex;
				}
			}
		}

		if (resultIndex > this->columbs)
			this->setColumbs(resultIndex);

		vector<TableValue*> row;
		for (int i = 0; i < resultIndex; ++i) {
			row.push_back(TableValue::createValue(result[i], this->rows, i));
		}
		table.push_back(row);
		++this->rows;
	}

	this->fillEmpty();

	Commands::Close(myFile, fileName);
}

int Table::getRows()const {
	return this->rows;
}

int Table::getColumbs()const {
	return this->columbs;
}

TableValue* Table::getCell(int row, int columb) {
	return this->table.at(row).at(columb);
}

string Table::getFileName() {
	return this->fileName;
}

vector<vector<TableValue*>> Table::getTable() {
	return this->table;
}

void Table::setRows(int newRows) {
	this->rows = newRows;
}

void Table::setColumbs(int newColumbs) {
	this->columbs = newColumbs;
}

void Table::setFileName(string newFileName) {
	this->fileName = newFileName;
}

void Table::fillEmpty() {
	for (int i = 0; i < this->rows; ++i)
		for (int j = table[i].size(); j < this->columbs; ++j)
			table.at(i).push_back(TableValue::createValue("\" \"", i, j));

}

//		-1-
// Проверявам дали текущият обхождан ред във файла е празен
bool Table::isRowEmpty(string buffer) {
	if (buffer.size() == 0)
		return true;
	for (int i = 0; i < buffer.size(); ++i) 
		if (buffer.at(i) != ',' || buffer.at(i) != ' ')
			return false;
	return true;
}

bool Table::isFileEmpty() {
	if (this->fileName.empty() == true)
		return true;
	return false;
}

void Table::findDistance() {
	//		-1-
	// При извикване на този метод е възможно да е имало промени по първоначалната таблица
	// за това всеки път се намират отново max size от char/s/ на дадена колона
	this->distance.clear();
	
	for (int i = 0; i < this->columbs; ++i) {
		int maxDistance = 0;
		for (int j = 0; j < this->rows; ++j) {
			if (maxDistance < this->table.at(j).at(i)->size())
				maxDistance = this->table.at(j).at(i)->size();
		}
		this->distance.push_back(maxDistance);
	}
}

void Table::printSpaces(int spaces) {
	for (int i = 0; i < spaces; ++i) 
		cout << " ";
}

void Table::Print() {

//		-1-
// Намиране спрямо всяка колона, елемента с max дължина и вмъкване на всеки
// от резултатите във вектор, като всеки индекс на вектора отговаря на индекса на колоната 
//		-2-
// Преди да се print-не всеки елемент да намира неговата дължина
// и да добавя char = ' ' толкова пъти, колкото е разликата 
//между max за тази колона и конкретният елемент 

	this->findDistance();

	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->columbs; ++j) {
			this->printSpaces(this->distance.at(j) - this->table.at(i).at(j)->size());
			table[i][j]->print();
		}
		std::cout << endl;
	}
}

bool Table::isFormula(string formula) {
	if (formula.at(0) != '=' )
		return false;

	for (int i = 1; i < formula.size(); ++i) {
		if (formula.at(i) != '=' && formula.at(i) != ' ' && formula.at(i) != '+' &&
			formula.at(i) != '-' && formula.at(i) != '*' && formula.at(i) != '/' &&
			formula.at(i) != '^' && formula.at(i) != 'R' && formula.at(i) != 'C' &&
			 formula.at(i) < '.' && (formula.at(i) < '0' || formula.at(i) > '9'))
			return false;
	}
	return true;
}

bool Table::isCell(string cell) {
	if (cell.at(0) != 'R')
		return false;
	for (int i = 1; i < cell.size(); ++i) {
		if (cell.at(i) != 'C' && (cell.at(i) < '0' || cell.at(i) > '9'))
			return false;
	}
	return true;
}

bool Table::isOnlyNumber(string cell) {
	int dots = 0;
	TableValue::isNumber(cell, dots);

	if (TableValue::isInteger(cell, dots) == true || TableValue::isDouble(cell, dots) == true)
		return true;
	return false;
}

bool Table::isCellValid(string cell) {
	if (isCell(cell) == true || isOnlyNumber(cell) == true)
		return true;
	return false;
}

bool Table::isValidCell(int row, int columb) {
	if (row >= this->rows || columb >= this->columbs)
		return false;
	return true;
}

bool Table::isOperator(char operato) {
	if (operato == '-' || operato == '+' || operato == '*'
		|| operato == '/' || operato == '^')
		return true;
	return false;
}

bool Table::devidedByZero(double value2, char operato) {
	if (value2 == 0 && operato == '/')
		return true;
	return false;
}

bool Table::isDevidedByZero(vector<double> values, vector<char> operators) {
	for (int i = 0; i < operators.size(); ++i)
		if (this->devidedByZero(values.at(i + 1), operators.at(i)) == true)
			return true;

	return false;
}

//		-1-
// Проверявам дали подаденият <string> е формула ---> if(true) continue;
//		-2-
// Разделям всяка клетка във един вектор от <string>, както и аритметичните знаци
// във вектор от <char> 
//		-3-
// Преобразувам клетките до техните стойности във вектор от <double> 
//		-4-
// Прехвърлям ги във вектор от <double> стойности
//		-5-
// Извършвам аритметичните операции между тях, без да гледам тяхният преоритет

void Table::findAllCells(string formula, vector<string>& cells, vector<char>& operators) {
	
	for (int i = 0; i < formula.size(); ++i) {
		if (formula.at(i) == 'R' || (formula.at(i) >= '0' && formula.at(i) <= '9')) {
			string temp;
			while (formula.at(i) != ' ') {
				temp.push_back(formula.at(i));
				if (i + 1 < formula.size())
					++i;
				else
					break;
			}
			cells.push_back(temp);
			if (formula.at(i) == ' ' && (i + 1) < formula.size()) {
				++i;
				operators.push_back(formula.at(i));
			}
		}
	}

}

double Table::toNumbers(string cell) {
	if (isCellValid(cell) == false)
		return 0.0;

	int row = 0;
	int columb = 0;
	double result = 0;

	if (isCell(cell) == true) {
		for (int i = 1; i < cell.size(); ++i) {
			if (cell.at(i) >= '0' && cell.at(i) <= '9') {
				while (cell.at(i) != 'C') {
					row = row * 10 + TableValue::fromCharToNumber(cell.at(i));
					++i;
				}
				++i;
				while (i < cell.size()) {
					columb = columb * 10 + TableValue::fromCharToNumber(cell.at(i));
					++i;
				}

			}
		}
		if (row-1 < this->getRows() && columb-1 < this->getColumbs() && row-1 >= 0 && columb - 1 >= 0) {
			this->getCell(row-1, columb-1)->setCell(result);
			return result;
		}
		else
			return 0;
	}
	else {
		result = (TableValue::toNumber(cell));
		return result;
	}
}

void Table::findAllNumbers(vector<double>& findedNumbers, vector<string>& cells) {
	for (int i = 0; i < cells.size(); ++i) {
		findedNumbers.push_back(toNumbers(cells.at(i)));
	}
}

double Table::arithmeticOperation(double value, double value2, char operators) {
	switch (operators)
	{
	case '+': return value + value2;
	case '-':return value - value2;
	case '*':return value * value2;
	case '/': return value / value2;
	case '^': return pow(value, value2);
	default:
		return 0;
	}
}

double Table::readyOperations(vector<double> allValues, vector<char> allOperators) {

	if (allOperators.size() == 1) {
		return arithmeticOperation(allValues.at(0), allValues.at(1), allOperators.at(0));
	}

	double result = allValues.at(allValues.size() - 1);
	
	for (int i = 0; i < allValues.size() - 1; ++i) {
		result = arithmeticOperation(result, allValues.at(i), allOperators.at(i));
	}
	return result;
}

ostream& operator<<(ostream& writeInFile, Table& table) {
	for (int i = 0; i < table.rows; ++i) {
		for (int j = 0; j < table.columbs; ++j)
			table.table.at(i).at(j)->writeValue(writeInFile);
		if (i < table.rows - 1)
			writeInFile << "\n";
	}
	return writeInFile;
}

void Table::Save() {
	ofstream myFile;
	myFile.open(this->fileName);
	myFile << *this;
	cout << endl << "Successfully saved " << this->fileName << endl;
	myFile.close();
}

void Table::SaveAs(string fileName) {
	ofstream myFile;
	myFile.open(fileName);
	myFile << *this;
	cout << endl << "Successfully saved another " << fileName << endl;
	myFile.close();
}

void Table::Edit(int row, int columb, string formula) {

	vector<string> cells;
	vector<char> operators;
	vector<double> findedNumbers;
	double result = 0;

	this->findAllCells(formula, cells, operators);
	this->findAllNumbers(findedNumbers, cells);

	if (this->isValidCell(row - 1, columb - 1) == false) {
		cout << "Not valid cell" << endl;
			return;
	}

	if (this->isDevidedByZero(findedNumbers, operators) || this->isFormula(formula) == false ) {
		string text = "\"ERROR\"";
		this->table.at(row - 1).at(columb - 1) = TableValue::createValue(text, row - 1, columb - 1);
		return;
	}

	result = this->readyOperations(findedNumbers, operators);

	string plainText = to_string(result);

	this->table.at(row - 1).at(columb - 1) = TableValue::createValue(plainText, row - 1, columb - 1);
	cout << endl << "Corrections made in R" << row << "C" << columb << endl;
}

void Table::findCommand(string command) {
	string file;
	fstream myFile;
	cin.ignore();
	if (command == "Save") {
		this->Save();
	}
	else if (command == "SaveAs") {
		cout << "Enter which file do you want to use: ";
		cin >> file;
		this->SaveAs(file);
		file.clear();
	}
	else if (command == "Edit") {
		int row, columb;
		string formula;
		cout << "Enter which cell do you want to correct: " << endl;
		cout << "Enter row = ";
		cin >> row;
		cout << "Enter columb = ";
		cin >> columb;
		cout << "Enter new value / formula for the cell ";
		cin.ignore();
		getline(cin, formula);

		this->Edit(row, columb, formula);
	}
	else if (command == "Print") {
		this->Print();
	}
	else if (command == "Open") {
		cout << "Enter which file do you want to use: ";
		getline(cin, file);
		Commands::Open(myFile, file);
		if (file != this->fileName) {
			
			Table currentTable(file);
			this->rows = currentTable.getRows();
			this->columbs = currentTable.getColumbs();
			this->fileName = currentTable.getFileName();
			this->table = currentTable.getTable();
		}
		file.clear();
	}
	else if (command == "Close") {
		cout << "Enter which file do you want to use: ";
		getline(cin, file);
		Commands::Close(myFile, file);
		file.clear();
	}
	else if (command == "Help") {
		Commands::Help();
	}
	else if (command == "Exit") {
		Commands::Exit();
	}
	else {
		cout << "Not found command " << endl;
	}
}

