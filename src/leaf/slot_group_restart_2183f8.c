// Restart the slots of one group: collect the idle (state 1) slots after the given one, shuffle them, then stagger their timers and targets over the group range and refresh the group.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char data00[0x10]; int state; float timer; float target; };
struct Pair { float first, second; };
struct Self {
    unsigned char pad0[0x270];
    struct Slot slots[2][6];
    int counts[2];
    unsigned char pad3C8[4];
    float step;
    unsigned char pad3D0[0x400 - 0x3D0];
    struct Pair pairA;
    unsigned char pad408[0x41C - 0x408];
    int results[2];
    unsigned char pad424[0x4F4 - 0x424];
    int type;
    unsigned char pad4F8[0x500 - 0x4F8];
    struct Pair pairB;
};
extern float D_0036BB98;
int func_0011E8F0(int low, int high);
void func_00217D50(struct Self *self, struct Slot *slot, int state, float value);
int func_00218C00(struct Self *self, int group, int arg);
void func_002183F8(struct Self *self, struct Slot *skip, int group, int arg)
{
    struct Slot *list[8];
    int count = 1;
    struct Pair *range;
    float delta, target, time;
    list[0] = skip;
    {
        int total = self->counts[group];
        int j;
        for (j = 0; j < total; j++) {
            struct Slot *slot = &self->slots[group][j];
            if (slot == skip) continue;
            if (slot->state == 1)
                list[count++] = slot;
        }
    }
    {
        int k;
        for (k = 1; k < count; k++) {
            int pick = func_0011E8F0(1, count - 1);
            struct Slot *swap = list[k];
            list[k] = *(struct Slot **)((char *)list + pick * 4);
            *(struct Slot **)((char *)list + pick * 4) = swap;
        }
    }
    range = self->type == 0x41 ? &self->pairB : &self->pairA;
    target = range->second;
    delta = (target - range->first) / (float)(count - 1);
    time = D_0036BB98;
    {
        int m;
        for (m = 0; m < count; m++) {
            struct Slot *slot = list[m];
            func_00217D50(self, slot, 2, time);
            slot->target = target;
            target -= delta;
            time += self->step;
        }
    }
    self->results[group] = func_00218C00(self, group, arg);
}
