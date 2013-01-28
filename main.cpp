#include "polygon.hpp"
//#include <iostream>
#include <dlfcn.h>

#include <stdio.h>

#define BUILDING_DLL

void* load_library(const char* library_so_path)
{
	
    // load the triangle library
    void* dll_ptr = dlopen("./triangle.so", RTLD_LAZY);
    if (dll_ptr == NULL) 
    {
		printf("ERROR: load_dynamic_library, cannot load library %s, error= %s \n", 
		library_so_path, dlerror() );
        //cerr << "Cannot load library: " << dlerror() << '\n';
        return NULL;
    }

    // reset errors
    dlerror();
	
	return dll_ptr;
}

void* load_symbol(void* loaded_library, const char* symbol_name)
{
	dlerror(); // reset errors
	
	void* symbol_ptr = dlsym(loaded_library, symbol_name);
	const char *dlsym_error = dlerror();
	if (dlsym_error) 
	{
		printf("ERROR: load_symbol, cannot load symbol %s, error= %s \n", 
		symbol_name, dlsym_error);
		dlclose(loaded_library);
		return NULL;
	}
	
	return symbol_ptr;
}

int main() {
    //using std::cout;
    //using std::cerr;


	void* loaded_dll = load_library("./triangle.so");
	
	{
		// load the symbol (Hello Function)
		printf("Loading symbol hello...\n");
		typedef void (*hello_t)();

		dlerror(); // reset errors
		hello_t hello = (hello_t) load_symbol(loaded_dll, "hello");
		
		// call the loaded function
		printf("Calling hello...\n");
		hello();		
	}
    
	{
		

		// load the symbols (class; creation/deletion and stuff)
		
		printf("Loading class symbols\n");

		create_t* create_triangle = (create_t*) load_symbol(loaded_dll, "create");
		destroy_t* destroy_triangle = (destroy_t*) load_symbol(loaded_dll, "destroy");

		if(create_triangle == NULL || destroy_triangle == NULL)
			return 1;
		// create an instance of the class
		class polygon* poly = create_triangle();

		// use the class
		poly->set_side_length(7);
		
		printf("class_test: the area is %f \n", poly->area() );

		// destroy the class
		destroy_triangle(poly);
	}
    // unload the triangle library
    dlclose(loaded_dll);
}
