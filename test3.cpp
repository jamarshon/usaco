/*
ID: jasonl91
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <limits.h>

using namespace std;

#define TARGET_HEIGHT 17


int main() {
    // ofstream fout ("skidesign.out");
    ifstream fin ("./1.3/skidesign.in");

    int N, hill;

    fin >> N;

    int hills[N];
    for(int i = 0; i < N; i++) {
        fin >> hills[i];
    }

    sort(hills, hills + N);

    int T = INT_MAX;
    for(int j = 0; j < hills[N-1] - 17 + 1; j++) {
            int k = j + 17;
            int a = 0;
            int e = 0;
            for(int i = 0; i < N; i++) {
                if(hills[i] <= j) a += pow(j - hills[i], 2);
                if(hills[i] >= k) e += pow(k - hills[i], 2);

            }
            if(a+e == 487881) cout << a << " " << e << " " << j << " " << k << endl;
            T = min(T, a+e);
    }
    
    cout << T << endl;
    
    return 0;
}