// Original controller lookup and fallback return the actual node pointer.
// Preserve that pointer through the consumer field60 store.
// Original USA entry 0x1f4a80; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Player  {
    char storage[0x11C0];
};
extern struct Player D_0036E740[];
extern char D_00475480[];
void *func_001A91D8(void *controller);
void *func_00165B28(void *context);
void *func_001F4A80(void *receiver)  {
    int i=*(int *)((char *)receiver+0x130);
    void *result;
    if(i==-1)i=0;
    result=func_001A91D8(&D_0036E740[i]);
    if(!result)result=func_00165B28(D_00475480);
    return result;
}
