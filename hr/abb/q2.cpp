/*
#Q2  Element Present in Tree?
You are provided a binary search tree with integers.  Each node has three primary members: an Integer
(which it holds), a pointer to its left child, and a pointer to its right child. A function stub is
provided in multiple languages.  You need to complete so this function so that it will search for the
presence of a specified integer in this tree. If the element (val) is found, return 1. Otherwise return 0. 
 
Each function stub will have its prototype, and an explanation of the data types or classes involved.
The section of the program which parses the input and displays the output is complete in each language and
will not need to be modified. Your task is to complete the body of the function provided so it returns the correct output.
 
Sample Test Cases:
 
Input #1:
val: 30
 
Output #1:
1
 
Explanation:
The element 30 is present in the given tree so return 1.
 
Input #2:
val: 79
 
Output #2:
0
 
Explanation:
The element 79 is not present in the given tree so return 0.
*/

#include <iostream>

using namespace std;

struct node {
  node* left, *right;
  int val;
};

int isPresent(node* root, int val){
/*
   The structure of the node is as follows:
      class node {
         public:
             node * left, *right;
             int val;
      };
*/
    if(root == NULL) return false;
   
    if(root -> val == val) return true;
    if(root -> val < val) {
        return isPresent(root -> right, val);
    } else {
        return isPresent(root -> left, val);
    }
}

int main() {
  return 0;
}