#include <iostream>
#include <vector>

int main()
{
    std::cout << "Hello World" << std::endl;
    
    int x;
    
    std::vector<int> my_int_vec;
    
    while (std::cin >> x) 
    {
        std::cout << x << std::endl;
        my_int_vec.push_back(x);
    }
    
    std::cout << "NEW AGE \n\n\n\n" << std::endl;

    
    for (std::vector<int>::iterator it = std::begin(my_int_vec); it != std::end(my_int_vec); it++)
    {
        std::cout << *it << std::endl;
    }
    
    
    return 0;
}