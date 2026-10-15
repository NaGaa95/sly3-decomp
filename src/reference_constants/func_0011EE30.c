// Original USA entry 0x11ee30; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Range  {
    float low,high;
};
int func_0011EE30(const struct Range *p,float value)  {
    return p->low<value && value<p->high;
}
