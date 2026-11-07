// Sly 2 counterpart: _sceSifLoadModuleBuffer (decomp src/lib/_sceSifLoadModuleBuffer.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    void *addr;      /* 0x000 */
    int arg_len;     /* 0x004 */
    char path[0xFC]; /* 0x008 */
    char args[0xFC]; /* 0x104 */
} LoadParam;
typedef struct { int pad[10]; } ClientData;
extern LoadParam D_004CC9C0;
extern ClientData D_004CCBC0;
int func_002979F0(void);
int func_00297AF0(void);
void *func_00291E8C(void *, const void *, unsigned int);
int func_00295F08(ClientData *, int, unsigned int, void *, int, void *, int, void *, void *);
int func_00297BB8(void *addr, int args, const char *argp, int *result)
{
    if (func_002979F0() < 0) return -0x10000;
    if (func_00297AF0()) return 0xFFFEFFFC;
    D_004CC9C0.addr = addr;
    if (argp) {
        if (args > 0xFC) {
            __builtin_memcpy(D_004CC9C0.args, argp, 0xFC);
            D_004CC9C0.arg_len = 0xFC;
        } else {
            func_00291E8C(D_004CC9C0.args, argp, args);
            D_004CC9C0.arg_len = args;
        }
    } else {
        D_004CC9C0.arg_len = 0;
    }
    if (func_00295F08(&D_004CCBC0, 6, 0, &D_004CC9C0, 0x200, &D_004CC9C0, 8, 0, 0) < 0)
        return 0xFFFEFFFF;
    *result = D_004CC9C0.arg_len;
    return (int)D_004CC9C0.addr;
}

