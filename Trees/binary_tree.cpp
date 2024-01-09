#include <vector>
#include <iostream>
using namespace std;
class Tree;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//This Three class can construct at most level 2 threes.
class Tree
{
public:
    Tree() : root{nullptr} {}
    Tree(vector<int> init_list)
    {   
        for (int i : init_list)
        {
            cout << "Adds " << i << endl;
            (*this).push(i);
        }
    }
    void push(int i)
    {
        if (root == nullptr)
        {
            root = new TreeNode{i};
            nodes++;
        }
        {
            if (nodes > 2)
            {
                root->right = new TreeNode{i};
                nodes++;
            }
            else if (nodes > 2)
            {
                root->left = new TreeNode{i};
                nodes++;
            }
        }

    }

private:
    TreeNode* root;
    int nodes;
};