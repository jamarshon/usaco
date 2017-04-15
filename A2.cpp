#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  int T, R, C;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
  	cin >> R >> C;
  	vector<string> v(R);
  	vector<string> e(R);
  	for(int j = 0; j < R; j++) {
  		cin >> v[j];
  		e[j] = v[j];
  	}

  	for(int j = 0; j < R; j++) {
  		for(int k = 0; k < C; k++) {
  			if(v[j][k] == '?') {
  				int dx = 0;
  				bool foundSolution = false;
  				while(j + dx < R && !foundSolution) {
  					if(v[j + dx][k] != '?') {
  						for(int z = 0; z <= dx; z++) {
  							v[j + z][k] = v[j + dx][k];
  						}
  						foundSolution = true;
  					}
  					dx++;
  				}
  				dx = 0;
  				while(j - dx >= 0 && !foundSolution) {
  					if(v[j - dx][k] != '?') {
  						for(int z = 0; z <= dx; z++) {
  							v[j - z][k] = v[j - dx][k];
  						}
  						foundSolution = true;
  					}
  					dx++;
  				}

  				dx = 0;
  				while(k + dx < C && !foundSolution) {
  					if(v[j][k + dx] != '?') {
  						for(int z = 0; z <= dx; z++) {
  							v[j][k + z] = v[j][k + dx];
  						}
  						foundSolution = true;
  					}
  					dx++;
  				}

  				dx = 0;
  				while(k - dx >= 0 && !foundSolution) {
  					if(v[j][k - dx]  != '?') {
  						for(int z = 0; z <= dx; z++) {
  							v[j][k - z] = v[j][k - dx];
  						}
  						foundSolution = true;
  					}
  					dx++;
  				}
  			}
  		}
  	} 

    cout << "Case #" << i << ": "<< endl;
  	for(auto s: v) cout << s << endl;
  		cout<<endl;
  	for(auto s: e) cout << s << endl;
  }


  return 0;
}