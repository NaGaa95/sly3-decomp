// Port of the Sly 2 source src/hand/func_002166B0.c (store asm replaced by plain C + one pin).
typedef int qword __attribute__((mode(TI)));
typedef struct { float a[6]; } __attribute__((aligned(16))) T;
typedef struct { float a[16]; } __attribute__((aligned(16))) O;
struct RT {char pad[8];void *font;char padC[0x14];qword color0,color1;char pad40[0x20];int changed;float cameraX,cameraY,offsetX,offsetY,width,height,sx,sy,lineHeight,fontScale;int vAlign,hAlign,priority;};
struct DATA {unsigned int color;int mode;float priority;unsigned int limit;qword color0,color1;};

void func_00265308(struct RT *p, O *po, T *pt);
void func_00265660(struct RT *p, O *po, struct DATA *q);
void func_002655C0(struct RT *p, T *pt, struct DATA *q)
{
    T t = *pt;
    O o;
    register float x __asm__("$f2")=t.a[0]; /* pin: x in f2 */
    float y=t.a[3],g=p->fontScale,shift=p->lineHeight;
    p->sy=y; p->sx=x;
    t.a[0] = x*g;
    t.a[3] = y*g;
    t.a[5] += shift*y;
    func_00265308(p, &o, &t);
    func_00265660(p, &o, q);
}
