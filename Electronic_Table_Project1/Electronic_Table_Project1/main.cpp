#include "Commands.h"

// ПРИМЕРЕН ТЕСТ

//Please enter command : Open
//Enter the file you want to use : AnotherNewFiletxt
//Successfully opened AnotherNewFile.txt
//Successfully closed AnotherNewFile.txt
//Please enter command : Print
//10	 | Hello World!| 123.56 |   |	
//Quoted |			   |        |   |	
//1		 | 2	       | 3		| 4 |	
//Please enter command : Edit
// Enter which cell to edit
// Enter row = 1
// Enter columb = 1
// Enter the new value / formula = 3 * 1.5 
// Correction maded in cell R1C1
//Please enter command : Print
//4.5	 | Hello World!| 123.56 |   |	
//Quoted |		   	   |        |   |	
//1		 | 2	       | 3		| 4 |	
//Please enter command : Save	
//Successfully saved AnotherNewFile.txt
//Please enter command : Exit
//Exiting program...


int main() {

	string command;

	while (command != "Open") {
		cout << "Please enter command " << endl;
		cin >> command;
		Commands::searchCommand(command);
		cout << endl;
	}

	Table table(Commands::currentFile);

	while (command != "Exit") {
		cout << "Please enter command " << endl;
		cin >> command;
		table.findCommand(command);
		cout << endl;
	}

	return 0;
}