#include <iostream>
using namespace std;

void toggle(string& s, int i) {
	s[i] = s[i] == '-' ? '+' : '-';
}

string convert(string s, int k) {
	int len = s.size();
	int i = 0;
	int swaps = 0;
	for(int iLen = len - k + 1; i < iLen; i++) {
		if(s[i] == '-') {
			for(int j = 0; j < k; j++) {
				toggle(s, i + j);
			}
			swaps++;
		}
	}
	for(; i < len; i++) {
		if(s[i] == '-') return "IMPOSSIBLE";
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