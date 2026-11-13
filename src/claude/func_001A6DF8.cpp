// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001A6DF8: JOBINVESTIGATE::FindSearchPlaces (cf. Sly 2 FindSearchPlaces__14JOBINVESTIGATE)
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; int i[4]; } U;
struct VTE { short d; short pad; void *pfn; };
struct M4 { U r[4]; };
typedef struct NODE {
    char pad0[0xC]; VTE *pvt; char pad10[0x114 - 0x10]; struct NODE *next114; char pad118[4]; float reach;
    char pad120[0x140 - 0x120]; struct NODE *next140; char pad144[0x154 - 0x144]; struct NODE *next154;
    char pad158[0x170 - 0x158]; struct NODE *next170; char pad174[0x1C4 - 0x174]; struct NODE *next1C4;
} NODE;
typedef struct PAIR { U candidate, original; } PAIR;
typedef struct P { char pad0[0x10]; NODE *actor; char pad14[0x28]; float time; char pad40[0x10]; PAIR pair[4]; int index; } P;
typedef struct ROW { U point; float angle; } ROW;
typedef struct QUERY { U point; float heading; unsigned count; ROW row[64]; U candidate, delta, scalar; } QUERY;
typedef struct WORK { QUERY query; NODE *result256[256]; NODE *result32[32]; NODE *result128[128]; } WORK;
typedef struct LM { float low, high; } LM;
extern "C" {
extern NODE *D_00479B20, *D_00479B14, *D_00479B2C, *D_00479B08, *D_00479AE4, *D_00479AFC, *D_00479AF0, *D_00479B44, *D_00479B68;
extern char D_00475480;
extern qword D_00317530, D_00317550;
extern LM D_00322300, D_00322308;
extern float D_00322310;
float func_002A3EE8(float, float);
int func_001A6CE0(QUERY *);
void func_0022EA88(NODE *, qword, void *, qword *, qword *, float *, float *);
int func_0017E208(void *, int, int, NODE *, int, NODE **);
int func_001A6DD0(ROW *, ROW *);
void func_00292540(void *, unsigned, unsigned, int (*)(ROW *, ROW *));
qword func_0011FD70(float, float, float);
float func_0011E940(float, float);
void func_001A6DF8(P *p);
}
static inline M4 *Mat(NODE *s) { return ((M4 *(*)(void *))s->pvt[36].pfn)((char *)s + s->pvt[36].d); }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwSubFrom(const qword &a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLength(qword v) { qword qw, vfOne, qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qw)); return qwLen; }
static inline qword QwLengthOne(qword v) { qword qw, vfOne, qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qw), "0"(vfOne)); return qwLen; }
static inline qword QwLengthXY(qword v) { qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw)); return qw; }
static inline float GXOfQw(qword qw) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw)); return x; }
static inline qword QwDot(qword a, qword b) { qword qw, vfOne;
    __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(vfOne), "=j"(qw) : "j"(a), "j"(b), "j"(b)); return qw; }
static inline qword QwScaleX(qword v, qword g) { qword qw; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(v), "0"(g)); return qw; }
static inline qword QwDivide(qword v, qword g) { qword qw; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(v), "j"(g)); return qw; }
static inline qword QwAddScaled(qword base, qword vec, qword g) { qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(base), "j"(vec), "j"(g)); return qw; }
static inline qword VuFloatFromMemWord(int n) { qword v; __asm__("qmtc2 %1, %0" : "=j"(v) : "rV"(n)); return v; }
static inline qword VuFloatVolatile(float g) { qword v; __asm__ __volatile__("qmtc2 %1, %0" : "=j"(v) : "r"(g)); return v; }
#define QW_SUB_T(r, t, b) __asm__("vsub.xyzw %0, %1, %2" : "=j"(r), "=j"(t) : "0"(b), "1"(t))

