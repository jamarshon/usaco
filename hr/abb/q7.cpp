/*
Count the number of paths through a matrix
Consider an n × m matrix named a where each cell contains either a 0 (indicating it's blocked) 
or a 1 (indicating it's empty). From any cell (i, j), you can either move one cell to the right 
or one cell down (i.e., to either cell (i, j + 1) or cell (i + 1, j)) as long as the destination 
cell is empty. Can you count all the paths from cell (0, 0) to cell (n − 1, m − 1)? Note that all 
cells visited along a path must be empty for it to be valid.

Example

There are two possible paths from cell (0, 0) to cell (1, 3) in this matrix.

Complete the function in the editor. It has one parameter: an n × m matrix, a. The function 
must return an integer denoting the total number of possible paths from cell (0, 0) to cell 
(n — 1, m — 1), modulo (109 + 7).

Input Format
    The first line contains an integer, n, denoting the number of rows in matrix a.
    The second line contains an integer, m, denoting the number of columns in matrix a.
    Each line i of the n subsequent lines contains m space-separated integers describing the 
    respective values of ai,0, ai,1, …, ai,m-1.

Constraints
    1 ≤ n, m ≤ 1000
    Each cell in matrix a contains either a 0 or a 1.


Output Format

Return an integer denoting the total number of possible paths from cell (0, 0) to cell (n — 1, m — 1), 
modulo (109 + 7).

Sample Case 0

Sample Input 0
3
4
1 1 1 1
1 1 1 1
1 1 1 1

Sample Output 0
10

Explanation 0
There are 10 possible paths from cell (0, 0) to cell (2, 3).

Thus, we return 10 as our answer.

Sample Case 1

Sample Input 1

2
2
1 1
0 1

Sample Output 1
1

Explanation 1


There is 1 possible path from cell (0, 0) to cell (1, 1).

Thus, we return 1 as our answer.
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
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

int numberOfPaths(vector < vector < int > > a) {
    int MOD = 1e9 + 7;
    if(a.empty()) return 0;
    int rows = a.size();
    int cols = a[0].size();
    vector<long long> dp(cols, 0);
    
    if(a[0][0] == 0) return 0;
    dp[0] = 1;
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(a[i][j] == 0) {
                dp[j] = 0;
            } else {
                if(j > 0) dp[j] = (dp[j] % MOD + dp[j-1] % MOD) % MOD;
            } 
        }
    }
    
    return dp.back();
}

int main() {
    return 0;
}