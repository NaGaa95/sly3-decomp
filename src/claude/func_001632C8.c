// Sly 2 reference: /home/claude/decomp src/hand/func_001471C0.c.
void func_001F3B50(void *p);
void func_001C9118(void *p, int n);
extern char *D_0036BB80;
void func_001632C8(char *p)
{
    unsigned int v;
    func_001F3B50(p);
    D_0036BB80 = p;
    *(int *)(p + 0x198) = -1;
    *(int *)(p + 0x190) = -1;
    *(int *)(p + 0x1B8) = -1;
    func_001C9118(p, 1);
    v = *(unsigned int *)(p + 0x3C);
    if ((v ^ 1) & 1) *(int *)v |= 2;
    else *(unsigned int *)(p + 0x3C) = v | 2;
}
