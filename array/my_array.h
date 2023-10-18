#ifndef MY_ARRAY
#define MY_ARRAY
#include <array>
const int default_size{5};
const float default_value{-1};

class My_Array
{
public:
    My_Array(int const& size = default_size, float const& initvalue = default_value);
    ~My_Array() = default;
    float& operator[](int i);

    void hello_world();
    void set_values(int a, int b, int c, int d, int e);

private:
    int size;
    float* arr;
};

#endif


