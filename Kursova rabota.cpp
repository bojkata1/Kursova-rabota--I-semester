#include <iostream>
#include <fstream>	
#include <string>
#define N 100
using namespace std;
float max(float x[], int nx);
float min(float x[], int nx);
bool numcheck(string input, int fl);
bool namecheck(string name);
int main() {
	float allNumbers[N], otherNumbers[N], negativeNumbers[N], max_a, min_a, max_b, min_b, max_c, min_c;
	int choice = 0, z = 0, n = 0, otherNumbersCounter = 0, negativeNumbersCounter = 0;
	string choice_string, n_string, allNumbers_string[N];
	do {
		do {
			cout << "1) Input from text file\n2) Manual input\nChoose option: "; getline(cin, choice_string);
		} while (numcheck(choice_string, 0) == false); // checks if the choice is valid
		choice = stoi(choice_string);
	} while (choice < 1 || choice > 2); // checks if the command exists
	switch(choice) {
	case 1: { // import data from file
		string filename;
		ifstream Input;
		do {
			cout << "Enter file's name and extension: "; getline(cin, filename);
			Input.open(filename);
		} while (Input.fail()); // checks if the file exists
		while (getline(Input, allNumbers_string[n])) { // loads the elements in the string array
			n++;
		}
		for(int i = 0; i < n; i++){ // checks the string array for invalid elements
			if (numcheck(allNumbers_string[i], 1) == false) {
				cout << "File contains symbols different from numbers!" << endl;
				z++; // changing z means the input is invalid and the array won't be displayed
				break;
			}
			else {
				allNumbers[i] = stof(allNumbers_string[i]); // if the element is a valid number, copy it in the float array
				if (allNumbers[i] < 0) { // checks if the number is negative, if yes - puts the number in the negative array
					negativeNumbers[negativeNumbersCounter] = allNumbers[i];
					negativeNumbersCounter++;
				}
				else { // puts the number in the otherNumbers array
					otherNumbers[otherNumbersCounter] = allNumbers[i];
					otherNumbersCounter++;
				}
			}
		}
		if (z == 0) { // if the input is valid, display the array
			for (int i = 0; i < n; i++) {
				cout << i+1 << ") " << allNumbers[i] << endl;
			}
		}
		break;
	}
	case 2: { // Manual input
		do {
			do {
				cout << "How many numbers do you wish to type? - "; getline(cin, n_string);
			} while (numcheck(n_string, 0) == false); // checks if the input is a valid number
			n = stoi(n_string);
		} while (n >= N || n <= 0); // checks if the choice is between 0 and N (100)
		for (int i = 0; i < n; i++) { // gives the user the option to enter the elements, checks the elements and separates them between the other two arrays
			do {
				printf("%d) ", i + 1);
				getline(cin, allNumbers_string[i]);
				if (numcheck(allNumbers_string[i], 1) == false) {
					cout << "Please, enter a number!" << endl;
				}
			} while (numcheck(allNumbers_string[i], 1) == false);
			allNumbers[i] = stof(allNumbers_string[i]);
			if (allNumbers[i] < 0) {
				negativeNumbers[negativeNumbersCounter] = allNumbers[i];
				negativeNumbersCounter++;
			}
			else {
				otherNumbers[otherNumbersCounter] = allNumbers[i];
				otherNumbersCounter++;
			}
		}
		break;
	}
	}
	if (z == 0) { // if the input is valid, displays the arrays and their min and max elements
		max_a = max(allNumbers, n);
		min_a = min(allNumbers, n);
		cout << "Biggest number = " << max_a << endl; cout << "Smallest number = " << min_a << endl;
		if (otherNumbersCounter != 0) {
			max_b = max(otherNumbers, otherNumbersCounter);
			min_b = min(otherNumbers, otherNumbersCounter);
			cout << "Biggest non negative number = " << max_b << endl; cout << "Smallest non negative number = " << min_b << endl;
		}
		else {
			cout << "No non negative numbers found" << endl;
		}
		if (negativeNumbersCounter != 0) {
			max_c = max(negativeNumbers, negativeNumbersCounter);
			min_c = min(negativeNumbers, negativeNumbersCounter);
			cout << "Biggest negative number = " << max_c << endl; cout << "Smallest negative number = " << min_c << endl;
		}
		else {
			cout << "No negative numbers found" << endl;
		}
		do {
			do {
				cout << "Do you want to save the list in a text file?\n1) Yes \n2) No\n"; choice = 0; getline(cin, choice_string); // gives the choice to save the array with all of the elements
			} while (numcheck(choice_string, 0) == false);
			choice = stoi(choice_string);
		} while (choice == 0 || choice < 1 || choice > 2); // checks the choice
		if (choice == 1) {
			string outputname;
			float max_line = 0, tmp_line = 0; int lineNum = 1, k = 0;
			do {
				cout << "Enter file name - ";
				getline(cin, outputname);
			} while (namecheck(outputname) == false); // checks name
			ofstream Output(outputname);
			for (int i = 0; i < n; i++) { // loads the elements in the text file
				Output << allNumbers[i];
				tmp_line += allNumbers[i];
				if ((i + 1) % 6 == 0 || i == n - 1) {
					Output << "\n";
					if (k == 1) {
						if (tmp_line > max_line) {
							max_line = tmp_line;
							lineNum++;
						}
					}
					else {
						max_line = tmp_line;
						k = 1;
					}
					tmp_line = 0;
				}
				else {
					Output << " ";
				}
			}
			cout << "Line number " << lineNum << " has the biggest sum of numbers = " << max_line << endl; // displays the line with the biggest sum of numbers
		}
	}
	return 0;
}
float max(float x[], int nx) {
	float max;
	int k;
	max = x[0];
	for (k = 0; k < nx; k++) {
		if (x[k] > max) {
			max = x[k];
		}
	}
	return max;
}
float min(float x[], int nx) {
	float min;
	int k;
	min = x[0];
	for (k = 0; k < nx; k++) {
		if (x[k] < min) {
			min = x[k];
		}
	}
	return min;
}
bool numcheck(string input, int fl) {
	int n = 0, f = 0;
	if (input.size() == 0) {
		return false;
	}
	if (input[0] == '-') {
		n = 1;
		if (input.size() == 1) {
			return false;
		}
	}
	if (fl == 0) { // validation for integers
		for (int i = n; i < input.size(); i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
	}
	else { // validation for numbers of type float
		for (int i = n; i < input.size(); i++) {
			if (input[n] == '.') {
				return false;
			}
			if (input[i] == '.') {
				f++;
				i++;
			}
			if (f > 1) {
				return false;
			}
			if (!isdigit(input[i])) {
				return false;
			}
		}
	}
	return true;
}
bool namecheck(string name) {
	string invalidChars = "@$&/:*?\"<>'\\|~#^+=;{}!";
	if (name.size() == 0) {
		return false;
	}
	if (name[0] == ' ') {
		return false;
	}
	for (int i = 0; i < name.size(); i++) {
		if (invalidChars.find(name[i]) != string::npos) {
			return false;
		}
	}
	return true;
}