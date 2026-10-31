// Advance the timed slots of both groups: a slot in state 2 moves to state 3 (when the group check passes) or back to state 1 once its timer has run out, and a state 3 slot returns to state 1.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char data00[0x10]; int state; float timer; float delay; };
struct Self {
    unsigned char pad0[0x270];
    struct Slot slots[2][6];
    int counts[2];
};
extern float D_0036BB98;
extern float D_00325CB4;
int func_002185B0(struct Self *self, struct Slot *slot, int group);
void func_00217D50(struct Self *self, struct Slot *slot, int state, float value);

void func_00217D90(struct Self *self)
{
    float now = D_0036BB98;
    int i, j;
    for (i = 0; i < 2; i++) {
        int count = self->counts[i];
        for (j = 0; j < count; j++) {
            struct Slot *slot = &self->slots[i][j];
            int state;
            do {
                state = slot->state;
                switch (state) {
                case 2:
                    if (slot->timer < now) {
                        if (func_002185B0(self, slot, i))
                            func_00217D50(self, slot, 3, D_0036BB98 + slot->delay);
                        else
                            func_00217D50(self, slot, 1, D_00325CB4);
                    }
                    break;
                case 3:
                    if (slot->timer < now)
                        func_00217D50(self, slot, 1, D_00325CB4);
                    break;
                }
            } while (slot->state != state);
        }
    }
}
