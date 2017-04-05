/*
ID: jasonl91
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getPossibleVals(int num, int N) {
	if(N < 5) {
		vector<int> ret(N);
		iota(ret.begin(), ret.end(), 1);
		return ret;
	}

	vector<int> ret(5);
	for(int i = 0; i <= 4; i++) {
		int result = num + i - 2;
		result = result <= 0 ? result + N : result > N ? result - N : result; // handles wrap around
		ret[i] = result;
	}
	sort(ret.begin(), ret.end());
	return ret;
}

int main() {
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");

    int N;
    int farmerComb[3];
    int masterComb[3];

    fin >> N;

    int maxRange = min(5, N);
    int numberOfCombinations = maxRange*maxRange*maxRange*2;
    int numberOfIntersections = 1;

    for(int i = 0; i < 3; i++) { fin >> farmerComb[i]; }
    for(int i = 0; i < 3; i++) { fin >> masterComb[i]; }

    // total algorithm complexity is O(1) with respect to N as we are not calculating
    // all the combinations with digits between 1 to N instead we are calculating
    // the product of size of intersection of digits and subtracting by the total possible number
    // of combinations
		for(int i = 0; i < 3; i++) { 
			vector<int> farmPosVal = getPossibleVals(farmerComb[i], N); // O(1) as maximum 5 iterations
			vector<int> mastPosVal = getPossibleVals(masterComb[i], N);
			vector<int> intersection;

			set_intersection(farmPosVal.begin(), farmPosVal.end(), mastPosVal.begin(), mastPosVal.end(), 
				back_inserter(intersection)); // O(1) as takes O(n) to get intersection sorted sequence and here n is maximum 10

			numberOfIntersections *= intersection.size();
		}

    int result = numberOfCombinations - numberOfIntersections;
    cout << result << endl;
    fout << result << endl;
    return 0;
}