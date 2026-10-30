// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_00149C80.cpp (callback/event pump; node release now via its out-of-line dtor).
extern "C" void func_0011E1F0(void *pheap, void *pv);
struct NODE {
    short x0;
    short cref;
};
extern "C" void func_002BA840(NODE *pn, int flags);   /* NODE's deleting destructor */
struct O { int cref; };
extern "C" void func_002BABA8(O *, int);
struct SP {
    O *p;
    SP(const SP &r);
    ~SP() { O *q = p; if (q && --q->cref == 0) func_002BABA8(q, 3); }
};
struct OSP { O *p; };
extern "C" {
int func_002BA9A8(void);
SP func_002BAB88(int);
void func_0013B9A0(void *pv, NODE *pn, O *po, int n);
}

struct CObj { virtual void Dummy(); };
struct CB {
    CObj *pobj;
    void (CObj::*pmf)(int);
    int arg;
    CB *pnext;
};
struct EV {
    float t;
    OSP *posp;
    NODE *pnode;
    int nC;
};
struct LIST { void *pvFirst; void *pvLast; int ib; };
struct CLOCK { float t; };
extern "C" CLOCK g_clock;

struct MGR {
    char pad[0x3F20];
    LIST levs;          /* 3F20 */
    char poolEv[0x442C - 0x3F2C];
    char poolCb[0x4444 - 0x442C];
    LIST lcbs;          /* 4444 */
};

extern "C" {
void func_0011AD70(LIST *pl);
int func_0011AEF8(LIST *pl);
void func_0011AE28(LIST *pl, void *pv);
void func_0015DE78(MGR *p);
}

void func_0015DE78(MGR *p)
{
    while (!func_0011AEF8(&p->lcbs)) {
        CB *pcb = (CB *)p->lcbs.pvFirst;
        func_0011AD70(&p->lcbs);
        while (pcb) {
            void (CObj::*pmf)(int) = pcb->pmf;
            (pcb->pobj->*pmf)(pcb->arg);
            CB *pcbNext = pcb->pnext;
            func_0011E1F0(p->poolCb, pcb);
            pcb = pcbNext;
        }
    }

    EV *pev;
    while ((pev = (EV *)p->levs.pvFirst) != 0) {
        if (g_clock.t < pev->t)
            break;
        pev->nC = -1;
        OSP *posp = pev->posp;
        if (posp) {
            func_0013B9A0(posp, pev->pnode, posp->p, 0);
        } else {
            int x = func_002BA9A8();
            SP sp = func_002BAB88(x);
            func_0013B9A0(p, pev->pnode, sp.p, 0);
        }
        func_0011AE28(&p->levs, pev);
        NODE *pn = pev->pnode;
        if (--pn->cref == 0) {
            if (pn)
                func_002BA840(pn, 3);
        }
        func_0011E1F0(p->poolEv, pev);
    }
}
