// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *); };
struct VT { char pad[0x48]; struct VTE e48; };
struct LO { char pad[0xC]; struct VT *pvt; char pad10[0x40 - 0x10]; void *p40; };
struct P {
    char pad[0x18]; void *p18; char pad1C[0x48 - 0x1C]; void *p48; void *p4C;
    char pad50[0x290 - 0x50]; float f290; char pad294[0x328 - 0x294]; struct LO *p328; void *p32C;
    char pad330[0x404 - 0x330]; struct LO *p404; struct LO *p408; char pad40C[0x4B0 - 0x40C];
    char x4B0[0x4C4 - 0x4B0]; void *p4C4; char pad4C8[0x11D4 - 0x4C8]; void *p11D4; void *p11D8;
};
extern char D_003498E0[];
extern qword D_00317570;
void func_0024D9D8(void *s);
void func_001C8970(void *p, int k, void *pv, int n);
void func_0024F1E8(void *pjt, float g);
void func_0028F068(void *receiver, void *channel, int mode);
void func_002538C8(void *p);
void func_00256788(void *p);
void *func_001D27F0(unsigned int size);
void func_00259D60(void *a, void *b);
void func_002599E8(void *a, void *b);
void *func_00150690(int kind, void *owner, int id, int option);
void func_00197420(void *receiver, int a, int b, int c, float g, int d);
void func_001975C8(void *p);
void *func_0023DDA0(void *owner, void *identity, int kind);
void *func_00130078(void *owner, void *channel, int a, int b, int c, qword value);
void func_00250BD8(struct P *p)
{
    func_0024D9D8(p);
    func_001C8970(p, 2, D_003498E0, 0);
    func_0024F1E8(p, p->f290);
    func_0028F068(p, p->p48, 2);
    func_0028F068(p, p->p4C, 2);
    func_002538C8(p);
    func_00256788(p);
    p->p4C4 = func_001D27F0(0x14);
    func_00259D60(p->p4C4, p);
    func_002599E8(p->x4B0, p);
    p->p328 = (struct LO *)func_00150690(0x86, 0, 0x322, -1);
    func_00197420(p->p328, -1, -1, -1, 40.0f, 1);
    func_001975C8(p->p328);
    p->p32C = p->p328->p40;
    p->p328->pvt->e48.pfn((char *)p->p328 + p->p328->pvt->e48.d);
    if (p->p404) p->p404->pvt->e48.pfn((char *)p->p404 + p->p404->pvt->e48.d);
    if (p->p408) p->p408->pvt->e48.pfn((char *)p->p408 + p->p408->pvt->e48.d);
    p->p11D4 = func_0023DDA0(p, p->p18, 0xC);
    if (p->p11D4)
        p->p11D8 = func_00130078(p, p->p11D4, 0, 8, 2, D_00317570);
}
