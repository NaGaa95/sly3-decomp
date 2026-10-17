// SLY3_CFLAGS: -Os -G0
struct Owner { unsigned char prefix[0x2C8]; int counts[7]; };
extern char D_00474FF0[];
extern char D_00475480[];
int func_00246F30(void *context,unsigned int index);
void *func_0017E1B8(void *game,int flags,int key_word,void *owner);
void *func_00239A10(void *owner,void *receiver);
void func_00239C20(void *object);
void func_0024F8C0(struct Owner *owner,unsigned int mask)
{
    int index;
    for(index=0;index<7;index++) {
        unsigned int bit=0;
        if((unsigned int)index<7)
            bit=1<<index;
        if(mask&bit) {
            if(owner->counts[index]) {
                --owner->counts[index];
                if(owner->counts[index]<=0) {
                    int key=func_00246F30(D_00474FF0,index);
                    void *object=func_0017E1B8(D_00475480,4,key,owner);
                    if(object) {
                        void *receiver=func_00239A10(object,owner);
                        if(receiver)
                            func_00239C20(receiver);
                    }
                }
            }
        }
    }
}
