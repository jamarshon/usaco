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
    unordered_map<int, vector<int>> m;
    for(int j = 1; j <= N; j++) {
        int currentNode = j;

        unordered_set<int> s{currentNode};
        vector<int> v{currentNode};

        while(s.find(arr[currentNode]) == s.end()) {
            currentNode = arr[currentNode];
            s.insert(currentNode);
            v.push_back(currentNode);
        }

        m[j] = v;
    }

    int maxPath = -1;
    for(int j = 1; j <= N; j++) {
        int cycleEnded = m[j].back();
        int currentPath = m[j].size();
        // Matching nodes so take the max of cycleEnded neighbors
        bool endsOnMatchingNodes = arr[arr[cycleEnded]] == cycleEnded;
        if(endsOnMatchingNodes) {
            int extention = 0;
            for(auto it: m) {
                vector<int> path2 = it.second;
                int path2Len = (int)path2.size();
                if(path2[path2Len - 1] == arr[cycleEnded] && path2[path2Len - 2] == cycleEnded) {
                    extention = max(extention, path2Len);
                }
            }
            currentPath += extention - 2;
        }

        // cout << "here" << cycleEnded << " " << arr[m[j][0]] << endl;
        if(endsOnMatchingNodes || arr[cycleEnded] == m[j][0]) {
            maxPath = max(maxPath, currentPath);
        }
    }
    // for(auto it: m) {
    //     cout << it.first << endl;
    //     for(auto t: it.second) cout << t << " ";
    //     cout << endl;
    // }
    cout << "Case #" << i << ": " << maxPath << endl;
  }


  return 0;
}