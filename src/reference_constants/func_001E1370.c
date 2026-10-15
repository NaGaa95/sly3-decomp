// Reference algorithm: src/hand/func_001B8988.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct T { char pad[8]; float x1C; } T;
typedef struct P {
    char pad0[0x134];
    T *x150;
    char pad154[0x113C - 0x138];
    void *x1030;
    char pad1034[0x1890 - 0x1140];
    int x1810;
    char pad1814[0x181C - 0x1814];
    int x181C;
} P;
int func_00138AC8(void *p);
void func_001DE690(P *p, int s);
int func_001E0DF8(P *p);
#include "input_query_api.h"
void func_001E1018(P *p, int k);
int func_001DF888(P *p);
void func_001E1320(P *p);

void func_001E1370(P *p)
{
    int s;
    for (;;) {
        s = p->x1810;
        if (!p->x1030 || func_00138AC8(p->x1030)) {
            func_001DE690(p, 0);
        } else {
            switch (p->x1810) {
            case 0:
            case 1:
                if (func_001E0DF8(p) && func_001A7A80(p->x150, 0x80, 0.25f)) {
                    func_001E1018(p, p->x1810 == 0);
                } else if (!func_001E0DF8(p) || !func_001DF888(p)) {
                    if (p->x181C && 0.0f < p->x150->x1C) func_001E1320(p);
                }
                break;
            case 2:
            case 3:
                if (func_001E0DF8(p) && func_001A7A80(p->x150, 0x10, 0.25f)) {
                    func_001E1018(p, (p->x1810 == 2) ? 3 : 2);
                } else if (!func_001E0DF8(p) || !func_001DF888(p)) {
                    if (p->x181C && 0.0f < p->x150->x1C) func_001E1320(p);
                }
                break;
            }
        }
        if (p->x1810 == s || p->x1810 == -1) break;
    }
}
