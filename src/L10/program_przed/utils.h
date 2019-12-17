#ifndef _UTILS_H
#define _UTILS_H

#ifdef DEBUG
    #define debug(...) fprintf(stdout, __VA_ARGS__)
#else
    #define debug(...) 
#endif

#endif