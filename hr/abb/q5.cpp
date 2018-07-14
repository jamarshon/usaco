/*
Hopping Jack
Find the maximum step number that Jumping Jack can reach.

Jumping Jack is standing at the bottom of a flight of stairs at step number 0, and each subsequent 
step up the staircase is numbered sequentially from 1 to infinity. Jack performs n consecutively 
numbered actions; for example, if n = 3, then Jack will perform three actions, numbered 
1, 2, and 3, in order. For each action i, Jack can choose to either jump exactly i steps 
or remain at his current step. This means that if Jack is standing on step j at the time of 
action i, he may either stay on step j or jump to step j + i.

Complete the maxStep function in the editor below. It has two parameters:
    An integer, n, denoting the number of actions Jack must take.
    An integer, k, denoting the step number Jack must not land on.


The function must return an integer denoting the maximum step number Jack can reach 
from step 0 if he performs exactly n actions and never jumps on step k (though he may jump over it).

Input Format

Locked stub code in the editor reads the following input from stdin and passes it to the function:

The first line contains an integer, n, denoting the number of actions Jack must take.

The second line contains an integer, k, denoting the step number Jack must not land on.

Constraints
    1 ≤ n ≤ 2 × 10^3
    1 ≤ k ≤ 4 × 10^6

Output Format

The function must return an integer denoting the maximal step number Jack can reach. 
This is printed to stdout by locked stub code in the editor.

Sample Input 0
2
2

Sample Output 0

3

Explanation 0

Jack performs the following sequence of n = 2 actions:
    Jack jumps from step 0 to step 0 + 1 = 1.
    Jack jumps from step 1 to step 1 + 2 = 3; observe that he avoided step k = 2 by jumping over it.

Sample Input 1
2
1

Sample Output 1
2

Explanation 1
Jack performs the following sequence of n = 2 actions:
    Jack cannot jump onto step 1 (because k = 1 and he can only jump 1 step during his first action), 
    so he stays on step 0.
    Jack jumps from step 0 to step 0 + 2 = 2.

Sample Input 2
3
3

Sample Output 2
5

Explanation 2
Jack must skip some jump, because performing one jump during each step will land 
him on step k = 3 on the second jump. There are two ways for him to perform all n = 3 actions:

    For the first action, jump 1 unit to step 0 + 1 = 1. For the second action, remain at step 1. For 
    the third action, jump 3 units to step 1 + 3 = 4. In other words, his sequence of actions is 
    0 → 1 → 1 → 4.
    For the first action, remain at step 0. For the second action, jump 2 units to step 0 + 2 = 2. 
    For the third action, jump 3 units to step 2 + 3 = 5. In other words, his sequence of actions 
    is 0 → 0 → 2 → 5.

Because we want the maximal step number that Jack can reach by performing any sequence of 
possible actions, we return 5 as our answer.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define v vector
#define uos unordered_set
#define uom unordered_map

int isSquare(int k) {
    int base = round(sqrt(8*k+1));
    return base*base == 8*k+1;
}

int rootWithinBounds(int n, int k) {
    int base = round(sqrt(8*k+1));
    int root1 = (-1+base)/2;
    int root2 = (-1-base)/2;
    return 0 <= root1 <= n || 0 <= root2 <= n;
}

// the actual solution check rootWithinBounds 
int maxStep(int n, int k) {
    return isSquare(k) ? n * (n + 1) / 2 - 1 : n * (n + 1) / 2;;
}

int maxStepTrue(int n, int k) {
    bool test = false;
    for (int i = 0; i <= k; i++) {
        if (i * (i + 1) / 2 == k) {
            test = true;
        }
    }
    return test ? n * (n + 1) / 2 - 1 : n * (n + 1) / 2;;
}

// sum to 2000 or n*(n+1)/2
#define MX (2001001)
int dp[MX];
int maxStep0(int n, int k) {
    fill(dp, dp+MX, -1);
    int res = 0;
    dp[0] = 0;
    int rem = 1; // count of non zeros from [i,end)
    for(int i = 0; i < MX; i++) {
        if(rem == 0) break;
        if(dp[i] == -1) continue;
        res = i;
        for(int j = dp[i] + 1; j <= n; j++) {
            if(i + j == k) continue;
            if(dp[i+j] == -1) {
                rem++;
                dp[i+j] = j;
            } else {
                dp[i+j] = min(dp[i+j], j);
            }
        }
        rem--;
    }

    return res;
}

// timeout
int f(int x, int step, int n, int k) {
    if(step == n + 1) return x;
    if(x == k) return -1;
    if(x > k) {
        return x + n*(n+1)/2 - (step-1)*step/2;
    }
    return max(f(x, step + 1, n, k), f(x + step, step + 1, n, k)); 
}

int maxStep1(int n, int k) {
    return f(0,1,n,k);
}

// timeout
int maxStep2(int n, int k) {
    vector<int> prev{0};
    int res = 0;
    for(int i = 1; i <= n; i++) {
        vector<int> temp;
        for(auto e: prev) {
            int new_item = e + i;
            res = max(res, new_item);
            if(new_item == k) {
                temp.push_back(e);
            } else if(new_item > k) {
                res = max(res, new_item + n*(n+1)/2 - i*(i+1)/2);
            } else {
                temp.push_back(e);
                temp.push_back(new_item);
            }
        }
        prev = temp;
    }

    return res;
}

// timeout sorting
int maxStep3(int n, int k) {
    map<int,int> m{{0,0}};
    int res = 0;

    for(auto it = m.begin(); it != m.end(); ++it) {
        auto p = *it; 
        
        res = p.first;

        for(int j = p.second + 1; j <= n; j++) {
            int jump_to = p.first + j;
            if(jump_to == k) continue;
            if(m.count(jump_to)) {
                m[jump_to] = min(m[jump_to], j);
            } else {
                m[jump_to] = j;
            }
        }

    }

    return res;
}


int main() {
    cout << maxStep(2,2) << ' ' << 3 << endl;
    cout << endl;
    cout << maxStep(2,1) << ' ' << 2 << endl;
    cout << endl;
    cout << maxStep(3,3) << ' ' << 5 << endl;

    cout << maxStep(1,3) << ' ' << maxStep0(1,3) << endl;
    for(int i = 1; i <= 2e3; i++) {
        for(int j = 1; j <= 4e6; j++) {
            int a = maxStep(i,j);
            int b = maxStepTrue(i,j);
            if(a != b) {
                cout << "i=" << i << ' ' << j << endl;
                cout << "a=" << a << ' ' << b << endl;
                assert(false);
            }
            return 0;
        }
    }
    // for(auto kv: dp) {
        // cout << kv.first.first << ' ' << kv.first.second << ' ' << kv.second << endl;
    // }
    // cout << endl;
    return 0;
}