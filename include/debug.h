#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <errno.h>
#include <stdio.h>

#define handle_error(msg) \
        do { perror(msg); return -1; } while (0)

#define handle_error_exit(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error_return(msg, return_value)\
        do { errno = return_value; perror(msg); return return_value; } while (0)

#endif //_DEBUG_H_
