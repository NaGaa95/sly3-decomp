// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0028B730 (agent A60): DmatXf - Sly 3 form of Sly 2 DmatXf__FP2XFPv (0x22CDC0), rewritten without instruction asm.
// Sly 3: k98 memset list 0,3,11,13-17,20; inner k98 lists shifted (1,2,8-10,12,18,19,21,22 / 5-7); k9A 5 skews qwF0.
// One pin: the first k9A switch's value lives in v0 and is copied (por) into s0 at the join.
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float m[4][4]; } M4;
struct M3 { qword r[3]; };
union FRAME { M4 matrix; M3 basis; };
struct JOB;
struct O;
union SOURCE { O *object; float deadline; };
union MOTIONDATA { qword r[4]; M3 rotation; };
struct O {
    FRAME local; M4 world; float g80, g84; float *pg88, *pg8C; JOB *job; int k94;
    short k98, k9A; unsigned tag; O *parent; int priority; SOURCE source;
    unsigned short force, damping; qword qB0; MOTIONDATA data;
};
extern qword D_00317560;
extern "C" {
void *CopyAb(void *d, const void *s, unsigned int n) __asm__("memcpy");
void *memset(void *p, int c, unsigned int n);
M4 *func_0028B640(M4 *pm, O *pa, const M3 *basis, qword v);
M4 *func_0028B500(M4 *pr, O *pa, const M3 *basis, qword c, qword d);
M4 *func_0028B570(M4 *pm, O *po, qword v);
qword func_0028B388(O *pa, const M4 *matrix);
qword func_0011D3C0(const M3 *rotation);
void func_00118558(float g0, float g1, float g2, qword q0, qword q1, qword q2, qword q3, qword *pa, qword *pb, qword *pc);
}
static inline void Eval(O *po, qword *pa, qword *pb, qword *pc)
{
    func_00118558(po->g84 - po->g80, *po->pg88 - po->g80, *po->pg8C, po->data.r[0], po->data.r[1], po->data.r[2], po->data.r[3], pa, pb, pc);
}
extern "C" M4 *func_0028B730(M4 *pr, O *po)
{
    M4 m, m2;
    switch (po->k98) {
    case 0: case 3: case 11: case 13: case 14: case 15: case 16: case 17: case 20:
        memset(pr, 0, 0x40);
        break;
    default:
        switch (po->k94) {
        case 0: case 2: case 3: case 13: case 15:
            break;
        case 8: case 14:
            func_0028B730(&m, po->source.object);
            CopyAb(pr, &m, 0x40);
            pr->m[3][0] = -pr->m[3][0];
            pr->m[3][1] = -pr->m[3][1];
            pr->m[3][2] = -pr->m[3][2];
            break;
        case 6: case 7:
            switch (po->k98) {
            case 1: case 2: case 8: case 9: case 10: case 12: case 18: case 19: case 21: case 22:
                func_0028B640(&m, po, &po->local.basis, po->qB0);
                CopyAb(pr, &m, 0x40);
                break;
            case 5: case 6: case 7:
                if (po->k9A == 5) {
                    func_0028B640(&m, po, &po->local.basis, po->data.r[3]);
                    CopyAb(pr, &m, 0x40);
                } else {
                    qword q, t;
                    register qword initial __asm__("$2"); // pin: the first value stays in v0 until the por into s0
                    switch (po->k9A) {
                    case 0:
                        initial = func_0028B388(po, &po->local.matrix);
                        break;
                    case 1:
                        Eval(po, &m.r[0], 0, 0);
                        initial = m.r[0];
                        break;
                    case 2: case 3: case 4:
                        initial = po->data.r[0];
                        break;
                    case 5:
                        initial = func_0011D3C0(&po->data.rotation);
                        break;
                    default:
                        initial = D_00317560;
                        break;
                    }
                    q = initial;
                    switch (po->k9A) {
                    case 3: case 4:
                        t = po->data.r[1];
                        break;
                    case 1:
                        Eval(po, 0, &m.r[0], 0);
                        t = m.r[0];
                        break;
                    case 0: case 2: case 5: default:
                        t = D_00317560;
                        break;
                    }
                    func_0028B500(&m, po, &po->local.basis, q, t);
                    CopyAb(pr, &m, 0x40);
                }
                break;
            }
            break;
        case 1: case 4: case 5: case 9: case 10: case 11: case 12: {
            switch (po->k98) {
            case 1: case 2: case 8: case 9: case 10: case 12: case 18: case 19: case 21: case 22:
                m.r[0] = po->qB0;
                break;
            case 5: case 6: case 7: {
                qword *output = &m.r[0];
                qword value;
                switch (po->k9A) {
                case 3: case 4:
                    value = po->data.r[1];
                    break;
                case 1:
                    Eval(po, 0, &m.r[1], 0);
                    value = m.r[1];
                    break;
                case 0: case 2: case 5: default:
                    value = D_00317560;
                    break;
                }
                *output = value;
                break;
            }
            }
            func_0028B570(&m2, po, m.r[0]);
            CopyAb(pr, &m2, 0x40);
            break;
        }
        }
        break;
    }
    return pr;
}
