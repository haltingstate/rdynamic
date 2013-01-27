#include "polygon.hpp"
#include <math.h>

/*
	Example of a Class that wil be exported by module
*/

#include <iostream>

extern "C" void hello() 
{
    std::cout << "hello" << '\n';
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
