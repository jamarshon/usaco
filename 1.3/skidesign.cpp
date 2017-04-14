/*
ID: jasonl91
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <limits.h>

using namespace std;

#define TARGET_HEIGHT 17

// Derivation of cost (sum of squared error) with relation to a change in x denoted as dx
// cost_n = sigma_(i = 1 to n) { (x - x_i)^2 }
// if we change the threshold by dx then
// newCost = sigma_(i = 1 to n) { ((x + dx) - x_i)^2 }
// newCost = sigma_(i = 1 to n) { x^2 - 2x*x_i + x_i^2 + dx^2 + 2dx*x - 2dx*x_i }
// newCost = sigma_(i = 1 to n) { (x - x_i)^2 } + sigma_(i = 1 to n) { dx^2 + 2dx*x - 2dx*x_i }
// newCost = cost_n + sigma_(i = 1 to n) { dx^2 + 2dx*x - 2dx*x_i }
// newCost = cost_n + n(dx^2 + 2dx*x) - 2*dx*(sigma_(i = 1 to n) { x_i } )

// Therefore, calculating new cost from a previous cost can be done in O(1) through keeping
// track of the current sum as well as the new threshold x and its change (dx) from the previous one
int getCost(int prevCost, int n, int dx, int x, int sum) {
  return prevCost + n*(pow(dx, 2) + 2*dx*x) - 2*dx*sum;
}

int* getCostArr(int range, int init, int final, int inc, int* hills,
				unordered_map<int, pair<int, int>> m, unordered_map<int, int> frequency) {
	int prevCost = 0;
    int prevI = 0;
    int* costArr = new int[range]();

    for(int i = init; i != final; i += inc) {
    	int dx = i-prevI;
    	int j = i - hills[0];
    	if(m.find(i) == m.end()) {
    		costArr[j] = getCost(prevCost, m[prevI].first + frequency[prevI], dx, prevI, m[prevI].second + prevI*frequency[prevI]);
    	} else {
    		prevCost = getCost(prevCost, m[i].first, dx, prevI, m[i].second);
    		prevI = i;
    		costArr[j] = prevCost;
    	}
    }

    return costArr;
}

int main() {
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");

    int N, hill;

    fin >> N;

    int hills[N];
    for(int i = 0; i < N; i++) {
    	fin >> hills[i];
    }

    sort(hills, hills + N);

    unordered_map<int, int> frequency;
    unordered_map<int, pair<int, int>> mLeft;
    unordered_map<int, pair<int, int>> mRight;

    int totalSum = 0;
    for(int i = 0; i < N; i++) {
    	if(frequency.find(hills[i]) == frequency.end()) {
    		frequency[hills[i]] = 1;
    	} else {
    		frequency[hills[i]]++;
    	}

    	if(mLeft.find(hills[i]) == mLeft.end()) {
	    	mLeft[hills[i]] = make_pair(i, totalSum);
    	}
    	totalSum += hills[i];
    }

    totalSum = 0;
    for(int i = N-1; i >= 0; i--) {
    	if(mRight.find(hills[i]) == mRight.end()) {
    		mRight[hills[i]] = make_pair(N-i-1, totalSum);
    	}
    	totalSum += hills[i];
    }

    int range = hills[N-1] - hills[0] + 1;

    // O(NlogN) sort + O(Emax - Emin) from getCostArr + O(k) from adding costs where k is TARGET_HEIGHT 
    // if Emax - Emin is constant ie range of hills is constant with respect to number of hills N, then getCostArr is O(1)
    // so total complexity would be O(NlogN + k) which would be better than O(kN) if k > NlogN/(N-1)
    int* costLeft = getCostArr(range, hills[0], hills[N-1], 1, hills, mLeft, frequency);
    int* costRight = getCostArr(range, hills[N-1], hills[0], -1, hills, mRight, frequency);

    int minCost = INT_MAX;
    for(int i = 0, len = range - TARGET_HEIGHT; i < len; i++) {
    	int totalCost = costLeft[i] + costRight[i + TARGET_HEIGHT];
    	if(totalCost < minCost) {
    		minCost = totalCost;
    	}
    }

    cout << minCost << endl;
    fout << minCost << endl;
    
    return 0;
}