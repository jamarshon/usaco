#include <iostream>

using namespace std;

string getTidyNumber(string s) {
	int len = s.size();
	int minIndex = -1;
	char adjacentMinVal;

	// find first occurence of s[i-1] < s[i] denote as i_min
	for(int i = 1; i < len; i++) {
		if(s[i] - '0' < s[i-1] - '0') {
			minIndex = i;
			adjacentMinVal = s[i-1];
			break;
		}
	}

	if(minIndex == -1) return s;

	// from i_min to 0, find an occurence of non s[i_min - 1] for cases like 3440
	// it would get the 4 at the index 1
	int maxIndex = minIndex - 1;
	while(maxIndex >= 0 && s[maxIndex] == adjacentMinVal) maxIndex--;
	maxIndex++;

	// decrease number by 1 and replace all numbers after it with 9
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