// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Per-frame link check of a carried/attached object (same routine as Sly 2 func_001A2460): the link must accept the object's
// raised point; a downward direction (or an unattached state) triggers the link's contact reaction, and every tracked entry whose
// predicted position crosses the point's height triggers the link effect and restarts its timer.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M4 { U r[4]; };
struct VTE { short delta, pad; void *fn; };
struct EFFECT { char pad[0xC]; VTE *vt; };
struct L { char pad[0xC]; VTE *vt; char pad10[0x154 - 0x10]; EFFECT *effect; char pad158[0x160 - 0x158]; int arg0, arg1, arg2; };
struct P;
struct ENTRY { P *object; float time; };
struct P {
    char pad[0xC]; VTE *vt; char pad10[0x33C - 0x10]; int state; char pad340[0xE44 - 0x340]; int mode;
    char padE48[0x1164 - 0xE48]; L *link; ENTRY *entries; int count; char pad1170[0x1178 - 0x1170]; float height;
};
struct CLOCK { float time, dt; };
struct MSG { U position; };
extern "C" {
extern CLOCK D_0036BB98;
void *func_0028F680(void *frame, int a, M4 *pred, int b, float dt);
M4 func_0011D558(const M4 *a, const M4 *b);
int func_001C4408(P *p, L *link, qword *point);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);
void func_001FE728(void *effect, int a);
}
static inline float Z(qword q) { float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f; }
static inline qword Direction(P *p) { return ((qword(*)(void *))p->vt[38].fn)((char *)p + p->vt[38].delta); }
static inline qword Position(P *p) { return ((M4 *(*)(void *))p->vt[36].fn)((char *)p + p->vt[36].delta)->r[3].q; }
extern "C" void func_001C40E0(P *p)
{
    U point;
    int valid;
    if (p->link) {
        point.q = Position(p);
        point.f[2] += p->height;
        if (p->mode == 3 || p->mode == 11)
            point.f[2] -= 10.0f;
        valid = ((int(*)(void *, qword))p->link->vt[77].fn)((char *)p->link + p->link->vt[77].delta, point.q);
    } else
        valid = 0;
    if (!valid)
        return;
    if (p->link->arg1 || p->link->arg2) {
        int notify = 0;
        if (Z(Direction(p)) < 0.0f || (p->state == -1 && p->mode != 8))
            notify = 1;
        if (notify)
            func_00240CB0(p->link, 0, p, p->link->arg0, p->link->arg1, p->link->arg2, Position(p), Direction(p), 0);
    }
    if (!p->link->effect)
        return;
    if (!func_001C4408(p, p->link, &point.q))
        return;
    {
        int i;
        U position;
        M4 predicted, base;
        for (i = 0; i < p->count; i++) {
            ENTRY *entry = &p->entries[i];
            if (D_0036BB98.time - entry->time < 0.05f)
                continue;
            P *object = entry->object;
            position.q = Position(object);
            void *frame = ((void *(*)(void *, M4 *))object->vt[37].fn)((char *)object + object->vt[37].delta, &base);
            func_0028F680(frame, 0, &predicted, 0, D_0036BB98.dt);
            predicted = func_0011D558(&predicted, &base);
            int crossed = 0;
            if (point.f[2] <= position.f[2]) {
                if (predicted.r[3].f[2] <= point.f[2])
                    crossed = 1;
            } else if (point.f[2] <= predicted.r[3].f[2])
                crossed = 1;
            if (crossed) {
                EFFECT *effect;
                position.f[2] = point.f[2];
                effect = p->link->effect;
                ((void (*)(void *, qword))effect->vt[34].fn)((char *)effect + effect->vt[34].delta, position.q);
                func_001FE728(p->link->effect, 1);
                entry->time = D_0036BB98.time;
            }
        }
    }
}
