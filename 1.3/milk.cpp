/*
ID: jasonl91
PROG: milk
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct MilkInventory {
	int price;
	int numOfUnits;
};

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

    int N, M;

    fin >> N >> M;

    int price, numOfUnits;
    vector<MilkInventory> v(M);
    for(int i = 0; i < M; i++) {
    	fin >> price >> numOfUnits;
    	v[i] = {price, numOfUnits};
    }

    // sort by price
    sort(v.begin(), v.end(), [](MilkInventory a, MilkInventory b){ return a.price < b.price; });

    int cheapestCost = 0;
    for(MilkInventory m: v) {
    	if(N == 0) break;
    	int numUnitsBought = min(N, m.numOfUnits);
    	cheapestCost +=numUnitsBought * m.price;
    	N -= numUnitsBought;
    }

    cout << cheapestCost << endl;
    fout << cheapestCost << endl;
    return 0;
}