// SLY3_CFLAGS: -Os -G0
extern int D_0036DBEC;
extern char D_0036E340[];
extern char *D_0036C328;
char *func_00168968(unsigned int flags)
{
    if(!((D_0036DBEC>>1)&1) || (flags&4)) return D_0036E340;
    return D_0036C328+0x100;
}
