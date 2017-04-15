#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

struct Range {
	int low;
	int high;
};

int main() {
  int T, N, P;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
  	cin >> N >> P;
  	int R[N];
  	for(int j = 0; j < N; j++) {
  		cin >> R[j];
  	}

  	vector<vector<int>> v(N, vector<int>(P));
  	for(int j = 0; j < N; j++) {
  		for(int k = 0; k < P; k++) {
  			cin >> v[j][k];
  		}
  	}

  	vector<vector<Range>> v2(N, vector<Range>(P));

  	for(int j = 0; j < N; j++) {
  		for(int k = 0; k < P; k++) {
  			int floored = v[j][k]/R[j];
  			double up = 1.1*R[j];
  			double down = 0.9*R[j];
  			up = double(v[j][k])/up;
  			down = double(v[j][k])/down;

  			int a = ceil(up);
  			int b = floor(down);
			// cout << v[j][k] << "a " << R[j] << " " << up << " " << down << endl;
  			if(double(v[j][k])/(a*R[j]) < 0.9 || double(v[j][k])/(a*R[j]) > 1.1){
  				// cout << v[j][k] << "a " << R[j] << " " << up << " " << down << endl;
  				v2[j][k] = {INT_MAX, INT_MAX};
  			} else if(double(v[j][k])/(b*R[j]) < 0.9 || double(v[j][k])/(b*R[j]) > 1.1) {
  				// cout << v[j][k] << "b " << R[j] << " " << up << " " << down << endl;
  				v2[j][k] = {INT_MAX, INT_MAX};
  			} else {
	  			v2[j][k] = {a, b};
  			}
  		}
  	}

  	for(int j = 0; j < N; j++) {
	  	sort(v2[j].begin(), v2[j].end(), [](Range a, Range b){ 
	  		if(a.low != b.low) return a.low < b.low;
	  		return a.high < b.high;
	  	});
  	}

  	for(int j = 0; j< N;j ++){
  		for(int k= 0;k < P; k++) {
  			cout << v[j][k] << " "<< v2[j][k].low << " " << v2[j][k].high << endl;
  		}
  	}
  	int result = 0;
  	bool condition = true;
	for(int k = 0; k < P; k++) {
  		int low = v2[0][k].low;
  		int high = v2[0][k].high;
	  	for(int j = 0; j < N; j++) {
	  		// cout << v[j][k] << " " << low << " " << high << endl;
  			if(v2[j][k].low > high || v2[j][k].high < low || v2[j][k].low == INT_MAX) {
  				condition = false;
  				break;
  			}
  			// low = max(v2[j][k].low, low);
  			// high = min(v2[j][k].high, high);
  		}
  		// cout << endl;
  		if(!condition) break;
  		result++;
  	}



    cout << "Case #" << i << ": "<< result << endl;
  	// for(auto s: v) cout << s << endl;
  		// cout<<endl;
  	// for(auto s: e) cout << s << endl;
  }


  return 0;
}