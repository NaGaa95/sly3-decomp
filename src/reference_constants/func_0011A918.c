// Original USA entry 0x11a918; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Entry  {
    void *value;
};
void *func_00119790(void *,void *,void *,int);
void *func_0011A918(struct Entry **p,void *source,void *destination)  {
    return func_00119790(destination,source,(*p)->value,7);
}
