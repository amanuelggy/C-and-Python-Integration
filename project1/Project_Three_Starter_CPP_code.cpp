#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>
#include <map>


#include <sstream>
#include <iomanip>

using namespace std;

#define SEARCH_ITEM "SearchItem"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"


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
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Project_Three_Starter_PY_Code");
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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Project_Three_Starter_PY_Code");
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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Project_Three_Starter_PY_Code");
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

map<string, int> displayItems(string task) {
	// Reading from file
	ifstream readFile("Project_Three_Input_File.txt");

	string item;
	map<string, int> items;
	while (getline(readFile, item)) {
		//check if item is in the map
		map<string, int>::iterator itr = items.find(item);
		if (itr == items.end()) {
			// if item not in map add it into map as pair
			// item not found
			items.insert(pair<string, int>(item, 1));
		}
		else {
			// if item in map increment it's value
			// item found, update (increment) it's value
			int value = itr->second;
			value++;
			itr->second = value;
		}
	}

	// close file
	readFile.close();

	if (task == SEARCH_ITEM) {
		return items;
	}

	cout << "List of Items and their frequency:" << endl;
	int i = 0;
	for (map<string, int>::iterator iter = items.begin(); iter != items.end(); iter++) {
		int value = (*iter).second;
		string itemLine = to_string(i) + ". " + (*iter).first + ": " + to_string(value);
		i++;
		callIntFunc("DisplayItems", itemLine);

	}
	return items;
}

// print n characters
string nCharString(size_t n, char c) {

	stringstream sstrm;
	string val = "";
	sstrm << setfill(c) << setw(n) << val;
	val = sstrm.str();

	return val;
}

int countChars(string textLine, char chr) {
	int count = 0;
	for (size_t i = 0; i < textLine.size(); i++) {
		if (textLine.at(i) == '*') {
			count++;
		}
	}
	return count;
}

void displayHistogram() {
	map<string, int> items = displayItems(SEARCH_ITEM);

	// create file
	ofstream myfile("frequency.dat");

	// write to file
	for (map<string, int>::iterator iter = items.begin(); iter != items.end(); iter++) {
		int value = (*iter).second;
		string itemLine = (*iter).first + " " + nCharString(value, '*') + "\n";

		myfile << itemLine;
	}
	myfile.close();

	ifstream readfile("frequency.dat");
	string textLine;
	while (getline(readfile, textLine)) {
		int count = countChars(textLine, '*');
		if (count > 0 && count <= 2) {
			cout << RED << textLine << endl;
		} else if (count > 2 && count <= 4) {
			cout << YELLOW << textLine << endl;
		} else if (count > 4 && count <= 6) {
			cout << GREEN << textLine << endl;
		} else if (count > 6) {
			cout << BLUE << textLine << endl;
		}
		//cout << textLine << endl;
	}
	readfile.close();
}


int main()
{
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);


	bool isNotExit = true;
	int input;

	while (isNotExit) {
		CallProcedure("printMenu");
		cin >> input;

		if (input == 1) {
			displayItems("display");
		}
		else if (input == 2) {
			map<string, int> items = displayItems(SEARCH_ITEM);
			string value;

			cout << "please type the item name" << endl;
			cin >> value;
			map<string, int>::iterator itr = items.find(value);
			string result = itr->first + ": " + to_string(itr->second);

			// display result in python
			callIntFunc("DisplaySearchResult", result);

			// display result in C++
			cout << "C++ output: Frequency of " << itr->first << " is " << itr->second << endl;
		}
		else if (input == 3) {

			// display data as histogram
			displayHistogram();
		}
		else if (input == 4) {
			isNotExit = false;
		}
		else {
			CallProcedure("Error");

		}
		input = 0;
	}	
	

	return 0;

	

}
