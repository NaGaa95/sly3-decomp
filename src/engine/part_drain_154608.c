// SLY3_CFLAGS: -Os -G0
struct CostRow { unsigned char prefix[0xC]; int cost; int drain; unsigned char rest[0x3C - 0x14]; };
struct SlotRecord { int id; };
extern struct CostRow D_00343098[];
extern int D_0036DBE0;
void func_001F4498(void *meter, float rate);
int func_001F4430(void *meter);
void func_001540A0(void);
void func_00154350(void *object, void *part, int flag);
void func_001548E8(void *self, int a, int b);
void func_00154608(void *self, struct SlotRecord *slot)
{
    if(slot->id != -1) {
        int notmode;
        func_001F4498(self, (float)D_00343098[slot->id].drain);
        if(func_001F4430(self) <= 0) {
            func_001540A0();
            func_00154350(self, slot, 0);
            notmode = (D_0036DBE0 != 2);
            if(!notmode) func_001548E8(self, 0, 0);
        }
    }
}
