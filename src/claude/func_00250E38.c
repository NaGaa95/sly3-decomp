// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct BITS { unsigned char ab[16]; };
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct VT { char pad[0x40]; struct VTE e40; struct VTE e48; char pad50[0x120 - 0x50]; struct VTE e120; };
struct O { char pad[0xC]; struct VT *pvt; };
struct XF { char pad[0x30]; qword pos; };
struct LINK { char pad[8]; void *p8; };
struct ACT { char pad[0xD0]; void *pD0; void *pD4; };
struct SUB { char pad[0xA0]; };
struct P {
    char pad[0xC]; struct VT *pvt; char pad10[0x29C - 0x10]; char x29C[0x32C - 0x29C]; struct LINK *p32C;
    qword q330; float f340; char pad344[0x4AC - 0x344]; int n4AC; char pad4B0[0x1024 - 0x4B0]; int n1024; int n1028;
    char pad102C[0x10D0 - 0x102C]; struct ACT *p10D0; void *p10D4; char pad10D8[0x1148 - 0x10D8]; struct O *p1148;
    char pad114C[0x11C8 - 0x114C]; struct O *p11C8; char pad11CC[0x11E8 - 0x11CC]; int c11E8; struct SUB a11EC[1];
};
extern struct BITS D_00475440;
extern int D_0036B334;
void func_0024DA88(struct P *p);
int func_001F43F0(void *self);
void func_001F43D0(void *p, int a);
void func_00252DE0(struct P *p, struct BITS *grf);
float atan2f(float y, float x);
void func_0024E878(void *self, float value);
void func_001C7A00(void *a, void *b, int c);
void func_00170018(void *receiver, int, int);
void func_0016FE30(void *receiver, int, int);
void func_001F1A30(struct P *);
void func_001F1CF8(struct P *);
struct O *func_00238690(void *list, int kind);
void func_00253AA8(void *);
void func_00257B80(struct SUB *);
void func_00250E38(struct P *p)
{
    int i;
    struct O *o;
    float *pv;
    qword *pq = &p->q330;
    func_0024DA88(p);
    func_001F43D0(p, func_001F43F0(p));
    p->n1028 = p->n1024;
    func_00252DE0(p, &D_00475440);
    p->q330 = ((struct XF *)p->pvt->e120.pfn((char *)p + p->pvt->e120.d))->pos;
    pv = (float *)p->pvt->e120.pfn((char *)p + p->pvt->e120.d);
    p->f340 = atan2f(pv[1], pv[0]);
    p->p32C->p8 = pq;
    func_0024E878(p, p->f340);
    func_001C7A00(p->p10D0, p, 0xF);
    p->p10D0->pD0 = p;
    func_00170018(p->p10D0, D_0036B334, 3);
    func_0016FE30(p->p10D0, 0x33, 4);
    func_0016FE30(p->p10D0, 0x56, 5);
    if (p->n4AC) {
        func_001F1A30(p);
        func_001F1CF8(p);
    }
    if (p->p1148) p->p1148->pvt->e48.pfn((char *)p->p1148 + p->p1148->pvt->e48.d);
    if (p->p11C8) p->p11C8->pvt->e48.pfn((char *)p->p11C8 + p->p11C8->pvt->e48.d);
    o = func_00238690(p->x29C, 0xC8);
    o->pvt->e40.pfn((char *)o + o->pvt->e40.d);
    p->p10D0->pD4 = p->p10D4 ? p->p10D4 : p;
    func_00253AA8(p);
    for (i = 0; i < p->c11E8; i++)
        func_00257B80(&p->a11EC[i]);
}
