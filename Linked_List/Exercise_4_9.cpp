#include <iostream>

struct Triple{int row, col, value;};
class Matrix;
class MatrixNode
{
public:
    friend Matrix;
    friend std::istream& operator>>(std::istream&,Matrix&);
private:
    MatrixNode(bool, Triple*);
    MatrixNode* down;
    MatrixNode* right;
    bool head;
    union{
        MatrixNode* next;
        Triple triple;
    };
};

int main()
{
    std::cout << "Hello. Now you shall input your sparse matrix in the "
    "following format: \n" 
    "#row, #col, #nonzelements; row, col, value; ... row, col, value." << std::endl;
    std::cin >>
    
    return 0;
}