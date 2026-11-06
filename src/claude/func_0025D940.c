// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Send a message to an object by id (cf. Sly 2 src/hand/func_00210538.c).
struct VT { char pad[0x1B8]; short d; short pd; void (*pf)(void *, void *); };
struct X { char pad[0xC]; struct VT *pvt; };
struct MSG { unsigned int grf; struct X *p4; float g8; char padc[0x24]; struct X *p30; char pad34[0xC]; };
struct X *func_0017E1B8(void *pg, int k, int oid, void *ctx);
int func_0013B500(struct X *, int);
void func_001FE728(struct X *, int);
void func_0025D940(void *pg, int oid, int oid1, void *ctx, float g)
{
    struct X *x;
    struct MSG msg;
    if (oid == -1)
        return;
    x = func_0017E1B8(pg, 4, oid, ctx);
    if (!x)
        return;
    if (func_0013B500(x, 0x2D)) {
        func_001FE728(x, 1);
        __asm__("" : : "r"(ctx)); /* zero-insn: raises ctx's allocation priority */
        return;
    }
    msg.grf = 0;
    if (oid1 != -1) {
        struct X *y = func_0017E1B8(pg, 4, oid1, ctx);
        if (y) {
            msg.p4 = y;
            msg.grf |= 1;
        }
    }
    {
        unsigned int v = msg.grf;
        if ((v ^ 1) & 1) {
            msg.p4 = x;
            msg.grf = v | 1;
        }
    }
    if (g != 1.0f) {
        msg.g8 = g;
        msg.grf |= 0x18;
    }
    x->pvt->pf((char *)x + x->pvt->d, &msg);
}
