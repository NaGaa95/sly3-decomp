// SLY3_CFLAGS: -Os -G0 -ffast-math
enum Mode { MODE_NONE = -1, MODE0, MODE1, MODE2, MODE3, MODE4, MODE5, MODE6, MODE7 };
enum Phase { PHASE_NONE = -1, PHASE0, PHASE1, PHASE2 };
struct Goal { char pad0[4]; float g4; };
struct Self {
    char pad0[0x28]; unsigned long pad28 : 56; unsigned long b2F : 8;
    char pad30[0x134 - 0x30]; int n134;
    char pad138[0x1B0 - 0x138]; enum Mode n1B0;
    char pad1B4[4]; enum Phase n1B8;
    char pad1BC[4]; int n1C0;
    char pad1C4[0x1DC - 0x1C4]; struct Goal *goal;
    char pad1E0[0x218 - 0x1E0]; float g218; float g21C; float g220; float g224; float g228; float g22C;
    char pad230[0x414 - 0x230]; int n414;
    char pad418[0x4F4 - 0x418]; int n4F4;
    char pad4F8[0x550 - 0x4F8]; int n550;
};
static inline float MinG(float a, float b) { return b < a ? b : a; }
struct Clock { float t; float dt; };
extern struct Clock D_0036BB98;
extern char D_00325C10[];
float func_00219000(struct Self *);
void func_00216350(struct Self *);
void func_00216680(struct Self *);
int func_001A7A80(int, int, float);
void func_002159D8(struct Self *, int);
float func_00219058(struct Self *, float);
float func_00216318(struct Self *);
float func_002A35F8(float);
float func_0011E598(void *, float, float, float, int);
int func_00239E70(int);
int func_00239E50(int);
void func_002412C8(struct Self *, float);
void func_00216020(struct Self *self)
{
    enum Mode state;
    float scale;
    self->g218 = 0;
    for (;;) {
        state = self->n1B0;
        switch (state) {
        case MODE2:
        case MODE4:
            self->g21C = func_00219000(self);
            switch (self->n1B8) {
            case PHASE0:
                func_00216350(self);
                break;
            case PHASE1:
                func_00216350(self);
                break;
            case PHASE2:
                func_00216680(self);
                break;
            }
            break;
        case MODE3:
            if (func_001A7A80(self->n134, 0x6F0, 0.1f))
                func_002159D8(self, 2);
            break;
        }
        if (self->n1B0 == state || self->n1B0 == MODE_NONE)
            break;
    }
    if (self->g218 != 0.0f)
        scale = self->g218;
    else
        scale = func_00219058(self, self->g21C);
    switch (self->n1B0) {
    case MODE2:
        if (self->n550)
            self->g224 = func_00216318(self);
        else
            self->g224 = self->goal->g4 * scale;
        if ((self->n1B8 == PHASE2 && self->n1C0 == 4) || self->n550) {
            scale = self->goal->g4;
        } else {
            scale = self->goal->g4 * MinG(1.0f, scale);
        }
        self->g228 = scale * func_002A35F8(self->g22C) / self->g220;
        break;
    case MODE4:
        if (self->n550)
            self->g224 = func_00216318(self);
        else
            self->g224 = self->goal->g4 * scale;
        {
            struct Goal *goal = self->goal;
            self->g228 = goal->g4 * func_002A35F8(self->g22C) / self->g220;
        }
        if (self->n4F4 == 0x3E)
            self->g228 = self->g228 * 1.75f;
        break;
    case MODE5:
        {
            float zero = 0.0f;
            self->g224 = func_0011E598(D_00325C10, self->g224, zero, D_0036BB98.dt, 0);
            self->g228 = zero;
        }
        break;
    case MODE7:
        if ((int)self->b2F & 1) {
            if (self->n414) {
                if (func_00239E70(self->n414) != func_00239E50(self->n414))
                    break;
            }
            func_002412C8(self, 1.0f);
        }
        break;
    default:
        self->g224 = 0;
        self->g228 = 0;
        break;
    }
}
