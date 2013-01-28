#pragma once

#ifdef BUILDING_DLL
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif
  
#define EXPORT __declspec(dllexport)

DLLEXPORT extern int test_var;
