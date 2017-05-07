#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct Pancake {
  double topArea;
  double sideArea;
};

bool operator>(const Pancake& lhs, const Pancake& rhs) {
  return lhs.sideArea > rhs.sideArea;
}

// The key is that the top surface area is always equal to just
// the bottom circle uncovered.
int main() {
  int T;
  int N, K;
  cin >> T; 
  const double pi = 3.1415926535897f;
  for (int i = 1; i <= T; i++) {
    cin >> N >> K;
    double r, h;
    Pancake R[N];
    for(int j = 0; j < N; j++) {
      cin >> r >> h;
      R[j] = {pi*r*r, 2*pi*r*h};
    }

    sort(R, R + N, [](Pancake a, Pancake b){ return a.topArea < b.topArea; });
    double heapSideArea = 0.f;
    priority_queue<Pancake, vector<Pancake>, greater<Pancake>> pancake_heap;

    for(int j = 0; j < K - 1; j++) {
      pancake_heap.push(R[j]);
      heapSideArea += R[j].sideArea;
    }
    
    double area = 0.f;

    for(int j = K - 1; j < N; j++) {
      area = max(area, heapSideArea + R[j].topArea + R[j].sideArea);
      if(!pancake_heap.empty()) {
        double currentSideArea = R[j].sideArea;
        double heapTopSideArea = pancake_heap.top().sideArea;
        if(currentSideArea > heapTopSideArea) {
          pancake_heap.pop();
          pancake_heap.push(R[j]);
          heapSideArea -= heapTopSideArea;
          heapSideArea += currentSideArea;
        }
      }
    }

    cout << "Case #" << i << ": ";
    printf("%.9f\n", area);
  }
  return 0;
}