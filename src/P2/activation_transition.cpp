// Sly3 activation transition, recovered from the original and Sly2 algorithm.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "activation_selector_api.h"

typedef struct { short delta; short padding; void *function; } VTE;
struct SO { char pad0[0xC]; VTE *vt; };
struct SUB { char pad[0x68]; int flag68; };
struct GS { char pad[0x4044]; SUB *child4044; };
struct REQUEST { void *owner; int word4; unsigned int word8; };
struct OBJ {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x134 - 0x10];
    void *owner134;
    char pad138[0x190 - 0x138];
    int state190;
    void *observer194;
    void *token198;
    char pad19C[0x24C - 0x19C];
    REQUEST request24C;
};
typedef char CheckVtableEntry[(sizeof(VTE) == 8) ? 1 : -1];
typedef char CheckRequest[(sizeof(REQUEST) == 12) ? 1 : -1];
typedef char CheckUsedObjectPrefix[(sizeof(OBJ) == 0x258) ? 1 : -1];
typedef char CheckSubobjectPrefix[(sizeof(SUB) == 0x6C) ? 1 : -1];
typedef char CheckGameContextPrefix[(sizeof(GS) == 0x4048) ? 1 : -1];
extern "C" {
extern GS D_00475480;
extern int D_004798A8;
extern char D_0036C700[];
void func_00187040(SUB *);
int func_0017E208(GS *, int, int, void *owner, int, SO **);
void func_00155F28(SO *);
void func_00156768(SO *, int);
void func_001734E0(void);
int func_00185700(void *, unsigned int);
int func_00239A78(void *, int);
int func_00239B80(void *, int);
void func_00213728(OBJ *, int);
}
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].function)((char *)(o) + (o)->vt[n].delta)
#define MSG(o, event) ((void (*)(void *, int, int, int, void **, int))(o)->vt[3].function)((char *)(o) + (o)->vt[3].delta, event, 0, 0, 0, 0)
extern "C" void func_00213418(OBJ *p, int state)
{
    if (p->state190 == state)
        return;
    if (p->state190 == 1) {
        D_004798A8 = 0x1A8;
        func_0023AAE8(0, p, -1, 0, &p->token198);
        MSG(p, 6);
    }
    p->state190 = state;
    if (state == 1) {
        SO *first[16];
        SO *second[32];
        SO *third[32];
        int count;
        int index;
        if (D_00475480.child4044 && !D_00475480.child4044->flag68)
            func_00187040(D_00475480.child4044);
        count = func_0017E208(&D_00475480, 5, 0x33, 0, 16, first);
        for (int i = 0; i < count; i++) {
            SO *so = first[i];
            func_00155F28(so);
            func_00156768(so, 1);
        }
        func_001734E0();
        count = func_0017E208(&D_00475480, 0x105, 0x71, 0, 32, second);
        for (int i = 0; i < count; i++)
            ((void (*)(void *, int))second[i]->vt[80].function)((char *)second[i] + second[i]->vt[80].delta, 4);
        count = func_0017E208(&D_00475480, 0x105, 0x59, 0, 32, third);
        for (int i = 0; i < count; i++)
            VCALL(third[i], 9);
        if (p->observer194) {
            int candidate = func_00185700(D_0036C700, 0);
            if (func_00239A78(p->observer194, candidate) == -1)
                index = func_00239B80(p->observer194, 0);
            else
                index = candidate;
        } else {
            index = -1;
        }
        func_0023AAE8(p->observer194, p, index, 0, &p->token198);
        func_00213728(p, 0);
        func_001A99D0(&p->request24C, p->owner134);
        MSG(p, 5);
    }
}
