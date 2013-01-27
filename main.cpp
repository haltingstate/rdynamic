#include "polygon.hpp"
#include <iostream>
#include <dlfcn.h>

#include <stdio.h>

void* load_dynamic_library(const char* library_so_path)
{
	
    // load the triangle library
    void* triangle = dlopen("./triangle.so", RTLD_LAZY);
    if (!triangle) 
    {
		printf("ERROR: load_dynamic_library, cannot load library %s, error= %s \n", 
		library_so_path, dlerror() );
        //cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();
    	
	
}

int main() {
    using std::cout;
    using std::cerr;



	{
		// load the symbol (Hello Function)
		cout << "Loading symbol hello...\n";
		typedef void (*hello_t)();

		// reset errors
		dlerror();
		hello_t hello = (hello_t) dlsym(triangle, "hello");
		const char *dlsym_error = dlerror();
		if (dlsym_error) 
		{
			cerr << "Cannot load symbol 'hello': " << dlsym_error <<
				'\n';
			dlclose(triangle);
			return 1;
		}
		
	}
    
	{
		
		// call the loaded function
		cout << "Calling hello...\n";
		hello();
		// load the symbols (class; creation/deletion and stuff)
		
		cout << "Loading class symbols\n";

		create_t* create_triangle = (create_t*) dlsym(triangle, "create");
		const char* dlsym_error = dlerror();
		if (dlsym_error) 
		{
			cerr << "Cannot load symbol create: " << dlsym_error << '\n';
			return 1;
		}
		
		destroy_t* destroy_triangle = (destroy_t*) dlsym(triangle, "destroy");
		dlsym_error = dlerror();
		if (dlsym_error) 
		{
			cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
			return 1;
		}

		// create an instance of the class
		class polygon* poly = create_triangle();

		// use the class
		poly->set_side_length(7);
			cout << "The area is: " << poly->area() << '\n';

		// destroy the class
		destroy_triangle(poly);
	}
    // unload the triangle library
    dlclose(triangle);
}
