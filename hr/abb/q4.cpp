/*
#Q4  Lego Blocks
You have 4 types of Lego™ blocks, of sizes (1 x 1 x 1), (1 x 1 x 2), (1 x 1 x 3), and (1 x 1 x 4).
Assume that you have an infinite number of blocks of each type. For brevity, we can call these types,
respectively, the 1-block, 2-block, 3-block and 4-block, or even (1), (2), (3) and (4).
 
Using these blocks, you want to make a wall of height N and width M. The wall should be a solid
continuous structure with no holes. The wall should be structurally connected, so no straight
vertical should exist that would allow the wall to be separated in two without cutting one or more bricks.
 
Input:
The first line contains the number of test cases T. T test cases follow. Each case contains two integers, N and M.
 
Output:
Output T lines, one for each test case, containing the number of ways to build the wall.
As the numbers can be very large, output the result modulo 1,000,000,007.
 
Constraints:
1 ≤ T ≤ 100
1 ≤ N,M ≤ 1000
 
Sample Input:
4
2 2
3 2
2 3
4 4
 
Sample Output:
3
7
9
3375
 
Explanation:
    For the first case, the 3 ways are:
        two 2-blocks stacked one on top of another.
        one 2-block  stacked on top of two 1-blocks.
        two 1-blocks stacked on top of one 2-block.
   
    For the second case,
        each row of the wall can contain either two blocks of width 1, or one block of width 2. However,
        the wall where all rows contain two blocks of width 1 is not a solid one as it can be divided vertically.
        Thus, the number of ways is 2 × 2 × 2 - 1 = 7.
   
    
    For the third case,
        A 3-unit course of brick can be built four ways:
            Three singles (1,1,1)
            One triple (3)
            A double before a single (2,1)
            A single before a double (1,2)
       
        Any of the four patterns above can go on top of the (3) or on bottom of the (3). Total: 8.
        If we do not use a 3, then the only other stable pattern is (2,1) on top of (1,2). Cumulative total: 9.
   
    
    For the fourth case, we have
        8 ways of building each of the four layers of bricks:
       
            1,1,1,1
            1,1,2
            1,2,1
            2,1,1
            1,1
            1,3
            3,1 
            4
       
        Total number of patterns: 8^4= 4,096
        Of these 4,096 patterns, some will fail to satisfy the structural integrity condition.
        So we need to subtract the patterns that contain a vertical split. There are 3 vertical seams
        that provide possible locations for the vertical split, and 7 ways of placing any of 1, 2 or 3
        splits among these 3 seams.
            There is exactly one way to have three splits, one on each of the three vertical seams (4 4-high towers of 1-block bricks) .  Cumulative: 4,096 - 1 = 4,095.
            If we have two splits, along the left and middle seams, then there are 
                two 1-block towers and one 4-high, 2-wide tower.
                Exactly one way to build two 4-high towers of 1-blocks
                15 ways to build the 4-high, 2-wide sub-wall:
                    (1,1) or (2)
                    
                    repeated for at any of four layers,
                    
                    minus the separable pattern where the (1,1) layer repeats 4 times.
                
                15 × 1 = 15 ways to have two splits, one along the left seam an done along the middle seam.
           
            Similarly, two splits, left and right seams:  15 ways
            And two splits, middle and right seams 15 ways
            Cumulative 4,095 - 15 - 15 - 15 = 4,050.
            If we have exactly one split down the middle, this means
           
                there are two separate non-splitting 4-high, 2-wide walls.
                Each such wall can be built 24-1=15 ways (as above).
                The count of walls that can split once down the middle is thus 15 × 15 = 225. 
                Cumulative: 4,050 - 225 = 3,825.
           
            
            Exactly one split along the leftmost seam:
            
                There is one tower of 1-bricks on the left next to a 4-high, 3-wide wall.
                The ways of building the 4-high, 3-wide wall are:
               
                    4^4 = 256 is the number of ways of repeating any of (1,1,1) or (3) or (2,1) or (1,2) four times
                    of these 256 patterns, some are separable, hence already accounted for before in the enumeration
                   
                        the three 1-block towers: one pattern
                        one two-wide, four-high tower on the right next to a 1-block tower: 15 patterns (derivation above)
                        ditto on the left: 15 patterns
                        Total: 256 - 15 - 15 - 1 = 225
           
            Ditto for a split along the rightmost seam: 225 ways
            Cumulative : 3,825 - 225 - 225 = 3,375.
*/ 
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cassert>
 
