/*
ID: jasonl91
PROG: ariprog
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>

using namespace std;

struct ComparePair {
    // different from standard pair compare as second key goes first
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const {
        return lhs.second == rhs.second ? lhs.first < rhs.first: lhs.second < rhs.second;
    }
};

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        hash<int> hash_int;
        return hash_int(p.first) ^ (hash_int(p.second) >> 1);
    }
};

int main() {
    ofstream fout ("ariprog.out");
    ifstream fin ("ariprog.in");

    int N, M;
    fin >> N >> M;

    set<int> sq;
    unordered_set<int> sq_uno;
    int max_el = INT_MIN;
    for(int p = 0; p <= M; p++) {
        for(int q = p; q <= M; q++) {
            int item = p*p + q*q;
            max_el = max(item, max_el);
            sq_uno.insert(item);
            sq.insert(item);
        }
    }
    
    unordered_set<pair<int, int>, PairHash> res;

    auto last_1 = prev(sq.end(), N - 1);
    for(auto it = sq.begin(); it != last_1; ++it) {
        auto inner_it = it;
        for(++inner_it; inner_it != sq.end(); ++inner_it) {
            int difference = *inner_it - *it;

            if(*it + (N - 1)*difference > max_el) break;

            bool ok = true;
            for(int n = 2; n < N; n++) {
                int next = *it + n*difference;
                if(next > max_el || !sq_uno.count(next)) {
                    ok = false;
                    break;
                }
            }

            if(ok) {
                res.emplace(*it, difference);
            }
        }
    }

    set<pair<int, int>, ComparePair> sorted_res(res.begin(), res.end());
    for(auto p: sorted_res) {
        fout << p.first << ' ' << p.second << endl;
    }

    if(res.size() == 0) fout << "NONE" << endl;
    return 0;
}