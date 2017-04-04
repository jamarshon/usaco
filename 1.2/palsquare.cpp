/*
ID: jasonl91
PROG: palsquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define N 300

string toBase(int num, int base) {
    string result;
    while(num) {
        int rem = num % base;
        char c = rem < 10 ? rem + 48 : 65 + rem - 10;
        result = c + result;
        num /= base;
    }
    return result;
}

bool isPalindrome(string x) {
    int len = x.size();
    for(int i = 0, iLen = len/2; i <= iLen; i++) {
        if(x[i] != x[len - i - 1]) return false;
    }
    return true;
}

int main() {
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

    int B;
    fin >> B;

    for(int i = 1; i <= N; i++) {
  		string squareInBase = toBase(i*i, B);
  		if(isPalindrome(squareInBase)) {
	  		string rootInBase = toBase(i, B);
  			cout << rootInBase << " " << squareInBase << endl;
  			fout << rootInBase << " " << squareInBase << endl;
  		}
    }

    return 0;
}