/*
Programmer Name: Caroline Tran
Program # : 9
Course: CIS1202
Date: 06/26/2019
Program Description : This program prints out information on the periodic table. Additionally, it allows users to search
the table, sort the table, and assess themselves on their periodic table knowledge.
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <array>
#include <cstddef>
#include <stdio.h> 
#include <stdlib.h>

using namespace std;

//Global Variables
const int SIZENUM = 118;
int elementNum[SIZENUM];

const int ROWS = 118;
const int COLS = 2;
string elementSymbol[ROWS][COLS];

// Function Prototypes
void readElements(int[], string (&Symbol)[ROWS][COLS], const int, const int); // read elements from files into two arrays
void printElements(int[], string(&Symbol)[ROWS][COLS], const int, const int); // prints elements with corresponding number and symbol
void sortElements(int[], string(&Symbol)[ROWS][COLS], const int, const int); // sort element by symbol
void searchElements(); // search element information by asking for user input for an element name
void elementsQuiz(string(&Symbol)[ROWS][COLS]); // randomized quiz for users to input the correct name/symbol for a certain element.


// Main

int main()
{
	readElements(elementNum, elementSymbol, ROWS, COLS);
	bool quit = false;

	while (!quit) // menu opens
	{
		int choice;

		cout << "Welcome to Periodic Table Database" << endl;
		cout << "\n";
		cout << "Please choose one of the following options:" << endl;
		cout << "1. Show Periodic Table" << endl;
		cout << "2. Search for Elements" << endl;
		cout << "3. Sort Elements by Symbol" << endl;
		cout << "4. Elements Quiz" << endl;
		cout << "5. Exit program" << endl;
		cout << "Enter choice: ";
		cin >> choice;


		switch (choice)
		{
		case 1:
		{
			printElements(elementNum, elementSymbol, ROWS, COLS);
			break;
		}

		case 2:
		{
			searchElements();
			break;
		}

		case 3:
		{
			sortElements(elementNum, elementSymbol, ROWS, COLS);
			break;
		}

		case 4:
		{
			elementsQuiz(elementSymbol);
			break;
		}

		case 5:
		{
			quit = true; // exits the program
			break;
		}

		default:
			cout << "Invalid option, please enter one of the menu options above" << endl;
			break;
		}
	}


}

void elementsQuiz(string(&Symbol)[ROWS][COLS])
{
	int numberRows = std::rand() % ROWS;
	int numberCols = std::rand() % COLS;
	int otherCol = 0;
	bool quiz = false;
	int attempt = 0;

	while (!quiz)
	{

		if (numberCols == 0)
		{
			cout << "Please enter the correct symbol for the following name: " << elementSymbol[numberRows][numberCols] << endl;
			otherCol = 1;
		}
		if (numberCols == 1)
		{
			cout << "Please enter the correct name for the following chemical symbol: " << elementSymbol[numberRows][numberCols] << endl;
		}

		string userGuess;
		cin >> userGuess;

		if (userGuess.compare(elementSymbol[numberRows][otherCol]) == 0)
		{
			cout << "Correct!" << endl;
			cout << "\n";
			quiz = true;
		}

		else							
		{
			if (attempt == 0) // user gets only one more attempt if they get the first answer incorrect
			{
				string temp;
				temp = elementSymbol[numberRows][otherCol];
				size_t found = temp.find_first_of("aeiouy"); // string library member function size_t and str.find_first_of
				while (found != std::string::npos)
				{
					temp[found] = '_';
					found = temp.find_first_of("aeiouy", found + 1);
				}
				cout << "Incorrect. 1 more attempt (Hint :" << temp << ")" << endl;
				++attempt;
			}

			else if (attempt > 0)
			{
				cout << "Incorrect. The correct answer was " << Symbol[numberRows][otherCol] << endl;
				cout << "\n";
				quiz = true;

			}
		}
	}	
}

void readElements(int elementNum[SIZENUM], string (&Symbol)[ROWS][COLS], const int ROWS, const int COLS)
{
	ifstream myfile1("periodic_table_elements.txt"), myfile2("number_elements.txt"); // text files to be read
	
	if (myfile1.is_open() && myfile2.is_open())
	{
		for (int i = 0; i < SIZENUM; i++)
		{
			myfile2 >> elementNum[i];
				
		}

		for (int j = 0; j < ROWS; j++)
		{
			for (int k = 0; k < COLS; k++)
			{
				myfile1 >> Symbol[j][k];
			}
		}
		cout << "\n" << endl;
	}

	else
	{
		cout << "Unable to open file" << endl;

	}

	myfile1.close();
	myfile2.close();
}

void printElements(int elementNum[SIZENUM], string(&Symbol)[ROWS][COLS], const int ROWS, const int COLS)
{
	int i = 0;
	int j = 0;

	cout << "Number  " << "Symbol  " << "Element Name  " << endl; // prints neat columns for periodic table

	while (i < SIZENUM)
	{
		cout.width(10); cout << left << elementNum[i];
			for (int k = 0; k < COLS; k++)
			{
				cout.width(6); cout << left << Symbol[j][k];
			}
			cout << endl;
			j++;
			i++;
	}

	cout << "\n";
}

void sortElements(int elementNum[SIZENUM], string(&Symbol)[ROWS][COLS], const int ROWS, const int COLS)
{
	int startScan, minIndex, temp;
	string minValue, temp2;

	for (startScan = 0; startScan < (118-1); startScan++)
	{
		minIndex = startScan;
		minValue = Symbol[startScan][0];
		temp = elementNum[startScan];
		temp2 = Symbol[startScan][1];

		for (int index = startScan + 1; index < 118; index++)
		{

			if (Symbol[index][0] < minValue)
			{
				minValue = Symbol[index][0];
				minIndex = index;
				temp = elementNum[index];
				temp2 = Symbol[index][1];
			}
		}
		Symbol[minIndex][0] = Symbol[startScan][0];
		Symbol[startScan][0] = minValue;

		elementNum[minIndex] = elementNum[startScan];
		elementNum[startScan] = temp;

		Symbol[minIndex][1] = Symbol[startScan][1];
		Symbol[startScan][1] = temp2;
	}
	cout << "Elements successfully sorted in ALPHABETICAL order by SYMBOLS" << endl;
	cout << "\n";
}

void searchElements()
{
	string elementChoice;
	
	cout << "Enter the name of the element you would like to search information for: ";
	cin >> elementChoice;
	bool found = false;
	for (int j = 0; j < ROWS; j++)
	{
		for (int k = 0; k < COLS; k++)
		{
			if (elementChoice.compare(elementSymbol[j][k]) == 0) // string library member function str.compare
			{
				found = true;
				cout << "The chemical symbol for the searched element is: " << elementSymbol[j][0] << endl;
				cout << "The atomic number for this element is: " << elementNum[j] << endl;
			}
		}
	}
	if (found == false)
	{
		cout << "No element could be found for the searched name." << endl;
	}
	cout << "\n";
}
