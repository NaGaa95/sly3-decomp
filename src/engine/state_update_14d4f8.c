// SLY3_CFLAGS: -Os -G0
struct StateEntry { short delta; short pad; int (*method)(void *); };
struct StateTarget { unsigned char prefix[0xC]; struct StateEntry *table; };
struct StateOwner { unsigned char prefix[0x138]; struct { unsigned char prefix[0xC]; int word; } *node; unsigned char gap13C[4]; struct StateTarget *target; unsigned char gap144[0x164 - 0x144]; int state; float since; unsigned char gap16C[4]; float limit; float next; };
struct StateInput { unsigned char bytes[0x11C0]; };
extern float D_0036BB98;
extern const float D_003202A0[3];
extern const float D_003202B0[2];
extern struct StateInput D_0036E740[];
void func_0023C660(void *self);
void func_0014DC08(void *self, int value);
void func_0014DC98(void *self, int value);
void func_00155ED8(void *target, int value);
int func_001C8610(void *target);
void *func_002459F8(int id);
void func_00244F08(void *sound, int flag);
void func_001A9058(void *input, float scale, int mode);
void func_0014D4F8(struct StateOwner *self)
{
    func_0023C660(self);
    switch(self->state) {
    case 5:
        if(D_0036BB98 - self->since >= 5.0f) func_0014DC08(self, 0);
        break;
    case 2:
        if(!func_001C8610(self->target) || self->target->table[81].method((char *)self->target + self->target->table[81].delta) == 2) {
            func_0014DC98(self, 4);
            func_00155ED8(self->target, 5);
        }
        break;
    case 4:
        if(self->node->word) {
            float now = D_0036BB98;
            if(self->limit < now) {
                func_00244F08(func_002459F8(0x52), 0);
                func_00155ED8(self->target, 5);
            } else if(self->next < now) {
                float t, value, result, base, lo, hi;
                unsigned int i;
                for(i = 0; i < 2; i++) func_001A9058(&D_0036E740[i], 0.15f, 3);
                func_00244F08(func_002459F8(0x35), 0);
                lo = D_003202B0[0];
                hi = D_003202B0[1];
                t = self->limit - now;
                value = D_003202A0[0] + t * (D_003202A0[1] + t * D_003202A0[2]);
                base = D_0036BB98;
                if(value < lo) result = lo;
                else if(hi < value) result = hi;
                else result = value;
                self->next = base + result;
            }
        }
        break;
    }
}
