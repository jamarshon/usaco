/*
Start 7:06

Algorithm:
+ Got null serialization immediately, explained it clearly

Coding:
Start 7:07
+ Wrote serialize() in 4 minutes
+ Methodical about how the recursion should work
+ Code is clean, concise and easy to read
+ Wrote a test case without being prompted, wanted to do other test cases
Finished serialize 7:13
+ Saw that for deserialize, we have to "consume" pieces of the serialization and pass around the progress of the consumption to recursive steps.
+ Can step through code
+ Reasoned about different cases of the code correctly
+ Fixed bug with find() and with substr - took a bit of time with substr
End: 7:35
+ Complexity: time: linear for both, space: asked about if we include stack, O(height(tree)) for both
7:38

Follow ups:
What if we have strings instead of integers?
+ Can't use nulls or commas, since strings might have them.
-/+ "wrap" commas - gave away escaping
What if we have byte arrays?
+ Convert to binary representation in Ascii

End: 7:47



Write a function to serialize a binary tree of integers to a string. Write a second function to deserialize the string back to a binary tree with the same values and structure. You can choose any format for the string.

Example input:
  1
 / \
2   3

string serialized = serialize(node);
Node node2 = dserialize(serialized);

preorder o(n) for both operations
null nodes

serialize(1)
"1,2,null,null,3,null,null"
  1
2      3
null, null

TreeNode("a",b")
a","b
"a","b"

char[]

0010101 -> 21

0010101,0010100,0010111,1010101
[0010101,0010100,0010111,1010101], null, null

"asd\"sdf" -> asd"sdf
"asdf\\\"asd" -> asdf\"asd
*/

#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left, *right;
  TreeNode(int _val): val(_val), left(NULL), right(NULL) {}
};

class SerializeTree {
  void serializeHelper(TreeNode* root, string& res) {
    if(!res.empty()) res += ",";
    if(root == NULL) {
      res += "null";
    } else {
      res += to_string(root -> val);
      serializeHelper(root -> left, res);
      serializeHelper(root -> right, res);
    }
  }
  
  TreeNode* deserializeHelper(string s, size_t& idx) {
    size_t comma_ind = s.find(",", idx);
    
    if(comma_ind == string::npos) return NULL;
    
    string root_str = s.substr(idx, comma_ind - idx);
    TreeNode* root = NULL;
    
    
    idx = comma_ind + 1;
    if(root_str != "null") {
      root = new TreeNode(stoi(root_str));
      root -> left = deserializeHelper(s, idx);
      root -> right = deserializeHelper(s, idx);
    }
    
    return root;
  }
public:
  string serialize(TreeNode* root) {
    string res;
    serializeHelper(root, res);
    return res;
  }
  
  TreeNode* deserialize(const string& s) {
    size_t idx = 0;
    return deserializeHelper(s, idx);
  }
};

int main() {
  SerializeTree st;
  TreeNode* a = new TreeNode(1);
  a -> left = new TreeNode(2);
  a -> right = new TreeNode(3);
  a -> right -> right = new TreeNode(4);
  string output = st.serialize(a);
  cout << output << endl;
  TreeNode* output2 = st.deserialize(output);
  string output2_ser = st.serialize(output2);
  cout << output2_ser << endl;
  return 0;
}