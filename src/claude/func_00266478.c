// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Queue the selected VU microprogram pair in a DMA packet.
typedef unsigned int uint;
typedef unsigned long ulong;
struct R {char pad[0xC];unsigned char *cur;};
struct S {char pad[0x94];int priority;};
struct E {int kind;float priority;uint address;int pad;};
extern struct R D_0036C308;
extern char D_00000000[],D_00000030[],D_00000060[],D_00000090[],D_000000C0[],D_00000100[];
struct E *func_00209B60(void);
static inline void Word(struct R *r,uint word){*(uint *)r->cur=word;r->cur+=4;}
static inline void Mscal(struct R *r,void *entry){Word(r,0x14000000|((uint)entry>>3));}
static inline void Align(struct R *r){while((uint)r->cur&15){*(uint *)r->cur=0;r->cur+=4;}}
void func_00266478(struct S *p,int mode,float priority){
    unsigned char *tag=D_0036C308.cur;
    struct E *e;
    *(ulong *)tag=0x10000000UL;
    D_0036C308.cur+=16;
    switch(mode){
    case 1:
        Word(&D_0036C308,0x13000000);Mscal(&D_0036C308,D_00000000);Mscal(&D_0036C308,D_000000C0);Word(&D_0036C308,0x13000000);break;
    case 2:
        Word(&D_0036C308,0x13000000);Mscal(&D_0036C308,D_00000030);Mscal(&D_0036C308,D_000000C0);Word(&D_0036C308,0x13000000);break;
    case 3:
        Word(&D_0036C308,0x13000000);Mscal(&D_0036C308,D_00000100);Mscal(&D_0036C308,D_00000060);Word(&D_0036C308,0x13000000);break;
    case 4:
        Word(&D_0036C308,0x13000000);Mscal(&D_0036C308,D_00000100);Mscal(&D_0036C308,D_00000090);Word(&D_0036C308,0x13000000);break;
    }
    Align(&D_0036C308);
    *(uint *)tag|=((D_0036C308.cur-tag)>>4)-1;
    *(ulong *)D_0036C308.cur=0x60000000UL;
    D_0036C308.cur+=16;
    e=func_00209B60();
    e->kind=0x90;e->priority=priority+p->priority*65536.0f;e->address=(uint)tag&0x0FFFFFFF;e->pad=0;
}
