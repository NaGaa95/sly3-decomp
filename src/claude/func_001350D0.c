// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* func_001350D0 / func_001351B0: push the owner's rotation (m80) and positions (vB0, aC0[]) into its two attached effects */
typedef int qword __attribute__((mode(TI)));
typedef union { float m[4][4]; qword r[4]; } M4;
typedef struct { qword r[3]; } M3;
struct X { char pad[0x1760]; void *p1760; char pad2[0x1770 - 0x1764]; void *p1770; void *p1774; };
struct S { char pad[0x10]; struct X *px; char pad2[0x80 - 0x14]; M3 m80; qword vB0; qword aC0[3]; };
extern struct { qword q; } D_00479350;
void func_00238AE0(struct S *p);
int func_00134AB8(struct S *p);
void func_001C8328(void *pv, qword q, qword a, qword b, float g0, float g1);
qword *func_002BA818(qword *out, qword v);
void func_001C8248(void *pv, qword q, M4 *pm, float g0, float g1);
void func_001351B0(struct S *p, qword a, qword b);
static inline void BuildMat(M4 *pmat, M3 *pm, qword pos)
{
    func_002BA818(&pmat->r[3], pos);
    *(M3 *)pmat = *pm;
    pmat->m[1][3] = 0.0f;
    pmat->m[2][3] = 0.0f;
    pmat->m[0][3] = 0.0f;
    pmat->m[3][3] = 1.0f;
}
#define SEND(p, field, pos) { \
    M4 mat; \
    BuildMat(&mat, &(p)->m80, pos); \
    func_001C8248((p)->px->field, D_00479350.q, &mat, 1.0f, 1.0f); \
}
void func_001350D0(struct S *p)
{
    int i;
    func_00238AE0(p);
    if (func_00134AB8(p)) {
        qword *pv = p->aC0;
        for (i = 2; i >= 0; i--)
            func_001351B0(p, p->vB0, *pv++);
        if (p->px->p1770)
            SEND(p, p1770, p->vB0)
    }
}
void func_001351B0(struct S *p, qword a, qword b)
{
    if (p->px->p1760)
        func_001C8328(p->px->p1760, D_00479350.q, a, b, 1.0f, 1.0f);
    if (p->px->p1774)
        SEND(p, p1774, b)
}
