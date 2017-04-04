/*
ID: jasonl91
PROG: transform
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace std;

void readFileToVec(vector<vector<char>>& v, int N, ifstream* fin) {
	string line;
	for(int i = 0; i < N; i++) {
  	*fin >> line;
  	for(int j = 0; j < N; j++) {
  		v[i][j] = line[j];
  	}
  }
}

// inner gets increment every loop
bool isEqual(int N, int outer, int inner, function<bool(int, int, int, int)> comparison) {
  int innerCopy = inner;
  int outerInc = outer == 0 ? 1 : -1;
  int innerInc = inner == 0 ? 1 : -1;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j ++) {
      if(!comparison(i,j,outer,inner)) return false;
      inner += innerInc;
    }
    outer += outerInc;
    inner = innerCopy;
  }

  return true;
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

    int N;

    fin >> N;

    vector<vector<char>> original(N, vector<char>(N));
    vector<vector<char>> transformed(N, vector<char>(N));

    readFileToVec(original, N, &fin);
    readFileToVec(transformed, N, &fin);

    function<bool(int,int,int,int)> regularComparison = [original, transformed](int i, int j, int outer, int inner) -> bool { 
      return original[i][j] == transformed[outer][inner];
    };

    function<bool(int,int,int,int)> inverseComparison = [original, transformed](int i, int j, int outer, int inner) -> bool { 
      return original[i][j] == transformed[inner][outer];
    };

    // Need to execute in order as transformations are not unique and simpler transformations
    // should be checked first
    // format of outer, inner, inverseComparison, tranformationId
    int transformationArgs [8][4] = {
      {N-1, 0, 1, 1}, // N-1 0 inverseComparison : 90 cw
      {N-1, N-1, 0, 2}, // N-1 N-1 regularComparison : 180 cw
      {0, N-1, 1, 3}, // 0 N - 1 inverseComparison : 270 cw
      {0, N-1, 0, 4}, // 0 N - 1 regularComparison : Reflection
      {N-1, N-1, 1, 5}, // N-1 N-1 inverseComparison: Reflect + Rotation
      {N-1, 0, 0, 5}, // N-1 0 regularComparison: Reflect + Rotation
      {0, 0, 1, 5}, // 0 0 inverseComparison: Reflect + Rotation
      {0, 0, 0, 6}, // 0 0 regularComparison : No change
    };

    int tranformationId = 7;
    function<bool(int,int,int,int)> comparisonArr[2] { regularComparison, inverseComparison };
    for(int i = 0; i < 8; i++) {
      int* args{transformationArgs[i]};
      if(isEqual(N, args[0], args[1], comparisonArr[args[2]])){
        tranformationId = args[3];
        break;
      }
    }

    cout << "here" << endl;
    cout << tranformationId << endl;
    fout << tranformationId << endl;

    return 0;
}