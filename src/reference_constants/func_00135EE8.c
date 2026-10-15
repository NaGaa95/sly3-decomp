// Original USA entry 0x135ee8; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_0036B118[];
void func_001519C8(void *,void *);
int func_00119128(void *);
void func_00135FB0(void *,void *,void *);
void func_00135EE8(char *p,void *stream)  {
    int value;
    func_001519C8(p,stream);
    value=func_00119128(stream);
    *(int *)(p+0xA4)=value;
    if(!value)  {
        *(int *)(p+0xA8)=1;
        func_00135FB0(p,stream,D_0036B118);
    }
}
