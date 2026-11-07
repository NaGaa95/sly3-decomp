// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *); };
struct VT { char pad[0x48]; VTE e48; };
struct LO { char pad[0x20]; LO *next20; char pad24[0x3C - 0x24]; unsigned int grf3C; char pad40[0x70 - 0x40]; char x70[0xBC - 0x70]; int nBC; };
struct SW { char pad[0xC]; VT *pvt; char pad10[0x44F8 - 0x10]; int n44F8; };
struct BATCH { char pad[0x30]; int grf30; };
class ObjectToken { public: ~ObjectToken(); };
struct ObjectBucket { LO *head; };
extern "C" {
extern BATCH *D_0036C328;
extern qword *D_00468D00;
extern qword D_00447B00[];
void func_001C5E08(SW *);
ObjectBucket *func_0017DBD0(void *psw, int k);
int func_0013BEC8(int k, int cid);
void func_00182C68(void);
void func_00182EE0(void);
void func_0018E0B8(void *);
void func_0025C128(SW *psw);
}
static inline unsigned int Grf(LO *plo)
{
    unsigned int grf = plo->grf3C;
    if (!(grf & 1)) grf = *(unsigned int *)grf;
    return grf;
}
void func_0025C128(SW *psw)
{
    int k;
    LO *p;
    func_001C5E08(psw);
    for (k = 0x2F; func_0013BEC8(k, 0x2F); k++) {
        ObjectToken token;
        func_0017DBD0(psw, k);
        for (p = func_0017DBD0(psw, k)->head; p; p = p->next20) {
            if (!(Grf(p) & 8)) continue;
            if (p->nBC == psw->n44F8) continue;
            if (!D_0036C328) {
                func_00182C68();
                D_0036C328->grf30 &= ~0xF;
                D_00468D00 = D_00447B00;
            }
            func_0018E0B8(p->x70);
            if (D_00468D00 - D_00447B00 >= 0x200) {
                psw->pvt->e48.pfn((char *)psw + psw->pvt->e48.d);
                func_00182EE0();
            }
        }
    }
    if (D_0036C328) {
        psw->pvt->e48.pfn((char *)psw + psw->pvt->e48.d);
        func_00182EE0();
    }
}
