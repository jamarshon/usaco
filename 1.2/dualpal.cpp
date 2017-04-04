/*
ID: jasonl91
PROG: dualpal
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits.h>

using namespace std;

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
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

    int N, S;
    fin >> N >> S;

    for(int s = S + 1; s < INT_MAX; s++) {
    	int numberOfPalindromes = 0;
    	for(int base = 2; base <= 10; base++) {
    		if(isPalindrome(toBase(s, base))) {
    			numberOfPalindromes++;
    			if(numberOfPalindromes == 2) break;
    		}
    	}

    	if(numberOfPalindromes == 2) {
    		cout << s << endl;
    		fout << s << endl;
    		N--;
    		if(N == 0) break;
    	}
    }
    
    return 0;
}