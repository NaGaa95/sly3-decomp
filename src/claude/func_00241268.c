// SLY3_CFLAGS: -Os -G0
// Find the object (kind 2, oid 0x1A6) relative to p; report it as missing if absent.
extern char D_00475480[];
void *func_0017E1B8(void *psw, int n, int oid, void *p);
void func_00150690(int n, void *p, int oid, int m);
void func_00241268(void *p)
{
    if (!func_0017E1B8(D_00475480, 2, 0x1A6, p))
        func_00150690(0x11, p, 0x1A6, -1);
}
