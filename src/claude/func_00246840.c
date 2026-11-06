// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VE {short d;short pad;void *pf;};
struct XF {char pad[0x30];qword pos;};
struct LO {char pad0[0xC];struct VE *vt;char pad10[0x2F-0x10];unsigned long b2F:8;};
struct RANGE {float low,high;};
struct E {struct LO *object;struct RANGE limits;float gain;};
struct P {char pad1C[0x1C];struct LO *object;qword position;char pad30[0x70];int counts[6];struct E entries[6][8];};
extern qword D_00317560;
int func_0011E9F0(float,float,float);
void func_00245138(struct P *);
void func_00245440(qword,const struct RANGE *,float *,int *,int);
void func_00246230(struct P *,int,int);
void func_00246190(struct P *,int,float);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return func_0011E9F0(X(a), X(b), 0.0001f) && func_0011E9F0(Y(a), Y(b), 0.0001f) && func_0011E9F0(Z(a), Z(b), 0.0001f);
}
// Port of Sly 2 src/hand/func_001FC9B0.c (CSndVoice::Update3D).
void func_00246840(struct P *p)
{
    int group;
    if (p->object || !FNear(D_00317560, p->position))
        func_00245138(p);
    for (group = 0; group < 6; group++) {
        int count = p->counts[group];
        if (count) {
            float maximum = 0.0f;
            int flags = 0, active = 0, i;
            int *pflags = &flags;
            float fade;
            for (i = 0; i < count; i++) {
                struct E *entry = &p->entries[group][i];
                struct LO *object = entry->object;
                if (object && (object->b2F & 1)) {
                    active++;
                    func_00245440(((struct XF *(*)(void *))object->vt[36].pf)((char *)object + object->vt[36].d)->pos, &entry->limits, &fade, pflags, 0);
                    pflags = 0;
                    { float gain = fade * entry->gain; maximum = maximum > gain ? maximum : gain; }
                }
            }
            func_00246230(p, group, active == 1 ? flags : 0);
            func_00246190(p, group, maximum);
        }
    }
}
