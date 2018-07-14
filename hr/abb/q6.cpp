/*
String Similarity
For two strings A and B, we define the similarity of the strings to be the length of the longest 
prefix common to both strings.

For example, the similarity of strings abc and abd is 2, while the similarity of strings aaa and 
aaab is 3.

Calculate the sum of similarities of a string S with each of its suffixes, including the string 
itself as the first suffix.

Input Format
The first line contains the number of test cases T. Next subsequent T lines contains a string 
representing the value of string S for each test case.

Constraints

1 ≤ T ≤ 10

1  ≤ |s| ≤ 10^5

The strings contain only lowercase characters [a-z].

Output Format
Output T lines, each containing one integer that is the answer for the corresponding test case.

Sample Input 1
1
ababaa 

Sample Output 1
11

Sample Input 2
1
aa

Sample Output 2
3

Explanation

Sample Case 1:
T = 1

S = ababaa
The suffixes of the string are ababaa, babaa, abaa, baa, aa and a. The similarities of 
each of these strings with the string ababaa are 6,0,3,0,1,1 respectively.

Hence the output is 6 + 0 + 3 + 0 + 1 + 1 = 11.

Sample Case 2:

T = 1

S = aa

The Suffixes of the string are aa, a.The similarities of each of these strings with 
the string aa is 2, 1 .

Hence the output is 2 + 1 = 3.
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

#define MAXN 100001
// ceil(100001) + 1
#define MAXLG 18

/*
    s_cmp is (sort_index, sort_index + jump) 
        e.g ippi is (1,4) for mississippi as "ip" is index 1 when sort by 2 characters and 
        "pi" is index 4 when sort by 2 characters -> "ip|pi"
        -1 is when the jump is larger than the suffix
    index is i for which s.substr(i) is the suffix
*/
struct SuffixTuple {
    int s_cmp[2];
    int index;
    // sort by s_cmp[0] and break ties on s_cmp[1]
    bool operator<(const SuffixTuple& rhs) const {
        return (s_cmp[0] == rhs.s_cmp[0]) ? (s_cmp[1] < rhs.s_cmp[1]) : (s_cmp[0] < rhs.s_cmp[0]);
    }
};

/*
    After running, L[i].index for i [0,N) is the suffix s.substr(i) lexicographically ascending
    e.g 5 3 1 0 4 2 for s="banana" means smallest is s.substr(5) which is "a"
    P[last_row][i] shows the suffix s.substr(i) would appear at what order
    e.g. 3 2 5 1 4 0 means "banana" would be the 3rd ascending and "a" at index 5 would be the 0th
*/
SuffixTuple L[MAXN];
int P[MAXLG][MAXN];

int BuildSuffixArray(string s) {
    int N = s.size();

    // first row is just the order of s[i]
    for(int i = 0; i < N; i++) {
        P[0][i] = s[i] - 'a';
    }

    int last_row = 0;

    // we sort by powers of two for a runtime of O(Nlog^2N)
    for(int i = 1; (1 << (i-1)) < N; i++) {
        for(int j = 0; j < N; j++) {
            L[j].s_cmp[0] = P[i-1][j];
            L[j].s_cmp[1] = j + (1 << (i-1)) < N ? P[i-1][j + (1 << (i-1))] : -1;
            L[j].index = j;
        }

        sort(L, L + N);

        for(int j = 0; j < N; j++) {
            if(j > 0) {
                // if L[j] and L[j-1] is the same then use P[i][L[j-1].index] else use j
                bool same_with_prev = L[j].s_cmp[0] == L[j-1].s_cmp[0] && L[j].s_cmp[1] == L[j-1].s_cmp[1];
                if(same_with_prev) {
                    P[i][L[j].index] = P[i][L[j-1].index];
                    continue;
                }
            }

            P[i][L[j].index] = j;
        }

        last_row = i;
    }

    return last_row;
}

// returns the longest common prefix of s.substr(x) and s.substr(y) in lO(logN)
int LCP(int x, int y, int last_row, int N) {
    if (x == y) return N - x; // same string so it is just the length of s.substr(x)

    int res = 0;
    for(int i = last_row; x < N && y < N && i >= 0; i--) {
        // the sort index of x and y is same when the first i letters are the same
        if(P[i][x] == P[i][y]) {
            // a common prefix of length 2^i has been found
            res += 1 << i;
            x += 1 << i; 
            y += 1 << i;
        }
    }

    return res; 
}

int solve(string s) {
    int N = s.size();
    int last_row = BuildSuffixArray(s);
    int suffix_arr[N], lcp_arr[N], R[N];

    int k;
    for(int i = 0; i < N; i++) {
        suffix_arr[i] = L[i].index;
        if(suffix_arr[i] == 0) k = i;
        R[i] = 0;
    }

    // lcp array is lcp of ith suffix and i-1th suffix in the suffix array
    // lcp_arr[i] = lcp(suffix_arr[i], suffix_arr[i-1]) for i > 0
    for(int i = 1; i < N; i++) lcp_arr[i] = LCP(suffix_arr[i], suffix_arr[i-1], last_row, N);

    // R[i] is the similarity of suffix[i] with the string s
    R[k] = N; // k is the whole string so the similarity is just N

    for(int i = k - 1; i >= 0; i--) {
        // for suffix[i], there is the similarity of R[i+1] for suffix[i+1] and string s
        // and the lcp of suffix_arr[i+1] suffix_arr[i]
        // so if suffix[i] has x common with suffix[i+1] and suffix[i+1] has y common with s
        // then suffix[i] must have at most min(x,y) common with s
        R[i] = min(lcp_arr[i+1], R[i+1]); 
    }

    for(int i = k + 1; i < N; i++) {
        R[i] = min(lcp_arr[i], R[i-1]);
    }

    int res = 0;
    for(int i = 0; i < N; i++) {
        res += R[i];
    }

    return res;
}

vector < int > stringSimilarity(vector < string > inputs) {
    int T = inputs.size();
    vector<int> res(T);
    for(int i = 0; i < T; i++) {
        string input = inputs[i];
        res[i] = solve(input);
    }

    return res;
}



int main() {
    vector<string> v;
    v = {
        "ababaa", // 11
        "aa", // 3
        "abcabbca"
    };

    vector<int> t;
    t = stringSimilarity(v);
    for(int i = 0; i < t.size(); i++) cout << v[i] << ' ' << t[i] << endl;
    return 0;
}

