// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_00129DF8.c (Sly 3: short tag, tags 2 lower, one more case).
typedef struct VT { short d; short pad; void (*pfn)(void *); } VT;
typedef struct O { char pad[0xC]; VT *vt; } O;
typedef struct CRef { short m_tagk; union { int *pn; char *pb; O *po; } u; } CRef;
void func_0012BB38(CRef *pref)
{
    switch (pref->m_tagk) {
    case 0x19:
        (*(int *)(pref->u.pb + 0x40))++;
        break;
    case 0x18:
    case 0x1A:
        (*(int *)(pref->u.pb + 0x10))++;
        break;
    case 0x1B:
        (*(int *)(pref->u.pb + 0x8))++;
        break;
    case 0x1C:
        (*(int *)(pref->u.pb + 0xC))++;
        break;
    case 0x1D:
        (*(unsigned short *)(pref->u.pb + 0x2))++;
        break;
    case 0x1F: {
        O *po = pref->u.po;
        if (po)
            po->vt[1].pfn((char *)po + po->vt[1].d);
        break;
    }
    case 0x1E:
    case 0x20:
        (*pref->u.pn)++;
        break;
    }
}
