#include <iostream>
#include <string>
#include <stack>

using namespace std;

class BTS
{
public:
BTS(): root{nullptr} {}
void insert(int x)
{
    if (root)
    {
        //Search for the element x
        Node* temp_node{root};
        while (temp_node)
        {
            if (x == temp_node->key)
            {
                temp_node = nullptr;
            }
            else if(x < temp_node->key)
            {
                if (!(temp_node->left_child))
                {
                    temp_node->left_child = new Node{x, nullptr, nullptr};
                    temp_node = nullptr;
                }
                else {temp_node = temp_node->left_child;}
            }
            else if(x > temp_node->key)
            {
                if (!(temp_node->right_child))
                {
                    temp_node->right_child = new Node{x, nullptr, nullptr};
                    temp_node = nullptr;
                }
                else {temp_node = temp_node->right_child;}
            }
        }

    }
    else
    {
        root = new Node{x, nullptr, nullptr};
    }

}


int size(int x)
{
    Node* temp{root};
    int size{-1};
    while (temp)
    {
        if (x < temp->key)
        {
            temp = temp->left_child;
        }
        else if(x > temp->key)
        {
            temp = temp->right_child;
        }
        else
        {
            size = 0;
            break;
        }
    }
    stack<Node*> s{};
    while (true)
    {
        while (temp)
        {
            s.push(temp);
            temp = temp->left_child;
        }
        if (s.empty()){break;}
        temp = s.top();
        s.pop();
        size++;
        temp = temp->right_child;
    }
    return size;

}

private:
struct Node
{
    Node(int x, Node* lhs, Node* rhs): key{x}, left_child{lhs}, right_child{rhs} {}
    int key;
    Node* left_child;
    Node* right_child;
};

Node* root;
};

int main()
{
    BTS tree{};
    string dummy{};
    int x;
    while(cin >> dummy){
    cin >> x;    
    if (dummy == "Insert")
    {
        tree.insert(x);
    }
    if (dummy == "Size")
    {
        cout << tree.size(x) << endl;
    }
    }
    return 0;
}