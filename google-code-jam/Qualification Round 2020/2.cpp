#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(const string S) {
  int open = 0;
  string res = "";
  for (const char& c : S) {
    int x = c - '0';
    if (x > open) {
      res += string(x - open, '(');
    } else if (x < open) {
      res += string(open - x, ')');
    }
    res.push_back(c);
    open = x;
  }

  if (open > 0) res += string(open, ')');
  cout << res << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    string S;
    cin >> S;
    cout << "Case #" << i + 1 << ": ";
    solve(S);
  }
  return 0;
}