#include <iostream>
#include <cmath>
using namespace std;

int main() {
  string str_n = "5";

  int b = stoi(str_n);
  int sum = 0;
  for(int i = 0; i <= b; i++) {
    cout << i*sqrt(2) << endl;
    sum += floor(i*sqrt(2));
  }
  cout << sum << endl;
  return 0;
}