// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Shape { void *first; };
struct Candidate {
    unsigned char opaque00[0xC];
    Method *methods;
    unsigned char opaque10[4];
    Shape **shape;
    unsigned char opaque18[0xD0 - 0x18];
    Candidate *next;
    unsigned char opaqueD4[0xE4 - 0xD4];
    int group;
};
struct Self {
    unsigned char opaque00[0x418];
    int group;
    unsigned char opaque41C[0x424 - 0x41C];
    Candidate *current;
};
extern "C" {
extern Candidate *D_00479AD8;
extern const float D_00325CC0;
extern float D_00468D0C, D_00468D14, D_00468D1C;
extern int D_00468D10, D_00468D18, D_00468D20;
int func_001C8F20(void *object, void *other);
qword func_001C9428(int a, void *self, qword position);
float func_001205C8(qword v);
float func_0011E3B8(float rad);
int func_0013B500(void *object, int type);
void func_002BC490(void *object, int flags);
}
struct Guard {
    int storage[4];
    ~Guard() { func_002BC490(this, 2); }
};
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
static __inline__ qword LengthXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0, %1, %2
	vaddy.x %0, %0, %0y" : "=j"(d) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x
	vwaitq
	vaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static __inline__ float GetX(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
extern "C" Candidate *func_00218C00(Self *self, int mode, Candidate *skip)
{
    if (self->current) return self->current;
    Guard guard;
    Candidate *best = skip;
    float bestScore = D_00325CC0;
    Candidate *object;
    for (object = D_00479AD8; object; object = object->next) {
        if (object->group != self->group) continue;
        if (func_001C8F20(object, self)) continue;
        if (skip && !func_001C8F20(object, skip)) continue;
        {
            qword position = func_001C9428(0, self, MATRIX(object)->position);
            float bias = 0.0f;
            int ok = 0;
            switch (mode) {
            case 0:
                ok = 0.0f < GetY(position);
                bias = -1.5707964f;
                break;
            case 1:
                ok = GetY(position) < 0.0f;
                bias = 1.5707964f;
                break;
            }
            if (!ok) continue;
            if (!D_00468D10) {
                D_00468D0C = 0.9599312f;
                D_00468D10 = 1;
            }
            {
                float score = func_0011E3B8(bias + func_001205C8(position));
                score = score < 0.0f ? -score : score;
                if (score < D_00468D0C) {
                    if (!func_0013B500(*(void **)object->shape, 0x58)) {
                        if (!D_00468D18) {
                            D_00468D14 = 0.3490659f;
                            D_00468D18 = 1;
                        }
                        score += D_00468D14;
                    }
                    if (!D_00468D20) {
                        D_00468D1C = 1.7453294e-05f;
                        D_00468D20 = 1;
                    }
                    score += GetX(LengthXY(position)) * D_00468D1C;
                    if (score < bestScore) {
                        bestScore = score;
                        best = object;
                    }
                }
            }
        }
    }
    return best;
}
