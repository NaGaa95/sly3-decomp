// Sly 2 counterpart: topThread (decomp src/lib/topThread.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char mode; unsigned char data; } TopReq;
typedef struct { int count; int pad; TopReq req[512]; } TopArg;
extern int D_004C92C0;
extern char D_0032A7A0[];
int func_002936E0(int);
int func_002935D0(int);
int func_00293550(int);
int func_00293610(int);
int func_00295660(const char *, ...);
void func_00293F30(TopArg *ta)
{
    int idx;
    while (1) {
        func_002936E0(D_004C92C0);
        idx = ta->count & 0x1FF;
        ta->count = idx + 1;
        switch (ta->req[idx].mode) {
        case 0:
            func_002935D0(ta->req[idx].data);
            break;
        case 1:
            func_00293550(ta->req[idx].data);
            break;
        case 2:
            func_00293610(ta->req[idx].data);
            break;
        default:
            func_00295660(D_0032A7A0);
            break;
        }
    }
}
