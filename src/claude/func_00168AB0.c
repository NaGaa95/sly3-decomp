// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Camera DMA upload: matrix (or func_00167E40 pair when the debug flag is set), frustum scale/offset block, VIF flush.
typedef int qword __attribute__((mode(TI)));
typedef union { struct { qword r[4]; } q; float af[4][4]; } M4;
struct VEC3 { float x, y, z; };
typedef union { int an[3]; struct VEC3 v; } VEC3I;
static VEC3I s_vScale = { { 0x4BFD70A4, 0x4BFD70A4, 0x4F7D70A4 } }; /* 0x347FA0 */
static VEC3I s_vOffset = { { 0x50008000, 0x50008000, 0x50400000 } }; /* 0x347FB0 */
struct DMAS { void *pbMax; void *ab; void *pqwCnt; int pb; };
struct LO;
struct VTE { short d; short pad; void (*pfn)(struct LO *, void *, struct DMAS *); };
struct LOV { char pad[0x1D0]; struct VTE e; };
struct LO { int a[3]; struct LOV *pvt; };
struct CM { struct LO lo; char pad[0x90 - 0x10]; char x90[0x144 - 0x90]; float gNear; float gFar; char pad1[0x1E0 - 0x14C]; M4 m1E0; };
struct CMD { int an[4]; M4 m; };
struct ST { struct VEC3 vScale; float gScaleW; struct VEC3 vOffset; float gOffsetW; float g60; float g64; int pad[2]; };
struct GS { char pad[0xC]; int grf; char pad1[0x14 - 0x10]; float g14; float g18; };
extern struct GS D_0036DBE0;
extern int D_0036C328;
void func_00166A40(struct CM *p);
void func_001746C0(struct DMAS *p);
void func_001748F8(struct DMAS *p);
void func_0027E228(struct DMAS *p, int a, int b);
void func_0027E4C0(struct DMAS *p, int k, int c, void *pv, int n);
void func_0027E2A8(struct DMAS *p);
struct CMD *func_00167DA8(struct CM *p, int n);
void func_00167E40(struct CM *p, int k, void *pv);
void *func_00292034(void *p, int c, int cb);
void func_00168AB0(struct CM *p, int i, void *pv, struct DMAS *pdmas)
{
    M4 m;
    struct ST st;
    func_00166A40(p);
    p->lo.pvt->e.pfn((struct LO *)((char *)p + p->lo.pvt->e.d), pv, pdmas);
    func_001746C0(pdmas);
    func_0027E228(pdmas, 0, 0);
    if ((D_0036DBE0.grf >> 1) & 1) {
        struct CMD *pcmd = func_00167DA8(p, D_0036C328);
        func_00167E40(p, 1, &m);
        func_00167E40(p, 2, &pcmd->m);
        pcmd->an[i] = pdmas->pb;
    } else {
        m = p->m1E0;
    }
    func_0027E4C0(pdmas, 0xC, 4, &m, 3);
    func_0027E4C0(pdmas, 0xC, 4, p->x90, 7);
    func_00292034(&st, 0, sizeof(st));
    {
        float gNear = p->gNear;
        float gFar = p->gFar;
        float g = (gNear + gFar) / (gNear - gFar);
        float d = gNear * (1.0f - g);
        st.vScale = s_vScale.v;
        st.gScaleW = 1.0f / d;
        st.vOffset = s_vOffset.v;
        st.gOffsetW = -g / d;
        st.g60 = D_0036DBE0.g14;
        st.g64 = D_0036DBE0.g18;
    }
    func_0027E4C0(pdmas, 0xC, 3, &st, 0);
    func_0027E228(pdmas, 0x34, 0x1E6);
    func_0027E2A8(pdmas);
    func_001748F8(pdmas);
}
