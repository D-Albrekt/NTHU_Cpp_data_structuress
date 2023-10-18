#include <iostream>
class Chain;

class ChainNode
{
public:
friend Chain;
    ChainNode(int data = 0, ChainNode* next = nullptr)
    : data{data}, next{next}
    {}

    int data;
    ChainNode* next;
};

class Chain
{
private: 
public:  
    Chain()
    : first{nullptr}
    {}
    ~Chain()
    {
        if(first != nullptr)
        {
            ChainNode* temp{};
            while (first != nullptr)
            {
                temp = first;
                first = first->next;
                delete temp;

            }
        }
    }
    int length()
    {
        if (first != nullptr) 
        {
            int i = 1;
            ChainNode* temp{first};
            while (temp->next != nullptr)
            {
                temp = temp->next;
                i++;
            }
            return i;
        }
        else
        {
            return 0;
        }
    }

    ChainNode* push(int data)
    {
        if (first!= nullptr)
        {
            ChainNode* temp{first};
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new ChainNode{data, nullptr};
            return temp->next;
        }
        else
        {
            first = new ChainNode{data, nullptr};
            return first;
        }
    }
    void print()
    {
        ChainNode* temp{first};
        while (temp != nullptr)
        {
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
        std:: cout << std::endl;
    }
    void delete_element_x(ChainNode* x)
    {
        ChainNode* temp{first};
        if (x != first)
        {
            while (temp->next != x || temp->next == nullptr)
            {
                temp = temp->next;
            }
        temp->next = temp->next->next;
        delete x;
        }
        else
        {
            first = first->next;
            delete x;
        }
    }
    void delete_odd()
    {
        if(first != nullptr)
        {
            ChainNode* deleter{first};
            first = first->next;
            delete deleter;
            if (first->next != nullptr)
            {
                ChainNode* set_new_next{first};
                while(set_new_next != nullptr)
                {
                    deleter = set_new_next->next;
                    if(deleter != nullptr)
                    {
                        set_new_next->next = deleter->next;
                        set_new_next = deleter->next;
                        delete deleter;
                    }
                    else
                    {
                        set_new_next = nullptr;
                    }
                }
            }
        } 
    }
private:
    ChainNode* first;
};

int main()
{
    std::cout << "Hello exercise one world" << std::endl;
    Chain my_chain{};
    std::cout << "the chain is " << my_chain.length() << " element long" << std::endl;
    ChainNode* first_element = my_chain.push(1);
    ChainNode* second_element = my_chain.push(2);
    for (int i = 3; i <= 11; i++)
    {
        my_chain.push(i);
    }
    std::cout << "the chain is " << my_chain.length() << " element long" << std::endl;
    my_chain.print();
    my_chain.delete_element_x(second_element);
    my_chain.print();
    my_chain.delete_element_x(first_element);
    my_chain.print();

    my_chain.delete_odd();
    my_chain.print();
    Chain my_other_chain{};
    for (int i = 0; i <= 11; i++)
    {
        my_other_chain.push(i);
    }
    my_other_chain.print();
    my_other_chain.delete_odd();
    my_other_chain.print();

    
    return 0;
}