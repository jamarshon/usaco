/*
ID: jasonl91
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define DICT_LEN 4618
#define ENCODING_SIZE 3

const string ENCODING[][ENCODING_SIZE] = {
	{"", "", ""}, // 0
	{"", "", ""}, // 1
	{"A", "B", "C"}, // 2 first valid input
	{"D", "E", "F"},
	{"G", "H", "I"},
	{"J", "K", "L"},
	{"M", "N", "O"},
	{"P", "R", "S"},
	{"T", "U", "V"},
	{"W", "X", "CY"},
};

string* getDict() {
	ifstream fRead;
  int dictInd = 0;
  string* dict = new string[DICT_LEN]();
	string output;

	fRead.open("dict.txt");
	while (!fRead.eof()) {
		fRead >> output;
		dict[dictInd++] = output;
	}
	fRead.close();

	return dict;
}

int binarySearch(string* dict, string query) {
	int low = 0;
	int high = DICT_LEN - 1;
	while(low <= high) {
		int mid = low + ((high - low) / 2);
		string midVal = dict[mid];
		if(midVal < query) 
			low = mid + 1;
		else if(midVal > query)
			high = mid - 1;
		else
			return mid;
	}

	return -(low + 1);
};

// N <= 12 so maximum times function will be called is 3^12 permutations (531441)
// Using bitIndexRep similar to checking bits to see which index to use
string decode(string number, int bitIndexRep, int N) {
  string result;
  for(int i = N-1; i >= 0; i--) {
      result = ENCODING[number[i] - '0'][bitIndexRep % ENCODING_SIZE] + result;
      bitIndexRep /= ENCODING_SIZE;
  }
  return result;
}

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");

    string number;
    fin >> number;

    string* dict = getDict();

    int N = number.size();
    int len = pow(ENCODING_SIZE, N);

    bool foundResult = false;
    for(int i = 0; i < len; i++) {
    	string possibleResult = decode(number, i, N);
    	int indexInDict = binarySearch(dict, possibleResult);
    	if(indexInDict > 0) {
    		cout << dict[indexInDict] << endl;
    		fout << dict[indexInDict] << endl;
    		foundResult = true;
    	}
    }

    if(!foundResult) {
	    cout << "NONE" << endl;
			fout << "NONE" << endl;
    }
    
    return 0;
}