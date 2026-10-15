// Normalize the signed angle into0..359 and mark its actual property only when it changes.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0
struct S {
    char prefix[0x14];
    int angle;
};
void func_00245320(void *receiver,int mask,int value);
void func_00244E78(struct S *p,int angle) {
    angle%=360;
    if(angle<0)angle+=360;
    if(angle!=p->angle) {
        p->angle=angle;
        func_00245320(p,0x20,0x20);
    }
}
