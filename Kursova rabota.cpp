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
	float a[N], b[N], c[N], max_a, min_a, max_b, min_b, max_c, min_c;
	int n = 0, z = 0, an = 0, bn = 0, cn = 0;
	string n1, an1, a1[N];
	do {
		do {
			cout << "1) Input from text file\n2) Manual input\nChoose option: "; getline(cin, n1);
		} while (numcheck(n1, 0) == false);
		n = stoi(n1);
	} while (n < 1 || n > 2);
	switch(n) {
	case 1: {
		string filename;
		ifstream Input;
		do {
			cout << "Enter file's name and extension: "; getline(cin, filename);
			Input.open(filename);
		} while (Input.fail());
		while (getline(Input, a1[an])) {
			an++;
		}
		for(int i = 0; i < an; i++){
			if (numcheck(a1[i], 1) == false) {
				cout << "File contains symbols different from numbers!" << endl;
				z++;
				break;
			}
			else {
				a[i] = stof(a1[i]);
				if (a[i] < 0) {
					c[cn] = a[i];
					cn++;
				}
				else {
					b[bn] = a[i];
					bn++;
				}
			}
		}
		if (z == 0) {
			for (int i = 0; i < an; i++) {
				cout << i+1 << ") " << a[i] << endl;
			}
		}
		break;
	}
	case 2: {
		do {
			do {
				cout << "How many numbers do you wish to type? - "; getline(cin, an1);
			} while (numcheck(an1, 0) == false);
			an = stoi(an1);
		} while (an >= N || an <= 0);
			for (int i = 0; i < an; i++) {
				do {
					printf("%d) ", i + 1);
					getline(cin, a1[i]);
					if (numcheck(a1[i], 1) == false) {
						cout << "Please, enter a number!" << endl;
					}
				} while (numcheck(a1[i], 1) == false);
				a[i] = stof(a1[i]);
				if (a[i] < 0) {
					c[cn] = a[i];
					cn++;
				}
				else {
					b[bn] = a[i];
					bn++;
				}
		}
			break;
	}
	}
	if (z == 0) {
		max_a = max(a, an);
		min_a = min(a, an);
		cout << "Biggest number = " << max_a << endl; cout << "Smallest number = " << min_a << endl;
		if (bn != 0) {
			max_b = max(b, bn);
			min_b = min(b, bn);
			cout << "Biggest non negative number = " << max_b << endl; cout << "Smallest non negative number = " << min_b << endl;
		}
		else {
			cout << "No non negative numbers found" << endl;
		}
		if (cn != 0) {
			max_c = max(c, cn);
			min_c = min(c, cn);
			cout << "Biggest negative number = " << max_c << endl; cout << "Smallest negative number = " << min_c << endl;
		}
		else {
			cout << "No negative numbers found" << endl;
		}
		do {
			do {
				cout << "Do you want to save the list in a text file?\n1) Yes \n2) No\n"; n = 0; getline(cin, n1);
			} while (numcheck(n1, 0) == false);
			n = stoi(n1);
		} while (n == 0 || n < 1 || n > 2);
		if (n == 1) {
			string outputname;
			float max_line = 0, tmp_line = 0; int lineNum = 1, k = 0;
			do {
				cout << "Enter file name - ";
				getline(cin, outputname);
			} while (namecheck(outputname) == false);
			ofstream Output(outputname);
			for (int i = 0; i < an; i++) {
				Output << a[i];
				tmp_line += a[i];
				if ((i + 1) % 6 == 0 || i == an - 1) {
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
			cout << "Line number " << lineNum << " has the biggest sum of numbers = " << max_line << endl;
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
	if (fl == 0) {
		for (int i = n; i < input.size(); i++) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
	}
	else {
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
	if (name.size() == 0) {
		return false;
	}
	if (name[0] == ' ') {
		return false;
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == '@' || name[i] == '$' || name[i] == '&' || name[i] == '/' || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '"' || name[i] == '<' || name[i] == '>' || name[i] == '|' || name[i] == '~' || name[i] == '#' || name[i] == '^' || name[i] == '+' || name[i] == '=' || name[i] == '{' || name[i] == '}' || name[i] == ';' || name[i] == '!' || name[i] == '\\') {
			return false;
		}
	}
	return true;
}