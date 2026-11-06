// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { char pad[0x40]; struct VTE e7; struct VTE e8; };
struct O { char pad[0xC]; struct VT *pvt; };
struct P107C { char pad[0xB0]; char sub[1]; };
struct S {
    char pad0[0x2F]; unsigned long f2F : 8;
    char pad30[0x218 - 0x30]; int n218;
    char pad21C[0x29C - 0x21C]; char a29C[0x36C - 0x29C];
    void *p36C; char pad370[0x49C - 0x370]; int n49C;
    char pad4A0[0x4B0 - 0x4A0]; char a4B0[0x4C4 - 0x4B0]; void *p4C4;
    char pad4C8[0x107C - 0x4C8]; struct P107C *p107C; char pad1080[0x1088 - 0x1080]; int n1088;
    char pad108C[0x10F0 - 0x108C]; int n10F0;
    char pad10F4[0x112C - 0x10F4]; int k;
    char pad1130[0x11C8 - 0x1130]; struct O *p11C8;
    char pad11CC[0x16EC - 0x11CC]; int n16EC; char a16F0[1];
};
extern qword D_00317560;
extern const int D_003273C8[3];
void func_0024E1A0(struct S *);
void func_002517C0(struct S *);
void func_00251150(struct S *);
int func_00254EB8(void *);
void func_00256828(struct S *, int, int, qword);
void func_00256980(struct S *);
void func_001F1CF8(struct S *);
void func_00259A40(void *);
void func_00259DB0(void *);
void func_00251AD0(struct S *);
void func_002385A8(void *);
int func_00138AC8(void *);
void func_00137688(void *);
int func_002533C0(struct S *, int);
void func_0024FCA0(struct S *, void *);
void func_00251880(struct S *p)
{
    func_0024E1A0(p);
    if (!(p->f2F & 1) || p->k == 0x16)
        return;
    func_002517C0(p);
    func_00251150(p);
    if (p->p107C && func_00254EB8(p->p107C->sub))
        func_00256828(p, 0, 0, D_00317560);
    if (p->n1088)
        func_00256980(p);
    if (p->n49C)
        func_001F1CF8(p);
    func_00259A40(p->a4B0);
    func_00259DB0(p->p4C4);
    func_00251AD0(p);
    func_002385A8(p->a29C);
    if (p->p36C && func_00138AC8(p->p36C))
        func_00137688(&p->p36C);
    if (p->p11C8) {
        int f = 0;
        unsigned int i;
        if (!func_002533C0(p, 0x41) && !func_002533C0(p, 6)) {
            for (i = 0; i < 3; i++) {
                if (func_002533C0(p, D_003273C8[i])) {
                    f = 1;
                    break;
                }
            }
        }
        if (f) {
            struct O *o = p->p11C8;
            o->pvt->e8.pfn((char *)o + o->pvt->e8.d);
        } else {
            struct O *o = p->p11C8;
            o->pvt->e7.pfn((char *)o + o->pvt->e7.d);
        }
    }
    if (p->n16EC && p->n10F0 == -1 && p->n218)
        func_0024FCA0(p, p->a16F0);
}
