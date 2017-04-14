/*
ID: jasonl91
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Coord {
	int x;
	int y;
};

int nCr(int n, int r) {
	int numerator = 1;
	int denominator = 1;
	for(int i = n; i > n - r; i--) numerator *= i;
	for(int i = r; i > 0; i--) denominator *= i;
	return numerator/denominator;
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");

    int N;

    fin >> N;

    Coord wormholes[N];
    unordered_map<int, int> m;

    int x, y;
    for(int i = 0; i < N; i++) {
    	fin >> x >> y;
        if(m.find(x) == m.end()) {
            m[x] = 1;
        } else {
            m[x]++;
        }
    	wormholes[i] = {x, y};
    }

    int count = 0;
    for(pair<int, int> it : m) {
        cout << it.second << endl;
        count += it.second;
    }

    cout << count << endl;
    // int remainingPairs = nCr(N-2, 2);
    // Infinite cycle exists if there is a wormhole pairing that has the same x coordinates
    // sort(wormholes, wormholes + N, [](Coord a, Coord b){ return a.x < b.x; });
    // for(int i = 0; i < N - 1; i++) {
    	// if(wormholes[i].x == wormholes[i + 1].x) {
    		// this pair is a cycle find how many different ways we can pair the others
    		// remainingPairs - 

    	// }
    	// cout << wormholes[i].x << " " << wormholes[i].y << endl;
    // }

    // cout << nCr(7,2) << endl;
    return 0;
}