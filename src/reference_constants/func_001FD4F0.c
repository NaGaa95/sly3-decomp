// Original USA entry 0x1fd4f0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    char storage[0x48];
    int key;
};
struct Record *func_001FD540(void *,int);
void *memset(void *,int,unsigned int);
void func_001FD4F0(char *p,int key)  {
    struct Record *r=*(struct Record **)(*(char **)(p+0x20)+0x10);
    if(r->key!=key)  {
        r=func_001FD540(p,1);
        r->key=key;
        memset(r,0,0x20);
    }
}
