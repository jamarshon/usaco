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
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;

bool overlap(const tii l, const tii r) {
  return !(get<0>(l) >= get<1>(r) || get<0>(r) >= get<1>(l));
}

void solve(const int S) {
  vector<tii> v;
  v.reserve(S);
  int a, b;
  for (int i = 0; i < S; i++) {
    cin >> a >> b;
    v.emplace_back(a, b, i);
  }

  sort(v.begin(), v.end());
  tii c{-1, -1, -1}, j{-1, -1, -1};

  string res(S, 'x');
  for (const auto& p : v) {
    const bool c_overlap = overlap(p, c);
    const bool j_overlap = overlap(p, j);
    cout << c_overlap << ' ' << j_overlap << endl;
    const int index = get<2>(p);
    if (c_overlap && j_overlap) {
      res = "IMPOSSIBLE";
      break;
    } else if (!c_overlap && j_overlap) {
      c = p;
      res[index] = 'C';
    } else if (c_overlap && !j_overlap) {
      j = p;
      res[index] = 'J';
    } else {
      // both dont overlap so choose the one with the largest end
      if (get<1>(c) > get<1>(p)) {
        c = p;
        res[index] = 'C';
      } else {
        j = p;
        res[index] = 'J';
      }
    }
  }
  cout << res << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int S;
    cin >> S;
    cout << "Case #" << i + 1 << ": ";
    solve(S);
  }
  return 0;
}