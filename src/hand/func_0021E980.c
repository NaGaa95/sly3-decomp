// Update state transitions through the actual attached actor and global clock.
// Full receiver/state inputs, concrete callback examples and original boundary independently reviewed.
// Transition the controller state and update its actual attached actor.
// Entering state0 invokes both distinct actor setters with their own integer1.
// Only A0 receiver/A1 requested state are incoming inputs; time is loaded from the real clock.
// SLY3_CFLAGS: -Os -G0
// Sly3 adds both actor setters for entering state0 and moves events/slot.
extern struct CLOCK {
    float t;
    float dt;
}
D_0036BB98;
typedef struct VT {
    struct {
        short d;
        short pad;
        void (*pfn)(void *);
    }
    a[64];
}
VT;
typedef struct {
    char pad[0xC];
    VT *vt;
}
LO;
typedef struct {
    char pad[0x10];
    int state;
    float t;
    int x18;
    float x1C;
    int x20;
    float x24;
    LO *x28;
}
OBJ;
void func_00262188(LO *, int);
void func_00260DD0(LO *, int, int *);
void func_00261050(LO *, int);
void func_00261070(LO *, int);
void func_0021E980(OBJ *p, int n) {
    LO *plo;
    if (n == p->state) return;
    switch (p->state) {
        case 3: if (n == 1 && p->t == D_0036BB98.t) n = 2;
        break;
        case 4: p->x18 = p->x20;
        p->x1C = p->x24;
        p->x20 = -1;
        p->x24 = -1.0f;
        break;
    }
    if (n == 0) p->x18 = -1;
    plo = p->x28;
    if (plo) {
        if (p->state == 4 && n == 2) func_00262188(plo, 0x377);
        switch (n) {
            case 4: func_00262188(p->x28, 0x379);
            break;
            case 3: p->x28->vt->a[54].pfn((char *)p->x28 + p->x28->vt->a[54].d);
            break;
            case 0: func_00261050(p->x28, 1);
            func_00261070(p->x28, 1);
            break;
            case 1: func_00260DD0(p->x28, 1, &p->x18);
            break;
        }
    }
    p->state = n;
    p->t = D_0036BB98.t;
}
