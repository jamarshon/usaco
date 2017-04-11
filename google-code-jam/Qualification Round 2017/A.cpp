#include <iostream>
#include <deque>
using namespace std;

string convert(string s, int k) {
	int len = s.size();
	int i = 0;
	int swaps = 0;
	// array corresponding to number of swaps
	deque<bool> A(len, false);

	bool currentParity = false;
	for(int iLen = len - k + 1; i < iLen; i++) {
		if(s[i] == '-' && !currentParity || s[i] == '+' && currentParity) {
			A[i + k - 1] ^= true;
			currentParity ^= true;
			swaps++;
		}

		currentParity ^= A[i];
	}

	for(; i < len; i++) {
		if(s[i] == '-' && !currentParity || s[i] == '+' && currentParity) return "IMPOSSIBLE";
		currentParity ^= A[i];
	}

	return to_string(swaps);
}

int main() {
  int T, K;
  string S;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> S >> K;
    cout << "Case #" << i << ": " << convert(S, K) << endl;
  }
  return 0;
}