#include <iostream>
#include <stdexcept>
#include "my_array.h"

My_Array::My_Array(int const& size, float const& initvalue)
: size{size}
{
    arr = new float[size - 1];
    for (int i = 0; i != size; i++)
    {
        arr[i] = default_value;
    }
}

float& My_Array::operator[](int i)
{
    if (i < size && i >= 0)
    {
        return arr[i];
    }
    else
    {
        throw std::out_of_range("Index out of range"); 
    }
}

void My_Array::hello_world()
{
    std::cout << "Hello ARray-World" << std::endl;
    for (int i = 0;i < size; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void My_Array::set_values(int a, int b, int c, int d, int e)
{
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;
    arr[4] = e;
}
