// Advance both segment tracks by the frame time and speed, wrap to the next segment when needed, evaluate the current polynomial, mark the resource dirty, and refresh the paired scalar result.
// Reference algorithm: src/hand/func_001DF3D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float t; float dt; } D_0036BB98;
typedef struct { float a; float b; float c; float max; float u; } SEG;
typedef struct {
    int pad0;
    int kind;
    char pad8[0x14 - 0x8];
    float x14; char unknown18[0x10];
    int c;
    SEG aseg[6];
    int i;
    char pad98[0xA0 - 0x98];
} TRK;
typedef struct { TRK atrk[2]; float x140; float x144; void *x148; char pad14c[4]; } ENT;
typedef struct { char pad[0x70]; unsigned long fl; } W;
typedef struct OBJ {
    char pad[0xDC];
    W *pw;
    char padF0[0x178 - 0xE0];
    int c;
    ENT *ae;
    char pad1a0[0x1C0 - 0x1A0];
    float speed;
} OBJ;
typedef struct { int a[8]; } VPAIR;
extern char D_00479950[];
float func_002A4188(float, float);
void func_0011AF60(void *, W *);
void func_00224338(OBJ *, ENT *, VPAIR *, float *);
void func_00224730(OBJ *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        ENT *e = &p->ae[i];
        int f = 0;
        unsigned int j;
        for (j = 0; j < 2; j++) {
            TRK *q = &e->atrk[j];
            SEG *ps;
            float u;
            if (q->kind != 1)
                continue;
            ps = &q->aseg[q->i];
            ps->u = u = ps->u + p->speed * D_0036BB98.dt;
            if (ps->max < u) {
                float r = func_002A4188(u, ps->max);
                q->i = (q->i + 1) % q->c;
                ps = &q->aseg[q->i];
                ps->u = r;
            }
            q->x14 = ps->a + ps->b * ps->u + ps->c * ps->u * ps->u * 0.5f;
            if (!(p->pw->fl & 2)) {
                p->pw->fl |= 2;
                func_0011AF60(D_00479950, p->pw);
            }
            f = 1;
        }
        if (f && e->x148 == 0) {
            VPAIR v;
            float g;
            func_00224338(p, e, &v, &g);
            e->x140 = e->x144 = g;
        }
    }
}
