#include "Commands.h"

string Commands::currentFile = "";

void Commands::Open(fstream& myFile, string fileName) {
	
	myFile.open(fileName);
	if (myFile.is_open()) {
		cout << endl << "Successfully opened " << fileName << endl;
	}
	else if(myFile.good() == false) {
		myFile.open(fileName, ios::out);
		cout << endl << "Successfully created and opened " << fileName << endl;
	}
	currentFile = fileName;
}

void Commands::Close(fstream& myFile, string fileName) {
	myFile.close();
	if (!myFile.is_open()) {
		cout << endl << "Successfully closed " << fileName << endl;
	}
}

void Commands::Help() {
	cout << "The following commands are supported :\n" <<
			"open <file> opens <file>\n" <<
			"close			closes currently opened file\n" <<
			"save			saves the currently open file\n" <<
			"saveas <file>	saves the currently open file in <file>\n" <<
			"help			prints this information\n" <<
			"exit			exists the program\n" << endl;

}

void Commands::Exit() {
	cout << "Exiting the program..." << endl;
	exit(EXIT_SUCCESS);
}

void Commands::searchCommand(string command) {
	fstream myFile;
	string fileName;

	if (command == "Open") {
		cout << "Enter which file do you want to use: ";
		cin >> fileName;
		Commands::Open(myFile, fileName);
		fileName.clear();
		cin.ignore();
	}
	else if (command == "Close") {
		cin >> fileName;
		Commands::Close(myFile, fileName);
		fileName.clear();
		cin.ignore();
	}
	else if (command == "Help") {
		Commands::Help();
		cin.ignore();
	}
	else if (command == "Exit") {
		Commands::Exit();
		cin.ignore();
	}
	else {
		cout << "Invalid command." << endl;
	}
}

