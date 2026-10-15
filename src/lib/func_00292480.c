// Reference: Sly 2 src/lib/atoi.c; target Sly 3 0x00292480.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
long strtol(const char *, char **, int);
int atoi(const char *s) { return (int)strtol(s, 0, 10); }
