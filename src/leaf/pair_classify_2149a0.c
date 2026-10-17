// SLY3_CFLAGS: -Os -G0
struct KindPair {
    unsigned char prefix[0x51C];
    int firstCount;
    int firstKinds[1];
    unsigned char gap524[0xC];
    int secondCount;
    int secondKinds[1];
};
int func_0013B500(void *object,int kind);
int func_001C8768(void *object,int key);
int func_0023E178(struct KindPair *pair,void *object);
int func_002149A0(struct KindPair *pair,void *object)
{
    int i,j;
    if(pair->firstCount||pair->secondCount) {
        for(i=0;i<pair->firstCount;i++) {
            if(func_0013B500(object,pair->firstKinds[i]))
                return 2;
        }
        for(j=0;j<pair->secondCount;j++) {
            if(func_001C8768(object,pair->secondKinds[j]))
                return 2;
        }
        return 1;
    }
    return func_0023E178(pair,object);
}
