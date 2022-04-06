#include <Python.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("GroceryList");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"GroceryList");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}



/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"GroceryList");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
// function to display menu options
void DisplayMenu() {
	cout << "\t\t MENU\n";
	cout << "=========================================\n";
	cout << "[1] Display number of times each item appears.\n";
	cout << "[2] Disply frequency of a signle item.\n";
	cout << "[3] Display histogram.\n";
	cout << "[4] Exit\n";
}
void ReadHistogram(vector<string> &histogramList) { // function to create vector of contents from a file

	ifstream outFS; //variable for the file
	string histogramEle; //define variable for the fioe contents 

	outFS.open("frequency.dat"); //open file 
	
	if (!outFS.is_open()) { //display error message if file cannot be read
		cout << "Cound not openfile \"frequency.dat\"\n";
	}
	else {
		getline(outFS, histogramEle); //reads first line of the file
		while (!outFS.fail()) { //reads each line of file as long as the file does not fail
			histogramList.push_back(histogramEle); //add contents from file to vector
			getline(outFS, histogramEle); //reads next line ion file 
		}

		outFS.close(); // closefile when finished
	}

}

void DisplayHistogram(const vector<string>& histogramList) {

	for (int i = 0; i < histogramList.size(); ++i) {
		cout << histogramList.at(i) << endl;
	}
}

void main(){
	vector<string> histogramList; //calls vector
	int menuOption; //define varible for a menu option
	bool endProgram = false; //define boolean assigned with false

	while (!endProgram) { //runs program as long as endProgran = false
		string userItem; // // define userItem variable 
		DisplayMenu(); //calls display menu varibale

		cout << "Enter menu option 1, 2, 3, or 4\n"; //prompt user to select a menu option
		cin >> menuOption;

		if (menuOption == 1){
			system("CLS"); //clears the consol screen
			cout << "Option 1: Display number of times each item appears.\n";
			cout << "==================================================== \n";
			CallProcedure("ItemCounter"); //calls python function to display frquency of each item in a file
			system("pause"); //pauses program and displays message to press any key to continue
		}
		else if (menuOption == 2) {
			system("CLS");
			cout << "Option 2: Display frequency of a single item.\n";
			cout << "=============================================\n";
			cout << "Enter an item.\n";
			cin >> userItem; // prompt users to select an item to find its frequency

			system("pause");
			system("CLS");

			cout << "Option 2: Display frequency of " << userItem << ".\n";
			cout << "=============================================\n";

			cout << callIntFunc("ItemFrequency", userItem); //calls python function to display the frequency of the iten the user chose
			system("pause");
		}
		else if (menuOption == 3) {
			system("CLS");
			cout << "Option 3: Display histogram.\n";
			cout << "============================\n";
			CallProcedure("HistogramFile"); // calls python function to create a new list from the contents of an existing list

			ReadHistogram(histogramList); //calls ReadHistogramfunction to creast vector from new file
			DisplayHistogram(histogramList); //calls display histogram function to display the histogram of the contents of a vector


			system("pause");
		}
		else if (menuOption == 4) {
			system("CLS");
			cout << "\n\n\t\t**********\n";
			cout << "\t\t*GOODBYE!*\n";
			cout << "\t\t**********\n";

			endProgram = true; //changes endProgram to true to end the program with a message

			system("pause");
		}
		else {
			system("CLS");
			cout << "Invalid entry\n"; //displays wrror message when users selects a menue option that is not 1, 2, 3, or 4.
			system("pause");
		}
	}
}	
