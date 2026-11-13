// SLY3_CFLAGS: -Os -G0 -malign-loops=3
struct ANIMATION;
struct T { char pad[0x64]; float f74; };
struct A { struct T *pt; int n4; int n8; };
struct E8 { int n0; int n4; };
struct G { char pad[0x44]; struct E8 *a54; };
struct P { char pad[0x24]; struct G *pg; int n28; int n2C; struct ANIMATION *n30; int n34; int n38; int n3C; struct A *p40; float f44; int n48; };
int func_00239CC0(struct P *);
struct A *func_0023A380(struct G *, int, int, int);
struct A *func_0023A210(struct G *, int, int, int, int);
void func_00136908(struct T *, int, float, float, int, struct ANIMATION **);
void func_0013BD00(struct ANIMATION *, struct P *);
void func_00137B00(struct ANIMATION *);
void func_0023AA48(struct P *, int, int);
// SafeHouse port (ChooseSmaTransition). The do{}while(0) loop note + -malign-loops=3 gives the dead alignment nop after "b test".
void func_0023A428(struct P *p, int k)
{
    struct A *pa;
    int nx;
    register int fl __asm__("$17"); // pin: flag in s1
    if (func_00239CC0(p)) return;
    {
    goto test;
    do {
select:
    if(nx==-2){
        pa=func_0023A380(p->pg,p->n48,p->n34,0);
        if(pa)p->n3C=(pa->n4!=p->n34)?pa->n4:pa->n8;
    }else{
        p->n3C=nx;
        pa=func_0023A210(p->pg,p->n48,p->n34,nx,1);
    }
    } while (0);
    k=0;
apply:
        p->p40 = pa;
        if (!pa) return;
        fl = 0;
        if (pa->pt) {
            float a, b;
            int f;
            if (pa->n4 == p->n34) {
                p->n38 = pa->n8;
                a = 0.0f;
                b = p->f44;
            } else {
                p->n38 = pa->n4;
                b = -p->f44;
                a = pa->pt->f74;
            }
            f = p->n2C;
            if (k == 1) {
                f |= 2;
                f &= -2;
                fl = 1;
                a = pa->pt->f74 - a;
            } else if (pa->pt->f74 == 0.0f) {
                fl = 1;
            }
            func_00136908(pa->pt, p->n28, a, b, f, &p->n30);
        }
        {
            int oldArgument,newArgument;
            struct P *pArgument;
            if(!p->n30){
                int old=p->n34;
                int nw=pa->n4;
                if(nw==old)nw=pa->n8;
                __asm__("" : "=r"(pArgument) : "0"(p));
                p->n34=nw;
                oldArgument=old;
                newArgument=nw;
            }else{
                int nw;
                if(!fl){func_0013BD00(p->n30,p);return;}
                nw=p->n38;
                fl=p->n34;
                p->n34=nw;
                p->n38=-1;
                func_00137B00(p->n30);
                p->n30=0;
                __asm__ __volatile__("");
                oldArgument=fl;
                newArgument=nw;
                __asm__("" : "=r"(pArgument) : "0"(p));
            }
            func_0023AA48(pArgument,oldArgument,newArgument);
        }
    if(func_00239CC0(p))return;
    if(p->n30)return;
test:
    if(p->n34!=p->n3C){
        pa=func_0023A210(p->pg,p->n48,p->n34,p->n3C,1);
        goto apply;
    }
    {struct E8 *e=p->pg->a54; e+=p->n34; nx=e->n4;}
    if(nx!=-1)goto select;
}
}

