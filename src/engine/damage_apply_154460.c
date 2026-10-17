// SLY3_CFLAGS: -Os -G0
struct CostRow { unsigned char prefix[0xC]; int cost; unsigned char rest[0x3C - 0x10]; };
extern struct CostRow D_00343098[];
extern int D_0036DBE0;
int func_001F4430(void *self);
void func_001F4438(void *self, int value);
void func_001548E8(void *self, int a, int b);
void func_00154460(void *self, int index)
{
    int cost;
    int notmode;
    if(index != -1) cost = D_00343098[index].cost;
    else cost = 0;
    notmode = (D_0036DBE0 != 2);
    if(!notmode) {
        if(index == 0x19) cost = 0x1A;
    }
    func_001F4438(self, func_001F4430(self) - cost);
    notmode = (D_0036DBE0 != 2);
    if(!notmode) {
        if(func_001F4430(self) <= 0) func_001548E8(self, 0, 0);
    }
}
