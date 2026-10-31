// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0017E208: collect objects of a class id (parents / children / class list / scoped search); Sly 2 func_0015E9C8.
typedef struct LO LO;
typedef struct CH CH;
struct LO {
    char unused00[0x10];
    LO *parent;
    int unused14;
    int key;
    int unused1C;
    LO *next_key;
    LO *sibling;
    union {
        unsigned long flags;
        struct {
            unsigned long reserved40 : 40;
            unsigned int priority : 4;
            unsigned int reserved44 : 12;
            unsigned int enabled : 1;
        } bits;
    } packed;
    char unused30[0x54 - 0x30];
    LO *child;
    char unused58[0x60 - 0x58];
    LO *child_end;
};
class ObjectToken { public: ~ObjectToken(); };
struct ObjectBucket { LO *head; };
extern "C" {
int func_0013B500(LO *plo, int cid);
ObjectBucket *func_0017DBD0(void *psw, int k);
int func_0013BEC8(int k, int cid);
void func_0017DC10(void *pv, LO *plo, CH *pch, unsigned int grf, LO *ctx, CH *pchList, int cMax, int *pc, LO **aplo, int *pips);
int func_0017E208(void *psw, int grf, int cid, LO *ploCtx, int cMax, LO **aplo);
}
int func_0017E208(void *psw, int grf, int cid, LO *ploCtx, int cMax, LO **aplo)
{
    int cplo;
    int ips;
    LO *plo;
    LO *p;
    int k;
    if (cid == -1 || (!ploCtx && (grf & 0xFF) != 5))
        return 0;
    cplo = 0;
    switch (grf & 0xFF) {
    case 3:
        for (p = ploCtx->parent; p; p = p->parent) {
            if (!func_0013B500(p, cid))
                continue;
            if ((grf & 0x100) && ((int)(p->packed.flags >> 56) & 1) == 0)
                continue;
            if (cplo < cMax)
                aplo[cplo] = p;
            cplo++;
        }
        break;
    case 2: {
        LO *pEnd = 0;
        if (grf & 0x100)
            pEnd = ploCtx->child_end;
        for (p = ploCtx->child; p != pEnd; p = p->sibling) {
            if (!func_0013B500(p, cid))
                continue;
            if (cplo < cMax)
                aplo[cplo] = p;
            cplo++;
        }
        break;
    }
    case 5: {
        for (k = cid; k < 249 && func_0013BEC8(k, cid); k++) {
            ObjectToken token;
            func_0017DBD0(psw, k);
            for (p = func_0017DBD0(psw, k)->head; p; p = p->next_key) {
                if ((grf & 0x100) && ((int)(p->packed.flags >> 56) & 1) == 0)
                    continue;
                if (cplo < cMax)
                    aplo[cplo] = p;
                cplo++;
            }
        }
        break;
    }
    default:
        switch (grf & 0xFF) {
        case 1:
        case 3:
        case 4:
        case 5: {
            int i = 0;
            p = ploCtx;
            plo = p;
            for (; p; p = p->parent)
                p->packed.bits.priority = ++i;
            ips = 0x7FFFFFFF;
            break;
        }
        default:
            plo = 0;
            break;
        }
        for (k = cid; k < 249 && func_0013BEC8(k, cid); k++) {
            ObjectToken token;
            func_0017DBD0(psw, k);
            for (p = func_0017DBD0(psw, k)->head; p; p = p->next_key)
                func_0017DC10(psw, p, 0, grf | 0x400, ploCtx, 0, cMax, &cplo, aplo, &ips);
        }
        for (p = plo; p; p = p->parent)
            p->packed.bits.priority = 0;
        break;
    }
    if (!(grf & 0x200) && cMax < cplo)
        cplo = cMax;
    return cplo;
}
