// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Move a world object (and optionally its children) to the proxy copy-tree node idProxy: the path is the ids from the
// root down to the object's current node with idProxy added at the end. Nodes the object owned are released and nodes
// of the new path that belong to single-object sources become the object's. Ported from Sly 2 LO::SetIdProxy
// (func_001CA118); here the vtable slots are viewed through offset-only structs.
struct FRAME { char b; FRAME(); ~FRAME(); };
struct LO;
struct VTE_SET { short delta; short pad; void (*method)(void *, int, int); };
struct VTE_CHILDREN { short delta; short pad; int (*method)(void *, LO ***); };
struct LOVT { char pad[0xD8]; VTE_SET setIdProxy; char padE0[0x108 - 0xE0]; VTE_CHILDREN ploChildren; };
struct PXR { int idProxy; PXR *ppxrParent; int pad8; int padC; LO *plo; };
struct PROXYSRC { int cplo; char pad[0x6C - 4]; };
struct SW { char pad[0x4630]; PROXYSRC *aproxysrc; PXR *ppxrRoot; };
struct LO { char pad[0xC]; LOVT *vt; char pad10[0x38 - 0x10]; PXR *ppxr; };
extern SW D_00475480;
extern "C" {
int func_001FA5B8(int idProxy);
PXR *func_001FA640(PXR *root, int cid, int *aid);
void func_001FAD68(LO *self, int idProxy, int fChildren);
}
inline PROXYSRC *PproxysrcFromIdProxy(int idProxy)
{
    return &D_00475480.aproxysrc[func_001FA5B8(idProxy)];
}
extern "C" void func_001FAD68(LO *self, int idProxy, int fChildren)
{
    int aid[16];
    int cid = 16;
    PXR *ppxrIter;
    for (ppxrIter = self->ppxr; ppxrIter; ppxrIter = ppxrIter->ppxrParent)
    {
        if (ppxrIter->idProxy == -1)
            break;
        aid[--cid] = ppxrIter->idProxy;
    }
    aid[--cid] = idProxy;
    PXR *ppxrNew = func_001FA640(D_00475480.ppxrRoot, 16 - cid, &aid[cid]);
    for (ppxrIter = self->ppxr; ppxrIter->idProxy != -1; ppxrIter = ppxrIter->ppxrParent)
    {
        if (ppxrIter->plo == self)
            ppxrIter->plo = 0;
        else
            break;
    }
    for (ppxrIter = ppxrNew; ppxrIter->idProxy != -1; ppxrIter = ppxrIter->ppxrParent)
    {
        if (PproxysrcFromIdProxy(ppxrIter->idProxy)->cplo == 1 && !ppxrIter->plo)
            ppxrIter->plo = self;
        else
            break;
    }
    self->ppxr = ppxrNew;
    if (fChildren)
    {
        FRAME scope;
        LO **aplo;
        int cplo = self->vt->ploChildren.method((char *)self + self->vt->ploChildren.delta, &aplo);
        for (int iplo = 0; iplo < cplo; iplo++)
        {
            LO *child = aplo[iplo];
            child->vt->setIdProxy.method((char *)child + child->vt->setIdProxy.delta, idProxy, 1);
        }
    }
}
