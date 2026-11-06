// SLY3_CFLAGS: -Os -G0
// Port of Sly 2 func_00230598 (src/lib/func_00230598.c).
typedef struct { char pad[0x98]; unsigned short x98; } B;
void func_0028F068(void *, B *, int);
void func_0028F260(void *a, B *b)
{
    switch ((short)b->x98) {
    case 7: case 11: func_0028F068(a, b, 8); break;
    case 13: func_0028F068(a, b, 0xC); break;
    case 20: func_0028F068(a, b, 0x13); break;
    case 3: func_0028F068(a, b, 1); break;
    }
}
