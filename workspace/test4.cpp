#include <iostream>
using namespace std;

int main() {
  int T;
  int D, K;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> D >> K;
    double result = -1.0f;
    double t1, t2;
    for(int j = 0; j < K; j++) {
      cin >> t1 >> t2;
      result = max(result, (D - t1)/t2); // get the maximum amount of time it would take
    }
    cout << "Case #" << i << ": ";
    printf("%.9f\n", D/result);
  }
  return 0;
}