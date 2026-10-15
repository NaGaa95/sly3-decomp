// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int f0; int f4; };
int func_002BB7F0(void);
void func_002BBF40(int *, int);
void func_002BBFA8(int);
void func_0013B540(struct S *p) {
    int *pf = &p->f4;
    if (p->f4 == 0) { func_002BBF40(pf, func_002BB7F0()); func_002BBFA8(p->f4); }
}
