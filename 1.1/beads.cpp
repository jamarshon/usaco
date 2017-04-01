/*
ID: jasonl91
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    int N;
    string beads;

    fin >> N >> beads;

    beads += beads;

    int dpLen = 2*N+1;
    int leftR[dpLen];
    int leftB[dpLen];

    leftR[0] = leftB[0] = 0;
    for(int i = 0, len = 2*N; i < len; i++) {
      switch(beads[i]){
        case 'w': // both the red and blue can increase
          leftR[i+1] = leftR[i] + 1;
          leftB[i+1] = leftB[i] + 1;
          break;
        case 'b': // blue seen so red sequence ends
          leftR[i+1] = 0;
          leftB[i+1] = leftB[i] + 1;
          break;
        case 'r': // red seen so blue sequence ends
          leftR[i+1] = leftR[i] + 1;
          leftB[i+1] = 0;
          break;
      }
    }

    int rightR[dpLen];
    int rightB[dpLen];

    rightR[dpLen - 1] = rightB[dpLen - 1] = 0;
    for(int i = 2*N - 1; i >= 0; i--) {
      switch(beads[i]){
        case 'w':
          rightR[i] = rightR[i+1] + 1;
          rightB[i] = rightB[i+1] + 1;
          break;
        case 'b':
          rightR[i] = 0;
          rightB[i] = rightB[i+1] + 1;
          break;
        case 'r':
          rightR[i] = rightR[i+1] + 1;
          rightB[i] = 0;
          break;
      }
    }

    int currentLen;
    int maxLen = 0;
    for(int i = 0; i < dpLen; i++) {
      currentLen = max(leftR[i], leftB[i]) + max(rightR[i], rightB[i]);
      maxLen = max(maxLen, currentLen);
    }

    fout << min(N, maxLen) << endl;
    return 0;
}