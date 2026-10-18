// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ColorBytes { unsigned char r, g, b, a; };
struct Color {
    unsigned char r, g, b, a;
    Color(const Color &c) { *(ColorBytes *)this = *(const ColorBytes *)&c; }
} __attribute__((aligned(16)));
struct Matrix2D { float a[6]; } __attribute__((aligned(16)));
struct FrameSlot { char pad[8]; short savedFrame; short subframe; float time; int active; int sound; };
struct Frame {char pad[8];float duration;char padC[8];};
struct FrameOwner { int x0; Frame *frames; FrameSlot *slots; char padc[0x20]; Matrix2D *matrix; };
static inline Matrix2D Mul(const Matrix2D &q, const Matrix2D &n)
{
    float m0 = q.a[0], m1 = q.a[1], m2 = q.a[2], m3 = q.a[3], m4 = q.a[4], m5 = q.a[5];
    Matrix2D r;
    r.a[0] = m0 * n.a[0] + m1 * n.a[2];
    r.a[1] = m0 * n.a[1] + m1 * n.a[3];
    r.a[2] = m2 * n.a[0] + m3 * n.a[2];
    r.a[3] = m2 * n.a[1] + m3 * n.a[3];
    r.a[4] = m4 * n.a[0] + m5 * n.a[2] + n.a[4];
    r.a[5] = m4 * n.a[1] + m5 * n.a[3] + n.a[5];
    return r;
}
extern "C" void func_00267AE8(float,Frame *,int,Matrix2D *,Color,Color);
extern "C" void func_00269418(float,Frame *,int,Matrix2D *,Color,Color);
extern "C" void func_00267608(FrameOwner *p,int i,Matrix2D *matrix,float dt,Color c0,Color c1) {
    FrameSlot *e=&p->slots[i];
    int h=e->savedFrame;
    if(h<0)return;
    Matrix2D m;
    Matrix2D *pmUse;
    if(p->matrix) {
        m=Mul(*matrix,*p->matrix);
        pmUse=&m;
    } else pmUse=matrix;
    if(e->active) {
        func_00267AE8(dt,&p->frames[h],i,pmUse,c0,c1);
    } else {
        if(p->frames[h].duration <= e->time) {
            e->time=0.0f;
            e->subframe=0;
        } else e->time+=dt;
        func_00269418(dt,&p->frames[h],i,pmUse,c0,c1);
    }
}