#define POS(o) (Mat(o)->r[3].q)
void func_001A6DF8(P *p)
{
    WORK w; NODE *object; NODE **cursor; int remaining, i; unsigned accepted; float lastAngle;
    w.query.point.q = POS(p->actor);
    { M4 *m = Mat(p->actor); w.query.heading = func_002A3EE8(m->r[0].f[1], m->r[0].f[0]); }
    w.query.count = 0;
    for (object = D_00479B20; object; object = object->next114) {
        qword posObj = POS(object);
        qword qwFallback = D_00317530;
        w.query.delta.q = QwSubFrom(w.query.point.q, posObj);
        w.query.delta.i[2] = 0;
        qword len = QwLength(w.query.delta.q);
        qword g = VuFloatFromMemWord(*(int *)&object->reach);
        qword n;
        if (GXOfQw(len) < 0.0001f) { w.query.scalar.q = g; n = qwFallback; }
        else { w.query.scalar.q = g; n = QwDivide(w.query.delta.q, len); }
        w.query.candidate.q = QwAddScaled(posObj, n, g);
        func_001A6CE0(&w.query);
    }
    for (object = D_00479B14; object; object = object->next1C4) { func_0022EA88(object, w.query.point.q, 0, &w.query.candidate.q, 0, 0, 0); func_001A6CE0(&w.query); }
    for (object = D_00479B2C; object; object = object->next114) { w.query.candidate.q = POS(object); func_001A6CE0(&w.query); }
    for (object = D_00479B08; object; object = object->next170) { w.query.candidate.q = POS(object); func_001A6CE0(&w.query); }
    for (object = D_00479AE4; object; object = object->next1C4) { func_0022EA88(object, w.query.point.q, 0, &w.query.candidate.q, 0, 0, 0); func_001A6CE0(&w.query); }
    for (object = D_00479AFC; object; object = object->next114) { w.query.candidate.q = POS(object); func_001A6CE0(&w.query); }
    for (object = D_00479AF0; object; object = object->next1C4) { func_0022EA88(object, w.query.point.q, 0, &w.query.candidate.q, 0, 0, 0); func_001A6CE0(&w.query); }
    for (object = D_00479B44; object; object = object->next140) { w.query.candidate.q = POS(object); func_001A6CE0(&w.query); }
    { int count = func_0017E208(&D_00475480, 0x505, 0x21, 0, 0x100, w.result256);
      if (count > 0) { cursor = w.result256; remaining = count; do { NODE *item = *cursor++; --remaining; w.query.candidate.q = POS(item); func_001A6CE0(&w.query); } while (remaining); } }
    { int count = func_0017E208(&D_00475480, 0x505, 0x74, 0, 0x20, w.result32);
      if (count > 0) { cursor = w.result32; remaining = count; do { NODE *item = *cursor++; --remaining; w.query.candidate.q = POS(item); func_001A6CE0(&w.query); } while (remaining); } }
    { int count = func_0017E208(&D_00475480, 0x505, 0x19, 0, 0x80, w.result128);
      if (count > 0) { cursor = w.result128; remaining = count; do { NODE *item = *cursor++; --remaining; w.query.candidate.q = POS(item); func_001A6CE0(&w.query); } while (remaining); } }
    for (object = D_00479B68; object; object = object->next154) { w.query.candidate.q = POS(object); func_001A6CE0(&w.query); }
    lastAngle = 0.0f;
    func_00292540(w.query.row, w.query.count, sizeof(ROW), func_001A6DD0);
    accepted = 0;
    {
        PAIR *previous = 0;
        for (i = 0; i < (int)w.query.count && accepted < 4; i++) {
            ROW *row = &w.query.row[i]; qword original = row->point.q;
            qword up = D_00317550;
            qword delta = QwSub(original, w.query.point.q);
            qword qwFallback = D_00317530;
            qword planar = QwSub(delta, QwScaleX(up, QwDot(delta, up)));
            qword len = QwLength(planar);
            qword dir;
            if (GXOfQw(len) < 0.0001f) { dir = qwFallback; __asm__("" : "=r"(dir) : "0"(dir)); } /* zero-insn tie: keeps dir in the GPR class on this arm and stops jump.c hoisting the fallback copy above the test */
            else dir = QwDivide(planar, len);
            qword s = VuFloatVolatile(200.0f);
            qword target = QwAddScaled(w.query.point.q, dir, s);
            w.query.delta.q = s;
            register qword probe __asm__("vf2") = target;
            if (previous) { qword d; QW_SUB_T(d, probe, previous->candidate.q); if (GXOfQw(QwLengthXY(d)) < 150.0f) continue; }
            previous = &p->pair[accepted++]; lastAngle = row->angle; previous->original.q = original; previous->candidate.q = target;
        }
    }
    qword origin = w.query.point.q;
    qword anchor = QwAdd(origin, func_0011FD70(w.query.heading + 3.1415927f, -350.0f, 0.0f));
    while (accepted < 4) {
        float angle, length; qword point;
        lastAngle += func_0011E940(D_00322300.low, D_00322300.high);
        angle = lastAngle + w.query.heading;
        length = func_0011E940(D_00322308.low, D_00322308.high);
        point = QwAdd(anchor, func_0011FD70(angle, length, 0.0f));
        { PAIR *pair = &p->pair[accepted]; pair->candidate.q = point; pair->original.q = point; } accepted++;
    }
    p->index = 0; p->time = D_00322310;
}
