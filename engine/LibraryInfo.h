#pragma once

// Generic info:
#define LIB_NAME      "Engine Dynamic Library v0.1a"  
#define LIB_VERSION   10 

#ifdef _WINDOWS // Under Windows
	#ifdef ENGINE_EXPORTS
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else // Under Linux
	#define ENGINE_API  // Dummy declaration
#endif

