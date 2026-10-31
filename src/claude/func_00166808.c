// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00166808: recalc the camera frustrum/projection from the fov and viewport (cf. Sly 2 RecalcCmFrustrum).
struct RECT { int left, top, right, bottom; };
struct CM {
    char pad0[0x110]; float x110; float x114; float x118; char pad11C[0x134 - 0x11C];
    float x134; float x138; float x13C; float x140; float x144; float x148; char pad14C[0x160 - 0x14C];
    struct RECT rc; char pad170[0x1A0 - 0x170]; char m1A0[1];
};
struct SCR { int x0; int x4; int x8; int xC; int x10; };
extern struct SCR D_0036DBE0;
float tanf(float);
int func_002BC640(struct SCR *p, int n);
int func_002BC648(struct SCR *p, int n);
void func_0011D8A8(void *p, float a, float b, float c, float d, float e, float f);
static __inline__ float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }
static __inline__ float GMin(float a, float b) { return b < a ? b : a; }
void func_00166808(struct CM *pcm)
{
    struct RECT *prc = &pcm->rc;
    struct SCR *pscr = &D_0036DBE0;
    float fov = pcm->x118;
    float t, c;
    int cx, cy;
    pcm->x134 = (640.0f / (float)pscr->x4) * ((float)(prc->right - prc->left) / (float)(prc->bottom - prc->top));
    t = tanf(fov * 0.5f);
    c = pcm->x134;
    pcm->x13C = t;
    pcm->x138 = t * c;
    pcm->x114 = GMin(1.0f, fov / pcm->x110);
    pcm->x140 = t * SqrtF(c * c + 1.0f) * pcm->x144 + 1.0f;
    cx = (pcm->rc.left + pcm->rc.right) / 2;
    cy = (pcm->rc.top + pcm->rc.bottom) / 2;
    {
        float k = 1.0f / 2048.0f;
        float a = (float)(prc->right - prc->left) / (pcm->x138 * 4096.0f);
        float b = (float)((prc->bottom - prc->top) / pscr->x10) / (t * 4096.0f);
        float x, y;
        x = (float)(cx - func_002BC640(pscr, pscr->x4) / 2) * k;
        cy /= pscr->x10;
        y = (float)(cy - func_002BC648(pscr, pscr->x8) / 2) * k;
        func_0011D8A8(pcm->m1A0, a, b, x, y, pcm->x144, pcm->x148);
        __asm__("" :: "r"(pcm)); /* empty: keeps pcm live so the f17 load is not its last use (sched1 reg weight) */
    }
}
