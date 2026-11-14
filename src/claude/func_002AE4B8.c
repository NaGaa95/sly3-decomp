// Sly 2 counterpart: _sceMpegError1 (decomp src/lib/_sceMpegError1.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
typedef char *va_list;
int func_00295598(char *, unsigned int, const char *, va_list); void _sceMpegError(void *, const char *);
void func_002AE4B8(void *mp, const char *fmt, va_list ap) { char buf[256]; char *p = buf; func_00295598(p, 256, fmt, ap); _sceMpegError(mp, p); }
