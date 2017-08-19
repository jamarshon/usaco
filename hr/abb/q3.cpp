/*
#Q3  Spiral Matrix
 
Write a function to print out a matrix in spiral order.
 
Example:
 
1,2,3
4,5,6
7,8,9
 
should be printed as 1,2,3,6,9,8,7,4,5
 
Input:
 
You will read input from STDIN and print output to STDOUT.
 
The first line of input consists of 2 numbers, separated by a comma. The first number denotes the number of
rows in the matrix, while the second number specifies the number of columns (the matrix doesn't have to be square).
 
The remaining lines specify the actual values inside of the matrix. Each line represents a row, the values
inside a separated by commas.
 
Output:
 
All values from the matrix in the spiral order (clockwise, starting from top left), separated by commas.
*/

#include <iostream>
#include <sstream>
#include <vector>
 
using namespace std;

int main() {
    int rows, cols;
    char comma;
    cin >> rows >> comma >> cols;
   
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cin >> grid[i][j];
            if(j != cols-1) cin >> comma;
        }
    }
   
    int left = 0, top = 0, right = cols - 1, bottom = rows - 1;
    vector<int> res;
    while(left <= right) {
        for(int i = left; i <= right; i++) res.push_back(grid[top][i]);
        top++;
       
        if(top > bottom) break;
        for(int i = top; i <= bottom; i++) res.push_back(grid[i][right]);
        right--;
       
        if(right < left) break;
        for(int i = right; i >= left; i--) res.push_back(grid[bottom][i]);
        bottom--;
       
        if(bottom < top) break;
        for(int i = bottom; i >= top; i--) res.push_back(grid[i][left]);
        left++;
    }
   
    int N = res.size();
    for(int i = 0; i < N; i++) {
        cout << res[i];
        if(i != N - 1) cout << ",";
    }
    return 0;
}