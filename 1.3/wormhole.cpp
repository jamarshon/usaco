/*
ID: jasonl91
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

struct Coord {
    int x;
    int y;
    int paired;
};

struct CompareWormHole {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
        return p1.first < p2.first;
    }
};

bool IsCycle(Coord wormholes [], int N, unordered_map<int, set<pair<int, int>, CompareWormHole>>& m) {
    for(int i = 0; i < N; i++) {
        int curr = i;
        unordered_set<int> visited;
        visited.insert(curr);

        while(true) {
            int paired = wormholes[curr].paired;

            set<pair<int, int>, CompareWormHole> on_a_line = m[wormholes[paired].y];
            auto right = on_a_line.upper_bound({wormholes[paired].x, 0});

            if(right == on_a_line.end()) break; // nothing right of this so we're done
            int right_neighbor = right -> second;

            if(visited.count(right_neighbor)) return true; // visit same cell
            visited.insert(right_neighbor);

            curr = right_neighbor;
        }
    }

    return false;
}

int GetPairings(Coord wormholes[], int N, unordered_map<int, set<pair<int, int>, CompareWormHole>>& m) {
    int i = 0;
    for(; i < N; i++) {
        if(wormholes[i].paired == -1) break;
    }

    if(i == N) { 
        bool is_cycle = IsCycle(wormholes, N, m); // everything is paired so just check cycle
        return is_cycle;
    }

    int count = 0;
    for(int j = i + 1; j < N; j++) {
        if(wormholes[j].paired != -1) continue;
        // pair i and j
        wormholes[j].paired = i;
        wormholes[i].paired = j;

        // see if cycle exists
        count += GetPairings(wormholes, N, m);

        // reset variables
        wormholes[i].paired = wormholes[j].paired = -1;
    }

    return count;
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");

    int N;

    fin >> N;

    Coord wormholes[N];

    int x, y;
    for(int i = 0; i < N; i++) {
    	fin >> x >> y;
    	wormholes[i] = {x, y, -1};
    }

    // key is y coordinate and value is all the x coordinates
    unordered_map<int, set<pair<int, int>, CompareWormHole>> m;
    for(int i = 0; i < N; i++) {
        m[wormholes[i].y].insert({wormholes[i].x, i});
    }

    fout << GetPairings(wormholes, N, m) << endl;
    return 0;
}