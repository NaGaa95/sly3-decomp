// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00187998, UpdateJoy).
static __inline__ float sqrtf(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }

typedef struct LM { float gMin, gMax; } LM;
struct X110C { char pad[0x138]; unsigned int grfbtn; };

typedef struct JOY {
    float x;              /* 0x00 */
    float y;              /* 0x04 */
    float uDeflect;       /* 0x08 */
    float x2;             /* 0x0C */
    float y2;             /* 0x10 */
    float uDeflect2;      /* 0x14 */
    unsigned int grfbtn;  /* 0x18 */
    char pad1C[0x1044 - 0x1C];
    int nPort;            /* 0x1044 */
    int nSlot;            /* 0x1048 */
    int x104C;            /* 0x104C */
    int pad1050;
    int joyk;             /* 0x1054 */
    int pad1058;
    float tRead;          /* 0x105C */
    float tActive;        /* 0x1060 */
    int x1064;            /* 0x1064 */
    unsigned int grfbtnPrev;     /* 0x1068 */
    unsigned int grfbtnReleased; /* 0x106C */
    char pad1070[0x10B0 - 0x1070];
    unsigned char bX, bY; /* 0x10B0 */
    short pad10B2;
    float gSmooth;        /* 0x10B4 */
    int fStickMoved;      /* 0x10B8 */
    LM alm[4];            /* 0x10BC */
    unsigned char bX2, bY2; /* 0x10DC */
    short pad10DE;
    float gSmooth2;       /* 0x10E0 */
    int fStickMoved2;     /* 0x10E4 */
    LM alm2[4];           /* 0x10E8 */
    char pad1108[4];
    struct X110C *p110C;  /* 0x110C */
    char pad1110[8];
    unsigned char mpbtnpb[12]; /* 0x1118 */
} JOY;

struct CLOCK { char pad[0x40]; float tReal; };
extern struct CLOCK g_clock;
extern char D_0036BB88[];
typedef struct SND { float t; } SND;
extern SND D_0036C700;
extern char D_00475480[];

extern void *memset(void *pv, int b, int cb);
extern int func_002A18C8(int port, int slot, unsigned char *pb);
extern void func_001A8F10(JOY *p);
extern void CopyAb(void *dst, void *src, int cb);
extern void func_001A8930(JOY *p, unsigned char bX, unsigned char bY, float *px, float *py, float *pu, float *pgSmooth,
                          unsigned char *pbX, unsigned char *pbY, int *pf, LM *alm);
extern void func_00163F58(void *p, JOY *pjoy);
extern int func_001F4AD0(void *p, int n);
extern void func_001854C8(float *p, int n, int a);

int func_001A8B88(JOY *p)
{
    unsigned char ab[0x40];
    int fRet = 1;
    unsigned int btn;

    memset(ab, 0, 0x40);
    if (func_002A18C8(p->nPort, p->nSlot, ab) > 0) {
        btn = ((ab[2] << 8) | ab[3]) ^ 0xFFFF;
        p->grfbtnPrev = p->grfbtn;
        p->grfbtnReleased = p->grfbtnReleased & btn;
        p->grfbtn = btn & ~p->grfbtnReleased;
        if (p->p110C)
            p->grfbtn = p->grfbtn | p->p110C->grfbtn;
        func_001A8F10(p);
        if (p->x104C != 0 && p->x104C != ab[1])
            fRet = 0;
        p->x104C = ab[1];
        if (p->joyk == 4)
            CopyAb(p->mpbtnpb, &ab[8], 0xC);
        if (p->joyk >= 2) {
            func_001A8930(p, ab[6], ab[7], &p->x, &p->y, &p->uDeflect, &p->gSmooth, &p->bX, &p->bY, &p->fStickMoved, p->alm);
            func_001A8930(p, ab[4], ab[5], &p->x2, &p->y2, &p->uDeflect2, &p->gSmooth2, &p->bX2, &p->bY2, &p->fStickMoved2, p->alm2);
        } else {
            p->bX2 = p->bY2 = 0;
            p->bX = p->bY = 0;
            p->x2 = p->y2 = 0.0f;
            p->x = p->y = 0.0f;
        }
        if (p->grfbtn & 0xF000) {
            p->x = p->y = p->uDeflect = 0.0f;
            if (p->grfbtn & 0x8000)
                p->x = -1.0f;
            else if (p->grfbtn & 0x2000)
                p->x = 1.0f;
            if (p->grfbtn & 0x1000)
                p->y = 1.0f;
            else if (p->grfbtn & 0x4000)
                p->y = -1.0f;
            if (p->x * p->y != 0.0f) {
                p->x = p->x * sqrtf(0.5f);
                p->y = p->y * sqrtf(0.5f);
            }
            p->uDeflect = 1.0f;
        }
        func_00163F58(D_0036BB88, p);
        p->tRead = g_clock.tReal;
        if (p->grfbtn != 0 || p->uDeflect != 0.0f || p->uDeflect2 != 0.0f) {
            p->tActive = g_clock.tReal;
            p->x1064 = 0;
            if (g_clock.tReal - D_0036C700.t > 15.0f) {
                func_001854C8(&D_0036C700.t, 9, func_001F4AD0(D_00475480, 0));
                D_0036C700.t = g_clock.tReal;
            }
        } else {
            p->x1064 = (int)(g_clock.tReal - p->tActive);
        }
    } else {
        if (g_clock.tReal - p->tRead >= 2.0f)
            fRet = 0;
    }
    return fRet;
}
