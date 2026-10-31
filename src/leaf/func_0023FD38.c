// SLY3_CFLAGS: -Os -G0
// Flag bit 58 of the packed 64-bit word at +0x120: setter (also notifies the global object table) and getter.
struct Object {
    char unknown0[0x120];
    unsigned long low58 : 58; unsigned long flag58 : 1; unsigned long high5 : 5;
};
extern char D_00475480[];
void func_0013CD10(void *game, void *owner);

void func_0023FD38(struct Object *p, unsigned int enabled)
{
    p->flag58 = enabled;
    func_0013CD10(D_00475480, p);
}

unsigned long func_0023FD98(struct Object *p)
{
    return p->flag58;
}
