#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  int T, N;
  cin >> T; 
  for (int i = 1; i <= T; i++) {
    cin >> N;

    int arr[N+1];
    arr[0] = -1;
    for (int j = 1; j <= N; j++) {
        cin >> arr[j];
        }

        // first is elem, second is cycle ended on, third is path length
        unordered_map<int, pair<int, unordered_set<int>>> m;
        for(int j = 1; j <= N; j++) {
            int currentNode = j;

            unordered_set<int> s{currentNode};

            while(s.find(arr[currentNode]) == s.end()) {
                currentNode = arr[currentNode];
                s.insert(currentNode);
            }

            m[j] = make_pair(currentNode, s);
        }

        int maxPath = -1;
        for(int j = 1; j <= N; j++) {
            int cycleEnded = m[j].first;
            int currentPath = m[j].second.size();
            // Matching nodes so take the max of cycleEnded neighbors
            if(arr[arr[cycleEnded]] == cycleEnded) {
                int extention = 0;
                for(auto it: m) {
                    pair<int, unordered_set<int>> elem = it.second;
                    if(elem.first == arr[cycleEnded]) {
                        if(elem.second.size() > extention) {
                            extention = elem.second.size();
                        }
                    }
                }
                cout << j << "e " << extention << endl;
                currentPath += extention - 2;
            }
            maxPath = max(maxPath, currentPath);
        }
        for(auto it: m) {
            cout << it.first << " " << it.second.first << " " << it.second.second.size() << endl;
        }
    cout << "Case #" << i << ": " << maxPath << endl;
  }


  return 0;
}