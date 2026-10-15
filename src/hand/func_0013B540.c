// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
// The factory result, stored reference and both helper arguments carry pointers.
struct S { int f0; void *f4; };
void *func_002BB7F0(void);
void func_002BBF40(void *reference, void *script);
void func_002BBFA8(void *object);
void func_0013B540(struct S *p) {
    void **pf = &p->f4;
    if (p->f4 == 0) { func_002BBF40(pf, func_002BB7F0()); func_002BBFA8(p->f4); }
}
