#ifndef _UTILS_H
#define _UTILS_H

#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)
#else
    #define debug (...)
#endif

#endif