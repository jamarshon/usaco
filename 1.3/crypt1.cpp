/*
ID: jasonl91
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cmath>

using namespace std;

bool canBeConstructed(int i, unordered_set<int> digitSet) {
	while(i) {
		if(digitSet.find(i % 10) == digitSet.end()) return false;
		i /= 10;
	}
	return true;
}

bool is3Digits(int i) {
	return floor(log10(i)) + 1 == 3;
}

int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    int N, digit;
    unordered_set<int> digitSet;

    fin >> N;
    for(int i = 0; i < N; i++) {
    	fin >> digit;
    	digitSet.insert(digit);
    }

    int numberOfSolutions = 0;
    for(int i = 100; i < 1000; i++) {
    	if(canBeConstructed(i, digitSet)) {
    		for(int j = 10; j < 100; j++) {
    			if(canBeConstructed(j, digitSet)) {
    				int e = j % 10;
    				int d = j / 10;
    				int productE = i*e;
    				int productD = i*d;
    				if(is3Digits(productE) && is3Digits(productD)) {
    					if(canBeConstructed(productE, digitSet) && canBeConstructed(productD, digitSet)) {
    						int finalProduct = productE + productD * 10;
    						if(canBeConstructed(finalProduct, digitSet)) {
    							numberOfSolutions++;
    						}
    					}
    				}
    			}
    		}
    	}
    }

    cout << numberOfSolutions << endl;
    fout << numberOfSolutions << endl;
    return 0;
}