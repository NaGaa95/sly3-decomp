// SLY3_CFLAGS: -Os -G0
// func_00161380 and func_001614E8 share one unit: their jump tables are adjacent in .rodata (0x320AF0, 0x320B10).
struct OWNER { char pad[0x17D4]; int x17D4; int x17D8; int x17DC; char pad1[0x17EC - 0x17E0]; int x17EC; };
struct S0 { char pad[0x10]; struct OWNER *powner; char pad1[0x30 - 0x14]; int x30; char pad2[0x38 - 0x34]; int state; float tState; char pad3[0x48 - 0x40]; int x48; int x4C; };
extern struct CLOCK { float t; } D_0036BB98;
void func_0023AC58(int *p);
void func_00137628(int *p);
void func_00137588(int a, struct OWNER *powner, int n, int *p, float g0, float g1);
void func_0023AAE8(int a, struct OWNER *powner, int id, int n, int *p);
void func_00239CE8(int a, int id);
struct Q { char pad[0x18]; int x18; };
struct Q *func_0015F908(struct S0 *p);
int func_001FBEA0(int a);
int func_001A7A80(struct Q *q, int n, float g);
int func_00239E70(int a);
int func_00138AC8(int a);
void func_001614E8(struct S0 *p, int state);
void func_00161380(struct S0 *p)
{
    int st = p->x30;
    struct Q *q;
    int state;
    if (st >= 11 && (st < 19 || st == 20)) return;
    q = func_0015F908(p);
    do {
        state = p->state;
        switch (state) {
        case -1:
            if (p->powner->x17EC && func_001FBEA0(p->powner->x17EC) && func_001A7A80(q, 8, 0.25f))
                func_001614E8(p, 0);
            break;
        case 1:
            if (!(q->x18 & 8)) func_001614E8(p, -1);
            else if (func_00239E70(p->x4C) == 0x32A) func_001614E8(p, 2);
            break;
        case 2:
            if (!(q->x18 & 8)) func_001614E8(p, 3);
            break;
        case 0:
        case 3:
        case 4:
            if (func_00138AC8(p->x48)) func_001614E8(p, -1);
            break;
        }
    } while (p->state != state);
}
void func_001614E8(struct S0 *p, int state)
{
    if (p->state == state) return;
    p->state = state;
    p->tState = D_0036BB98.t;
    switch (state) {
    case -1:
        if (p->x4C) func_0023AC58(&p->x4C);
        if (p->x48) func_00137628(&p->x48);
        break;
    case 0:
    case 3:
    case 4:
        if (p->powner->x17D4) {
            func_0023AC58(&p->x4C);
            func_00137588(p->powner->x17D4, p->powner, 1, &p->x48, 0.0f, 1.0f);
        } else {
            func_001614E8(p, -1);
        }
        break;
    case 1:
        if (!p->powner->x17D8 || !p->powner->x17DC) {
            func_001614E8(p, -1);
        } else {
            func_00137628(&p->x48);
            func_0023AAE8(p->powner->x17DC, p->powner, 0x329, 1, &p->x4C);
            func_00239CE8(p->x4C, 0x32A);
        }
        break;
    }
}
/* Next .rodata items of the original unit (float literals read by a later function); they follow the jump table. */
const float D_00320B28 = -0.4f;
const float D_00320B2C = 0.4f;
