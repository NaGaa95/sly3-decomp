// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// State change of an object with two animated parts (x210 / x214), an actuator (x204) and per-state sounds:
// stop the looping emitter, leave the old state, enter the new one, show or hide the attachments, then start the
// sounds listed for the new state.
typedef int qword __attribute__((mode(TI)));
struct VT { short delta, pad; void *function; };
struct OBJ { char pad0[0xC]; VT *vt; };
struct XF { char pad0[0x30]; qword pos; };
struct ITEM { char data[0xD0]; };
struct SOUND { int state, id, loop; float volume, pitch; };
struct EMITTER;
struct P {
    char pad0[0xD0]; int count; ITEM *items; char padD8[0x198 - 0xD8]; int state; float stateTime;
    char pad1A0[0x204 - 0x1A0]; void *actuator; OBJ *target; void *x20C; OBJ *primary, *secondary;
    char pad218[0x2C0 - 0x218]; void *sequencer; char pad2C4[0x2E4 - 0x2C4]; OBJ *attachment; int soundCount;
    SOUND sounds[(0x3DC - 0x2EC) / 0x14]; EMITTER *emitter;
};
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct VU_FLOAT { qword q; };
extern struct CLOCK { float time, dt; } g_clock;
extern qword D_00317560;
extern const VECTOR D_003296D0, D_00329700, D_00329710;
extern const qword D_003296E0, D_003296F0;
extern "C" {
void func_00244CA8(EMITTER *, float);
void func_002BBCD8(EMITTER **, void *);
void func_00288950(void *, int);
void func_0022F540(OBJ *, void *);
void func_0022F578(OBJ *, OBJ *);
void func_0022F668(OBJ *, int);
void func_0022F638(OBJ *, const VECTOR *);
void func_0022F600(OBJ *, float);
void func_00288050(void *);
void *func_001F4A80(P *);
qword func_00212FA0(void *, void *, qword, qword, int);
void func_00287E70(void *, qword);
void func_00287F48(void *);
void func_001C7A00(P *, int, int);
void func_0023D938(P *, qword);
void func_0023D9D0(P *, qword);
void func_0023B978(P *, ITEM *);
void func_0023B920(P *, ITEM *);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_00244E08(void *, float);
void func_00244ED0(void *, float);
}
static inline void Call(OBJ *o, int slot) { VT *e = &o->vt[slot]; ((void (*)(void *))e->function)((char *)o + e->delta); }
static inline XF *Xf(OBJ *o) { VT *e = &o->vt[36]; return ((XF *(*)(void *))e->function)((char *)o + e->delta); }
static inline void Clear(EMITTER **emitter) { if (emitter && *emitter) { func_00244CA8(*emitter, 0.0f); func_002BBCD8(emitter, 0); } }
static inline VU_FLOAT Scalar(float f) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(f)); return v; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Normalize(qword v)
{
    qword d, one, l, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s.q)); return r; }
struct SOUNDREF {
    void *p;
    int unused[3]; // 16-byte object: it shares the VU_FLOAT temporary's stack slot (sp+0)
    SOUNDREF(void *o) { func_002BFDD0(&p, o); }
    ~SOUNDREF() { if (p) Call((OBJ *)p, 2); }
    static void func_002BFDD0(void **, void *) __asm__("func_002BFDD0");
} __attribute__((aligned(16)));
extern "C" void func_00286630(P *p, int state)
{
    if (p->state == state)
        return;
    Clear(&p->emitter);
    if (p->state == 3 || p->state == 5) {
        if (p->sequencer)
            func_00288950(p->sequencer, 0);
    }
    p->state = state;
    p->stateTime = g_clock.time;
    switch (state) {
    case -1:
        Call(p->primary, 9);
        Call(p->secondary, 9);
        func_00288050(p->actuator);
        break;
    case 1:
        func_0022F540(p->primary, 0);
        func_0022F578(p->primary, 0);
        Call(p->primary, 9);
        Call(p->secondary, 9);
        func_0022F668(p->primary, -1);
        func_00288050(p->actuator);
        break;
    case 4:
        func_0022F668(p->primary, 0);
        break;
    case 2: {
        func_0022F540(p->primary, p->x20C);
        func_0022F578(p->primary, p->target);
        func_0022F638(p->primary, &D_003296D0);
        func_0022F600(p->primary, 50.0f);
        func_0022F668(p->primary, 2);
        qword goal = func_00212FA0(0, func_001F4A80(p), D_003296E0, D_003296F0, 0);
        qword dir = Sub(goal, Xf(p->target)->pos);
        func_00287E70(p->actuator, Scale(Normalize(dir), Scalar(10000.0f)));
        Call(p->primary, 8);
        Call(p->secondary, 8);
        if (p->sequencer)
            func_00288950(p->sequencer, 1);
        break;
    }
    case 3:
        func_0022F668(p->primary, 3);
        func_0022F638(p->primary, &D_00329700);
        func_00287F48(p->actuator);
        break;
    case 5:
        func_001C7A00(p, 0, 0x13);
        func_0023D938(p, D_00317560);
        func_0023D9D0(p, D_00317560);
        func_0022F668(p->primary, 3);
        func_0022F638(p->primary, &D_00329710);
        if (p->sequencer)
            func_00288950(p->sequencer, 2);
        break;
    }
    if (p->state == 5) {
        for (int i = 0; i < p->count; i++)
            func_0023B978(p, &p->items[i]);
        if (p->attachment)
            Call(p->attachment, 9);
    } else {
        for (int i = 0; i < p->count; i++)
            func_0023B920(p, &p->items[i]);
        if (p->attachment)
            Call(p->attachment, 8);
    }
    for (int j = 0; j < p->soundCount; j++) {
        SOUND *sound = &p->sounds[j];
        if (sound->state == p->state) {
            void *voice = func_002459F8(sound->id);
            func_00244F08(voice, 0);
            SOUNDREF ref(voice);
            func_00244E08(ref.p, sound->volume);
            func_00244ED0(ref.p, sound->pitch);
            if (sound->loop)
                func_002BBCD8(&p->emitter, ref.p);
        }
    }
}
// The literal that follows this unit's jump table in .rodata (-FLT_MAX, read by func_00286E38).
extern const float D_0032973C;
const float D_0032973C = -3.40282347e+38f;
