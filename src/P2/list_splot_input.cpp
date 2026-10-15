// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SPLOTENTRY {
    int *an;
    int c;
    void (*pfn)(void *);
    void *pv;
    int i;
    int fRemove;
    SPLOTENTRY *next;
};
struct SPLOTLIST { SPLOTENTRY *first; SPLOTENTRY *last; int ibNext; float g; };
struct SPLOTINPUT {
    char pad0[0x18];
    int buttons;
    char pad1C[0x1068 - 0x1C];
    int previousButtons;
};
extern "C" int D_0046F74C;
extern "C" int func_0025E150();
extern "C" float g_splotTime;

extern "C" void func_00163F58(SPLOTLIST *p, SPLOTINPUT *input)
{
    if (!D_0046F74C && func_0025E150())
        return;
    int buttons = input->buttons & ~input->previousButtons;
    if (!buttons)
        return;
    for (SPLOTENTRY *n = p->first; n; n = n->next)
    {
        int fDone = n->i >= n->c;
        if (!fDone)
        {
            if (n->an[n->i] == buttons)
                n->i++;
            else
                n->i = 0;
        }
    }
    p->g = g_splotTime + 1.0f;
}
