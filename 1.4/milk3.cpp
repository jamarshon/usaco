/*
ID: jasonl91
PROG: milk3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int xor_total = 0^1^2;

void solve(int capacity[3], int size[3], int from, int to, set<int>& res) {
    cout << size[0] << ' ' << size[1] << ' ' << size[2] << endl;
    if(size[0] == 0) {
        res.insert(size[2]);
        if(size[1] != 0) return;
    }

    int to_temp = size[to];
    int from_temp = size[from];

    size[to] = min(capacity[to], size[from]);
    size[from] -= size[to];
    solve(capacity, size, to, xor_total^from^to, res);
    size[to] = to_temp;
    size[from] = from_temp;
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");

    int A, B, C;
    fin >> A >> B >> C;

    int capacity[3] = {A, B, C};
    int size[3] = {0, 0, C};

    set<int> res;
    solve(capacity, size, 2, 0, res);
    solve(capacity, size, 2, 1, res);

    for(auto t: res) {
        cout << t << ' ';
    }
    cout << endl;
    return 0;
}