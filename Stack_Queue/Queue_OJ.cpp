#include <iostream>
#include <string>
using namespace std;
const int MAX_SIZE = 100; // Maximum size of the stack

class Stack {
private:
    int arr[MAX_SIZE];
    int top; // Index of the top element

public:
    Stack() {
        top = -1; // Initialize the top index to -1
    }

    // Push an element onto the stack
    void push(int data) {
        if (top >= MAX_SIZE - 1) {
            std::cout << "Stack overflow! Cannot push element " << data << std::endl;
            return;
        }
        arr[++top] = data;
    }

    // Pop the top element from the stack
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Cannot pop." << std::endl;
            return;
        }
        --top;
    }

    // Peek at the top element without removing it
    int findTop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Cannot peek." << std::endl;
            return -1; // Return a sentinel value to indicate an error
        }
        return arr[top];
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }
};


bool isValid(string s) {
    Stack st; // create an empty stack to store opening brackets
    int i = 0;
    for (i = 0; s[i] != '\0'; i++) {
        char c ; 
        c = s[i]; // loop through each character in the string
        if (c == '(' || c == '{' || c == '[') { // if the character is an opening bracket
            st.push(c); // push it onto the stack
        } else { // if the character is a closing bracket
            if (st.isEmpty() || // if the stack is empty or 
                (c == ')' && st.findTop() != '(') || // the closing bracket doesn't match the corresponding opening bracket at the top of the stack
                (c == '}' && st.findTop() != '{') ||
                (c == ']' && st.findTop() != '[')) {
                return false; // the string is not valid, so return false
            }
            st.pop(); // otherwise, pop the opening bracket from the stack
        }
    }
    return st.isEmpty(); // if the stack is empty, all opening brackets have been matched with their corresponding closing brackets,
                        // so the string is valid, otherwise, there are unmatched opening brackets, so return false
};

int main() {
    char s[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;
        if (isValid(s)==true) {
            cout << "Valid" << endl;
        } else {
            cout << "Invalid" << endl;
        }

        s[0]='\0';
    }

    return 0;
}


