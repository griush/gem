/*
    made by griush
*/

#ifndef GEM_BASE_HPP
#define GEM_BASE_HPP

// Platform detection using predefined macros
#ifdef _WIN32
	#define GEM_WINDOWS
#elif defined(__linux__)
	#define GEM_LINUX
#else
	#define GEM_OTHER_PLAT
#endif // End of platform detection

namespace gem {

    typedef char                int8;
    typedef unsigned char       uint8;

    typedef int                 int32;
    typedef unsigned int        uint32;

    typedef long long           int64;
    typedef unsigned long long  uint64;

}

#endif // GEM_BASE_HPP
