#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

int main() {
  int T, N, D;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
  	cin >> N;

    unordered_map<int, int> m;
    for (int j = 0; j < 2*N - 1; j++) {
    	for(int k = 0; k < N; k++) {
    		cin >> D;
    		if(m.find(D) == m.end()) m[D] = 1;
    		else m[D]++;
    	}
		}

		set<int> result;
		for(auto it: m) {
			if(it.second % 2 == 1) {
				result.insert(it.first);
			}
		}

		string rStr = "";
		for(auto it: result) {
			rStr += to_string(it) + " ";
		}

    cout << "Case #" << i << ": " << rStr << endl;
  }
  
  return 0;
}