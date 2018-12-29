#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

int tt;
int W[int(1e5) + 1];


ll solve(int L, int N, int M, int D) {
    typedef pair<ll, int> p;

    vector<ll> dryers(M, 0);
    int dryer_ind = 0;

    priority_queue<p, vt<p>, greater<p>> pq; // shortest first
    for(int i = 0; i < N; i++) {
        pq.emplace(W[i], i);
    }

    ll res = 0;
    for(int i = 0; i < L; i++) {
        auto pp = pq.top();
        pq.pop();
        // at time pp.first, we can use the earliest ended dry at dryer_ind
        // if this dryer won't be done in time, then wait until it's done
        dryers[dryer_ind] = max(dryers[dryer_ind], pp.first) + D;
        res = dryers[dryer_ind];
        dryer_ind = (dryer_ind + 1) % M;

        pp.first += W[pp.second]; 
        pq.emplace(pp);

    }

    return res;
}

int main() {
    ifstream fin ("a.in");
    ofstream fout ("a.out");
    int T;
    int L, N, M, D;

    fin >> T;
    for(tt = 0; tt < T; tt++) {
        fin >> L >> N >> M >> D;
        for(int i = 0; i < N; i++) fin >> W[i];
        fout << "Case #" << tt + 1 << ": " << solve(L, N, M, D) << endl;
    }
    
    return 0;
}