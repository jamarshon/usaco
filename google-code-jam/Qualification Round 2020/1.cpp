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

void solve(const int N) {
  string line;
  int x;
  int trace = 0;
  unordered_map<int, unordered_set<int>> rows, cols;
  unordered_set<int> r, c;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> x;
      if (i == j) {
        trace += x;
      }

      if (rows[i].count(x)) r.insert(i);
      if (cols[j].count(x)) c.insert(j);
      rows[i].insert(x);
      cols[j].insert(x);
    }
  }
  printf("%d %d %d\n", trace, r.size(), c.size());
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int N;
    cin >> N;
    cout << "Case #" << i + 1 << ": ";
    solve(N);
  }
  return 0;
}