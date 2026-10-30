// SLY3_CFLAGS: -Os -G0
/* JT::FCanUseGadget (Sly 2 func_0018D760 shape); owns jump tables 0x31FE20/0x31FE70/0x31FEA0. */
struct CID { char pad[0x13C]; int idGadget; };
struct POCKET { int x0; void *pproxy; void *pcid; };
struct JT {
    char pad0[0x320]; char jtair[0x500 - 0x320]; char jtgrab[0x1108 - 0x500]; void *p1108;
    char pad1[0x1294 - 0x110C]; unsigned int nThrow; char pad2[0x12A0 - 0x1298]; struct CID *ploCarried;
    char pad3[0x1520 - 0x12A4]; int jts; char pad4[0x1868 - 0x1524]; int x1868;
    char pad5[0x193C - 0x186C]; int x193C; int x1940; char pad6[0x194C - 0x1944]; int x194C;
    char pad7[0x19B8 - 0x1950]; int x19B8;
};
int func_00156998(struct JT *);
int func_0021F410(int);
int func_00154518(struct JT *, int);
int func_00173428(void *);
int func_001BD830(void *, int);
int func_001B5D08(void *, int);
struct POCKET *func_001400C0(struct JT *, int);
int func_00277588(void *);
void *func_001FBA28(void *, int);
static inline int F1108(struct JT *p) { return p->p1108 && func_00173428(p->p1108); }
int func_0013FE50(struct JT *p, int id)
{
    int f;
    if (id == 7 && p->x194C) {
        if (func_00156998(p))
            return 0;
        f = func_0021F410(7);
    } else
        f = func_00154518(p, id);
    if (!f)
        return 0;
    if (p->x193C)
        return 0;
    if (p->x1940)
        return 0;
    if (id != 3) {
        if (id == 7) {
            if (F1108(p) && !p->x194C)
                return 0;
        } else if (F1108(p))
            return 0;
    }
    switch (p->jts) {
    case 2:
        if (!func_001BD830(p->jtair, id))
            return 0;
        break;
    case 3:
        if (!func_001B5D08(p->jtgrab, id))
            return 0;
        break;
    case 14:
        if (p->nThrow - 4 < 3) {
            switch (id) {
            case 6:
            case 8:
            case 10:
            case 13:
            case 15:
            case 16:
                if (p->ploCarried->idGadget == id)
                    return 1;
            }
        }
        return 0;
    case 0:
    case 1:
    case 5:
    case 6:
    case 7:
    case 9:
    case 17:
        break;
    default:
        return 0;
    }
    switch (id) {
    case 7:
        if (p->x1868)
            goto ret1;
        return 0;
    case 4:
    case 6:
    case 8:
    case 10:
    case 15:
    case 16: {
        struct POCKET *pp = func_001400C0(p, id);
        if (pp->pcid) {
            if (func_00277588(pp->pcid))
                return 1;
        } else {
            if (!pp->pproxy)
                return 0;
            if (func_001FBA28(pp->pproxy, 2))
                return 1;
        }
        return 0;
    }
    case 13: {
        struct POCKET *pp;
        if (p->x19B8)
            return 1;
        pp = func_001400C0(p, id);
        if (!pp->pproxy)
            return 0;
        if (func_001FBA28(pp->pproxy, 2))
            return 1;
    }
    default:
        return 0;
    case 1:
    case 2:
    case 3:
    case 9:
    case 12:
    case 14:
    ret1:
        return 1;
    }
}
