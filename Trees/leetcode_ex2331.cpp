//My solution to leetcode 2331 exercise. 
#include "binary_tree.cpp"

using namespace std;
/*
 //Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

 */

class Solution {
public:
    bool eval(int operand,TreeNode* left, TreeNode* right)
    {
        int lhs, rhs;
        if (left->val != 1 && left->val != 0)
        {
            lhs = eval(left->val, left->left, left->right);   
        }
        else
        {
            lhs = left->val;
        }

        if (right->val != 1 && right->val != 0)
        {
            rhs = eval(right->val, right->left, right->right);   
        }
        else
        {
            rhs = right->val;
        }
        if (operand == 2)
        {
            return (lhs || rhs);
        }
        else
        {
            return (lhs && rhs);
        }
    }
    bool evaluateTree(TreeNode* root) {
        if (root->val == 1 || root->val == 0)
        {
            return root->val;
        }
        else
        {
            return eval(root->val, root->left, root->right);
        }
    }
};