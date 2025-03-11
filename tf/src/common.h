#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED(...)  \
	do { 					\
		printf("%s:%d: UNIMPLEMENTED %s \n", __FILE__,__LINE__, __VA_ARGS__); \
		exit(1); \
	} while (0)

#define UNREACHABLE(...)  \
	do { 					\
		printf("%s:%d: UNREACHABLE %s \n", __FILE__,__LINE__, __VA_ARGS__); \
		exit(1); \
	} while (0)

#define UNUSED(...) \
	do {} while (0)

#define STRING(X) _STRING(X)
#define _STRING(X) #X

#endif // COMMON_H_
