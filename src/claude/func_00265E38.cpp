// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// func_00265E38: draw a text item - Sly 3 form of Sly 2 func_00216BC8 (sprite text / dialog subtitle /
// scrolling ticker). Text comes from the 178-entry generator table D_0047A4B8 (kind 1) or the string table (kind 0);
// id 0x34C is the dialog subtitle (D_004BC220), id 0x34E the ticker (D_0046F770 state 2), repeated across the width.
typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));
typedef struct {unsigned char r,g,b,a;} RGBA;
typedef struct {float a[8];} __attribute__((aligned(16))) T;
typedef union {qword q[3];struct {RGBA color;int mode;float priority;uint limit;char pad10[0x1C];float fade;};} DATA;
typedef struct {int pad[2];void *owner;int kind,id;int color;float scale,width,height;} S;
typedef struct {char pad[0x94];int lines;char pad98[0x1B0-0x98];} __attribute__((aligned(16))) RT;
typedef struct {char pad[0x4334];void *font;} WORLD;
typedef struct {int id;void (*get)(unsigned short *,int,void *);int context;} STRINGGEN;
typedef struct {char pad10[0x10];int state;float time;int pad18;float finish;} SCROLL;
typedef struct {int id;RGBA color;} DIALOGSUB;
typedef struct {float t,dt;} CLOCK;
extern "C" {
extern WORLD D_00475480;
extern STRINGGEN D_0047A4B8[];
extern DIALOGSUB D_004BC220;
extern SCROLL D_0046F770;
extern CLOCK g_clock;
const unsigned short *func_00150630(WORLD *,int);
unsigned short *func_00271730(unsigned short *,const unsigned short *);
RT *func_002649E0(RT *,unsigned short *,S *,DATA,int);
void func_0027EDA8(DIALOGSUB *,RT *);
void func_00264DE0(RT *,int);
void func_00264B70(RT *,RGBA *);
float func_00264EB0(RT *);
void func_0021E980(SCROLL *,int);
void func_002655C0(RT *,T *,DATA *);
void func_00265E38(S *p,T *t,DATA *data){
    unsigned short text[0x400];
    RT rt;
    DATA style;
    if(!D_00475480.font)return;
    text[0]=0;
    if(p->kind==1){
        uint i;
        for(i=0;i<178;i++)if(D_0047A4B8[i].id==p->id)break;
        if(i<178)D_0047A4B8[i].get(text,D_0047A4B8[i].context,p->owner);
    }else if(p->kind==0){
        func_00271730(text,func_00150630(&D_00475480,p->id));
    }
    if(p->kind==1 && p->id==0x34C){
        int visible;
        style=*data;
        func_002649E0(&rt,text,p,style,1);
        func_0027EDA8(&D_004BC220,&rt);
        visible=(int)(p->height/p->scale);
        if(visible<rt.lines)func_00264DE0(&rt,rt.lines-visible);
        style.color=D_004BC220.color;
        func_00264B70(&rt,&style.color);
        func_002655C0(&rt,t,data);
    }else if(p->kind==1 && p->id==0x34E && D_0046F770.state==2){
        float scale,paddingWidth,textWidth,total,elapsed,x,x0;
        int n,k;
        style=*data;
        func_002649E0(&rt,text,p,style,0);
        scale=t->a[0];
        { float s5=scale*5.0f; paddingWidth=p->scale*s5; }
        textWidth=func_00264EB0(&rt)*scale;
        total=textWidth+paddingWidth;
        elapsed=g_clock.t-D_0046F770.time;
        if(elapsed<0.25f){
            data->fade*=elapsed/0.25f;
            elapsed=0.0f;
        }else elapsed-=0.25f;
        n=0;
        k=0;
        x=paddingWidth-elapsed*100.0f;
        x0=t->a[4];
        if(x<0.0f){
            n=(int)(-x/total);
            x+=n*total;
        }
        while(x<p->width*scale){
            if(n>0 && ++k>=2 && D_0046F770.finish>=0.0f && elapsed>=D_0046F770.finish){
                func_0021E980(&D_0046F770,3);
                break;
            }
            if(x+textWidth>0.0f){
                t->a[4]=x0+x;
                func_002655C0(&rt,t,data);
            }
            x+=total;
        }
    }else{
        style=*data;
        func_002649E0(&rt,text,p,style,1);
        func_002655C0(&rt,t,data);
    }
}
}
