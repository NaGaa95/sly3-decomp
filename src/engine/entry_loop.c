// SLY3_CFLAGS: -Os -G0
struct LoopA { int words[5]; };
struct LoopB { int key; int words[9]; };
struct LoopOwner { unsigned char prefix[0x38]; int count; struct LoopA *a; struct LoopB *b; };
void func_0018FD10(void *owner,struct LoopA *a,struct LoopB *b,int p3,int p4,int p5,void *p6);
void func_0018FE80(struct LoopOwner *owner,int key,int arg,char *base)
{
    int i;
    for(i=0;i<owner->count;i++) {
        struct LoopB *b=&owner->b[i];
        struct LoopA *a=&owner->a[i];
        if(b->key==key) func_0018FD10(owner,a,b,0,0,arg,base+0x50);
    }
}
