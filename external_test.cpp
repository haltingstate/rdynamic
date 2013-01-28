#include "external_test.hpp"

extern "C" 
{
__attribute__ ((visibility ("default"))) int test_var = 0;
}
