// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002666A0: queue a sprite's screen transform (cf. Sly 2 func_00217500; Sly 3 scales by the screen size).
typedef unsigned int uint;
typedef unsigned long ulong;
struct CAMERA {char pad[0x8C];float x,y;};
struct OWNER {char pad[0x94];int priority;char pad98[0x20];struct CAMERA *camera;};
struct S {char pad[8];struct OWNER *owner;char padc[6];unsigned short mode;int count;char pad18[4];int tag;int f20;int f24;};
struct T {float a,b,c,d,x,y;};
struct M4 {float a[16];};
struct D {int a,mode;float priority;uint limit;char pad10[0x1C];float fade;};
struct R {char pad[0xC];unsigned char *cur;};
struct E {int kind;float priority;uint address;int tag;};
extern struct R D_0036C308;
void *memset(void *,int,int);
struct E *func_00209B60(void);
static inline int Min(int a,int b){return a<b?a:b;}
static inline void Word(struct R *r,uint word){*(uint *)r->cur=word;r->cur+=4;}
static inline void Align(struct R *r){while((uint)r->cur&15){*(uint *)r->cur=0;r->cur+=4;}}
static inline void CopyWords(int *d,const int *s,int n){int rem=n&3,cBulk=n-rem,i;for(i=0;i<rem;i++)*d++=*s++;for(i=0;i<cBulk;i+=4){int a=s[0],b=s[1],c=s[2],e=s[3];s+=4;d[0]=a;d[1]=b;d[2]=c;d[3]=e;d+=4;}}
static inline void Unpack(struct R *r,const int *s,int n,uint header){Word(r,header);CopyWords((int *)r->cur,s,n);r->cur+=n*4;}
struct SCREEN {int n0;int w;int h;};
extern struct SCREEN D_0036DBE0;
float func_002BE228(struct SCREEN *ps, float g);
float func_002BE230(struct SCREEN *ps, float g);
void func_002666A0(struct S *p,struct T *t,struct D *data){
    struct M4 m;
    unsigned char *tag;
    struct E *e;
    float sx, sy, off;
    struct OWNER *o, *o2;
    if(p->f24)return;
    memset(&m,0,0x40);
    sx=0.0015625f;sy=0.0020833334f;off=786432.0f;
    m.a[0]=func_002BE228(&D_0036DBE0,t->a*(float)D_0036DBE0.w*sx);
    m.a[1]=func_002BE230(&D_0036DBE0,t->b*(float)D_0036DBE0.h*sy);
    m.a[4]=func_002BE228(&D_0036DBE0,t->c*(float)D_0036DBE0.w*sx);
    m.a[5]=func_002BE230(&D_0036DBE0,t->d*(float)D_0036DBE0.h*sy);
    o=p->owner;
    m.a[8]=func_002BE228(&D_0036DBE0,t->x*(float)D_0036DBE0.w*sx)+o->camera->x+off;
    o2=p->owner;
    m.a[9]=func_002BE230(&D_0036DBE0,t->y*(float)D_0036DBE0.h*sy)+o2->camera->y+off;
    m.a[15]=m.a[10]=1.0f;
    if(p->mode>=2)data->mode=1;else data->mode=0;
    data->limit=0x7FFF;
    tag=D_0036C308.cur;
    *(ulong *)tag=0x10000000UL;D_0036C308.cur+=16;
    Unpack(&D_0036C308,(const int *)&m,16,0x6C04C000);
    Unpack(&D_0036C308,(const int *)data,12,0x6C03C004);
    Align(&D_0036C308);
    *(uint *)tag|=((D_0036C308.cur-tag)>>4)-1;
    *(ulong *)D_0036C308.cur=0x60000000UL;D_0036C308.cur+=16;
    e=func_00209B60();
    e->kind=0x90;e->priority=data->priority+(float)p->owner->priority*65536.0f;
    e->address=(uint)tag&0x0FFFFFFF;
    e->tag=p->tag;
}
