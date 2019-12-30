#ifndef _UTILS_H
#define _UTILS_H

#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)
#else
    #define debug (...)
#endif

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#endif