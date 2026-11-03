// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Selector mode change (port of Sly 2 func_001DB0C8): when the mode changes, cast a ray from the currently selected item along the
// input direction and select the nearest enabled item that the ray hits (or passes close to), then play the selection sound.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct Item {
    int id;
    unsigned char pad04[0x10];
    float x, y;
    int flags;
};
struct Input { float x, y; };
struct Selector {
    unsigned char pad00[0x1C];
    Input *input;
    unsigned char pad20[0x38 - 0x20];
    int mode;
    float changedAt;
    unsigned char pad40[0x58 - 0x40];
    int selected;
    int count;
    Item *items;
};
struct Proximity { float along, distance; };
struct Hit { qword position, other, normal; unsigned char pad30[0x10]; float fraction; unsigned char pad44[0x1C]; };
struct Clock { unsigned char pad[0x40]; float t40; };
extern Clock D_0036BB98;
extern float D_00349068, D_0034905C, D_00349060, D_00349064, D_003260A0;
extern "C" {
Item *func_0021F310(Selector *sel, int id);
int func_00164B08(qword point, qword start, qword end, int flags, Hit *hit, float radius);
void func_00120A00(qword point, qword start, qword end, qword *unused, float *along, float *distance);
void func_0021F948(Selector *sel, int id);
void func_0021EDC0(Selector *sel);
void *func_002459F8(int id);
void func_00244F08(void *sound, int flags);
}
static inline qword XYZ(float x, float y, float z, U &home)
{
    qword r, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(r), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    home.q = r;
    return home.q;
}
static inline qword ToVF(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0,$vf0,$vf0" : "=j"(r)); return r; }
static inline qword Normalize(qword a)
{
    qword d, one, r, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(a), "j"(l));
    return r;
}
static inline qword Splat(const float &f, U &home)
{
    qword s;
    __asm__("qmtc2.ni %1,%0" : "=j"(s) : "rV"(*(const int *)&f));
    home.q = s;
    return home.q;
}
static inline qword Scale(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static inline qword Add(qword a, const qword &b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

extern "C" void func_0021F6A0(Selector *sel, int mode)
{
    U home;
    Hit hit;
    Proximity proximity;
    if (mode == sel->mode)
        return;
    sel->mode = mode;
    sel->changedAt = D_0036BB98.t40;
    if (mode == -1 || sel->selected == -1)
        return;
    Item *current = func_0021F310(sel, sel->selected);
    qword position;
    position = XYZ(current->x, current->y * D_00349068, 0.0f, home);
    qword direction;
    if (sel->input)
        direction = ToVF(XYZ(sel->input->x, -sel->input->y, 0.0f, home));
    else
        direction = Zero();
    qword ray = Scale(Normalize(direction), Splat(D_0034905C, home));
    int bestId = -1;
    float best = D_003260A0;
    for (int i = 0; i < sel->count; i++) {
        Item *item = &sel->items[i];
        if (item == current)
            continue;
        if (!(item->flags & 4))
            continue;
        float zero = 0.0f;
        qword point;
        float score;
        if (func_00164B08(point = XYZ(item->x, item->y * D_00349068, zero, home), position, Add(position, ray), 1, &hit, D_00349060) > 0) {
            score = hit.fraction * D_0034905C;
        } else {
            func_00120A00(point, position, Add(position, ray), 0, &proximity.along, &proximity.distance);
            if (proximity.distance < D_00349064) {
                if (zero < proximity.along)
                    score = D_0034905C + proximity.distance;
                else
                    continue;
            } else
                continue;
        }
        if (score < best) {
            bestId = item->id;
            best = score;
        }
    }
    if (bestId != -1) {
        func_0021F948(sel, bestId);
        func_0021EDC0(sel);
        func_00244F08(func_002459F8(0x35), 0);
    }
}
