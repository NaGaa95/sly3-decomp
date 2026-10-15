// Submit the original signed integer ratio through the explicit two-float property API.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0
struct S {
    char prefix[0x2C8];
    void *target;
    int numerator;
};
int func_001F43F0(void *receiver);
void func_00261528(void *receiver,int identifier,float numerator,float denominator);
void func_002875C0(struct S *p) {
    if(p->target) {
        float numerator=(float)p->numerator;
        float denominator=(float)func_001F43F0(p);
        func_00261528(p->target,0x3CA,numerator,denominator);
    }
}
