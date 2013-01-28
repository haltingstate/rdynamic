#include "polygon.hpp"
#include <math.h>
#include <stdio.h>

#include "external_test.hpp"

/*
	Example of function that wil be exported by module
*/

extern "C" void hello() 
{
//    std::cout << "hello" << '\n';
	printf("hello \n");

	printf("EXTERN= %d \n", test_var);
}


/*
	Example of class that will be exported by module
*/

class triangle : public polygon 
{
	public:
    
    virtual double area() const 
    {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};

// the class factories
extern "C" polygon* create() 
{
    return new triangle;
}

extern "C" void destroy(polygon* p) 
{
    delete p;
}
