// SLY3_CFLAGS: -Os -G0
struct HIT { int a[8]; };
struct ACT { char pad[0x4CC]; void *x4CC; };
struct S0 { char pad[0x10]; struct ACT *pact; char pad1[0x30 - 0x14]; int state; };
extern char D_0036BD20[], D_0036C700[];
extern int D_0036DBE0;
int func_001F43C8(struct ACT *pact);
void func_001F43D0(struct ACT *pact, int n);
int func_00172268(void *p, int n, struct ACT *pact);
int func_001C0B70(void *p, struct HIT *phit, int n);
void func_001C11E0(void *p, struct HIT *phit);
void func_00160960(struct S0 *p, int state, void *pv);
void func_00161610(struct S0 *p);
void func_0015FBD8(struct S0 *p);
void func_001854C8(void *p, int n, struct ACT *pact);
int func_00238AD8(struct S0 *p, int msg, int *data);
int func_0015F918(struct S0 *p, int msg, int *data)
{
    switch (msg) {
    case 18: {
        struct HIT hit;
        int n;
        if (p->state != 14) {
            n = func_001F43C8(p->pact);
            func_001F43D0(p->pact, n - func_00172268(D_0036BD20, 10, p->pact));
            if (func_001F43C8(p->pact) > 0) {
                if (func_001C0B70(p->pact->x4CC, &hit, 0)) {
                    { int f = D_0036DBE0 != 2; if (f) { func_001C11E0(p->pact->x4CC, &hit);
                        func_00160960(p, 20, 0); } else { func_00160960(p, 12, &hit); } }
                } else {
                    func_00160960(p, 14, 0);
                }
            } else {
                func_00160960(p, 14, 0);
            }
        }
        return 1;
    }
    case 15:
        func_00160960(p, 13, data);
        return 1;
    case 16:
        func_00160960(p, 14, data);
        return 1;
    case 10:
        switch (data[2]) {
        case 0x32B:
            if (p->state == 14) func_001854C8(D_0036C700, 12, p->pact);
            break;
        case 0x62:
            if (p->state == 0x11) func_0015FBD8(p);
            break;
        case 0x2AA:
            func_00161610(p);
            break;
        }
        break;
    case 8:
        if (p->state != 14) func_00160960(p, 9, data);
        return 1;
    }
    return func_00238AD8(p, msg, data);
}
