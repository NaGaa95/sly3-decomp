// SLY3_CFLAGS: -Os -G0
#include "card_commands.h"

struct CardFormatView {
    int port, slot;
    unsigned char opaque08[4];
    int state;
    unsigned char opaque10[0x13960 - 0x10];
    unsigned char commandContext[1];
};
extern char D_003751D0[];
int func_002A2E40(int port, int slot);
void func_001D0D30(void *menu, int selection);

int func_001CF710(void *save)
{
    struct CardFormatView *context = save;
    void *commandContext = context->commandContext;
    int result = func_001CEFC8(commandContext,
        func_002A2E40(context->port, context->slot), 16, 0);
    if (result) {
        context->state = 2;
        func_001D0D30(D_003751D0, 3);
    } else {
        context->state = 3;
    }
    return result;
}

struct PMF { short delta, pad; int (*pfn)(void *); };
struct S { int x0, x4; struct PMF pmf; int x10; };
typedef struct { char ab[0x6808]; } BIG;
typedef struct {
    short ch;
    signed char x2;
    unsigned char x3;
    unsigned short x4, iChild, iSibling;
} ENT;
typedef struct { int c; ENT *ae; char ht[1]; } OBJ;
struct SaveDispatchView {
    unsigned char opaque00[0x13950];
    BIG *selectedBlock;
    unsigned char opaque13954[12];
    struct S worker;
};
typedef char MethodSizeIsEight[(sizeof(struct PMF) == 8) ? 1 : -1];
typedef char WorkerSizeIsTwenty[(sizeof(struct S) == 20) ? 1 : -1];
extern const struct PMF D_00323AD8, D_00323AE0;
extern char D_004793C8[];
int func_001CFDF8(void *save);
void func_0018AD58(void);
void func_0021C718(OBJ *records, BIG *block);
void func_001CEEC0(struct S *worker, struct PMF method);

void func_001CFD18(void *save)
{
    struct SaveDispatchView *context = save;
    if (!func_001CFDF8(save)) {
        func_0018AD58();
        func_0021C718((OBJ *)D_004793C8, context->selectedBlock);
        func_001CEEC0(&context->worker, D_00323AD8);
    }
}

void func_001CFD80(void *save)
{
    struct SaveDispatchView *context = save;
    if (!func_001CFDF8(save)) {
        func_0018AD58();
        func_0021C718((OBJ *)D_004793C8, context->selectedBlock);
        func_001CEEC0(&context->worker, D_00323AE0);
    }
}
