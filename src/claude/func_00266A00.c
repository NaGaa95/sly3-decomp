// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Build a screen-space matrix/parameter DMA packet for a type-6 or type-7 sprite source (cf. func_00266240).
typedef unsigned long u_long;
struct R { char pad[0xC]; unsigned char *cur; };
struct GS { int pad0; int w; int h; };
struct SUB { char pad[0x8C]; float x; float y; };
struct OBJ { char pad[0x94]; int depth; char pad98[0xB8 - 0x98]; struct SUB *sub; };
struct SRC { int pad0; int kind; struct OBJ *obj; int id; int pad10; int x14; };
struct D { int a; int mode; float z; int xC; char pad[0x20]; };
struct GIFS { int pad0; unsigned char *base; int pad8; unsigned char *cur; int a[8]; };
struct CTX { int a[4]; };
struct TEX { char pad[0x10]; u_long *tex0; };
struct CMD { int op; float z; unsigned int addr; int x; };
extern struct R D_0036C308;
extern struct GS D_0036DBE0;
void *memset(void *, int, unsigned int);
float func_002BE228(struct GS *, float);
float func_002BE230(struct GS *, float);
int func_001E8A38(int);
struct TEX *func_00265C58(struct SRC *, int);
void func_001E8908(int, struct R *);
void __3CTX(struct CTX *);
void _$_3CTX(struct CTX *, int);
void func_0018C750(struct GIFS *);
void func_001744E8(struct GIFS *, int);
void func_0018CA08(struct GIFS *, int, int, u_long);
void func_0018CCC0(struct GIFS *, long, u_long);
void AddPrimEnd__4GIFS(struct GIFS *);
void func_001746A8(struct GIFS *);
void CopyAqw__FPvT0i(void *, void *, int);
struct CMD *func_00209B60(void);
static inline void CopyWords(int *d,const int *s,int n){
    int rem=n&3,cBulk=n-rem,i;
    for(i=0;i<rem;i++)*d++=*s++;
    for(i=0;i<cBulk;i+=4){int a=s[0],b=s[1],c=s[2],e=s[3];s+=4;d[0]=a;d[1]=b;d[2]=c;d[3]=e;d+=4;}
}
static inline void Word(struct R *r,unsigned int word) {
    *(unsigned int *)r->cur=word;
    r->cur+=4;
}
static inline void Align(struct R *r) {
    while((int)r->cur&15) { *(int *)r->cur=0; r->cur+=4; }
}
static inline void Align12(struct R *r) {
    while(((int)r->cur&15)!=12) { *(int *)r->cur=0; r->cur+=4; }
}
static inline void Unpack(struct R *r,const int *s,int n,unsigned int header){Word(r,header);CopyWords((int *)r->cur,s,n);r->cur+=n*4;}
static inline float OffsetX(struct OBJ *obj, float x)
{
    return func_002BE228(&D_0036DBE0, x * (float)D_0036DBE0.w * 0.0015625f) + obj->sub->x + 786432.0f;
}
static inline float OffsetY(struct OBJ *obj, float y)
{
    return func_002BE230(&D_0036DBE0, y * (float)D_0036DBE0.h * 0.0020833334f) + obj->sub->y + 786432.0f;
}
void func_00266A00(struct SRC *p, const float *v, struct D *data)
{
    int id = 0;
    struct TEX *tex = 0;
    float m[16];
    unsigned char *tag;
    struct CMD *cmd;
    struct R *r0;
    switch (p->kind) {
    case 6:
        id = func_001E8A38(p->id);
        if (!id)
            return;
        break;
    case 7:
        tex = func_00265C58(p, p->id);
        if (!tex)
            return;
        break;
    default:
        return;
    }
    r0 = &D_0036C308; /* unused; its %hi is CSE'd into the later packet-cursor accesses */
    memset(m, 0, sizeof(m));
    m[0] = func_002BE228(&D_0036DBE0, v[0] * (float)D_0036DBE0.w * 0.0015625f);
    m[1] = func_002BE230(&D_0036DBE0, v[1] * (float)D_0036DBE0.h * 0.0020833334f);
    m[4] = func_002BE228(&D_0036DBE0, v[2] * (float)D_0036DBE0.w * 0.0015625f);
    m[5] = func_002BE230(&D_0036DBE0, v[3] * (float)D_0036DBE0.h * 0.0020833334f);
    m[8] = OffsetX(p->obj, v[4]);
    m[9] = OffsetY(p->obj, v[5]);
    m[10] = 1.0f;
    m[15] = 1.0f;
    data->xC = 0x7FFF;
    data->mode = 0;
    tag = D_0036C308.cur;
    *(u_long *)tag = 0x10000000UL;
    D_0036C308.cur += 16;
    Unpack(&D_0036C308, (const int *)m, 16, 0x6C04C000);
    Unpack(&D_0036C308, (const int *)data, 12, 0x6C03C004);
    switch (p->kind) {
    case 6:
        func_001E8908(id, &D_0036C308);
        break;
    case 7: {
        struct R *r = &D_0036C308;
        struct CTX ctx;
        struct GIFS gifs;
        unsigned char *base;
        unsigned int cqw;
        __3CTX(&ctx);
        func_0018C750(&gifs);
        func_001744E8(&gifs, 0x10);
        func_0018CA08(&gifs, 0, 1, 0xE);
        func_0018CCC0(&gifs, 6, *tex->tex0);
        func_0018CCC0(&gifs, 0x14, 0x60);
        func_0018CCC0(&gifs, 8, 5);
        func_0018CCC0(&gifs, 0x3F, 0);
        AddPrimEnd__4GIFS(&gifs);
        func_001746A8(&gifs);
        base = gifs.base;
        cqw = (unsigned int)(gifs.cur - base) >> 4;
        Align12(r);
        Word(r, cqw | 0x50000000);
        CopyAqw__FPvT0i(r->cur, base, cqw);
        r->cur += cqw * 16;
        _$_3CTX(&ctx, 2);
        break;
    }
    }
    Align(&D_0036C308);
    *(int *)tag |= ((D_0036C308.cur - tag) >> 4) - 1;
    *(u_long *)D_0036C308.cur = 0x60000000UL;
    D_0036C308.cur += 16;
    cmd = func_00209B60();
    cmd->op = 0x90;
    cmd->z = data->z + (float)p->obj->depth * 65536.0f;
    cmd->addr = (unsigned int)tag & 0x0FFFFFFF;
    if (p->kind == 6)
        cmd->x = p->x14;
    else if (p->kind == 7)
        cmd->x = p->x14;
}
