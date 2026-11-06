// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Load one proxy of an object list: reads source id, mode, transform index, placement matrix and visibility mask.
// Mode 1 (or -1 when the source asks for it) creates a single PROXY object that keeps the source and reads its list of
// per-kind change records; any other mode takes the source's next copy right now, applies the records to the copy's
// objects and loads the nested object list under the proxy's transform. Based on Sly 2 func_001C9B08.
#include "../P2/object_collection.h"
#include "../P2/bis.h"
struct PROXYSRC {
    int cplo;
    SCENE_OBJECT **aplo;
    int ccopy;
    int icopyNext;
    char pad10[0x60 - 0x10];
    int fUnk60;
    char pad64[0x6C - 0x64];
};
struct PROXYINIT {
    int kind;
    int cid;
    void *pframe;
    int cb;
    void *pvOptions;
    SCENE_OBJECT *plo;
};
struct PROXY {
    void *pframe;
    char pad04[0x34 - 4];
    float sBusy;
    char pad38[0x40 - 0x38];
    void *pxfParent;
    char pad44[0x50 - 0x44];
    MATRIX4 mat;
    MATRIX4 matWorld;
    PROXYSRC *psrc;
    int mode;
    char padD8[0xDC - 0xD8];
    int cinit;
    PROXYINIT *ainit;
};
struct SW { char pad[0x4630]; PROXYSRC *aproxysrc; void *ppxrRoot; };
struct SWALLOC { int cb; int cbAlign; };
extern "C" {
int func_001FC1A8(SW *psw, int idSource);
int func_001FA5A8(int isrc, int icopy);
void *func_0028C250(int ixf, SCENE_OBJECT *psoParent, int fUnk);
void *func_00150690(int cid, SCENE_OBJECT *psoParent, int oid, int n);
void func_00290078(PROXY *pproxy);
void func_001C9198(void *plo, unsigned int grfvis);
void *func_001D2538(SWALLOC *pswalloc);
void *func_001D2470(SWALLOC *pswalloc);
void *func_00249B78(SW *psw, int isplice, void *plo);
void func_002BAA50(void *pref, void *pframe);
int func_0013B500(void *plo, int cid);
void func_001519C8(void *plo, CBinaryInputStream *pbis);
int func_0017DEC0(SW *psw, int grffso, int oid, void *ploContext, void *ppxr, int cploMax, SCENE_OBJECT **aplo);
void func_001FAFB0(SW *psw, int isrc, SCENE_OBJECT *psoParent, void *pxf, int oid, MATRIX4 *pmatProxy, OBJECT_COLLECTION *pcollector);
void *func_001FA640(void *ppxrParent, int cid, int *aid);
void func_00151D80(SCENE_OBJECT *psoParent, CBinaryInputStream *pbis, OBJECT_COLLECTION *pcollector);
void func_0028C210(void *pxf);
void func_0028C238(void *pxf);
void func_001D26D0();
void func_001D2720();
void func_001FA778(SW *psw, SCENE_OBJECT *psoParent, int cid, int oid, int isplice, CBinaryInputStream *pbis, OBJECT_COLLECTION_BASE *pcollector);
}
struct VTE_IDPROXY { short delta; short pad; void (*method)(void *, int, int); };
struct VTE_APPLY { short delta; short pad; void (*method)(void *, MATRIX4 *); };
inline void SetIdProxy(SCENE_OBJECT *plo, int idProxy, int fChildren)
{
    VTE_IDPROXY *entry = (VTE_IDPROXY *)&plo->vtable[27];
    entry->method((char *)plo + entry->delta, idProxy, fChildren);
}
inline void ApplyProxy(SCENE_OBJECT *plo, MATRIX4 *pmat)
{
    VTE_APPLY *entry = (VTE_APPLY *)&plo->vtable[42];
    entry->method((char *)plo + entry->delta, pmat);
}
inline void *PvAllocSwClear(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    SWALLOC *pswalloc = &swalloc;
    pswalloc->cbAlign = cbAlign;
    return func_001D2538(pswalloc);
}
inline void *PvAllocSw(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    SWALLOC *pswalloc = &swalloc;
    pswalloc->cbAlign = cbAlign;
    return func_001D2470(pswalloc);
}
inline PROXY *NewProxy(int cid, SCENE_OBJECT *psoParent, int oid)
{
    return (PROXY *)func_00150690(cid, psoParent, oid, -1);
}
extern "C" void func_001FA778(SW *psw, SCENE_OBJECT *psoParent, int cid, int oid, int isplice, CBinaryInputStream *pbis, OBJECT_COLLECTION_BASE *pcollector)
{
    int idSource = pbis->S32Read();
    int mode = pbis->S8Read();
    int ixf = pbis->S16Read();
    void *pxf = func_0028C250(ixf, psoParent, 0);
    MATRIX4 mat;
    pbis->ReadMatrix4(&mat);
    unsigned int grfvis = pbis->U32Read();
    int isrc = func_001FC1A8(psw, idSource);
    int idProxy = func_001FA5A8(isrc, psw->aproxysrc[isrc].icopyNext);
    if (mode == -1)
        mode = psw->aproxysrc[isrc].fUnk60 != 0;
    if (mode > 0) {
        PROXY *pproxy = NewProxy(cid, psoParent, oid);
        pproxy->mode = mode;
        pproxy->pxfParent = pxf;
        pproxy->mat = mat;
        func_00290078(pproxy);
        func_001C9198(pproxy, grfvis);
        pproxy->psrc = &psw->aproxysrc[isrc];
        if (pproxy->psrc->cplo > 0)
            pproxy->sBusy = pproxy->psrc->aplo[pproxy->psrc->cplo * pproxy->psrc->ccopy - 1]->time34;
        pproxy->cinit = pbis->U8Read();
        pproxy->ainit = (PROXYINIT *)PvAllocSwClear(pproxy->cinit * sizeof(PROXYINIT), 0x10);
        for (int iinit = 0; iinit < pproxy->cinit; iinit++) {
            PROXYINIT *pinit = &pproxy->ainit[iinit];
            pinit->kind = pbis->S32Read();
            pinit->cid = pbis->S16Read();
            int isplice = pbis->S16Read();
            if (isplice != -1)
                pinit->pframe = func_00249B78(psw, isplice, 0);
            if (pinit->kind == 7) {
                func_002BAA50(pproxy, pinit->pframe);
                int cb = pbis->U16Read();
                if (!func_0013B500(pproxy, pinit->cid))
                    pbis->Skip(cb);
                else
                    func_001519C8(pproxy, pbis);
            } else {
                pinit->cb = pbis->U16Read();
                pinit->pvOptions = PvAllocSw(pinit->cb, 0x10);
                pbis->Read(pinit->cb, pinit->pvOptions);
            }
        }
        int cbList = pbis->S32Read();
        pbis->S16Read();
        pbis->Skip(cbList - 2);
        if (pcollector)
            pcollector->Append(1, (SCENE_OBJECT **)&pproxy);
    } else {
        if (!pcollector)
            func_001D26D0();
        OBJECT_COLLECTION listCopy;
        func_001FAFB0(psw, isrc, psoParent, pxf, oid, &mat, &listCopy);
        for (int iplo = 0; iplo < listCopy.count; iplo++) {
            SCENE_OBJECT *plo = listCopy.values[iplo];
            if (!plo->flags.fields.unknown54)
                func_001C9198(plo, grfvis);
        }
        void *ppxr;
        if (!listCopy.count)
            ppxr = 0;
        else
            ppxr = func_001FA640(psw->ppxrRoot, 1, &idProxy);
        int cinit = pbis->U8Read();
        for (int iinit = 0; iinit < cinit; iinit++) {
            SCENE_OBJECT *plo = 0;
            int kind = pbis->S32Read();
            int cidTarget = pbis->S16Read();
            if (ppxr) {
                if ((unsigned int)(kind - 7) < 2)
                    plo = listCopy.values[0];
                else
                    func_0017DEC0(psw, 0xA05, kind, 0, ppxr, 1, &plo);
            }
            if (plo && !func_0013B500(plo, cidTarget))
                plo = 0;
            int isplice = pbis->S16Read();
            if (plo && isplice != -1) {
                char *pframe = (char *)func_00249B78(psw, isplice, plo);
                func_002BAA50(pframe + 8, *(void **)plo);
                func_002BAA50(plo, pframe);
            }
            int cb = pbis->U16Read();
            if (plo)
                func_001519C8(plo, pbis);
            else
                pbis->Skip(cb);
        }
        OBJECT_COLLECTION listNested;
        pbis->S32Read();
        func_0028C210(pxf);
        func_00151D80(psoParent, pbis, &listNested);
        func_0028C238(pxf);
        for (int iplo = 0; iplo < listNested.count; iplo++) {
            SCENE_OBJECT *plo = listNested.values[iplo];
            SetIdProxy(plo, idProxy, 1);
            ApplyProxy(plo, &mat);
            if (!plo->flags.fields.unknown54)
                func_001C9198(plo, grfvis);
        }
        if (!pcollector)
            func_001D2720();
        else {
            pcollector->Append(listCopy.count, listCopy.values);
            pcollector->Append(listNested.count, listNested.values);
        }
    }
}
