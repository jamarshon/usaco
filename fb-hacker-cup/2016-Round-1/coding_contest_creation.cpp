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

int solve(vector<int>& v) {
    int res = 0;
    vector<int> buf;

    int N = v.size();
    for(int i = 0; i < N; i++) {
        if(buf.size() == 4) buf.clear();

        if(buf.empty()) {
            buf.push_back(v[i]);
        } else { // size >= 1
            if(v[i] <= buf.back()) {
                res += 4 - buf.size();
                buf = { v[i] };
            } else {
                int diff = v[i] - buf.back();
                int r = min((diff-1)/10, 4 - (int)buf.size());
                res += r;
                while(r--) buf.push_back(-1);
                if(buf.size() == 4) {
                    buf = { v[i] };
                } else {
                    buf.push_back(v[i]);
                }
            }
        }
    }

    return res + 4 - buf.size();
}

int main() {
    ifstream fin ("a.in");
    ofstream fout ("a.out");
    int T;
    int N;

    fin >> T;
    for(tt = 0; tt < T; tt++) {
        fin >> N;
        vector<int> v;
        v.reserve(N);
        int temp;
        for(int i = 0; i < N; i++) {
            fin >> temp;
            v.push_back(temp);
        }

        fout << "Case #" << tt + 1 << ": " << solve(v) << endl;
    }
    return 0;
}