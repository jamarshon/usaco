#include <iostream>
using namespace std;

string getLastWord(string s) {
	string retStr = string(s, 0, 1);
	for(int i = 1; i < s.size(); i++) {
		if(s[i] >= retStr[0]) {
			retStr = s[i] + retStr;
		} else {
			retStr += s[i];
		}
	}
	return retStr;
}

int main() {
  int T;
  string S;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> S;
    cout << "Case #" << i << ": " << getLastWord(S) << endl;
  }
  return 0;
}