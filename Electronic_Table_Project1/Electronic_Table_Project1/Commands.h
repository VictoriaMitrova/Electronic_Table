#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H
#include "Table.h"

class Commands{

public:

	static void Open(fstream&, string);
	static void Close(fstream&, string);
	static void Help();
	static void Exit();

	static void searchCommand(string);

	static string currentFile;

};

#endif 