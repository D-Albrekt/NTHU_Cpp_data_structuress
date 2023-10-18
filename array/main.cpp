#include "my_array.h"
#include <iostream>

int main()
{
    My_Array arrayen{2, 2};
    arrayen.hello_world();
    arrayen.set_values(2,3,1,2,1);   
    My_Array arr2 = arrayen;

    arr2.hello_world();

    std::cout << '\n' << arr2[1] << std::endl;
    
    std::cout << '\n' << arr2[0] << std::endl;
    try
    {
        std::cout << '\n' << arr2[5] << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
