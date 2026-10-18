// SLY3_CFLAGS: -Os -G0
struct RequestOwner {
    char prefix[0xD0]; void *primary;
    char gapD4[0x380-0xD4]; int firstCount; void *first[8];
    int secondCount; void *second[8];
};
int func_0013B500(void *object,int kind);
void *func_00291F38(void *destination,const void *source,unsigned int bytes);
void func_00170118(void *owner,void *object,int context);
void func_00170018(struct RequestOwner *owner,void *object,int context)
{
    int i;
    if(!object || object==owner->primary) return;
    func_0013B500(object,8);
    for(i=0;i<owner->secondCount;i++) {
        void **cursor=&owner->second[i];
        if(*cursor==object) {
            func_00291F38(cursor,&owner->second[i+1],(owner->secondCount-i)*4-4);
            owner->secondCount--;
            i--;
        }
    }
    if((unsigned int)owner->firstCount<8)
        owner->first[owner->firstCount++]=object;
    func_00170118(owner,object,context);
}
