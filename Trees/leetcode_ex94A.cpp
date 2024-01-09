#include <vector>
using namespace std;
 //Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

/*

* Solution using recursion. 

class Solution {
private:  
    void inTraversal(TreeNode* current_node, vector<int>& result) 
    { 
    if (current_node)
        {
        inTraversal(current_node->left, result);
        result.push_back(current_node->val);    
        inTraversal(current_node->right, result);
        }
    }   
public:

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result{};
        inTraversal(root, result);        
        return result;       
    }
};
*/
// Solution using stack and while.
#include <stack>
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result{};
        if(root)
        {
            stack<TreeNode*> s{};
            TreeNode* current_node{root};
            while(true)
            {
                while(current_node){
                    s.push(current_node);
                    current_node = current_node->left;
                }
                if (s.empty()) {return result;}
                current_node = s.top();
                s.pop();  
                result.push_back(current_node->val);
                current_node = current_node->right;
            }
        }
        return result;       
    }

};