using namespace std;
 
#define MAX_N 1001
#define MOD 1000000007
#define mod(a) (a < 0 ? a + MOD : (a < MOD ? a : a % MOD))
 
typedef long long ll;
 
ll tetra[MAX_N], tetra_pow[MAX_N];
 
ll get(int i) {
    return i < 0 ? 0: tetra[i];
}
 
ll mod_add(long long a, long long b) {
    return mod(mod(a) + mod(b));
}
 
ll mod_mul(long long a, long long b) {
    return mod(mod(a) * mod(b));
}
 
ll mod_pow(ll base, ll exp) {
    ll res = 1;
    while(exp) {
        if(exp % 2 == 1) {
            res = mod_mul(res, base);
        }
        base = mod_mul(base, base);
        exp /= 2;
    }
 
    return res;
}
 
void fill_tetra() {
    tetra[0] = tetra[1] = 1;
    for(int i = 2; i < MAX_N; i++) {
        // tetra[i] = mod_add(mod_add(mod_add(get(i-1), get(i-2)), get(i-3)), get(i-4));
        tetra[i] = mod(mod_mul(get(i-1),2) - get(i-5));
    }
}
 
void fill_tetra_pow(int H, int W) {
    for(int i = 0; i <= W; i++) {
        tetra_pow[i] = mod_pow(tetra[i], H);
    }
}
 
class Solve {
public:
    ll solve(int H, int W) {
        ll dp[W+1];
 
        fill_tetra_pow(H, W);
 
        // i is the width of the current row
        // j is where to split
        // f(w,h) = tetra(w)^h - sum{k = 1 to w-1}{ f(w-k,h)*tetra(k)^h }
        // tetra(w)^h represents all possible compositions including not solid ones
        // all(w) - sum(all(x)*solid(w-k))
 
        for(int i = 0; i <= W; i++) {
            dp[i] = tetra_pow[i];
            for(int j = 1; j < i; j++) {
                //dp[i] = mod(MOD + dp[i] - mod_mul(tetra_pow[i-j], dp[j]));
                 dp[i] -= mod_mul(tetra_pow[i-j], dp[j]);
                 dp[i] = mod(dp[i]);
            }
        }
 
        return mod(dp[W]);
    }
};
 
int main() {
    Solve s;
    fill_tetra();
   
    bool test = true;
    bool should_assert = true;
    if(!test) {
        int T;
        cin >> T;
        for(int i = 0; i < T; i++) {
            int N, M;
            cin >> N >> M;
            cout << s.solve(N, M) << endl;
        }
    } else {
        cout << s.solve(2,2) << ' ' << 3 << endl;
        cout << s.solve(3,2) << ' ' << 7 << endl;
        cout << s.solve(2,3) << ' ' << 9 << endl;
        cout << s.solve(4,1) << ' ' << 1 << endl;
        cout << s.solve(4,2) << ' ' << 15 << endl;
        cout << s.solve(4,3) << ' ' << 225 << endl;
        cout << s.solve(4,4) << ' ' << 3375 << endl;
        cout << s.solve(1000,1000) << ' ' << 294143550 << endl;
 
        if(should_assert) assert(s.solve(2,2) == 3);
        if(should_assert) assert(s.solve(3,2) == 7);
        if(should_assert) assert(s.solve(2,3) == 9);
        if(should_assert) assert(s.solve(4,1) == 1);
        if(should_assert) assert(s.solve(4,2) == 15);
        if(should_assert) assert(s.solve(4,3) == 225);
        if(should_assert) assert(s.solve(4,4) == 3375);
        if(should_assert) assert(s.solve(1000,1000) == 294143550);
    }
   
    return 0;
}