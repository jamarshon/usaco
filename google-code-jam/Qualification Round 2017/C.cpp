#include <iostream>
#include <unordered_map>
#include <set>
#include <cmath>

using namespace std;

string getLastStall(long long n, long long k) {
	if(n == k) return "0 0"; // short circuit just for performance

	set<long long> s{n};
	unordered_map<long long, long long> m{{n,1}};

	long long P = 0;
	long long L;
	long long R;
	while(true) {
		set<long long>::iterator it = --s.end();
		long long temp = *it;
		P += m[temp];

		L = temp/2;
		R = (temp-1)/2;
		if(P >= k) break;

		s.erase(it);
		s.insert(L);
		s.insert(R);

		// m[temp] is the number of occurences of temp so for each occurence of temp
		// there will be a corresponding occurence of L and R, therefore m[L] and m[R]
		// should increase by m[temp]
		if(m.find(L) == m.end()) {
			m[L] = m[temp];
		} else {
			m[L] += m[temp];
		}
		if(m.find(R) == m.end()) {
			m[R] = m[temp];
		} else {
			m[R] += m[temp];
		}
	}

	return to_string(L) + " " + to_string(R);
}

int main() {
  int T;
  long long N, K;
  cin >> T; 

  for (int i = 1; i <= T; i++) {
    cin >> N >> K;
    cout << "Case #" << i << ": " << getLastStall(N, K) << endl;
  }
  return 0;
}