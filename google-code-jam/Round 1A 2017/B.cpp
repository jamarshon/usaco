#include <iostream>
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
        double up = 1.1f*R[j];
        double down = 0.9f*R[j];
        up = (double)v[j][k]/up;
        down = (double)v[j][k]/down;

        int low = ceil(up);
        int high = floor(down);

        if(double(v[j][k])/(low*R[j]) < 0.9 || double(v[j][k])/(low*R[j]) > 1.1){
    			v2[j][k] = {INT_MAX, INT_MAX};
        } else if(double(v[j][k])/(high*R[j]) < 0.9 || double(v[j][k])/(high*R[j]) > 1.1) {
    			v2[j][k] = {INT_MAX, INT_MAX};
        } else {
    			v2[j][k] = {low, high};
        }
      }
    }

    for(int j = 0; j < N; j++) {
      sort(v2[j].begin(), v2[j].end(), [](Range a, Range b){ 
        if(a.low != b.low) return a.low < b.low;
        return a.high < b.high;
      });
    }

    int result = 0;
    bool condition = true;
    int indices[N];

    for(int j = 0; j < N; j++) indices[j] = 0;

    int maxIndex = 0;

  	while(maxIndex < P) {
  		int low = v2[0][indices[0]].low;
  		int high = v2[0][indices[0]].high;
  		bool foundIntersection = true;

  		// Loop through all ingredients and see if all of them of intersect
  		for(int j = 0; j < N; j++) {
  			int currentLow = v2[j][indices[j]].low;
  			int currentHigh = v2[j][indices[j]].high;
  			if(currentLow == INT_MAX) {
  				condition = false;
  				break;
  			}

  			// non intersection
  			if(currentLow > high || currentHigh < low) {
    			foundIntersection = false;
    			break;
  			}

  			low = max(currentLow, low);
  			high = min(currentHigh, high);
  		}
  		
      if(!condition) break;

  		if(!foundIntersection) {
  			// remove the least useful range (the one with the smallest upper limit
  			int smallestUpperLimit = INT_MAX;
  			int smallestLimitIndex = -1;
  			for(int j = 0; j < N; j++) {
          if(v2[j][indices[j]].high < smallestUpperLimit) {
            smallestLimitIndex = j;
            smallestUpperLimit = v2[j][indices[j]].high;
          }
  		  }

  			indices[smallestLimitIndex]++;
  		} else {
  			for(int j = 0; j < N; j++) {
  			  indices[j]++;
  			  maxIndex = max(maxIndex, indices[j]);
  			}
  			result++;
  		}
  	}

		cout << "Case #" << i << ": "<< result << endl;
	}

  return 0;
}