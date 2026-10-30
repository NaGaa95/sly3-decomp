// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { int id; int pad[2]; int c; };
struct X {
    char pad[0x360]; int x360; char pad1[0x3E4 - 0x364]; int x3E4; char pad2[0x3F0 - 0x3E8]; qword x3F0;
    int x400; char pad3[0x414 - 0x404]; struct E ae[8]; int x494; int x498; char pad4[0x10D0 - 0x49C]; int x10D0;
};
struct S0 { char pad[0x10]; struct X *px; };
extern char D_0036C700[], D_0036BD20[], D_00475480[];
void func_0016C980(struct S0 *p);
void func_001854C8(void *p, int n, struct X *px);
qword func_001C9428(struct X *px, int n, qword q);
void func_00171E50(void *p, qword q, int n, int a, struct X *px);
void func_0013CD10(void *p, struct X *px);
void func_00170360(int a);
void func_00257EC8(struct X *px, int n);
void func_0016D1B8(struct S0 *p)
{
    int n;
    func_0016C980(p);
    if (p->px->x360) return;
    p->px->x360 = 1;
    func_001854C8(D_0036C700, 0x10, p->px);
    if (p->px->x3E4 >= 0 || !p->px->x494) {
        n = p->px->x3E4;
    } else {
        int i;
        n = 0;
        for (i = p->px->x498; i < p->px->x494; i++) {
            struct E *pe = &p->px->ae[i];
            if (pe->id == 0x30A) n += pe->c;
        }
        n = (n + 1) / 2;
    }
    {
        qword q = func_001C9428(p->px, 0, p->px->x3F0);
        func_00171E50(D_0036BD20, q, n, p->px->x400, p->px);
    }
    func_0013CD10(D_00475480, p->px);
    func_00170360(p->px->x10D0);
    func_00257EC8(p->px, 0);
}
