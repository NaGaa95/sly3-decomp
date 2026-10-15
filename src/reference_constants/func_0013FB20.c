// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
union StateWord {
    float clock;
    void *callback;
};
typedef int qword __attribute__((mode(TI)));
typedef struct {
    qword r[3];
    qword pos;
}
M4;
struct VT {
    short d;
    short pad;
    void *f;
};
struct O {
    char pad[0xA0];
    void *xA0;
};
/* Scoped binary-layout views;
the complete C++ classes are not claimed. */ struct StatePrefix {
    struct G *owner;
    int state;
    float time;
    struct Q *query;
    struct P *focus;
};
struct G {
    char pad[0x1520];
    int main_state;
    char pad2[0x18E0 - 0x1524];
    struct StatePrefix state18E0;
};
struct Q {
    char pad[0xC];
    struct VT *vt;
};
struct P {
    char pad[0xC];
    struct VT *vt;
    char pad1[0x44 - 0x10];
    struct O *p54;
    struct O *p58;
    struct O *p5C;
    char pad2[0x1B8 - 0x50];
    int x1A4;
    char pad3[0xA24 - 0x1BC];
    int x9E4;
    char pad4[0x113C - 0xA28];
    int x1030;
    int x1034;
    char pad5[0x1924 - 0x1144];
    int k1800;
    union StateWord state_words[3];
    void *pv1810;
    void *pv1814;
};
extern struct G *D_0038AE90;
struct CLOCK {
    float t;
    float dt;
};
extern struct CLOCK D_0036BB98;
extern qword D_00317560;
#include "owner_parent_link.h"
void func_001309D8(void *);
void func_0028F068(struct P *, struct O *, int);
float func_002A3EE8(float y, float x);
void func_0024E878(struct P *, float);
void func_0024F0B0(struct P *);
void func_002734E8(void *, int);
M4 func_0028EC08(void *, void *, M4 *);
void *func_00130078(struct P *p, struct O *pso, int a, int b, int c, qword q);
qword func_0011D3C0(M4 *pm);
void func_0023AC58(void *);
void func_00137588(void *, struct P *, int, void *, float, float);
void func_0013FB20(struct P *p, int k) {
    void *pv;
    if (k == p->k1800) return;
    switch (p->k1800) {
        case 0: {
            int save = p->x9E4;
            func_001C7A00(p, 0, 0xF);
            p->x9E4 = save;
            func_001309D8(&p->pv1810);
            func_001309D8(&p->pv1814);
            func_0028F068(p, p->p58, 2);
            func_0028F068(p, p->p5C, 2);
            break;
        }
        case 1: {
            float *matrix = (float *)((M4 *(*)(void *))p->vt[36].f)((char *)p + p->vt[36].d);
            func_0024E878(p, func_002A3EE8(matrix[1], matrix[0]));
            p->x1A4 = 0;
            func_0024F0B0(p);
            break;
        }
    }
    p->k1800 = k;
    p->state_words[0].clock = D_0036BB98.t;
    {
        int byte_offset = k * 4;
        pv = ((union StateWord *)((char *)p + byte_offset + 0x192C))->callback;
    }
    switch (k) {
        case -1: {
            struct G *pg = D_0038AE90;
            if (pg->main_state != 0x10) return;
            if (pg->state18E0.state == 7) return;
            if (pg->state18E0.focus != p) return;
            func_002734E8(&pg->state18E0, 0);
            return;
        }
        case 0: {
            M4 m;
            struct O *parent_object;
            struct Q *pq = D_0038AE90->state18E0.query;
            parent_object = ((void *(*)(void *, M4 *))pq->vt[37].f)((char *)pq + pq->vt[37].d, &m);
            {
                M4 t = func_0028EC08(p->p54->xA0, p->p58->xA0, &m);
                m = t;
            }
            {
                int save = p->x9E4;
                ((OwnerParentCallback)p->vt[10].f)((char *)p + p->vt[10].d, D_0038AE90, parent_object, 3);
                p->x9E4 = save;
            }
            ((void (*)(void *, qword))p->vt[40].f)((char *)p + p->vt[40].d, D_00317560);
            ((void (*)(void *, qword))p->vt[41].f)((char *)p + p->vt[41].d, D_00317560);
            p->pv1810 = func_00130078(p, p->p58, 1, 8, 2, m.pos);
            p->pv1814 = func_00130078(p, p->p5C, 1, 8, 2, func_0011D3C0(&m));
            break;
        }
        case 1: p->x1A4 = 2;
        break;
    }
    func_0023AC58(&p->x1034);
    func_00137588(pv, p, 9, &p->x1030, 0.0f, 1.0f);
    ((void (*)(void *))p->vt[101].f)((char *)p + p->vt[101].d);
}
