// SLY3_CFLAGS: -Os -G0
struct RequestOwner {
    char prefix[0xD0]; void *primary;
    char gapD4[0x380-0xD4]; int firstCount; void *first[8];
    int secondCount; void *second[8];
};
int func_0013B500(void *object,int kind);
void *func_00291F38(void *destination,const void *source,unsigned int bytes);
void func_001702A0(void *owner,void *object);
void func_001701B0(struct RequestOwner *owner,void *object)
{
    int i;
    if(!object || object==owner->primary) return;
    func_0013B500(object,8);
    for(i=0;i<owner->firstCount;i++) {
        void **cursor=&owner->first[i];
        if(*cursor==object) {
            func_00291F38(cursor,&owner->first[i+1],(owner->firstCount-i)*4-4);
            owner->firstCount--;
            i--;
        }
    }
    if((unsigned int)owner->secondCount<8)
        owner->second[owner->secondCount++]=object;
    func_001702A0(owner,object);
}
