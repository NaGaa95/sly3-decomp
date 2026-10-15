#ifndef SLY3_COMMON_H
#define SLY3_COMMON_H
/* EE GCC baseline types. Confirm layouts and calling conventions per object. */
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong; /* 64 bits under the original EE compiler */
typedef int qword __attribute__((mode(TI)));
#ifndef NULL
#define NULL 0
#endif
#endif
