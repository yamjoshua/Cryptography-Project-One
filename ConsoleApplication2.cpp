// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


vector<int> frequencyCounter(vector<char> total, int pos) {
	// frequency vectors are [0,a,..,z]
	vector<int> frequency(27);
	int ascii;
	for (int j = pos; j < (pos+500); j++) {
		ascii = int(total[j]);
		cout << total[j];
		if (total[j] == ' ') {
			frequency[0]++;
		}
		else {
			frequency[ascii - 96]++;
		}
	}
	cout << '\n';
	return frequency;
}

int main()
{
	ifstream ifs("dictionary.txt");
	if (!ifs) {
		cerr << "Couldn't open 'dictionary.txt'\n";
		exit(1);
	}
	
	vector<char> temp;
	char x;
	while (ifs >> noskipws >> x) {
		temp.push_back(x);
	}


	/*for (size_t i = 0; i < temp.size(); i++) {
		cout << temp[i] << ' ';
	}*/

	cout << endl;

	// each vector contains the frequency of each char
	vector<int> plainText1 = frequencyCounter(temp, 0);
	vector<int> plainText2 = frequencyCounter(temp, 501);
	vector<int> plainText3 = frequencyCounter(temp, 1002);
	vector<int> plainText4 = frequencyCounter(temp, 1503);
	vector<int> plainText5 = frequencyCounter(temp, 2004);

	for (int k = 1; k < plainText1.size(); k++) {
		cout << char(k+96) << ' ' << plainText1[k] << '\n';
	}

    //cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
