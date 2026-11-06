// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_00202768.cpp; target Sly 3 0x0024C6D8.
// State change of a two-widget UI controller: leave the old state (undo its effects), then enter the new one.
typedef unsigned int uint;
struct VT { short adjustment, unused; void *function; };
struct ACTOR { char pad0[0xE4]; int id; char padE8[4]; int key; };
struct X { char pad0[0xC]; VT *vtable; char pad10[0x2C]; uint flags; char pad40[8]; void *shown; char pad4C[0x98]; ACTOR *actor; void *partner; };
struct MODEL { X *x; char pad4[0xA0]; void *resource; };
struct P { int state; char pad4[0x70]; int specialCount; char pad78[0x14]; ACTOR *actor; char pad90[0x10]; uint savedFlags; void *resource; MODEL *model; X *primary, *secondary; char padB4[8]; int selected, pending; };
extern char D_00475480[], D_00474FF0[], g_clock[], D_0036C700[];
extern "C" {
void func_001A93C8(void *, int, int);
void func_001A9420(void *, int, int);
void func_0024BFB0(P *);
void func_0024BF20(P *);
void func_0024C118(P *);
void func_00262280(X *, int);
void func_00262450(X *, int);
void func_00263080(X *, int);
void func_00165548(void *, int, float);
void func_00248598(void *, int, int);
void func_00169FC0(void *);
void func_002485D8(void *, int, int, int);
void func_0015AB18(void *, int, int);
void func_0024D640(ACTOR *, int);
void func_001854C8(void *, int, void *);
int func_0024C1E8(P *);
void func_0024C1B0(P *);
void func_0024BD80(P *);
void func_0024BE88(P *);
void func_0024BDF8(P *);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_00261580(X *, int, float);
void func_00261070(X *, int);
void func_00261050(X *, int);
void *func_001F4A80(X *);
}
static inline void Post(X *x, int n) { VT *entry = &x->vtable[53]; ((void (*)(void *, int))entry->function)((char *)x + entry->adjustment, n); }
static inline void Clear(X *x) { VT *entry = &x->vtable[54]; ((void (*)(void *))entry->function)((char *)x + entry->adjustment); }
static inline void Reset(X *x) { VT *entry = &x->vtable[56]; ((void (*)(void *))entry->function)((char *)x + entry->adjustment); }
static inline uint GetFlags(X *x) { int f = x->flags; if ((f ^ 1) & 1) f = *(int *)f; return f & ~1; }
static inline void SetFlags(X *x, uint mask) { uint f = x->flags; if ((f ^ 1) & 1) *(uint *)f = mask | (*(uint *)f & 1); else x->flags = mask | (f & 1); }
static inline void AddFlags(X *x, uint mask) { uint f = x->flags; if ((f ^ 1) & 1) *(uint *)f |= mask; else x->flags = f | mask; }
extern "C" void func_0024C6D8(P *p, int nextState)
{
    if (p->state == nextState)
        return;
    if (!p->primary)
        return;
    if (!p->secondary)
        return;
    if (((uint)(p->state - 8) < 2) != ((uint)(nextState - 8) < 2)) {
        if ((uint)(nextState - 8) < 2)
            func_001A93C8(D_00475480, -1, 0);
        else
            func_001A9420(D_00475480, -1, 0);
    }
    switch (p->state) {
    case -1: case 0: case 2: case 3: case 10:
        break;
    case 1:
        func_0024BFB0(p);
        func_0024BF20(p);
        func_00262450(p->primary, 0x3DC);
        if (p->specialCount > 0)
            func_00262450(p->primary, 0x3DD);
        func_0024C118(p);
        break;
    case 4:
        func_00262280(p->secondary, 0x3D8);
        break;
    case 5: case 6:
        func_00262280(p->secondary, 0x3D9);
        break;
    case 7:
        func_00262280(p->primary, 0x3D5);
        func_00262280(p->secondary, 0x3D5);
        func_00262280(p->secondary, 0x3D6);
        break;
    case 8:
        SetFlags(p->model->x, p->savedFlags);
        func_00165548(g_clock, 0, 1.0f);
        func_00248598(D_00474FF0, 1, 1);
        func_00262280(p->primary, 0x3D7);
        break;
    case 9:
        func_00169FC0(p->model->resource);
        func_00263080(p->primary, -1);
        Post(p->primary, 0x377);
        if (p->resource) {
            if (p->actor->key != -1)
                func_002485D8(D_00474FF0, p->actor->key, 0, 0);
            func_0015AB18(p->resource, 0x6D9, p->actor->key);
        }
        func_0024D640(p->actor, 1);
        p->actor = 0;
        if (func_0024C1E8(p)) {
            func_00262450(p->primary, 0x3DC);
            if (p->specialCount > 0)
                func_00262450(p->primary, 0x3DD);
        }
        func_0024C118(p);
        break;
    }
    int previous = p->state;
    p->state = nextState;
    switch (nextState) {
    case 0:
        p->actor = 0;
        p->selected = -1;
        p->pending = -1;
        func_0024C1B0(p);
        Reset(p->primary);
        func_0024BD80(p);
        func_0024BE88(p);
        func_001854C8(D_0036C700, 4, 0);
        break;
    case 1:
        func_00262280(p->primary, 0x3DC);
        Post(p->secondary, 0x3C0);
        break;
    case 5:
        func_00262450(p->secondary, 0x3D9);
        func_00261580(p->secondary, 0x3D9, 0.0f);
        break;
    case 6:
        func_00262450(p->secondary, 0x3D9);
        func_00261580(p->secondary, 0x3D9, 0.0f);
        break;
    case 7:
        func_00244F08(func_002459F8(0x52), 0);
        p->selected = p->actor->id;
        func_00262450(p->primary, 0x3D5);
        func_00262450(p->secondary, 0x3D5);
        func_00262450(p->secondary, 0x3D6);
        break;
    case 8:
        func_00262280(p->primary, 0x3DA);
        func_00262450(p->primary, 0x3D7);
        p->savedFlags = GetFlags(p->model->x);
        AddFlags(p->model->x, 0x242);
        func_00248598(D_00474FF0, 1, 0);
        func_00165548(g_clock, 0, 0.0f);
        break;
    case 9:
        Post(p->secondary, 0x3C0);
        Post(p->primary, 0x3DB);
        func_00263080(p->primary, 0);
        func_001854C8(D_0036C700, 5, 0);
        break;
    case 3: case 4:
    {
        void *partner = func_001F4A80(p->model->x);
        X *secondary = p->secondary;
        ACTOR *actor = p->actor;
        secondary->partner = partner;
        secondary->actor = actor;
    }
        Post(p->secondary, 0x3BE);
        func_00262450(p->secondary, 0x3D8);
        func_00261580(p->secondary, 0x3D8, 0.0f);
        break;
    case 2:
        Post(p->secondary, 0x3C0);
        break;
    case 10:
        p->actor = 0;
        p->selected = -1;
        p->pending = -1;
        Clear(p->secondary);
        Clear(p->primary);
        func_0024BDF8(p);
        func_001854C8(D_0036C700, 6, 0);
        break;
    case -1:
        if (previous != 10) {
            func_001854C8(D_0036C700, 6, 0);
            if (p->primary->shown) {
                func_00261070(p->primary, 1);
                func_00261050(p->primary, 1);
            }
            if (p->secondary->shown) {
                func_00261070(p->secondary, 1);
                func_00261050(p->secondary, 1);
            }
        }
        break;
    }
}
