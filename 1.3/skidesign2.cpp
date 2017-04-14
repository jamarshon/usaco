/*
ID: jasonl91
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits.h>

using namespace std;

#define TARGET_HEIGHT 17

int main() {
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");

    int N, hill;

    fin >> N;

    int hills[N];
    int maxHill = -1;
    for(int i = 0; i < N; i++) {
    	fin >> hills[i];
        maxHill = max(maxHill, hills[i]);
    }

    // O(kN) where k is TARGET_HEIGHT 
    int T = INT_MAX;
    for(int j = 0; j < maxHill - TARGET_HEIGHT + 1; j++) {
    		int k = j + TARGET_HEIGHT;
    		int leftCost = 0;
    		int rightCost = 0;
		    for(int i = 0; i < N; i++) {
		    	if(hills[i] <= j) leftCost += pow(j - hills[i], 2);
		    	if(hills[i] >= k) rightCost += pow(k - hills[i], 2);

		    }
		    T = min(T, leftCost + rightCost);
    }
    
    cout << T << endl;
    fout << T << endl;
    
    return 0;
}