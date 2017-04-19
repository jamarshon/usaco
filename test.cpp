#include <iostream>
#include <vector>
using namespace std;

int main() {
  int T, R, C;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> R >> C;
    vector<string> v(R);
    for(int j = 0; j < R; j++) {
      cin >> v[j];
    }

    // from a '?' find a character in the same row that is non '?' to replace it
    for(int j = 0; j < R; j++) {
      for(int k = 0; k < C; k++) {
        if(v[j][k] == '?') {
          int dk = 0;
          bool foundLetter = false;
          char writeChar;
          while(k + dk < C && !foundLetter) {
            if(v[j][k + dk] != '?') {
              writeChar = v[j][k + dk];
              foundLetter = true;
            }
            dk++;
          }

          dk = 0;
          while(k - dk >= 0 && !foundLetter) {
            if(v[j][k - dk] != '?') {
              writeChar = v[j][k - dk];
              foundLetter = true;
            }
            dk++;
          }

          if(!foundLetter) break; // empty row
          while(k < C && v[j][k] == '?') {
            v[j][k++] = writeChar;
          }
        }
      }
    }

    // from an empty row e.g. '???' find a corresponding non-empty row above or beneath it to fill in with
    for(int j = 0; j < R; j++) {
      if(v[j][0] == '?') { // empty row
        int rowToCopy = j;
        int dj = 0;
        bool foundRow = false;
        while(j + dj < R && !foundRow) {
          if(v[j + dj][0] != '?') {
            rowToCopy = j + dj;
            foundRow = true;
          }
          dj++;
        }

        dj = 0;
        while(j - dj >= 0 && !foundRow) {
          if(v[j - dj][0] != '?') {
            rowToCopy = j - dj;
            foundRow = true;
          }
          dj++;
        }
        
        v[j] = v[rowToCopy];
      }
    }

    cout << "Case #" << i << ": "<< endl;
    for(auto s: v) cout << s << endl;
  }

  return 0;
}