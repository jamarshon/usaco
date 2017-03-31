/*
ID: jasonl91
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>

using namespace std;

int getCode(string s) {
	int product = 1;
	for(int i = 0, len = s.size(); i < len; i++) {
  	product = ((s[i] - 'A' + 1) * product) % 47;
  }
  return product;
}
int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string comet, group;
    fin >> comet >> group;
    bool shouldGo = getCode(comet) == getCode(group);
    string output = shouldGo ? "GO" : "STAY";
    fout << output << endl;
    return 0;
}