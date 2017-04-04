/*
ID: jasonl91
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");

    int M, S, C;
    fin >> M >> S >> C;

    vector<int> stallNum(C);
    for(int i = 0; i < C; i++) {
    	fin >> stallNum[i];
    }
    // Example 6 3 8 14 into 2 boards meaning M = 2
    // Sort so 3 6 8 14
    // diffStallNum would be adjacent differences so 3 3 2 6
    // sort the differences excluding the first one 3 2 3 6
    // sum differences excluding first one and M - 1 last ones (largest) so 2 + 3 = 5
    // Add 1 and M - 1 so 5 + 1 + 1 = 7
    // Check board #1 would be 3-8 and board #2 would be 14 so the total number blocked is
    // (8-3+1) + (14-14+1) which is 6 + 1 = 7 <- same answer above

    // Get the adjacent different between the stallNum when they are sorted
    sort(stallNum.begin(), stallNum.end());
    vector<int> diffStallNum(C);
    adjacent_difference (stallNum.begin(), stallNum.end(), diffStallNum.begin());

    // Sort the adjacent different and remove the M - 1 largest differences at the end
    // Sum the differences and add 1 and add 1 for each difference removed from the sum i.e. M - 1
    sort(diffStallNum.begin() + 1, diffStallNum.end());

    M = min(M, C);
    int numBlockedStalls = accumulate(diffStallNum.begin() + 1, diffStallNum.end() - (M - 1), 0) + 1 + (M - 1);

    cout << numBlockedStalls << endl;
    fout << numBlockedStalls << endl;
    return 0;
}