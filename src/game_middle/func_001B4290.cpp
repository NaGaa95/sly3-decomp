// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse
// For every candidate on the global list whose target passes func_00170500 and is not flagged, measure the distance
// between the candidate and the self object. Far candidates are handled directly; near ones are first ray-tested
// against the collision records between the two positions inside a heap frame (FRAME), and handled only if the test
// reports a hit. Scope and FRAME are empty RAII objects (their destructors are the out-of-line functions below).
typedef int qword __attribute__((mode(TI)));
struct VirtualEntry { short adjustment; short reserved; qword *(*call)(void *); };
struct Matrixed { unsigned char opaque0[12]; VirtualEntry *vtable; };
struct Target { unsigned char pad0[0x3D8]; unsigned int flags; };
struct Candidate { unsigned char opaque0[12]; VirtualEntry *vtable; unsigned char pad10[0x10D0 - 0x10]; Target *target; unsigned char pad10D4[0x113C - 0x10D4]; Candidate *next; };
struct Self { Matrixed *object; };
extern "C" {
extern Candidate *D_00479B5C;
extern unsigned char D_00475480[];
int func_00170500(Target *target, Matrixed *object);
void func_001703C8(Target *target, Matrixed *object, int flag);
void func_002BC5F0(void *object, int flags);
int func_001B4210(void *context, void *record);
void func_0025CF18(void *game, qword start, qword end, int (*filter)(void *, void *), void *context, int *count, void ***records);
void *func_00165000(int flags, qword start, qword end, int count, void **records, void *output);
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float Length(qword v)
{
    qword d = v, one;
    float f;
    __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline qword Position(Matrixed *object)
{
    VirtualEntry *entry = &object->vtable[36];
    return entry->call((char *)object + entry->adjustment)[3];
}
class Scope { public: ~Scope() { func_002BC5F0(this, 2); } };
class FRAME { public: FRAME(); ~FRAME(); };
extern "C" void func_001B4290(Self *self)
{
    Scope scope;
    for (Candidate *candidate = D_00479B5C; candidate; candidate = candidate->next) {
        if (!func_00170500(candidate->target, self->object))
            continue;
        if (candidate->target->flags & 1)
            continue;
        {
            qword from = Position((Matrixed *)candidate);
            qword to = Position(self->object);
            if (1500.0f < Length(Sub(from, to))) {
                func_001703C8(candidate->target, self->object, 0);
            } else {
                FRAME frame;
                int count;
                void **records;
                func_0025CF18(D_00475480, from, to, func_001B4210, candidate, &count, &records);
                if (!func_00165000(0, from, to, count, records, 0))
                    continue;
                func_001703C8(candidate->target, self->object, 0);
            }
        }
    }
}
