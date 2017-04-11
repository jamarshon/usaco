#include <iostream>

using namespace std;

string getTidyNumber(string s) {
	int len = s.size();
	int minIndex = -1;
	char adjacentMinVal;

	for(int i = 1; i < len; i++) {
		if(s[i] - '0' < s[i-1] - '0') {
			minIndex = i;
			adjacentMinVal = s[i-1];
			break;
		}
	}

	if(minIndex == -1) return s;

	int maxIndex = minIndex - 1;
	while(maxIndex >= 0 && s[maxIndex] == adjacentMinVal) maxIndex--;
	maxIndex++;

	s[maxIndex] = s[maxIndex] == '0' ? '9': s[maxIndex] - 1;
	for(int i = maxIndex + 1; i < len; i++) {
		s[i] = '9';
	}
	int indFirstNonZero = s.find_first_not_of('0');
	s.erase(0, min(indFirstNonZero, len-1));
	
	return s;
}

int main() {
  int T;
  string N;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> N;
    cout << "Case #" << i << ": " << getTidyNumber(N) << endl;
  }
  return 0;
}