// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x1520]; int n13D0; char pad1[0x156C - 0x1524]; void *p1430; char pad2[0x18E0 - 0x1570]; int a1910[1]; };
int func_00156948(char *p, void *pv);
int func_001C8F20(void *pv, void *p1);
int func_0013CD00(int n, int k);
int func_00272FB0(int *pn, void *pv, int n);
int func_001E0D68(struct P *p, void *pv)
{
    int n = func_00156948((char *)p, pv);
    if (p->p1430 && func_001C8F20(pv, p->p1430))
        n = func_0013CD00(n, 3);
    else if (p->n13D0 == 16)
        n = func_00272FB0(p->a1910, pv, n);
    return n;
}
