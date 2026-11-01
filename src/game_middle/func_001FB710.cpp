// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Take a locked spare copy away from its proxy: invert and reset the spare's matrix, then for every object of the
// source's copy undo the splice frames, tell the proxy, remove the object, move it back by the inverse matrix, drop
// its parent and (for solid objects) restore the source's rest pose; finally unlink the spare from the proxy's list.
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct LO;
struct PROXYSPARE {
    struct PROXY *pproxy;
    PROXYSPARE *pspareNext;
    int fLocked;
    int pad0C;
    MATRIX4 mat;
};
struct PROXYREST { qword pos; float mat[3][4]; };
struct PROXYSRC {
    int cplo;
    LO **aplo;
    int ccopy;
    int icopyNext;
    char pad10[0x64 - 0x10];
    PROXYREST *aposRest;
    PROXYSPARE *aspare;
};
struct PROXYINIT {
    int kind;
    int cid;
    void *pframe;
    int cb;
    void *pvOptions;
    LO *plo;
};
struct PROXY {
    char pad00[0xC];
    void **vtable;
    char pad10[0xD0 - 0x10];
    PROXYSRC *psrc;
    int mode;
    PROXYSPARE *pspareFirst;
    int cinit;
    PROXYINIT *ainit;
};
struct VTE { short delta; short pad; void *method; };
struct LO {
    char pad00[0xC];
    VTE *vtable;
    char pad10[0x48 - 0x10];
    void *pxfUnk58;
    void *pxfUnk5c;
};
extern "C" {
extern char D_00475480[];
extern qword D_00317560;
void *func_00292034(void *, int, unsigned int);
MATRIX4 func_0011D768(MATRIX4 *mat);
int func_001FB5D8(PROXY *pproxy, PROXYSPARE *pspare);
void func_001FC5E0(void *world, PROXY *pproxy, LO *plo);
void func_002BAA50(void *pref, void *pframe);
void func_001C7A00(LO *plo, void *pso, int grf);
int func_0013B500(LO *plo, int cid);
}
inline void CallSplice(PROXY *plo, int ev, void **args)
{
    VTE *entry = (VTE *)&plo->vtable[0] + 3;
    ((void (*)(void *, int, int, int, void **, int))entry->method)((char *)plo + entry->delta, ev, 0, 1, args, 0);
}
inline void SetMatrix4Identity(MATRIX4 *pmat)
{
    func_00292034(pmat, 0, sizeof(MATRIX4));
    pmat->mat[3][3] = 1.0f;
    pmat->mat[2][2] = 1.0f;
    pmat->mat[1][1] = 1.0f;
    pmat->mat[0][0] = 1.0f;
}
extern "C" void func_001FB710(PROXY *pproxy, PROXYSPARE *pspare)
{
    pspare->fLocked = 1;
    MATRIX4 matInverse;
    matInverse = func_0011D768(&pspare->mat);
    SetMatrix4Identity(&pspare->mat);
    int icopy = func_001FB5D8(pproxy, pspare);
    for (int iplo = 0; iplo < pproxy->psrc->cplo; iplo++) {
        LO *plo = pproxy->psrc->aplo[icopy * pproxy->psrc->cplo + iplo];
        func_001FC5E0(D_00475480, pproxy, plo);
        void *apvArgs[1];
        apvArgs[0] = &plo;
        CallSplice(pproxy, 0x12, apvArgs);
        for (int iinit = 0; iinit < pproxy->cinit; iinit++) {
            PROXYINIT *pinit = &pproxy->ainit[iinit];
            if (pinit->kind == 7)
                continue;
            void *pframe = pinit->pframe;
            if (pframe && pproxy->mode != 2) {
                void **pparent = (void **)((char *)pframe + 8);
                func_002BAA50(pinit->plo, *pparent);
                func_002BAA50(pparent, 0);
            }
            pinit->plo = 0;
        }
        VTE *remove = &plo->vtable[9];
        ((void (*)(void *))remove->method)((char *)plo + remove->delta);
        VTE *apply = &plo->vtable[42];
        ((void (*)(void *, MATRIX4 *))apply->method)((char *)plo + apply->delta, &matInverse);
        func_001C7A00(plo, 0, 0);
        if (func_0013B500(plo, 0x2F)) {
            PROXYREST *prest = &pproxy->psrc->aposRest[iplo];
            LO *pso = plo;
            if (pso->pxfUnk58) {
                VTE *move = &pso->vtable[34];
                ((void (*)(void *, qword))move->method)((char *)pso + move->delta, prest->pos);
                VTE *vel = &pso->vtable[40];
                ((void (*)(void *, qword))vel->method)((char *)pso + vel->delta, D_00317560);
            }
            if (pso->pxfUnk5c) {
                VTE *rot = &pso->vtable[35];
                ((void (*)(void *, void *))rot->method)((char *)pso + rot->delta, prest->mat);
                VTE *angvel = &pso->vtable[41];
                ((void (*)(void *, qword))angvel->method)((char *)pso + angvel->delta, D_00317560);
            }
        }
    }
    PROXYSPARE *pcur = pproxy->pspareFirst;
    if (pcur) {
        if (pcur == pspare) {
            pproxy->pspareFirst = pspare->pspareNext;
            pspare->pspareNext = 0;
        } else {
            while (true) {
                PROXYSPARE **ppnext = &pcur->pspareNext;
                pcur = *ppnext;
                if (!pcur)
                    break;
                if (pcur == pspare) {
                    *ppnext = pspare->pspareNext;
                    pspare->pspareNext = 0;
                    break;
                }
            }
        }
    }
    pspare->pproxy = 0;
    pspare->fLocked = 0;
}
