// Filter resolver candidates using their actual parent and packed flag fields.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct LO LO;
struct LO {
    char pad[0x10];
    LO *pParent;
    char pad14[0x14];
    union {
        unsigned long flags;
        struct {
            unsigned long reserved40 : 40;
            unsigned int priority : 4;
            unsigned int reserved44 : 12;
            unsigned int enabled : 1;
        } b;
    } bits;
};
#define PRIORITY(p) (((p)->bits.flags >> 40) & 15UL)
#define KIND(p) ((long)((p)->bits.flags << 16) >> 60)
#define ENABLED(p) ((p)->bits.b.enabled)

typedef struct CH { int handle; struct CH *pNext; } CH;
typedef char CheckLongSize[(sizeof(long) == 8) ? 1 : -1];
typedef char CheckFlagViewSize[(sizeof(LO) == 48) ? 1 : -1];
typedef char CheckChainNodeSize[(sizeof(CH) == 8) ? 1 : -1];
extern int func_001FA5B8(int);

void func_0017DC10(void *pv, LO *plo, CH *pch, unsigned int grf,
                   void *ctx, CH *pchList, int cMax, int *pc,
                   LO **aplo, int *pips)
{
    LO *p;
    if (!(grf & 0x400)) {
        CH *q;
        switch (KIND(plo)) {
        case 0:
            q = pchList;
            while (1) {
                if (!q)
                    return;
                if (func_001FA5B8(q->handle) == func_001FA5B8(pch->handle))
                    break;
                if (grf & 0x800)
                    return;
                q = q->pNext;
            }
            break;
        case -1:
            while (pchList != pch) {
                if (!pchList || (grf & 0x800))
                    return;
                pchList = pchList->pNext;
            }
            break;
        case 1:
            break;
        }
    }
LMatch:
    switch (grf & 0xFF) {
    case 2:
        if (plo->pParent == ctx)
            goto LAdd;
        return;
    case 1:
        for (p = plo; p; p = p->pParent) {
            if (PRIORITY(p) == 0UL)
                continue;
            if (PRIORITY(p) == 1UL)
                goto LAdd;
            return;
        }
        return;
    case 3:
        if (PRIORITY(plo) >= 2UL)
            goto LAdd;
        return;
    case 4: {
        for (p = plo; p; p = p->pParent) {
            if ((p->bits.flags & (15UL << 40)) != 0 &&
                (unsigned int)p->bits.b.priority < (unsigned int)*pips) {
                unsigned int i = p->bits.b.priority;
                if ((grf & 0x100) && ENABLED(plo) == 0)
                    return;
                *pips = i;
                *pc = 0;
                goto LAdd2;
            }
        }
        if (*pips != 0x7FFFFFFF || p)
            return;
        goto LAdd;
    }
    case 5:
    LAdd:
        if ((grf & 0x100) && ENABLED(plo) == 0)
            return;
    LAdd2:
        if (*pc < cMax)
            aplo[*pc] = plo;
        (*pc)++;
        break;
    }
}
