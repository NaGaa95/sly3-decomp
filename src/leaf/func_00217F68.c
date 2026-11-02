// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char data00[0xC]; int active; int state; float timer; float delay; };
struct Self {
    unsigned char pad0[0x198];
    int totals[2];
    int used[2];
    unsigned char pad1A0[0x1B0 - 0x1A8];
    int kind;
    unsigned char pad1B4[0x270 - 0x1B4];
    struct Slot slots[2][6];
    int counts[2];
    unsigned char pad3C8[0x408 - 0x3C8];
    int limit;
    float fraction;
};
extern float D_00325CB8;
float func_002A3510(float value);
int func_0011E8F0(int low, int high);
void func_00217D50(struct Self *self, struct Slot *slot, int state, float value);
void func_00291F38(void *dest, void *src, int bytes);

void func_00217F68(struct Self *self, int group)
{
    struct { struct Slot *others[8]; struct Slot *fours[8]; } L;
    struct Slot **next;
    int nOther = 0, nFour = 0;
    int count = self->counts[group];
    int i;
    for (i = 0; i < count; i++) {
        struct Slot *slot = &self->slots[group][i];
        if (!slot->active) continue;
        if (slot->state == 4) L.fours[nFour++] = slot;
        else L.others[nOther++] = slot;
    }
    if (nFour + nOther == count) {
        float ratio = (float)(self->totals[group] - self->used[group]) / (float)self->totals[group] / ((1.0f - self->fraction) / (float)self->limit);
        int want = (int)func_002A3510(ratio);
        int a, b, c, mode;
        if (want > self->limit) want = self->limit;
        a = want - nFour;
        b = count - want;
        c = b - nOther;
        while (a > 0 && nOther > 0) {
            int last = nOther - 1;
            int pick = func_0011E8F0(0, last);
            struct Slot **entry = &L.others[pick];
            a--;
            func_00217D50(self, *entry, 4, D_00325CB8);
            func_00291F38(entry, entry + 1, (nOther - pick) * 4 - 4);
            nOther = last;
        }
        if (self->kind == 1 || self->kind == 4) mode = 1;
        else mode = 0;
        while (c > 0 && nFour > 0) {
            int last = nFour - 1;
            int pick = func_0011E8F0(0, last);
            c--;
            func_00217D50(self, L.fours[pick], mode, D_00325CB8);
            func_00291F38((void *)(pick * 4 + (int)&L + 0x20), (char *)(next = L.fours + 1) + pick * 4, (nFour - pick) * 4 - 4);
            nFour = last;
        }
    }
}
